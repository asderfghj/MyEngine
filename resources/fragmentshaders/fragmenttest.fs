#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	FragColor = texture2D(texture1, TexCoord);
}