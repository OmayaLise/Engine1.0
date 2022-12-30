#include "Object.hpp"

namespace LowRenderer
{
    Object::Object(std::string name, LowRenderer::Mesh* mesh , const Maths::Vec3& translation,
        const Maths::Vec3& scale, const Maths::Vec3& rotation)
    {
        this->name = name;
        this->mesh = mesh;
        transform.pos = translation;
        transform.scale = scale;
        transform.eulerRot = rotation;
    }

    void Object:: UpdateAll()
    {
        //if (!transform.hasMoved)
        //    return;

        if (parent)
            transform.modelMatrix = parent->transform.modelMatrix * 
            Maths::Mat4::CreateTransformationMatrix(transform.pos, transform.scale, transform.eulerRot);
        else
            transform.modelMatrix = Maths::Mat4::CreateTransformationMatrix
            (transform.pos, transform.scale, transform.eulerRot);

        for (auto&& child : children)
        {
            child->UpdateAll();
        }
    }

    void Object::AddChild(Object *child)
    {
        children.push_back(child);
        child->parent = this;
    }

}