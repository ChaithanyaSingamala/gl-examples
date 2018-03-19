#version 300 es
precision mediump float;

in vec3 vertexPosition;
in vec2 UV0;

uniform mat4 mvp;

out vec2 vUV0;

void main()
{
	gl_Position = mvp * vec4(vertexPosition, 1.0);
	vUV0 = UV0;
}