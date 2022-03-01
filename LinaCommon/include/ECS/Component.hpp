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
Class: ECSComponent

Defines the base component class as well as macros for drawing components
via the sandbox editor.

Timestamp: 5/23/2020 5:17:02 PM

*/

#pragma once

#ifndef ECSComponent_HPP
#define ECSComponent_HPP

#include "Core/CommonReflection.hpp"

namespace Lina
{
    class ReflectionRegistry;

    namespace Editor
    {
        class ComponentDrawer;
    }
} // namespace Lina

namespace Lina::ECS
{
    class Component
    {

    public:
        Component() = default;
        virtual ~Component(){};

        inline virtual void SetIsEnabled(bool enabled)
        {
            m_isEnabled = enabled;
        }

        inline bool GetIsEnabled()
        {
            return m_isEnabled;
        }

    protected:

        friend class Editor::ComponentDrawer;
        friend class ReflectionRegistry;
        bool m_isEnabled = true;
    };
} // namespace Lina::ECS

#endif
