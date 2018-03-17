#version 300 es
precision mediump float;

in vec3 vertexPosition;
//in vec3 vertexColor;

uniform mat4 mvp;
uniform vec3 color;

out vec3 vColor;
void main()
{
	gl_Position = mvp * vec4(vertexPosition, 1.0);

	vColor = color;
}