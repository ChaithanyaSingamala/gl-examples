#version 300 es
precision mediump float;

in vec3 vertexPosition;
in vec2 vertexUV0;
in vec3 vertexNormal;

uniform mat4 model;
uniform mat4 mvp;
uniform mat3 normalMatrix;

out vec2 vUV0;

out vec3 posInWorld;
out vec3 normalInWorld;

void main()
{
	gl_Position = mvp * vec4(vertexPosition, 1.0);
	vUV0 = vertexUV0;
	posInWorld = vec3(model * vec4(vertexPosition, 1.0));
	
	// assuming The normal matrix is defined as the transpose of the inverse of the upper-left corner of the model matrix
	//mat3 normalMatrix = mat3(transpose(inverse(model)));
	normalInWorld = normalMatrix * vertexNormal;
}