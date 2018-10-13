#include "Define.h"

void GroundTexture(GLuint object[])
{
	Load_TextureBMP(object,0,"Resource/ground.bmp");

	//텍스쳐가 입혀질때 텍스쳐의 색상과 기존픽셀색상과의 관계를 설정한다
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
}

void BlockTexture(GLuint object[])
{
	// Front
	Load_TextureBMP(object, 0, "Resource/block.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/block.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/block.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/block.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/block.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/block.bmp");

	// 텍스처 모드 설정
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

