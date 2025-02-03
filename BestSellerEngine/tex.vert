#version 400

uniform mat4 MVP;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
    gl_Position = MVP * vec4(v_position, 1.0);
    v_TexCoord = texCoord;
};