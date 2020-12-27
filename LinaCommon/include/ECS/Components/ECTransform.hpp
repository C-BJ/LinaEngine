/* 
This file is a part of: Lina Engine
https://github.com/inanevin/Lina

Author: Inan Evin
http://www.inanevin.com

Copyright (c) [2018-2020] [Inan Evin]

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
Class: ECSTransformComponent

Represents transformations for objects so that they could have
location, rotation and scale in the world.

Timestamp: 4/9/2019 1:28:05 PM

*/

#pragma once

#ifndef ECSTransformComponent_HPP
#define ECSTransformComponent_HPP


#include "Math/Vector.hpp"

namespace Lina::ECS
{
	struct ECTransform 
	{
		Vector3 m_position = V3_ZERO;
		Vector3 m_rotation = V3_ZERO;
		Vector3 m_scale = V3_ZERO;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(m_position, m_rotation, m_scale);
		}

	};
}


#endif