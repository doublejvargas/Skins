#version 330 core

in vec3 v_Color;

layout(location = 0) out vec4 o_Color;

void main()
{
	o_Color = vec4(v_Color, 1.0);
}