#ifndef __DEFINE_H
#define __DEFINE_H
#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


//#include <mmsystem.h>

// BGM 사용을 위함
#pragma comment(lib, "winmm.lib") 

// OpenGL Aux 사용을 위함
//#pragma comment(lib, "./OpenGL_Aux/GLAUX")
#include "OpenGL_Aux/GLAUX.H"
#pragma comment(lib, "./OpenGL_Aux/GLAUX")

//legacy_stdio_definitions.lib  <- 링커에 추가종속성에 추가하였다.  ( 안넣으니 안돌아감 )

void LocationGround(GLuint object, int x, int y, int z);
void SetGround(int size, GLuint object);
void LocationBlock(GLuint object[], int x, int y, int z);
void SetBlock(int size, GLuint object[]);

// 미로 블럭 텍스쳐
void BlockTexture(GLuint[]);
// 바닥 텍스쳐
void GroundTexture(GLuint[]);
// 플레이어 텍스쳐
void HeadTexture(GLuint[]);
void BodyTexture(GLuint[]);
void ArmTexture(GLuint[], GLuint[]);
void LegTexture(GLuint[], GLuint[]);
// 유령 텍스쳐 4개
void Ghost1Texture(GLuint[]);  
void Ghost2Texture(GLuint[]);
void Ghost3Texture(GLuint[]);
void Ghost4Texture(GLuint[]);


// 바닥 그리는 함수
void DrawGround(GLuint);

// 블럭 그리는 함수
void DrawBlock(GLuint[]);

// 블럭의 면 그리는 함수
void DrawBlockTop(int, bool, GLuint);
void DrawBlockBottom(int, bool, GLuint);
void DrawBlockFront(int, bool, GLuint);
void DrawBlockBack(int, bool, GLuint);
void DrawBlockLeft(int, bool, GLuint);
void DrawBlockRight(int, bool, GLuint);

// 미로 블럭 변수
static GLuint blockObject[6];

// 바닥 변수
static GLuint groundObject[1];

// 플레이어 변수
static GLuint headObject[6];  // 머리
static GLuint bodyObject[6];  // 몸통
static GLuint armObject[6];   // 팔 
static GLuint handObject[6];  // 손
static GLuint legObject[6];   // 허벅지
static GLuint footObject[6];  // 종아리 + 발

// 유령 변수
static GLuint ghostObject1[6];           
static GLuint ghostObject2[6];
static GLuint ghostObject3[6];
static GLuint ghostObject4[6];



// 비트맵 관련
void Load_TextureBMP(GLuint[], int, char *);
AUX_RGBImageRec *LoadBMP(char *Filename);

#endif