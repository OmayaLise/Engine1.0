#pragma once
#include <list>
#include <memory>

#include "Transform.hpp"
#include "Mesh.hpp"

namespace LowRenderer
{
	class Object 
	{
		public:
			Object(std::string name, LowRenderer::Mesh* mesh, const Maths::Vec3& translation,
				const Maths::Vec3& scale, const Maths::Vec3& rotation);
			Physics::Transform transform;
			LowRenderer::Mesh* mesh;
			std::string name;

			std::vector<Object*> children;
			Object* parent = nullptr;

			int parentID = -1;
			int childID;

			void UpdateAll();
			void AddChild(Object* child);
	};

}