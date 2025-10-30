#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in int aTextId;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform int test;

out vec2 uv;

void main()
{
    float offset = (1.0 / 94.0);
    uv = vec2((aUv.x * offset) + (offset * aTextId),  aUv.y);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}