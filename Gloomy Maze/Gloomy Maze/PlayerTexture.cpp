#include "Define.h"

void HeadTexture(GLuint object[])
{
	// Front
	Load_TextureBMP(object, 0, "Resource/머리/HeadFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/머리/HeadBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/머리/HeadLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/머리/HeadRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/머리/HeadTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/머리/HeadBottom.bmp");

	// 텍스처 모드 설정
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}
void BodyTexture(GLuint object[])
{
	// Front
	Load_TextureBMP(object, 0, "Resource/몸통/BodyFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/몸통/BodyBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/몸통/BodyLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/몸통/BodyRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/몸통/BodyTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/몸통/BodyBottom.bmp");
}

void ArmTexture(GLuint object[], GLuint object2[])
{
	// 팔---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object, 0, "Resource/팔/ArmsFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/팔/ArmsBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/팔/ArmsLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/팔/ArmsRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/팔/ArmsTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/팔/ArmsBottom.bmp");

	// 손---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object2, 0, "Resource/손/HandFront.bmp");
	// Back
	Load_TextureBMP(object2, 1, "Resource/손/HandBack.bmp");
	// Left
	Load_TextureBMP(object2, 2, "Resource/손/HandLeft.bmp");
	// Right
	Load_TextureBMP(object2, 3, "Resource/손/HandRight.bmp");
	// Top
	Load_TextureBMP(object2, 4, "Resource/손/HandTop.bmp");
	// Bottom
	Load_TextureBMP(object2, 5, "Resource/손/HandBottom.bmp");
}
void LegTexture(GLuint object[], GLuint object2[])
{
	// 허벅지---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object, 0, "Resource/허벅지/LegsFront.bmp");
	// Back
	Load_TextureBMP(object, 1, "Resource/허벅지/LegsBack.bmp");
	// Left
	Load_TextureBMP(object, 2, "Resource/허벅지/LegsLeft.bmp");
	// Right
	Load_TextureBMP(object, 3, "Resource/허벅지/LegsRight.bmp");
	// Top
	Load_TextureBMP(object, 4, "Resource/허벅지/LegsTop.bmp");
	// Bottom
	Load_TextureBMP(object, 5, "Resource/허벅지/LegsBottom.bmp");

	// 종아리 + 발---------------------------------------------------------------------
	// Front
	Load_TextureBMP(object2, 0, "Resource/종아리/FootFront.bmp");
	// Back
	Load_TextureBMP(object2, 1, "Resource/종아리/FootBack.bmp");
	// Left
	Load_TextureBMP(object2, 2, "Resource/종아리/FootLeft.bmp");
	// Right
	Load_TextureBMP(object2, 3, "Resource/종아리/FootRight.bmp");
	// Top
	Load_TextureBMP(object2, 4, "Resource/종아리/FootTop.bmp");
	// Bottom
	Load_TextureBMP(object2, 5, "Resource/종아리/FootBottom.bmp");
}