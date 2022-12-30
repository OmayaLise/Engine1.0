#pragma once
#include "myMath.hpp"

namespace LowRenderer
{
	class Light
	{
	public:
		Maths::Vec3 ambientColor;
		Maths::Vec3 diffuseColor;
		Maths::Vec3 specularColor;
	};

	class DirectionalLight : public Light
	{
	public:
		Maths::Vec3 direction;

		DirectionalLight(const Maths::Vec3& dir, const Maths::Vec3& ambientC, 
			const Maths::Vec3& diffuseC, const Maths::Vec3& specularC);
	};

	class PointLight : public Light
	{
		public:
		Maths::Vec3 position;

		float constant;
		float linear;
		float quadratic;

		PointLight(const Maths::Vec3& pos, const Maths::Vec3& ambientC,
			const Maths::Vec3& diffuseC, const Maths::Vec3& specularC, 
			const float cons, const float lin, const float quad);
	};

	class SpotLight : public Light
	{
	public:
		Maths::Vec3  position;
		Maths::Vec3  direction;
		float cutOff;
		float outerCutOff;
		float constant;
		float linear;
		float quadratic;

		SpotLight(const Maths::Vec3& pos, const Maths::Vec3& dir,
			const float cut, const float outerCutOff, const Maths::Vec3& ambientC,
			const Maths::Vec3& diffuseC, const Maths::Vec3& specularC, 
			const float cons, const float lin, const float quad);
	};
}