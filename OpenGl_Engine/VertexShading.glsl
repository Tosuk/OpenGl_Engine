#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pers;


void main()
{
	gl_Position = pers * view * model * vec4(aPos, 1.0);
	texCoord = aTexture;
}	

