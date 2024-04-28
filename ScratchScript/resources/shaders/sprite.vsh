#version 430 core

layout (location = 0) in vec4 Position;
layout (location = 1) in vec2 Tex;

layout (location = 0) out vec2 vTex;

uniform mat4 uP = mat4(1.0);
uniform mat4 uM = mat4(1.0);

void main()
{
	gl_Position = uP * uM * Position;
	vTex = Tex;
}
