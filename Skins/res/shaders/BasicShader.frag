#version 330 core

in vec2 v_TexCoord;
in vec3 v_NormalVector;
in vec3 v_ToLightVector;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Texture;
uniform vec3 u_LightColor;

void main()
{

	// Normalize the vectors
	vec3 unitNormal = normalize(v_NormalVector);
	vec3 unitLightVector = normalize(v_ToLightVector);

	// Compute how close the face is to facing the light
	float brightness = dot(unitNormal, unitLightVector);
	brightness = max(brightness, 0.0);

	// Compute right shade of light color
	vec3 diffuse = brightness * u_LightColor;

	// Final color is mix of texture and diffused light color
	o_Color = vec4(diffuse, 1.0) * texture(u_Texture, v_TexCoord);
}