#version 300 es
precision highp float;

out vec4 fragColor;
in vec2 vUV0;

uniform sampler2D Texture;

void main()
{
	fragColor = texture(Texture, vUV0);
//	fragColor = vec4(1.0);
	//fragColor = vec4(vUV0.x, vUV0.y, 1.0, 1.0);

}