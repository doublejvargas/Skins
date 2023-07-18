#version 460 core

in vec2 v_TexCoord;
in vec3 v_NormalVector;
in vec3 v_ToLightVector;
in vec3 v_ToCameraVector;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Texture;
uniform vec3 u_LightColor;
uniform float u_ShineDamper;
uniform float u_Reflectivity;
uniform float u_AmbientLight;

void main()
{    

	// Normalize the vectors
	vec3 unitNormal = normalize(v_NormalVector);
	vec3 unitLightVector = normalize(v_ToLightVector);
    
	/* ----------- Specular/Diffuse Lighting ------------ */
	// Compute how close the face is to facing the light
	float brightness = dot(unitNormal, unitLightVector);
	brightness = max(brightness, u_AmbientLight);

	// Compute right shade of light color
	vec3 diffuse = brightness * u_LightColor;

	/* ----------- Specular Lighting ---------- */
	vec3 unitCameraVector = normalize(v_ToCameraVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
	float specularFactor = dot(reflectedLightDirection, unitCameraVector);
	specularFactor = max(specularFactor, 0.0);
	float dampedSpecular = pow(specularFactor, u_ShineDamper);
	vec3 finalSpecular = dampedSpecular * u_Reflectivity * u_LightColor;

    o_Color = vec4(diffuse, 1.0) * texture(u_Texture, v_TexCoord) + vec4(finalSpecular, 1.0);
}