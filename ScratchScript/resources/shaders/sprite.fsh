#version 430 core

layout (location = 0) in vec2 vTex;

layout (location = 0) out vec4 Color;

uniform sampler2D uTexture;

void main()
{
	Color = texture(uTexture, vTex);
}
