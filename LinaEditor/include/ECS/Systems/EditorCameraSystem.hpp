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

/*
Class: EditorCameraSystem

Responsible for updating/controlling the editor camera.

Timestamp: 10/27/2020 4:58:35 PM
*/

#pragma once

#ifndef EditorCameraSystem_HPP
#define EditorCameraSystem_HPP

// Headers here.
#include "Core/CommonECS.hpp"
#include "Core/InputBackendFwd.hpp"
#include "ECS/System.hpp"

namespace Lina
{
    class Quaternion;
}

namespace Lina::Editor
{
    class LevelPanel;
}

namespace Lina::ECS
{
    class EditorCameraSystem : public System
    {
    public:
        void         Initialize(const std::string& name, Editor::LevelPanel& scenePanel);
        virtual void UpdateComponents(float delta) override;
        void         SetEditorCamera(Entity entity)
        {
            m_editorCamera = entity;
        }
        Entity GetEditorCamera()
        {
            return m_editorCamera;
        }
        void SetCameraSpeedMultiplier(float multiplier)
        {
            m_cameraSpeedMultiplier = multiplier;
        }

        inline Vector2 GetMovementSpeeds()
        {
            return m_movementSpeeds;
        }

        inline Vector2 GetRotationSpeeds()
        {
            return m_rotationSpeeds;
        }

        void MoveBehaviour(float delta, Vector2& mouseDragStart, Vector3& location, Quaternion& rotation);
        void RotateBehaviour(float delta, Quaternion& q, Vector2& angles);

    private:
        Vector2             m_movementSpeeds = Vector2::Zero;
        Vector2             m_rotationSpeeds = Vector2::Zero;
        Entity              m_editorCamera   = entt::null;
        Editor::LevelPanel* m_levelPanel;
        Input::InputEngine* m_inputEngine;
        float               m_horizontalKeyAmt      = 0.0f;
        float               m_verticalKeyAmt        = 0.0f;
        float               m_targetXAngle          = 0.0f;
        float               m_targetYAngle          = 0.0f;
        float               m_cameraSpeedMultiplier = 1.0f;
    };
} // namespace Lina::ECS

#endif
