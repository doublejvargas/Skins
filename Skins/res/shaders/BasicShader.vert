#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Color;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	
	v_Color = vec3(a_Position.x + 0.5, 1.0, a_Position.y + 0.5);
}