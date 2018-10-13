#define _CRT_SECURE_NO_WARNINGS
#include "Define.h"
#include <math.h>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);

// 플레이어 그리는 함수
void DrawPlayer();

//카메라 시점관련 함수
void Target(int x, int y);

// 유령4개 그리는 함수
void DrawGhost1();
void DrawGhost2();
void DrawGhost3();
void DrawGhost4();

// 맵 저장 변수
char mapData[6][30][30];

// 텍스트 읽기용 함수
void MapTextRead1();
void MapTextRead2();
void MapTextRead3();
void MapTextRead4();
void MapTextRead5();
void MapTextRead6();

// 텍스쳐 설정 함수
void InitTexture();

// 충돌체크 함수
void CollisionCheck();

// 조명 및 손전등 함수
void show_Light();
void FlashLight();

// UI 그리는 함수
void draw_UI(int CharX, int CharZ);


int width, height; // 너비, 높이


// 카메라 변수
float camRotateX = -90, camRotateY = -90, viewX = 0, viewY = 0, viewZ = -1000;
float playerX = 0, playerZ = 6920, playerY = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
int characterSpeed = 16, camDistance = 400, mouseSpeed = 10;
bool RotateCam = true;

// 플레이어 어깨 및 팔 각도를 위한 변수 
float rightSholderX, rightSholderY, rightSholderZ;
float leftShoulderX, leftShoulderY, leftShoulderZ;
float rightElbowX, rightElbowY, rightElbowZ;
float leftElbowX, leftElbowY, leftElbowZ;

// 충돌 체크 변수 
int collisionDist = 90;

// 미로 변화를 위한 값
int changeYpos = 240;
int changeMapNumber = 0;
bool changeDown = false;
bool changeUP = false;

// UI 변수
char drawTimeCount[100];
int timeCount = 35;

// 유령 이동 변수 
float ghost1Angle;
float ghost2Angle;
float ghost3X = 500, ghost3Z = 500, ghost3Angle = 90;
bool ghost3Change = false;
float ghost4X = 500, ghost4Z = 500, ghost4Angle = 0;
bool ghost4Change = false;


void main()
{
	MapTextRead1();
	MapTextRead2();
	MapTextRead3();
	MapTextRead4();
	MapTextRead5();
	MapTextRead6();

	leftShoulderY = 70;
	leftShoulderZ = -75;
	rightSholderY = 30;
	rightSholderZ = 0;
	leftElbowX = 25;
	rightElbowX = -30;

	//윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //디스플레이 모드 설정
	glutInitWindowPosition(500, 0); // 윈도우 위치 지정
	glutInitWindowSize(1200, 800); //윈도우 크기 지정
	glutCreateWindow("Gloomy Maze"); //윈도우 생성(윈도우 이름)

									 //상태 변수 초기화 함수
	InitTexture(); // 텍스쳐 초기화
	glutSetCursor(GLUT_CURSOR_NONE); // 화면 마우스 커서 삭제


	// 콜백 함수
	glutDisplayFunc(DrawScene); //출력 함수의 지정
	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);
	glutTimerFunc(1000, TimerFunction, 3);
	glutTimerFunc(10, TimerFunction, 4);
	glutPassiveMotionFunc(Motion); // 마우스 클릭하지 않은 상태로 움직일때 호출되는 콜백함수
	glutKeyboardFunc(Keyboard);//키보드입력
	PlaySound("Sound/Breath&Heart.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	//SND_ASYNC 비동기적 재생, 재생중에도 프로그램이 멈추지 않고 돌아감
	//SND_LOOP  반복재생 ( SND_ASYNC와 같이 써야됨)
	//SND_NODEFAULT 지정한 경로에 wav파일이 없어도 경고음이 나오지 않음

	glutReshapeFunc(Reshape);
	glutMainLoop(); //메인 루프 돌기

}

//윈도우 출력 함수
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//바탕색을'black'로지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / (float)height, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);      // 조명 활성화
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	glLoadIdentity();
	gluLookAt(playerX, playerY + 200, playerZ, playerX + viewX, playerY + viewY + 170, playerZ + viewZ, 0.0, 1.0, 0.0);

	glPushMatrix();
	glEnable(GL_DEPTH_TEST); // 가려진 면 제거
	glEnable(GL_CULL_FACE);


	//----------------------------------------------------
	// 조명 , 손전등 , 플레이어 
	glPushMatrix();
	glTranslatef(playerX, playerY + 130, playerZ);
	glRotatef(camRotateX + 180, 0, 1, 0);
	FlashLight();
	DrawPlayer();
	show_Light();
	glPopMatrix();


	//-----------------------------------------------------
	// 유령1
	glPushMatrix();
	glTranslatef(6500.f, 0.f, 6900.f);
	glRotatef(-ghost1Angle, 0, 1, 0);
	glTranslatef(4000.f, 0.f, 4000.f);
	glRotatef(-ghost1Angle, 0, 1, 0);
	DrawGhost1();
	glPopMatrix();
	//-----------------------------------------------------
	// 유령2
	glPushMatrix();
	glTranslatef(6500.f, 0.f, 6900.f);
	glRotatef(-ghost2Angle, 0, 1, 0);
	glTranslatef(2000.f, 0.f, 2000.f);
	glRotatef(-ghost2Angle, 0, 1, 0);
	DrawGhost2();
	glPopMatrix();
	//-----------------------------------------------------
	// 유령3
	glPushMatrix();
	glTranslatef(ghost3X, 0, ghost3Z);
	glRotatef(ghost3Angle, 0, 1, 0);
	DrawGhost3();
	glPopMatrix();
	//-----------------------------------------------------
	// 유령4
	glPushMatrix();
	glTranslatef(ghost4X, 0, ghost4Z);
	glRotatef(ghost4Angle, 0, 1, 0);
	DrawGhost4();
	glPopMatrix();


	//-----------------------------------------------------
	// 바닥 그리기
	glPushMatrix();
	glTranslatef(240.f, 0.f, 240.f);
	DrawGround(groundObject[0]);
	glPopMatrix();

	//-----------------------------------------------------
	// 미로 그리기
	glPushMatrix();
	glTranslatef(240.f, 0.f, 240.f);
	DrawBlock(blockObject);
	glPopMatrix();

	// 지금까지의 POP~
	glPopMatrix();

	//-----------------------------------------------------
	// UI 그리기
	glPushMatrix();
	draw_UI(playerX, playerZ);
	glPopMatrix();
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	//뷰포트 변환 설정
	glViewport(0, 0, w, h);
	width = w;
	height = h;

	//투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//클리핑 공간 설정 : 원근투영
	gluPerspective(60.0f, (float)width / (float)height, 0.1, 5000.0);

	//모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
}

void Motion(int x, int y)
{
	Target(x, y);
}

void TimerFunction(int value)
{
	switch (value)
	{
	case 1:
		if (RotateCam)
			glutWarpPointer(400, 300);
		CollisionCheck();
		glutTimerFunc(10, TimerFunction, 1);
		break;

	case 2:
		if (changeDown == true) {
			changeYpos -= 2;
			if (changeYpos <= -250) {
				changeDown = false;
				changeUP = true;
				changeMapNumber += 1;
				if (changeMapNumber >= 6)
					changeMapNumber = 0;

			}
		}
		if (changeUP == true) {
			changeYpos += 5;
			if (changeYpos >= 240)
				changeUP = false;
		}
		glutTimerFunc(10, TimerFunction, 2);
		break;

	case 3:
		timeCount -= 1;
		if (timeCount <= 0) {
			changeDown = true;
			timeCount = 75;
		}
		glutTimerFunc(1000, TimerFunction, 3);
		break;

	case 4:
		ghost1Angle += 0.1;
		ghost2Angle += 0.3;
		//---------------------------------------
		// 유령3 이동
		if (ghost3Change == false)
			ghost3X += 15;
		else {
			ghost3X -= 15;
		}
		if (ghost3X >= 12000) {
			ghost3Change = true;
			ghost3Angle = -90;
			ghost3Z += 1000;
		}
		if (ghost3X <= 0) {
			ghost3Change = false;
			ghost3Angle = 90;
			ghost3Z += 1000;
		}
		if (ghost3Z >= 12000)
			ghost3Z = 1000;
		//--------------------------------------------------
		// 유령4 이동
		if (ghost4Change == false)
			ghost4Z += 15;
		else {
			ghost4Z -= 15;
		}
		if (ghost4Z >= 12000) {
			ghost4Change = true;
			ghost4Angle = 180;
			ghost4X += 1000;
		}
		if (ghost4Z <= 0) {
			ghost4Change = false;
			ghost4Angle = 0;
			ghost4X += 1000;
		}
		if (ghost4X >= 12000)
			ghost4X = 1000;
		glutTimerFunc(10, TimerFunction, 4);
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {  // 27이 ESC  excpae
		exit(1);
	}
	if (key == 'w')
	{
		playerX += characterSpeed * cos((-camRotateX - 90) * 3.141592 / 180);
		playerZ += characterSpeed * sin((-camRotateX - 90) * 3.141592 / 180);

	}
	else if (key == 's')
	{
		playerX -= characterSpeed * cos((-camRotateX - 90) * 3.141592 / 180);
		playerZ -= characterSpeed * sin((-camRotateX - 90) * 3.141592 / 180);

	}
	if (key == 'a')
	{
		playerX -= characterSpeed * cos((-camRotateX) * 3.141592 / 180);
		playerZ -= characterSpeed * sin((-camRotateX) * 3.141592 / 180);

	}
	else if (key == 'd')
	{
		playerX += characterSpeed * cos((-camRotateX) * 3.141592 / 180);
		playerZ += characterSpeed * sin((-camRotateX) * 3.141592 / 180);
	}

	if (key == '1') {
		changeDown = true;
	}

	glutPostRedisplay();
}


void InitTexture()
{
	// 바닥 텍스처 변수에 적용
	GroundTexture(groundObject);

	// 플레이어 텍스처 변수에 적용
	HeadTexture(headObject);
	BodyTexture(bodyObject);
	ArmTexture(armObject, handObject);
	LegTexture(legObject, footObject);

	// 블럭 텍스처 변수에 적용
	BlockTexture(blockObject);

	// 유령 텍스처 변수에 적용
	Ghost1Texture(ghostObject1);
	Ghost2Texture(ghostObject2);
	Ghost3Texture(ghostObject3);
	Ghost4Texture(ghostObject4);
}

void Target(int x, int y)
{
	if (RotateCam == true)
	{
		nx = 400 - x;
		ny = 300 - y;

		camRotateX = camRotateX + (nx / mouseSpeed);
		camRotateY = camRotateY + (ny / mouseSpeed);
		leftShoulderX = camRotateY;
		rightSholderX = camRotateY;

		viewZ = 1000 * sin((camRotateY)* 3.141592 / 180) * cos((camRotateX)* 3.141592 / 180);
		viewX = 1000 * sin((camRotateY)* 3.141592 / 180) * sin((camRotateX)* 3.141592 / 180);
		viewY = 1000 * cos((camRotateY)* 3.141592 / 180);

		if (camRotateX <= -360 || camRotateX >= 360)
			camRotateX = 0;

		if (camRotateY < -179)
			camRotateY = -179;
		else if (camRotateY > -1)
			camRotateY = -1;
		bx = nx;
		by = ny;

	}
}
void DrawGhost1()
{
	glPushMatrix(); 
	glTranslated(0, 170, 0);
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject1[0]);
	DrawBlockBack(30, false, ghostObject1[1]);
	DrawBlockLeft(30, false, ghostObject1[2]);
	DrawBlockRight(30, false, ghostObject1[3]);
	DrawBlockTop(30, false, ghostObject1[4]);
	DrawBlockBottom(30, false, ghostObject1[5]);
	glPopMatrix();
}

void DrawGhost2()
{
	glPushMatrix();
	glTranslated(0, 170, 0);
	
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject2[0]);
	DrawBlockBack(30, false, ghostObject2[1]);
	DrawBlockLeft(30, false, ghostObject2[2]);
	DrawBlockRight(30, false, ghostObject2[3]);
	DrawBlockTop(30, false, ghostObject2[4]);
	DrawBlockBottom(30, false, ghostObject2[5]);
	glPopMatrix(); 
}

void DrawGhost3()
{
	glPushMatrix(); 
	glTranslated(0, 170, 0);
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject3[0]);
	DrawBlockBack(30, false, ghostObject3[1]);
	DrawBlockLeft(30, false, ghostObject3[2]);
	DrawBlockRight(30, false, ghostObject3[3]);
	DrawBlockTop(30, false, ghostObject3[4]);
	DrawBlockBottom(30, false, ghostObject3[5]);
	glPopMatrix();
}

void DrawGhost4()
{
	glPushMatrix(); 
	glTranslated(0, 170, 0);
	glScaled(2.0, 2.0, 1.4);
	DrawBlockFront(30, false, ghostObject4[0]);
	DrawBlockBack(30, false, ghostObject4[1]);
	DrawBlockLeft(30, false, ghostObject4[2]);
	DrawBlockRight(30, false, ghostObject4[3]);
	DrawBlockTop(30, false, ghostObject4[4]);
	DrawBlockBottom(30, false, ghostObject4[5]);
	glPopMatrix();
}

void DrawPlayer() {
	glPushMatrix(); 

	glPushMatrix();  // 머리
	glTranslated(0, 75, 0);
	glRotatef(-(camRotateY + 90) / 3, 1, 0, 0);
	glScaled(1.0, 1.0, 0.7);
	DrawBlockFront(30, false, headObject[0]);
	DrawBlockBack(30, false, headObject[1]);
	DrawBlockLeft(30, false, headObject[2]);
	DrawBlockRight(30, false, headObject[3]);
	DrawBlockTop(30, false, headObject[4]);
	DrawBlockBottom(30, false, headObject[5]);
	glPopMatrix();

	glPushMatrix(); // 몸통
	glScaled(1.0, 1.5, 0.5);
	DrawBlockFront(30, false, bodyObject[0]);
	DrawBlockBack(30, false, bodyObject[1]);
	DrawBlockLeft(30, false, bodyObject[2]);
	DrawBlockRight(30, false, bodyObject[3]);
	DrawBlockTop(30, false, bodyObject[4]);
	DrawBlockBottom(30, false, bodyObject[5]);
	glPopMatrix();

	glPushMatrix(); // 오른팔
	glTranslated(-45, 44, 0);
	glRotatef(-rightSholderX + 210, 1, 0, 0);
	glRotatef(rightSholderY, 0, 1, 0);
	glRotatef(rightSholderZ, 0, 0, 1);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, armObject[0]);
	DrawBlockBack(30, true, armObject[1]);
	DrawBlockLeft(30, true, armObject[2]);
	DrawBlockRight(30, true, armObject[3]);
	DrawBlockTop(30, true, armObject[4]);
	DrawBlockBottom(30, true, armObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); // 오른손
	glTranslated(0, -45, 0);
	glRotatef(rightElbowX, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	glPushMatrix();
	DrawBlockFront(30, true, handObject[0]);
	DrawBlockBack(30, true, handObject[1]);
	DrawBlockLeft(30, true, handObject[2]);
	DrawBlockRight(30, true, handObject[3]);
	DrawBlockTop(30, true, handObject[4]);
	DrawBlockBottom(30, true, handObject[5]);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); // 왼팔
	glTranslated(45, 44, 0);
	glRotatef(-leftShoulderX - 90, 1, 0, 0);
	glRotatef(leftShoulderY, 0, 1, 0);
	glRotatef(leftShoulderZ, 0, 0, 1);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, armObject[0]);
	DrawBlockBack(30, true, armObject[1]);
	DrawBlockLeft(30, true, armObject[2]);
	DrawBlockRight(30, true, armObject[3]);
	DrawBlockTop(30, true, armObject[4]);
	DrawBlockBottom(30, true, armObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); // 왼손
	glTranslated(0, -45, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, handObject[0]);
	DrawBlockBack(30, true, handObject[1]);
	DrawBlockLeft(30, true, handObject[2]);
	DrawBlockRight(30, true, handObject[3]);
	DrawBlockTop(30, true, handObject[4]);
	DrawBlockBottom(30, true, handObject[5]);
	glPopMatrix();
	glPopMatrix();
	//glPopMatrix();


	 // -------------------------------------------------------------------------

	glPushMatrix(); // 오른쪽 허벅지
	glTranslated(-15, -40, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, legObject[0]);
	DrawBlockBack(30, true, legObject[1]);
	DrawBlockLeft(30, true, legObject[2]);
	DrawBlockRight(30, true, legObject[3]);
	DrawBlockTop(30, true, legObject[4]);
	DrawBlockBottom(30, true, legObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //오른쪽 종아리 및 발
	glTranslated(0, -45, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, footObject[0]);
	DrawBlockBack(30, true, footObject[1]);
	DrawBlockLeft(30, true, footObject[2]);
	DrawBlockRight(30, true, footObject[3]);
	DrawBlockTop(30, true, footObject[4]);
	DrawBlockBottom(30, true, footObject[5]);
	glPopMatrix();

	glPopMatrix();


	glPushMatrix(); //왼쪽 허벅지
	glTranslated(15, -40, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, legObject[0]);
	DrawBlockBack(30, true, legObject[1]);
	DrawBlockLeft(30, true, legObject[2]);
	DrawBlockRight(30, true, legObject[3]);
	DrawBlockTop(30, true, legObject[4]);
	DrawBlockBottom(30, true, legObject[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); // 왼쪽 종아리 및 발
	glTranslated(0, -45, 0);
	glScaled(0.5, 0.75, 0.5);
	DrawBlockFront(30, true, footObject[0]);
	DrawBlockBack(30, true, footObject[1]);
	DrawBlockLeft(30, true, footObject[2]);
	DrawBlockRight(30, true, footObject[3]);
	DrawBlockTop(30, true, footObject[4]);
	DrawBlockBottom(30, true, footObject[5]);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}
void MapTextRead6()
{
	// 미로 6번 읽기
	FILE *fps6;
	fps6 = fopen("미로6.txt", "rt");
	if (fps6 == NULL) {
		printf("읽기 실패 \n");
	}
	char ch6;
	int i = 0;
	int j = 0;
	while (fscanf(fps6, "%c", &ch6) != EOF) {
		if (strchr(&ch6, '\n') == NULL) {
			mapData[5][i][j] = ch6;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps6);
}
void MapTextRead5()
{
	// 미로 5번 읽기
	FILE *fps5;
	fps5 = fopen("미로5.txt", "rt");
	if (fps5 == NULL) {
		printf("읽기 실패 \n");
	}
	char ch5;
	int i = 0;
	int j = 0;
	while (fscanf(fps5, "%c", &ch5) != EOF) {
		if (strchr(&ch5, '\n') == NULL) {
			mapData[4][i][j] = ch5;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps5);
}
void MapTextRead4()
{
	// 미로 4번 읽기
	FILE *fps4;
	fps4 = fopen("미로4.txt", "rt");
	if (fps4 == NULL) {
		printf("읽기 실패 \n");
	}
	char ch4;
	int i = 0;
	int j = 0;
	while (fscanf(fps4, "%c", &ch4) != EOF) {
		if (strchr(&ch4, '\n') == NULL) {
			mapData[3][i][j] = ch4;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps4);
}
void MapTextRead3()
{
	// 미로 3번 읽기
	FILE *fps3;
	fps3 = fopen("미로3.txt", "rt");
	if (fps3 == NULL) {
		printf("읽기 실패 \n");
	}
	char ch3;
	int i = 0;
	int j = 0;
	while (fscanf(fps3, "%c", &ch3) != EOF) {
		if (strchr(&ch3, '\n') == NULL) {
			mapData[2][i][j] = ch3;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps3);
}
void MapTextRead2()
{
	// 미로 2번 읽기
	FILE *fps2;
	fps2 = fopen("미로2.txt", "rt");
	if (fps2 == NULL) {
		printf("읽기 실패 \n");
	}
	char ch2;
	int i = 0;
	int j = 0;
	while (fscanf(fps2, "%c", &ch2) != EOF) {
		if (strchr(&ch2, '\n') == NULL) {
			mapData[1][i][j] = ch2;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);

	fclose(fps2);
}
void MapTextRead1()
{
	// 미로 1번 읽기
	FILE *fps1;
	fps1 = fopen("미로1.txt", "rt");
	if (fps1 == NULL) {
		printf("읽기 실패 \n");
	}
	char ch1;
	int i = 0;
	int j = 0;
	while (fscanf(fps1, "%c", &ch1) != EOF) {
		if (strchr(&ch1, '\n') == NULL) {
			mapData[0][i][j] = ch1;
			j++;
			if (j == 30) {
				j = 0;
				i++;
			}
		}
	}
	printf("%d, %d\n", i, j);
	fclose(fps1);
}

void DrawBlock(GLuint object[])
{
	glPushMatrix();
	int i = 0;
	for (int i = 0; i < 30; ++i) {  // 세로
		for (int j = 0; j < 30; ++j) {  // 가로
			if (mapData[changeMapNumber][i][j] == 88) {
				LocationBlock(object, i, changeYpos, j);
			}
		}
	}
	glPopMatrix();
}

void CollisionCheck()
{

	if (playerX <= 0)
		playerX = 0;
	// 좌표의 위치를 int형으로 받아서 맵데이터와 비교체크한다
	int X = (playerX / 480);
	int Z = (playerZ / 480);
	//□□□ < - 그림
	//□○□    ○ < - 플레이어
	//□□□    플레이어 기준으로 8방향 충돌 체크를 한다.
	if (changeDown == false) {   //  맵이 내려갈때 충돌체크가 없다.
		for (int z = Z - 1; z < Z + 2; z++)
		{
			for (int x = X - 1; x < X + 2; x++)
			{
				if (mapData[changeMapNumber][x][z] == 'X')
				{
					if ((x == X) && (z == Z))  // 기준 위치 체크 
					{
						if (playerX < x * 480 + 120)
							playerX = x * 480;
						else if (playerX > x * 480)
							playerX = x * 480 + 480;
						else if (playerZ < z * 480 + 60)
							playerZ = z * 480;
						else if (playerZ > z * 480)
							playerZ = z * 480 + 480;
					}
					else if ((x == X - 1) && (z == Z - 1)) //대각선 체크
					{
						if ((playerX < ((x * 480) + 480 + collisionDist)) && (playerZ < ((z * 480) + 480 + collisionDist)))
						{
							playerX = ((x * 480) + 480 + collisionDist);
							playerZ = ((z * 480) + 480 + collisionDist);
						}
					}
					else if ((x == X - 1) && (z == Z + 1))
					{
						if ((playerX < ((x * 480) + 480 + collisionDist)) && (((z * 480) - collisionDist) < playerZ))
						{
							playerX = ((x * 480) + 480 + collisionDist);
							playerZ = ((z * 480) - collisionDist);
						}
					}
					else if ((x == X + 1) && (z == Z - 1))
					{
						if ((((x * 480) - collisionDist) < playerX) && (playerZ < ((z * 480) + 480 + collisionDist)))
						{
							playerX = ((x * 480) - collisionDist);
							playerZ = ((z * 480) + 480 + collisionDist);
						}
					}
					else if ((x == X + 1) && (z == Z + 1))
					{
						if ((((x * 480) - collisionDist) < playerX) && (((z * 480) - collisionDist) < playerZ))
						{
							playerX = ((x * 480) - collisionDist);
							playerZ = ((z * 480) - collisionDist);
						}
					}
					else if (x == X - 1) // 기본 중앙에서 상하 좌우 체크(위의 그림 기준)
					{
						if (playerX < ((x * 480) + 480 + collisionDist))
							playerX = ((x * 480) + 480 + collisionDist);
					}
					else if (X + 1 == x)
					{
						if (((x * 480) - collisionDist) < playerX)
							playerX = ((x * 480) - collisionDist);
					}
					else if (z == Z - 1)
					{
						if (playerZ < ((z * 480) + 480 + collisionDist))
							playerZ = ((z * 480) + 480 + collisionDist);
					}
					else if (Z + 1 == z)
					{
						if (((z * 480) - collisionDist) < playerZ)
							playerZ = ((z * 480) - collisionDist);
					}
				}
			}
		}
	}
}

void show_Light() {
	GLfloat AmbientLight[] = { 0.1, 0.1, 0.1, 1.0f };
	//GLfloat DiffuseLight[] = { 1.0, 1.0, 1.0, 1.0f };
	GLfloat lightpos[] = { playerX, 200, playerZ, 1 };
	GLfloat SpecularLight[] = { 1, 1, 1, 1.0 };
	glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, (0, 0, 1));
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, (25));
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, 5);
}

void draw_UI(int CharX, int CharZ) {

	glPushMatrix();

	glViewport(0, 0, 1200, 800);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1200, 800, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glPopMatrix();

	glPushMatrix(); // 남은 시간 표시
	glColor3f(255.0f,255.0f,255.0f);
	glTranslatef(550, 30, 0);
	//glScalef(2.0f, 2.0f, 2.0f);
	glRasterPos2f(0, 0);
	glColor3f(255.0f, 255.0f, 255.0f);
	sprintf(drawTimeCount, "Time remaining until maze is changed : %d", timeCount);
	glColor3f(255.0f, 255.0f, 255.0f);
	int len = (int)strlen(drawTimeCount);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, drawTimeCount[i]);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(990, 0, 0);
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			int dataX = (i * 7), dataY = (i * 7) + 7;
			int LimitH = (j * 7) + 7;
			int char_X = (CharX / 480), char_Z = (CharZ / 480);  // 좌표값 계산
			glBegin(GL_POLYGON);
			if (i == char_X && j == char_Z) {  // 캐릭터 위치 표현
				glColor3f(0, 10, 0);
			}
			else if (i > 12 && i < 17 && j>12 && j < 17) { // 세이프티존
				glColor3f(0, 10, 10);
			}
			else if (i == 29 && j == 14) { // 탈출 지점
				glColor3f(0, 10, 7);
			}
			else {
				glColor3f(0.1, 0.1, 0.1);  //나머지 색 
			}
			// 그리기
			glVertex3f(dataX, 0, 0);
			glVertex3f(dataX, LimitH, 0);
			glVertex3f(dataY, LimitH, 0);
			glVertex3f(dataY, 0, 0);
			glEnd();
		}
	}
	glPopMatrix();
}

void FlashLight()
{
	glPushMatrix();
	glTranslatef(0, 60, 0);
	glRotatef(-rightSholderX - 90, 1, 0, 0);
	glTranslatef(0, -15, 50);

	// 전등 몸통 부분
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.2);
	glTranslatef(-10, -10, 35);
	glScalef(0.35, 0.35, 0.5);
	glutSolidCube(40);
	glPopMatrix();

	// 전등 머리 부분
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-10, -10, 55);
	glScalef(0.35, 0.35, 0.5);
	glutSolidCube(40);
	glPopMatrix();
	glPopMatrix();
}