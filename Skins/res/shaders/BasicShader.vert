#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_NormalVector;

uniform mat4 u_TransformMatrix; // "model matrix"
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform vec3 u_LightPosition;

out vec2 v_TexCoord;
out vec3 v_NormalVector;
out vec3 v_ToLightVector;
out vec3 v_ToCameraVector;

void main()
{
	// Calculate the position of the object in the world
	vec4 worldPosition = u_TransformMatrix * vec4(a_Position, 1.0);

	// Multiply the normal by transformation matrix (fixes normal if object is rotated)
	v_NormalVector = (u_TransformMatrix * vec4(a_NormalVector, 0.0)).xyz;

	// Get the vector of the light from the position the object is in the world
	v_ToLightVector = u_LightPosition - worldPosition.xyz;

	// Get the vector to the camera from the position of the object
	v_ToCameraVector = (inverse(u_ViewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	// Pass texture coordinates to fragment shader
	v_TexCoord = a_TexCoord;

	// Compute final position of object
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * worldPosition;
	
}