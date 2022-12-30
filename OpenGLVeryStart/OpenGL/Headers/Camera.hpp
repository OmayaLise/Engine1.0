#pragma once
#include "myMath.hpp"

namespace LowRenderer
{
	struct InputsCamera
	{
		float deltaX = 0.f;
		float deltaY = 0.f;
		bool moveForward = true;
		bool moveBackward = true;
		bool moveRight = true;
		bool moveLeft = true;
		bool moveUp = true;
		bool moveDown = true;
	};

	class Camera
	{
	private :
		Maths::Vec3 rotation;
		float far = 80.f;
		float near = 0.1f;
		float right = 1.f;
		float left = -1.f;
		float top = 1.f;
		float bottom = -1.f;
		float FOV = 60.f;
		float speed = 0.1f;
		int aspect;

	public:
		Maths::Vec3 position;
		int screenWidth = 1; 
		int screenHeight = 1;
		InputsCamera inputs;

		Maths::Mat4 viewMatrix;
		Maths::Mat4 projectionMatrix;

		Camera();
		void Update(const InputsCamera& inputs);

	};


}