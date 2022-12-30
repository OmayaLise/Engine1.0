
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 FragPos;  

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix; 

void main()
{
	gl_Position = mvpMatrix *vec4(aPos, 2.0);
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
	ourColor = mat3(transpose(inverse(modelMatrix)))* aColor;
	TexCoord = aTexCoord ;
};