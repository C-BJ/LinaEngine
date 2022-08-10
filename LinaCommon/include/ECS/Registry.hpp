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



#pragma once

#ifndef Registry_HPP
#define Registry_HPP

#include "Core/CommonECS.hpp"
#include "Data/Map.hpp"
#include <cereal/access.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <entt/config/config.h>
#include <entt/entity/snapshot.hpp>
namespace Lina
{
    namespace World
    {
        class Level;
    }
} // namespace Lina

namespace Lina::ECS
{

    class Registry : public entt::registry
    {
    public:
        Registry()          = default;
        virtual ~Registry() = default;

        inline static Registry* Get()
        {
            return s_ecs;
        }

        void               SerializeComponentsInRegistry(cereal::PortableBinaryOutputArchive& archive);
        void               DeserializeComponentsInRegistry(cereal::PortableBinaryInputArchive& archive);
        void               AddChildToEntity(Entity parent, Entity child);
        void               DestroyAllChildren(Entity parent);
        void               RemoveChildFromEntity(Entity parent, Entity child);
        void               RemoveFromParent(Entity child);
        void               CloneEntity(Entity from, Entity to);
        void               DestroyEntity(Entity entity, bool isRoot = true);
        void               SetEntityEnabled(Entity entity, bool isEnabled);
        Entity             CreateEntity(const String& name);
        Entity             CreateEntity(Entity copy, bool attachParent = true);
        Entity             GetEntity(const String& name);
        const Set<Entity>& GetChildren(Entity parent);

    private:
        friend class World::Level;
        static Registry* s_ecs;
    };
} // namespace Lina::ECS

#endif
