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
Class: ModelDrawer



Timestamp: 1/9/2022 11:54:18 PM
*/

#pragma once

#ifndef ModelDrawer_HPP
#define ModelDrawer_HPP

// Headers here.


namespace Lina
{
    class Vector2;
    class Matrix;

    namespace Graphics
    {
        class Model;
        class ModelNode;
    }
} // namespace Lina

namespace Lina::Editor
{
    class ModelDrawer
    {

    public:
        ModelDrawer() = default;
        ~ModelDrawer() = default;

        static void DrawModelSettings(Graphics::Model*& model, float leftPaneSize);
        static void DisplayNode(Graphics::ModelNode* node);
        static void DrawModel(Graphics::Model* model, Matrix& matrix, const Vector2& bgMin, const Vector2& bgMax);

    private:
    };
} // namespace Lina::Editor

#endif
