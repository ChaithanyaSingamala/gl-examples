#version 300 es
precision mediump float;

in vec3 vertexPosition;
in vec3 vertexColor;

out vec3 vColor;
void main()
{
	gl_Position = vec4(vertexPosition, 1.0);
	vColor = vertexColor;
}