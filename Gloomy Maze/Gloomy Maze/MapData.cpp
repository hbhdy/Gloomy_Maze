#include "Define.h"


void DrawGround(GLuint object)
{

	glPushMatrix();
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			LocationGround(object, i, 0, j);
		}
	}
	glPopMatrix();

}
void LocationGround(GLuint object, int x, int y, int z)
{
	glPushMatrix();
	glTranslatef(480 * x, y, 480 * z);
	SetGround(240, object);
	glPopMatrix();
}

void SetGround(int size, GLuint object)  // TOP ±âÁØ
{
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, object);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-size, 0, size);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(size, 0, size);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(size, 0, -size);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-size, 0, -size);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void LocationBlock(GLuint object[], int x, int y, int z)
{
	glPushMatrix();
	glTranslatef(480 * x, y, 480 * z);
	SetBlock(240, object);
	glPopMatrix();
}


void SetBlock(int size, GLuint object[]) {
	DrawBlockFront(size, false, object[0]);
	DrawBlockBack(size, false, object[1]);
	DrawBlockLeft(size, false, object[2]);
	DrawBlockRight(size, false, object[3]);
	DrawBlockTop(size, false, object[4]);
	//DrawBlockBottom(size, false, object[5]);
}