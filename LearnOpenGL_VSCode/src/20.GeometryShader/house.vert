
#version 330 core

layout (location=0) in vec3 pos;

// out vec3 thisColor;

void main()
{
    gl_Position= vec4(pos.xyz,1.0);
}