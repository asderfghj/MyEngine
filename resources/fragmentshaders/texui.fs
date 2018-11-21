#version 330 core
in vec2 TexCoord;


uniform vec4 color;
uniform sampler2D texture;

void main()
{
	gl_FragColor = vec4(texture2D(texture, TexCoord).x, texture2D(texture, TexCoord).y, texture2D(texture, TexCoord).z, 0.0);
	if(gl_FragColor.r > 0.5 && gl_FragColor.g < 0.5 && gl_FragColor.b > 0.5)
	{
		discard;
	}
	
}