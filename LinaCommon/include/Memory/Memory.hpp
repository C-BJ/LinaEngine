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

#ifndef Memory_HPP
#define Memory_HPP

#define NOMINMAX
#define GENERIC_MEMORY_SMALL_MEMSWAP_MAX 16

#include "Core/SizeDefinitions.hpp"
#include <cstring>

#ifdef LINA_ENABLE_PROFILING
extern bool g_skipAllocTrack;
#endif

namespace Lina
{

    struct Memory
    {
        enum
        {
            DefaultAlignment = 16,
            MinAlignment     = 8
        };

        static void* memmove(void* dest, const void* src, uintptr amt)
        {
            return ::memmove(dest, src, amt);
        }

        static int32 memcmp(const void* dest, const void* src, uintptr amt)
        {
            return ::memcmp(dest, src, amt);
        }

        template <typename T>
        static inline void* memset(void* destIn, T val, uintptr amt)
        {
            T*      dest      = (T*)destIn;
            uintptr amtT      = amt / sizeof(T);
            uintptr remainder = amt % sizeof(T);

            for (uintptr i = 0; i < amtT; ++i, ++dest)
                memcpy(dest, &val, sizeof(T));

            memcpy(dest, &val, remainder);
            return destIn;
        }

        static void* memzero(void* dest, uintptr amt)
        {
            return ::memset(dest, 0, amt);
        }

        static void* memcpy(void* dest, const void* src, uintptr amt)
        {
            return ::memcpy(dest, src, amt);
        }

        static void memswap(void* a, void* b, uintptr size)
        {
            if (size <= GENERIC_MEMORY_SMALL_MEMSWAP_MAX)
                smallmemswap(a, b, size);
            else
                bigmemswap(a, b, size);
        }

        template <typename T>
        static constexpr T align(const T ptr, uintptr alignment)
        {
            return (T)(((intptr)ptr + alignment - 1) & ~(alignment - 1));
        }

        static void*   malloc(uintptr amt, uint32 alignment = DefaultAlignment);
        static void*   realloc(void* ptr, uintptr amt, uint32 alignment);
        static void*   free(void* ptr);
        static uintptr getAllocSize(void* ptr);

    private:
        static void bigmemswap(void* a, void* b, uintptr size);
        static void smallmemswap(void* a, void* b, uintptr size)
        {
            // LINA_ASSERT(size <= GENERIC_MEMORY_SMALL_MEMSWAP_MAX, "Size is bigger than allowed!");
            char  temp_data[GENERIC_MEMORY_SMALL_MEMSWAP_MAX];
            void* temp = (void*)&temp_data;
            Memory::memcpy(temp, a, size);
            Memory::memcpy(a, b, size);
            Memory::memcpy(b, temp, size);
        }
    };

    template <>
    inline void* Memory::memset(void* dest, uint8 val, uintptr amt)
    {
        return ::memset(dest, val, amt);
    }
} // namespace Lina

#endif
