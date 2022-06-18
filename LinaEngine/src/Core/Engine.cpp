/*
This file is a part of: Lina Engine
https://github.com/inanevin/LinaEngine

Author: Inan Evin
http://www.inanevin.com

Copyright (c) [2018-] [Inan Evin]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Core/Engine.hpp"

#include "Audio/Audio.hpp"
#include "Core/Timer.hpp"
#include "EventSystem/ApplicationEvents.hpp"
#include "EventSystem/MainLoopEvents.hpp"
#include "EventSystem/PhysicsEvents.hpp"
#include "Log/Log.hpp"
#include "Profiling/Profiler.hpp"
#include "Utility/UtilityFunctions.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/Material.hpp"
#include "Rendering/ShaderInclude.hpp"
#include "Physics/PhysicsMaterial.hpp"
#include "Audio/Audio.hpp"
#include "Rendering/Shader.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "Core/ReflectionRegistry.hpp"

namespace Lina
{
    Engine* Engine::s_engine = nullptr;

    double Engine::GetElapsedTime()
    {
        return Utility::GetCPUTime() - m_startTime;
    }

    void Engine::SetPlayMode(bool enabled)
    {
        m_isInPlayMode = enabled;
        m_eventSystem.Trigger<Event::EPlayModeChanged>(Event::EPlayModeChanged{enabled});

        if (!m_isInPlayMode && m_paused)
            SetIsPaused(false);
    }

    void Engine::SetIsPaused(bool paused)
    {
        if (paused && !m_isInPlayMode)
            return;
        m_paused = paused;
        m_eventSystem.Trigger<Event::EPauseModeChanged>(Event::EPauseModeChanged{m_paused});
    }

    void Engine::SkipNextFrame()
    {
        if (!m_isInPlayMode)
            return;

        m_shouldSkipFrame = true;
    }

    void Engine::Initialize(ApplicationInfo& appInfo)
    {
        Event::EventSystem::s_eventSystem             = &m_eventSystem;
        Graphics::Window::s_Window                    = &m_window;
        Graphics::RenderEngine::s_renderEngine        = &m_renderEngine;
        Physics::PhysicsEngine::s_physicsEngine       = &m_physicsEngine;
        Input::InputEngine::s_inputEngine             = &m_inputEngine;
        Resources::ResourceManager::s_resourceManager = &m_resourceManager;
        Audio::AudioEngine::s_audioEngine             = &m_audioEngine;
        Resources::ResourceStorage::s_instance        = &m_resourceStorage;
        m_appInfo                                     = appInfo;

        m_eventSystem.Initialize();
        m_resourceStorage.Initialize();
        m_inputEngine.Initialize();
        m_resourceManager.Initialize(m_appInfo);
        m_audioEngine.Initialize();
        m_messageBus.Initialize(m_appInfo.m_appMode);
        m_physicsEngine.Initialize(m_appInfo.m_appMode);

        // m_renderEngine.SetScreenDisplay(Vector2::Zero, m_window.GetSize());
        // m_renderEngine.ConnectEvents();
        // m_renderEngine.Initialize(m_appInfo.m_appMode, &m_engineSettings.m_renderSettings, m_window.GetProperties());

        m_audioEngine.Shutdown();
        m_physicsEngine.Shutdown();
        m_inputEngine.Shutdown();
        m_resourceManager.Shutdown();
        m_resourceStorage.Shutdown();
        m_eventSystem.Shutdown();
        return;

        bool engineSettingsExists = Utility::FileExists("engine.linasettings");

        if (engineSettingsExists)
            m_engineSettings = Resources::LoadArchiveFromFile<EngineSettings>("engine.linasettings");
        else
            Resources::SaveArchiveToFile<EngineSettings>("engine.linasettings", m_engineSettings);

        RegisterResourceTypes();

        // Build main window.
        bool windowCreationSuccess = m_window.CreateContext(m_appInfo);
        if (!windowCreationSuccess)
        {
            LINA_ERR("Window Creation Failed!");
            return;
        }

        // Set event callback for main window.

        ReflectionRegistry::RegisterReflectedComponents();
    }

    void Engine::StartLoadingResources()
    {
        if (m_appInfo.m_appMode == ApplicationMode::Editor)
            m_resourceManager.LoadEditorResources();
        else
            m_resourceManager.ImportResourceBundle("", m_appInfo.m_bundleName);
    }

    void Engine::Run()
    {

        if (m_resourceStorage.Exists<World::Level>(m_engineSettings.m_startupLevel.m_sid))
        {
            // Load the startup level.
        }
        // else
        //     m_defaultLevel.Install();

        m_deltaTimeArray.fill(-1.0);

        if (m_appInfo.m_appMode == ApplicationMode::Editor)
        {
            // m_audioEngine.PlayOneShot(m_resourceStorage.GetResource<Audio::Audio>(StringID("Resources/Editor/Audio/LinaStartup.wav").value()));
        }
        else
            SetPlayMode(true);

        m_running            = true;
        m_startTime          = Utility::GetCPUTime();
        m_physicsAccumulator = 0.0f;

        PROFILER_MAIN_THREAD;
        PROFILER_ENABLE;

        int    frames       = 0;
        int    updates      = 0;
        double totalFPSTime = 0.0f;
        double previousFrameTime;
        double currentFrameTime = 0.0f;

        // Starting game.
        m_eventSystem.Trigger<Event::EStartGame>(Event::EStartGame{});

        while (m_running)
        {
            previousFrameTime = currentFrameTime;
            currentFrameTime  = GetElapsedTime();
            m_rawDeltaTime    = (currentFrameTime - previousFrameTime);
            m_smoothDeltaTime = SmoothDeltaTime(m_rawDeltaTime);

            PROFILER_BLOCK("Input Tick");
            m_inputEngine.Tick();
            PROFILER_END_BLOCK;

            updates++;
            UpdateGame((float)m_rawDeltaTime);
            DisplayGame(1.0f);
            frames++;

            double now = GetElapsedTime();
            // Calculate FPS, UPS.
            if (now - totalFPSTime >= 1.0)
            {
                m_frameTime  = m_rawDeltaTime * 1000;
                m_currentFPS = frames;
                m_currentUPS = updates;
                totalFPSTime += 1.0;
                frames  = 0;
                updates = 0;
            }

            if (m_firstRun)
                m_firstRun = false;
        }

        // Ending game.
        m_eventSystem.Trigger<Event::EEndGame>(Event::EEndGame{});

        // Shutting down.
        m_physicsEngine.Shutdown();
        m_renderEngine.Shutdown();
        m_audioEngine.Shutdown();
        m_inputEngine.Shutdown();
        m_resourceManager.Shutdown();
        m_resourceStorage.Shutdown();
        m_eventSystem.Trigger<Event::EShutdown>(Event::EShutdown{});
        m_eventSystem.Shutdown();

        PROFILER_DUMP("profile.prof");
        Timer::UnloadTimers();
    }

    void Engine::UpdateGame(float deltaTime)
    {
        PROFILER_FUNC("Update Game");

        // Pause & skip frame controls.
        if (m_paused && !m_shouldSkipFrame)
            return;
        m_shouldSkipFrame = false;

        PROFILER_BLOCK("Event: Pre Tick");
        m_eventSystem.Trigger<Event::EPreTick>(Event::EPreTick{(float)m_rawDeltaTime, m_isInPlayMode});
        PROFILER_END_BLOCK;

        // Physics events & physics tick.
        m_physicsAccumulator += deltaTime;
        float physicsStep = m_physicsEngine.GetStepTime();

        if (m_physicsAccumulator >= physicsStep)
        {
            m_physicsAccumulator -= physicsStep;
            PROFILER_BLOCK("Pre Tick");
            m_eventSystem.Trigger<Event::EPrePhysicsTick>(Event::EPrePhysicsTick{});
            PROFILER_END_BLOCK;

            PROFILER_BLOCK("Physics Engine Tick");
            m_physicsEngine.Tick(physicsStep);
            PROFILER_END_BLOCK;

            PROFILER_BLOCK("Event: Physics Tick");
            m_eventSystem.Trigger<Event::EPhysicsTick>(Event::EPhysicsTick{physicsStep, m_isInPlayMode});
            PROFILER_END_BLOCK;

            PROFILER_BLOCK("Event: Post Physics Tick");
            m_eventSystem.Trigger<Event::EPostPhysicsTick>(Event::EPostPhysicsTick{physicsStep, m_isInPlayMode});
            PROFILER_END_BLOCK;
        }

        // Other main systems (engine or game)
        PROFILER_BLOCK("ECS Pipeline Tick");
        m_mainECSPipeline.UpdateSystems(deltaTime);
        PROFILER_END_BLOCK;

        // Animation, particle systems.
        PROFILER_BLOCK("Render Engine Tick");
        m_renderEngine.Tick(deltaTime);
        m_renderEngine.SetAppData(deltaTime, (float)GetElapsedTime(), m_inputEngine.GetMousePosition());
        PROFILER_END_BLOCK;

        PROFILER_BLOCK("Event: Tick");
        m_eventSystem.Trigger<Event::ETick>(Event::ETick{(float)m_rawDeltaTime, m_isInPlayMode});
        PROFILER_END_BLOCK;

        PROFILER_BLOCK("Event: Post Tick");
        m_eventSystem.Trigger<Event::EPostTick>(Event::EPostTick{(float)m_rawDeltaTime, m_isInPlayMode});
        PROFILER_END_BLOCK;
    }

    void Engine::DisplayGame(float interpolation)
    {
        PROFILER_FUNC("Display Game");

        if (m_canRender)
        {
            PROFILER_BLOCK("Event: Render");
            m_renderEngine.Render(interpolation);
            PROFILER_END_BLOCK;

            PROFILER_BLOCK("Window Tick");
            m_window.Tick();
            PROFILER_END_BLOCK;
        }
    }

    void Engine::RemoveOutliers(bool biggest)
    {
        double outlier      = biggest ? 0 : 10;
        int    outlierIndex = -1;
        int    indexCounter = 0;
        for (double d : m_deltaTimeArray)
        {
            if (d < 0)
            {
                indexCounter++;
                continue;
            }

            if (biggest)
            {
                if (d > outlier)
                {
                    outlierIndex = indexCounter;
                    outlier      = d;
                }
            }
            else
            {
                if (d < outlier)
                {
                    outlierIndex = indexCounter;
                    outlier      = d;
                }
            }

            indexCounter++;
        }

        if (outlierIndex != -1)
            m_deltaTimeArray[outlierIndex] = m_deltaTimeArray[outlierIndex] * -1.0;
    }

    void Engine::RegisterResourceTypes()
    {
        m_resourceStorage.m_resources.clear();

        m_resourceStorage.RegisterResource<Audio::AudioAssetData>(
            Resources::ResourceTypeData{
                0,
                std::bind(Resources::CreateResource<Audio::AudioAssetData>),
                std::bind(Resources::DeleteResource<Audio::AudioAssetData>, std::placeholders::_1),
                Vector<std::string>{"linaaudiodata"}, Color::White, true});

        m_resourceStorage.RegisterResource<Graphics::ShaderInclude>(
            Resources::ResourceTypeData{
                0,
                std::bind(Resources::CreateResource<Graphics::ShaderInclude>),
                std::bind(Resources::DeleteResource<Graphics::ShaderInclude>, std::placeholders::_1),
                Vector<std::string>{"linaglh"}});

        m_resourceStorage.RegisterResource<Graphics::ImageAssetData>(
            Resources::ResourceTypeData{
                0,
                std::bind(Resources::CreateResource<Graphics::ImageAssetData>),
                std::bind(Resources::DeleteResource<Graphics::ImageAssetData>, std::placeholders::_1),
                Vector<std::string>{"linaimagedata"}, Color::White, true});

        m_resourceStorage.RegisterResource<Graphics::ModelAssetData>(
            Resources::ResourceTypeData{
                0,
                std::bind(Resources::CreateResource<Graphics::ModelAssetData>),
                std::bind(Resources::DeleteResource<Graphics::ModelAssetData>, std::placeholders::_1),
                Vector<std::string>{"linamodeldata"}, Color::White, true});

        m_resourceStorage.RegisterResource<Graphics::Shader>(
            Resources::ResourceTypeData{
                1,
                std::bind(Resources::CreateResource<Graphics::Shader>),
                std::bind(Resources::DeleteResource<Graphics::Shader>, std::placeholders::_1),
                Vector<std::string>{"linaglsl"}, Color(255, 71, 108, 255, true)});

        m_resourceStorage.RegisterResource<Graphics::Texture>(
            Resources::ResourceTypeData{
                2,
                std::bind(Resources::CreateResource<Graphics::Texture>),
                std::bind(Resources::DeleteResource<Graphics::Texture>, std::placeholders::_1),
                Vector<std::string>{"png", "jpg", "jpeg", "hdr", "tga"}, Color(204, 86, 255, 255, true)});

        m_resourceStorage.RegisterResource<Graphics::Material>(
            Resources::ResourceTypeData{
                3,
                std::bind(Resources::CreateResource<Graphics::Material>),
                std::bind(Resources::DeleteResource<Graphics::Material>, std::placeholders::_1),
                Vector<std::string>{"linamat"}, Color(56, 79, 255, 255, true)});

        m_resourceStorage.RegisterResource<Graphics::Model>(
            Resources::ResourceTypeData{
                4,
                std::bind(Resources::CreateResource<Graphics::Model>),
                std::bind(Resources::DeleteResource<Graphics::Model>, std::placeholders::_1),
                Vector<std::string>{"fbx", "obj", "gltf", "glb"}, Color(255, 146, 22, 255, true)});

        m_resourceStorage.RegisterResource<Audio::Audio>(Resources::ResourceTypeData{
            5,
            std::bind(Resources::CreateResource<Audio::Audio>),
            std::bind(Resources::DeleteResource<Audio::Audio>, std::placeholders::_1),
            Vector<std::string>{"wav", "mp3", "ogg"}, Color(255, 235, 170, 255, true)});

        m_resourceStorage.RegisterResource<Physics::PhysicsMaterial>(Resources::ResourceTypeData{
            5,
            std::bind(Resources::CreateResource<Physics::PhysicsMaterial>),
            std::bind(Resources::DeleteResource<Physics::PhysicsMaterial>, std::placeholders::_1),
            Vector<std::string>{"linaphymat"},
            Color(17, 120, 255, 255, true),
        });

        // TODO: Font class.
    }

    double Engine::SmoothDeltaTime(double dt)
    {

        if (m_deltaFirstFill < DELTA_TIME_HISTORY)
        {
            m_deltaFirstFill++;
        }
        else if (!m_deltaFilled)
            m_deltaFilled = true;

        m_deltaTimeArray[m_deltaTimeArrOffset] = dt;
        m_deltaTimeArrOffset++;

        if (m_deltaTimeArrOffset == DELTA_TIME_HISTORY)
            m_deltaTimeArrOffset = 0;

        if (!m_deltaFilled)
            return dt;

        // Remove the biggest & smalles 2 deltas.
        RemoveOutliers(true);
        RemoveOutliers(true);
        RemoveOutliers(false);
        RemoveOutliers(false);

        double avg   = 0.0;
        int    index = 0;
        for (double d : m_deltaTimeArray)
        {
            if (d < 0.0)
            {
                m_deltaTimeArray[index] = m_deltaTimeArray[index] * -1.0;
                index++;
                continue;
            }

            avg += d;
            index++;
        }

        avg /= DELTA_TIME_HISTORY - 4;

        return avg;
    }

} // namespace Lina
