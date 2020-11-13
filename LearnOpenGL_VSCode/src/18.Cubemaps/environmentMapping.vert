#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec2 tex;
layout (location=2) in vec3 norm;

out vec3 normal;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position= projection * view * model * vec4(pos.xyz,1.0);
    position= vec3(model*vec4(pos.xyz,1.0));
    normal=normalize(mat3(transpose(inverse(model))) * norm);
}