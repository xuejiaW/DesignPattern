#version 330 core
out vec4 color;

in vec2 TexCoord1;
in vec2 TexCoord2;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	//color=vec4(1.0f,0,0,1.0f);
	color=mix(texture(ourTexture1,TexCoord1),texture(ourTexture2,vec2(1-TexCoord2.x,1-TexCoord2.y)),0.5f);
	//Ҫ��1��ȥ��ֵ����Ȼ��gl_clamp_to_edgeģʽ�»������ʾ������
}