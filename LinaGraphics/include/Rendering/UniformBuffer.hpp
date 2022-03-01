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
Class: UniformBuffer

Represents a uniform buffer structure in the shaders. It creates and updates the buffer data.

Timestamp: 4/26/2019 6:41:58 PM
*/

#pragma once

#ifndef UniformBuffer_HPP
#define UniformBuffer_HPP

#include "Core/RenderBackendFwd.hpp"
#include "RenderingCommon.hpp"

namespace Lina::Graphics
{
    class UniformBuffer
    {
    public:
        UniformBuffer()
        {
        }
        ~UniformBuffer();

        void   Construct(uintptr dataSize, BufferUsage usage, const void* data = nullptr);
        void   Bind(uint32 point);
        void   Update(const void* data, uintptr offset, uintptr dataSize);
        void   Update(const void* data, uintptr dataSize);
        uint32 GetID()
        {
            return m_engineBoundID;
        }

    private:
        RenderDevice* m_renderDevice  = nullptr;
        uint32        m_engineBoundID = 0;
        uintptr       m_bufferSize    = 0;
        bool          m_isConstructed = false;
    };
} // namespace Lina::Graphics

#endif
