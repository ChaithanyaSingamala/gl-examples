#version 300 es
precision mediump float;

out vec4 fragColor;

in vec3 posInWorld;
in vec3 normalInWorld;
in vec2 vUV0;

uniform sampler2D Texture;

//uniform vec3 lightColor;

//uniform vec3 lightPos;
//uniform vec3 viewPos;

void main()
{
	vec3 lightColor = vec3(0.9,0.8,0.9);
	vec3 lightPos = vec3(-1.0,5.0,0.0);
	vec4 diffuseColor = texture(Texture, vUV0);
	vec3 normal = normalize(normalInWorld);
	vec3 lightDir = normalize(lightPos - posInWorld);
	float diffuseFactor = max(dot(normal,lightDir), 0.0);
	//diffuseColor = diffuseFactor * lightColor;

	float specularStrength = 0.5;
	float shininess = 32.0;
	vec3 viewDir = normalize(/*viewPos*/ - posInWorld);
	vec3 reflectDir = reflect(lightDir, normal);
	float specFactor = pow(max(dot(viewDir,reflectDir), 0.0), shininess);
	
	//fragColor = vec4(objectColor * specFactor * lightColor + diffuseFactor * diffuseColor.rgb, diffuseColor.a);
	fragColor = vec4(diffuseColor.rgb * (specFactor + diffuseFactor) * lightColor, 1.0);
}