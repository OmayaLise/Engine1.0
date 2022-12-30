#include "Light.hpp"

namespace LowRenderer
{
	DirectionalLight::DirectionalLight(const Maths::Vec3& dir, const Maths::Vec3& ambientC, 
		const Maths::Vec3& diffuseC, const Maths::Vec3& specularC) : direction{ dir }
	{
		ambientColor = ambientC;
		diffuseColor = diffuseC;
		specularColor = specularC;
	}

	PointLight::PointLight(const Maths::Vec3& pos, const Maths::Vec3& ambientC, 
		const Maths::Vec3& diffuseC, const Maths::Vec3& specularC, 
		const float cons, const float lin, const float quad)
		: position{pos}, constant {cons}, linear{lin}, quadratic{quad}
	{
		ambientColor = ambientC;
		diffuseColor = diffuseC;
		specularColor = specularC;
	}

	SpotLight::SpotLight(const Maths::Vec3& pos, const Maths::Vec3& dir, 
		const float cut, const float outerCut, const Maths::Vec3& ambientC,
		const Maths::Vec3& diffuseC, const Maths::Vec3& specularC, 
		const float cons, const float lin, const float quad)
		: position{ pos }, direction{ dir }, cutOff{ cut }, outerCutOff{ outerCut },
		constant{ cons }, linear{ lin }, quadratic{ quad }
	{
		ambientColor = ambientC;
		diffuseColor = diffuseC;
		specularColor = specularC;
	}

}
