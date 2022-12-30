
#include"Camera.hpp"

namespace LowRenderer
{
	Camera::Camera()
	{     
        aspect = screenWidth / screenHeight;
        viewMatrix = Maths::Mat4::CreateXRotationMatrix(-rotation.x)
                    * Maths::Mat4::CreateYRotationMatrix(-rotation.y)
                    * Maths::Mat4::CreateTranslationMatrix(-position);

        float a = 1.f / tanf(Maths::DEG2RAD * FOV / 2.f);

        projectionMatrix = Maths:: Mat4(     a / aspect, 0.f, 0.f, 0.f,
                                            0.f, a, 0.f, 0.f,
                                            0.f, 0.f, -(far + near) / (far - near), -(2 * far * near) / (far - near),
                                            0.f, 0.f, -1.f, 0.f
                                        );
  
	}

    void Camera::Update(const InputsCamera& inputsCamera)
    {
        rotation.y -= inputsCamera.deltaX / 6.f;
        rotation.x -= inputsCamera.deltaY / 6.f;

        if (rotation.x < -90.f)
            rotation.x = -90.f;

        if (rotation.x > 90.f)
            rotation.x = 90.f;

        if (rotation.y > 360.f)
            rotation.y = 360.f;

        if (rotation.y < -360.f)
            rotation.y = -360.f;

        if (inputsCamera.moveForward)
        {
            position.x += speed * cosf(Maths::DEG2RAD * (rotation.y + 90.f));
            position.z -= speed * sinf(Maths::DEG2RAD * (rotation.y + 90.f));
        }
        if (inputsCamera.moveBackward)
        {
            position.x -= speed * cosf(Maths::DEG2RAD * (rotation.y + 90.f));
            position.z += speed * sinf(Maths::DEG2RAD * (rotation.y + 90.f));
        }

        if (inputsCamera.moveLeft)
        {
            position.x -= speed * cosf(Maths::DEG2RAD * (rotation.y));
            position.z += speed * sinf(Maths::DEG2RAD * (rotation.y));
        }
        if (inputsCamera.moveRight)
        {
            position.x += speed * cosf(Maths::DEG2RAD * (rotation.y));
            position.z -= speed * sinf(Maths::DEG2RAD * (rotation.y));
        }

        if (inputsCamera.moveUp)
            position.y += speed;

        if (inputsCamera.moveDown)
            position.y -= speed;

        viewMatrix =  Maths::Mat4::CreateXRotationMatrix(-rotation.x)
                    * Maths::Mat4::CreateYRotationMatrix(-rotation.y)
                    * Maths::Mat4::CreateTranslationMatrix(-position);
    }
}