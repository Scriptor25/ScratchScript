#version 450 core

uniform sampler2D uTexture;

layout (location = 0) in vec2 vTex;

layout (location = 0) out vec4 Color;

void main() {
    Color = texture(uTexture, vTex);
}
