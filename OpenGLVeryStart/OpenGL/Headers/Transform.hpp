#pragma once
#include "myMath.hpp"

namespace Physics
{

	class Transform 
	{

	public:
        //Local space information world space
        Maths::Vec3 pos = { 0.f, 0.f, 0.f };
        Maths::Vec3 eulerRot = { 0.f, 0.f, 0.f };
        Maths::Vec3 scale = { 1.f, 1.f, 1.f };

        //Global space information concatenate in matrix
        Maths::Mat4 modelMatrix = Maths::Mat4::Identity();

        bool hasMoved = true;

	};


}