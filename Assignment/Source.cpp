
#include <Windows.h>
#include <gl/GL.h>
#include <stdio.h>
#include <math.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

GLUquadricObj *var = NULL;
int count = 0;
double rotateBi = 90, rotateBii = -90;
double upperLegAngle = 0;

float amb[] = { 1,1,1,0 };
float diff[] = { (float)0 / 255,(float)191 / 255,(float)255 / 255 };
float pos[] = { 1,1,1 };

float amb2[] = { 1,1,1,-1 };
float diff2[] = { 1,0,0,0 };
float pos2[] = { 0,0,0 };

boolean upperlegcond = true, lowerlegcond = true;
GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

float lowerleftlegx = -0.15, lowerleftlegy = -0.3, lowerleftlegz = 0;
float lowerrightlegx = 0.15, lowerrightlegy = -0.3, lowerrightlegz = 0;
float rightleglogox = 0, rightleglogoy = 0, rightleglogoz = 0;
float leftleglogox = 0, leftleglogoy = 0, leftleglogoz = 0;

float shieldhandx = 0.4, shieldhandy = 0.5, shieldhandz = 0;
float shieldx = -0.5, shieldy = -0.04, shieldz = 0;
float lazer_height = 0;
float zoom = 0;
float weaponrotatecamy = 0;
float weaponrotatecamz = 0;
float shieldrotatecamy = 0;
float shieldrotatecamz = 0;
float shieldrotatecamx = 0;
float rotateCam = 0;
float evorotateCam = 0;
float capeAngle = 0, capeX = 1, capeY = 0, capeZ = 0;

int evo_slices = 0;
int evo_stacks = 0;

float walk_translatex = 0, walk_translatez = 0;
boolean invi = false;
boolean evo_success = false, doneRotate = false;
boolean evolved = false;
boolean checkzoom = false;
GLuint* textures = new GLuint[8];
BITMAP image[8];


float lowerllegAngle = 90;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: // enable all the key on keyboard to be pressed
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_LEFT) {
			if (rotateCam <= 90) {
				rotateCam += 2;
				if (capeAngle < 10) {
					capeAngle += 1;
					capeY = -0.1;
					capeZ = -0.1;
				}
			}
			else {
				if (walk_translatex > -0.5) {
					walk_translatex -= 0.01;
				}
				while (capeAngle != 0) {
					capeAngle = 0;
					capeY = 0;
					capeZ = 0;
				}

			}
			if (upperLegAngle == 30) {
				upperlegcond = false;

			}
			else if (upperLegAngle == -30)
			{
				upperlegcond = true;
			}
			if (upperlegcond) {
				upperLegAngle += 10;

				lowerleftlegy += 0.01;
				lowerleftlegz += 0.06;
				leftleglogoy += 0.01;
				leftleglogoz += 0.06;

				lowerrightlegy -= 0.01;
				lowerrightlegz -= 0.06;
				rightleglogoy -= 0.01;
				rightleglogoz -= 0.06;
			}
			else
			{
				upperLegAngle -= 10;

				lowerleftlegy -= 0.01;
				lowerleftlegz -= 0.06;
				leftleglogoy -= 0.01;
				leftleglogoz -= 0.06;

				lowerrightlegy += 0.01;
				lowerrightlegz += 0.06;
				rightleglogoy += 0.01;
				rightleglogoz += 0.06;
			}
		}
		else if (wParam == VK_RIGHT) {
			if (rotateCam >= -90) {
				rotateCam -= 2;
				if (capeAngle < 10) {
					capeAngle += 1;
					capeY = -0.1;
					capeZ = -0.1;
				}
			}
			else {
				if (walk_translatex < 0.5) {
					walk_translatex += 0.01;
				}
				while (capeAngle != 0) {
					capeAngle -= 0.5;
					capeY = 0;
					capeZ = 0;
				}

			}

			if (upperLegAngle == 30) {
				upperlegcond = false;

			}
			else if (upperLegAngle == -30)
			{
				upperlegcond = true;
			}
			if (upperlegcond) {
				upperLegAngle += 10;
				lowerleftlegy += 0.01;
				lowerleftlegz += 0.06;
				leftleglogoy += 0.01;
				leftleglogoz += 0.06;

				lowerrightlegy -= 0.01;
				lowerrightlegz -= 0.06;
				rightleglogoy -= 0.01;
				rightleglogoz -= 0.06;


			}
			else
			{
				upperLegAngle -= 10;
				lowerleftlegy -= 0.01;
				lowerleftlegz -= 0.06;
				leftleglogoy -= 0.01;
				leftleglogoz -= 0.06;

				lowerrightlegy += 0.01;
				lowerrightlegz += 0.06;
				rightleglogoy += 0.01;
				rightleglogoz += 0.06;
			}

		}
		else if (wParam == VK_UP) {
			if (rotateCam >= -180) {
				rotateCam -= 2;
				if (capeAngle < 10) {
					capeAngle += 1;
					capeY = -0.1;
					capeZ = -0.1;
				}
			}
			else {
				if (walk_translatez > -1.0) {
					walk_translatez -= 0.01;
				}
				while (capeAngle != 0) {
					capeAngle -= 0.5;
					capeY = 0;
					capeZ = 0;
				}

			}

			if (upperLegAngle == 30) {
				upperlegcond = false;

			}
			else if (upperLegAngle == -30)
			{
				upperlegcond = true;
			}
			if (upperlegcond) {
				upperLegAngle += 10;
				lowerleftlegy += 0.01;
				lowerleftlegz += 0.06;
				leftleglogoy += 0.01;
				leftleglogoz += 0.06;

				lowerrightlegy -= 0.01;
				lowerrightlegz -= 0.06;
				rightleglogoy -= 0.01;
				rightleglogoz -= 0.06;


			}
			else
			{
				upperLegAngle -= 10;
				lowerleftlegy -= 0.01;
				lowerleftlegz -= 0.06;
				leftleglogoy -= 0.01;
				leftleglogoz -= 0.06;

				lowerrightlegy += 0.01;
				lowerrightlegz += 0.06;
				rightleglogoy += 0.01;
				rightleglogoz += 0.06;
			}
		}
		else if (wParam == VK_DOWN) {
			if (rotateCam < 0) {
				rotateCam += 2;
				if (capeAngle < 10) {
					capeAngle += 1;
					capeY = -0.1;
					capeZ = -0.1;
				}
			}
			else {
				if (walk_translatez < 1.0) {
					walk_translatez += 0.01;
				}
				while (capeAngle != 0) {
					capeAngle -= 0.5;
					capeY = 0;
					capeZ = 0;
				}

			}

			if (upperLegAngle == 30) {
				upperlegcond = false;

			}
			else if (upperLegAngle == -30)
			{
				upperlegcond = true;
			}
			if (upperlegcond) {
				upperLegAngle += 10;
				lowerleftlegy += 0.01;
				lowerleftlegz += 0.06;
				leftleglogoy += 0.01;
				leftleglogoz += 0.06;

				lowerrightlegy -= 0.01;
				lowerrightlegz -= 0.06;
				rightleglogoy -= 0.01;
				rightleglogoz -= 0.06;


			}
			else
			{
				upperLegAngle -= 10;
				lowerleftlegy -= 0.01;
				lowerleftlegz -= 0.06;
				leftleglogoy -= 0.01;
				leftleglogoz -= 0.06;

				lowerrightlegy += 0.01;
				lowerrightlegz += 0.06;
				rightleglogoy += 0.01;
				rightleglogoz += 0.06;
			}
		}
		else if (wParam == VK_SPACE) {
			lowerleftlegx = -0.15;
			lowerleftlegy = -0.3;
			lowerleftlegz = 0;
			lowerrightlegx = 0.15;
			lowerrightlegy = -0.3;
			lowerrightlegz = 0;
			rightleglogox = 0;
			rightleglogoy = 0;
			rightleglogoz = 0;
			leftleglogox = 0;
			leftleglogoy = 0;
			leftleglogoz = 0;
			upperLegAngle = 0;
			shieldhandx = 0.4;
			shieldhandy = 0.5;
			shieldhandz = 0;
			lazer_height = 0;
			evo_stacks = 0;
			evo_slices = 0;

			walk_translatex = 0;
			walk_translatez = 0;

			shieldrotatecamy = 0;
			shieldrotatecamz = 0;
			weaponrotatecamy = 0;
			weaponrotatecamz = 0;
			rotateCam = 0;
			evorotateCam = 0;
			capeAngle = 0, capeX = 1, capeY = 0, capeZ = 0;
		}
		else if (wParam == 'L') {
			if (!glIsEnabled(GL_LIGHTING)) {
				glEnable(GL_LIGHTING);
			}
			else {
				glDisable(GL_LIGHTING);
			}
		}
		else if (wParam == 'V') { //Attack shield
			if (!evolved) {
				if (shieldrotatecamy != -90) {
					shieldrotatecamy -= 1;
				}
				else {
					if (shieldrotatecamz != 50) {
						shieldrotatecamz += 1;
						if (rotateCam != -40) {
							rotateCam -= 1;
						}
						else {
							if (lazer_height < 1) {
								lazer_height += 0.1;
							}
						}
					}
				}
			}
			else {
				if (shieldrotatecamy != -10) {
					shieldrotatecamy -= 1;
				}
				if (shieldrotatecamz != -5) {
					shieldrotatecamz -= 1;
				}
				if (shieldrotatecamx != 5) {
					shieldrotatecamx += 1;
				}
				if (rotateCam != -40) {
					rotateCam -= 1;
				}
				else {
					if (lazer_height < 1) {
						lazer_height += 0.1;
					}
				}
			}
		}
		else if (wParam == 'B') { //Defend Gesture
			if (!evolved) {
				if (lazer_height == 0) {
					if (shieldrotatecamz != 0) {
						shieldrotatecamz -= 1;
						if (rotateCam != -0) {
							rotateCam += 1;
						}
					}
					else {
						if (shieldrotatecamy != 0) {
							shieldrotatecamy += 1;
						}
					}

				}
			}
			else {
				if (lazer_height == 0) {
					if (shieldrotatecamy != -0) {
						shieldrotatecamy += 1;
					}
					if (shieldrotatecamz != 0) {
						shieldrotatecamz += 1;
					}
					if (shieldrotatecamx != 0) {
						shieldrotatecamx -= 1;
					}
					if (rotateCam != 0) {
						rotateCam += 1;
					}
				}
			}
		}
		else if (wParam == 'C') { //Lazer Fire

			if (lazer_height < 1) {
				lazer_height += 0.1;
			}

		}
		else if (wParam == 'E') {
			if (evorotateCam < 4 && evo_success == false) {
				evorotateCam += 0.03;
				evo_slices += 1;
				evo_stacks += 1;
				pos2[0] = 0;
				pos2[1] = -1;
				pos2[2] = 0;
				glEnable(GL_LIGHTING);
			}
			else {
				evo_success = true;
				lazer_height = 0;
				evo_stacks = 0;
				evo_slices = 0;
				evorotateCam = 0;
				weaponrotatecamy = 0;
				pos2[0] = 0;
				pos2[1] = 0;
				pos2[2] = 0;
				glDisable(GL_LIGHTING);
			}
		}
		else if (wParam == 'R') {
			if (evorotateCam > -4 && evo_success == true) {
				evorotateCam -= 0.03;
				evo_slices += 1;
				evo_stacks += 1;
				pos2[0] = 0;
				pos2[1] = -1;
				pos2[2] = 0;
				glEnable(GL_LIGHTING);
			}
			else {
				evo_success = false;
				lazer_height = 0;
				evo_stacks = 0;
				evo_slices = 0;
				weaponrotatecamy = 0;
				evorotateCam = 0;
				pos2[0] = 0;
				pos2[1] = 0;
				pos2[2] = 0;
				glDisable(GL_LIGHTING);
			}
		}
		else if (wParam == 'O') { //Attack weapon

			if (!evolved) {
				if (weaponrotatecamy != -70) {
					weaponrotatecamy -= 1;
				}
			}
			else
			{
				if (rotateCam >= -90) {
					rotateCam -= 1;
				}
				if (walk_translatex > -0.5) {
					walk_translatex -= 0.01;
				}
				if (weaponrotatecamy != -50) {
					weaponrotatecamy -= 1;
				}
				if (rotateCam == -90) {
					doneRotate = true;
				}
				if (doneRotate) {
					if (walk_translatex < 0.5) {
						walk_translatex += 0.1;
						/*if (lazer_height < 1) {
							lazer_height += 0.1;
						}*/
					}
				}
			}
		}
		else if (wParam == 'P') {
			if (!evolved) {
				if (weaponrotatecamy != 0) {
					weaponrotatecamy += 1;
				}
			}
			else
			{
				if (walk_translatex > 0) {
					walk_translatex -= 0.01;
				}
				if (walk_translatex < 0) {
					walk_translatex += 0.01;
				}
				if (rotateCam != 0) {
					rotateCam += 1;
				}
				if (weaponrotatecamy != 0) {
					weaponrotatecamy += 1;
				}
			}

		}
		else if (wParam == 'T') {//'Lighting up'
			pos2[0] = 0;
			pos2[1] = 1;
			pos2[2] = 0;

		}
		else if (wParam == 'F') {//'Lighting left'
			pos2[0] = -1;
			pos2[1] = 0;
			pos2[2] = 0;

		}
		else if (wParam == 'G') {//'Lighting down'
			pos2[0] = 0;
			pos2[1] = -1;
			pos2[2] = 0;

		}
		else if (wParam == 'H') {//'Lighting right'
			pos2[0] = 1;
			pos2[1] = 0;
			pos2[2] = 0;
		}
		else if (wParam == 'W') {// Zoom in / out
			if (zoom > 0)
				zoom -= 1;
		}
		else if (wParam == 'S') {// Zoom out
			zoom += 1;
		}
		else if (wParam == 'A') {// Camera turn left
			rotateCam += 3;
		}
		else if (wParam == 'D') {// Camera turn right 
			rotateCam -= 3;
		}
		else if (wParam == 'L') {// Turn on / off the light
			if (!glIsEnabled(GL_LIGHTING)) {
				glEnable(GL_LIGHTING);
			}
			else {
				glDisable(GL_LIGHTING);
			}
		}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------



void loadTexture(GLuint texture, const char* filename) {
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
}

void duke_lower_leg() {
	if (evolved) {
		glEnable(GL_TEXTURE_2D);
	}

	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.05, 0.07, 0.4, 30, 30);
	gluDeleteQuadric(cylinder);

	if (evolved) {
		glDisable(GL_TEXTURE_2D);
	}
}

void duke_upper_leg() {
	if (evolved) {
		glEnable(GL_TEXTURE_2D);
	}

	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.07, 0.05, 0.4, 30, 30);
	gluDeleteQuadric(cylinder);

	if (evolved) {
		glDisable(GL_TEXTURE_2D);
	}
}
void duke_foot_logo() {
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3f((float)255 / 255, (float)0 / 255, (float)0 / 255);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.15f, -0.2f, 0.07f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.20f, -0.3f, 0.07f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.07f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.10f, -0.3f, 0.07f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void duke_foot_logo_ring() {
	glEnable(GL_TEXTURE_2D);

	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.06, 0.06, 0.03, 30, 30);
	gluDeleteQuadric(cylinder);

	glDisable(GL_TEXTURE_2D);
}
void duke_shield_lazer() {
	glEnable(GL_TEXTURE_2D);

	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	glTranslatef(-0.49, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	glRotatef(180, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	if (evo_success == true) {
		glBindTexture(GL_TEXTURE_2D, textures[5]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textures[4]);
	}
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.46, 0.46, lazer_height, 30, 30);
	gluDeleteQuadric(cylinder);

	glDisable(GL_TEXTURE_2D);
}
void duke_evo_sphere() {
	//glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(walk_translatex, 0, walk_translatez);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	//gluQuadricTexture(sphere, GL_TRUE);
	gluSphere(sphere, 1.0, evo_slices, evo_stacks);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);

}

void duke_hand() {
	glColor3f(1, 1, 1);
	glTranslatef(-0.4, -0.2, 0);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.07, 30, 30);
	gluDeleteQuadric(sphere);
	glTranslatef(0.4, 0.2, 0);
}

void duke_foots_logo() {
	glPushMatrix();
	glTranslatef(rightleglogox, rightleglogoy, rightleglogoz);
	duke_foot_logo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.3, 0, 0);
	glTranslatef(leftleglogox, leftleglogoy, leftleglogoz);
	duke_foot_logo();
	glPopMatrix();
}

void duke_logo_ring() {
	glColor3f((float)255 / 255, (float)255 / 255, (float)0 / 255);
	glPushMatrix();
	glTranslatef(0.15, -0.3, 0);
	glTranslatef(rightleglogox, rightleglogoy, rightleglogoz);
	glRotatef(180, 0, 1, 1);
	duke_foot_logo_ring();
	glLoadIdentity();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.15, -0.3, 0);
	glTranslatef(leftleglogox, leftleglogoy, leftleglogoz);
	glRotatef(180, 0, 1, 1);
	duke_foot_logo_ring();
	glLoadIdentity();
	glPopMatrix();
}

void duke_shield_tape() {
	glEnable(GL_TEXTURE_2D);

	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.075, 0.075, 0.04, 30, 30);
	gluDeleteQuadric(cylinder);

	glDisable(GL_TEXTURE_2D);
}

void duke_weapon_up_tape() {
	glEnable(GL_TEXTURE_2D);

	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.17, 0.19, 0.04, 30, 30);
	gluDeleteQuadric(cylinder);

	glDisable(GL_TEXTURE_2D);
}

void duke_weapon_down_tape() {
	glEnable(GL_TEXTURE_2D);

	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.135, 0.14, 0.04, 30, 30);
	gluDeleteQuadric(cylinder);

	glDisable(GL_TEXTURE_2D);
}


void duke_lower_legs() {
	duke_logo_ring();
	duke_foots_logo();
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	glPushMatrix();
	glTranslatef(lowerleftlegx, lowerleftlegy, lowerleftlegz);//left leg
	glRotatef(lowerllegAngle, 1, 0, 0);
	duke_lower_leg();

	glLoadIdentity();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(lowerrightlegx, lowerrightlegy, lowerrightlegz);//right leg
	glRotatef(lowerllegAngle, 1, 0, 0);
	duke_lower_leg();
	glLoadIdentity();
	glPopMatrix();
}

void duke_upper_legs() {
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	glPushMatrix();
	glTranslatef(0.15, 0, 0);
	glRotatef(upperLegAngle, 1, 0, 0);
	glRotatef(90, 1, 0, 0);
	duke_upper_leg();
	glLoadIdentity();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.15, 0, 0);
	glRotatef(-upperLegAngle, 1, 0, 0);
	glRotatef(90, 1, 0, 0);
	duke_upper_leg();
	glLoadIdentity();
	glPopMatrix();
}

void duke_foot() {
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);

	glColor3f((float)255 / 255, (float)0 / 255, (float)0 / 255);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.05, -0.7, 0.15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25, -0.7, 0.15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.25, -0.8, 0.15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.05, -0.8, 0.15);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.05, -0.7, -0.07);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.05, -0.7, 0.15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.05, -0.8, 0.15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.05, -0.8, -0.07);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.05, -0.7, -0.07);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25, -0.7, -0.07);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.25, -0.8, -0.07);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.05, -0.8, -0.07);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.25, -0.7, -0.07);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25, -0.7, 0.15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.25, -0.8, 0.15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.25, -0.8, -0.07);
	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.05, -0.7, -0.07);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25, -0.7, -0.07);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.25, -0.7, 0.15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.05, -0.7, 0.15);
	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.05, -0.8, -0.07);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25, -0.8, -0.07);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.25, -0.8, 0.15);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.05, -0.8, 0.15);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void duke_foots() {
	glPushMatrix();
	glTranslatef(rightleglogox, rightleglogoy, rightleglogoz);
	duke_foot();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.3, 0, 0);
	glTranslatef(leftleglogox, leftleglogoy, leftleglogoz);
	duke_foot();
	glPopMatrix();
}
void duke_waist() {
	glBegin(GL_QUADS);
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	//front
	glVertex3f(0.2, 0.1, 0.07);
	glVertex3f(0.05, 0, 0.07);
	glVertex3f(-0.05, 0, 0.07);
	glVertex3f(-0.2, 0.1, 0.07);
	//left
	glVertex3f(-0.2, 0.1, 0.07);
	glVertex3f(-0.2, 0.1, -0.07);
	glVertex3f(-0.05, 0, -0.07);
	glVertex3f(-0.05, 0, 0.07);
	//back
	glVertex3f(0.2, 0.1, -0.07);
	glVertex3f(0.05, 0, -0.07);
	glVertex3f(-0.05, 0, -0.07);
	glVertex3f(-0.2, 0.1, -0.07);
	//right
	glVertex3f(0.2, 0.1, -0.07);
	glVertex3f(0.2, 0.1, 0.07);
	glVertex3f(0.05, 0, 0.07);
	glVertex3f(0.05, 0, -0.07);
	//top
	glVertex3f(0.2, 0.1, -0.07);
	glVertex3f(-0.2, 0.1, -0.07);
	glVertex3f(-0.2, 0.1, 0.07);
	glVertex3f(0.2, 0.1, 0.07);
	//bottom
	glVertex3f(0.2, 0, -0.07);
	glVertex3f(-0.2, 0, 0.07);
	glVertex3f(-0.2, 0, 0.07);
	glVertex3f(0.2, 0, -0.07);
	glEnd();
}

void duke_chest() {
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	glBegin(GL_QUADS);
	//front
	glVertex3f(-0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(0.15, 0.25, 0.15);
	glVertex3f(-0.15, 0.25, 0.15);
	//left
	glVertex3f(-0.3, 0.45, -0.15);
	glVertex3f(-0.3, 0.45, 0.15);
	glVertex3f(-0.15, 0.25, 0.15);
	glVertex3f(-0.15, 0.25, -0.15);
	//back
	glVertex3f(-0.3, 0.45, -0.15);
	glVertex3f(0.3, 0.45, -0.15);
	glVertex3f(0.15, 0.25, -0.15);
	glVertex3f(-0.15, 0.25, -0.15);
	//right
	glVertex3f(0.3, 0.45, -0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(0.15, 0.25, 0.15);
	glVertex3f(0.15, 0.25, -0.15);
	//top
	glVertex3f(-0.3, 0.45, -0.15);
	glVertex3f(-0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, -0.15);
	//bottom
	glVertex3f(-0.15, 0.25, -0.15);
	glVertex3f(-0.15, 0.25, 0.15);
	glVertex3f(0.15, 0.25, 0.15);
	glVertex3f(0.15, 0.25, -0.15);
	glEnd();

	glBegin(GL_QUADS);
	//front
	glVertex3f(-0.3, 0.6, 0.15);
	glVertex3f(0.3, 0.6, 0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(-0.3, 0.45, 0.15);
	//left
	glVertex3f(-0.3, 0.6, -0.15);
	glVertex3f(-0.3, 0.6, 0.15);
	glVertex3f(-0.3, 0.45, 0.15);
	glVertex3f(-0.3, 0.45, -0.15);
	//back
	glVertex3f(-0.3, 0.6, -0.15);
	glVertex3f(0.3, 0.6, -0.15);
	glVertex3f(0.3, 0.45, -0.15);
	glVertex3f(-0.3, 0.45, -0.15);
	//right
	glVertex3f(0.3, 0.6, -0.15);
	glVertex3f(0.3, 0.6, 0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, -0.15);
	//top
	glVertex3f(-0.3, 0.6, -0.15);
	glVertex3f(-0.3, 0.6, 0.15);
	glVertex3f(0.3, 0.6, 0.15);
	glVertex3f(0.3, 0.6, -0.15);
	//bottom
	glVertex3f(-0.3, 0.45, -0.15);
	glVertex3f(-0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, -0.15);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glTranslatef(0, 0.5, 0.16);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	//front
	glTexCoord2f(-1.0f, 1.0f);
	glVertex2f(-0.1, -0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.1, -0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.11, -0.1);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(-0.21, -0.23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(-0.01, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.11, -0.1);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(0.21, -0.23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.01, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0, 0.04);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(-0.1, -0.09);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.1, -0.09);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void duke_evo_chest() {
	glBegin(GL_QUADS);
	//front
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.15, 0.25, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(-0.15, 0.25, 0.15);
	//left
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, -0.15);
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(-0.15, 0.25, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(-0.15, 0.25, -0.15);
	//back
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, -0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, -0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.15, 0.25, -0.15);
	glColor3f(1, 0, 0);
	glVertex3f(-0.15, 0.25, -0.15);
	//right
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, -0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.15, 0.25, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.15, 0.25, -0.15);
	//top
	glVertex3f(-0.3, 0.45, -0.15);
	glVertex3f(-0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, -0.15);
	//bottom
	glColor3f(0, 0, 0);
	glVertex3f(-0.15, 0.25, -0.15);
	glColor3f(1, 0, 0);
	glVertex3f(-0.15, 0.25, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.15, 0.25, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.15, 0.25, -0.15);
	glEnd();

	glBegin(GL_QUADS);
	//front
	glColor3f(1, 0, 0);
	glVertex3f(-0.3, 0.6, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.3, 0.6, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, 0.15);
	//left
	glColor3f(1, 0, 0);
	glVertex3f(-0.3, 0.6, -0.15);
	glColor3f(1, 0, 0);
	glVertex3f(-0.3, 0.6, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, -0.15);
	//back
	glColor3f(1, 0, 0);
	glVertex3f(-0.3, 0.6, -0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.3, 0.6, -0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, -0.15);
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.45, -0.15);
	//right
	glColor3f(1, 0, 0);
	glVertex3f(0.3, 0.6, -0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.3, 0.6, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.45, -0.15);
	//top
	glColor3f(0, 0, 0);
	glVertex3f(-0.3, 0.6, -0.15);
	glColor3f(1, 0, 0);
	glVertex3f(-0.3, 0.6, 0.15);
	glColor3f(1, 0, 0);
	glVertex3f(0.3, 0.6, 0.15);
	glColor3f(0, 0, 0);
	glVertex3f(0.3, 0.6, -0.15);
	//bottom
	glVertex3f(-0.3, 0.45, -0.15);
	glVertex3f(-0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, 0.15);
	glVertex3f(0.3, 0.45, -0.15);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glTranslatef(0, 0.5, 0.16);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	//front
	glTexCoord2f(-1.0f, 1.0f);
	glVertex2f(-0.1, -0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.1, -0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.11, -0.1);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(-0.21, -0.23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(-0.01, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.11, -0.1);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(0.21, -0.23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.01, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0, 0.04);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(-0.1, -0.09);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.1, -0.09);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}
//void duke_evo_chest() {
//	glBegin(GL_QUADS);
//	//front
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.15, 0.25, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.15, 0.25, 0.15);
//	//left
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, -0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.15, 0.25, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.15, 0.25, -0.15);
//	//back
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, -0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, -0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.15, 0.25, -0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.15, 0.25, -0.15);
//	//right
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, -0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.15, 0.25, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.15, 0.25, -0.15);
//	//top
//	glVertex3f(-0.3, 0.45, -0.15);
//	glVertex3f(-0.3, 0.45, 0.15);
//	glVertex3f(0.3, 0.45, 0.15);
//	glVertex3f(0.3, 0.45, -0.15);
//	//bottom
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.15, 0.25, -0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.15, 0.25, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.15, 0.25, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.15, 0.25, -0.15);
//	glEnd();
//
//	glBegin(GL_QUADS);
//	//front
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.3, 0.6, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.3, 0.6, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, 0.15);
//	//left
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.3, 0.6, -0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.3, 0.6, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, -0.15);
//	//back
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.3, 0.6, -0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.3, 0.6, -0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, -0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.45, -0.15);
//	//right
//	glColor3f(1, 0, 0);
//	glVertex3f(0.3, 0.6, -0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.3, 0.6, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.45, -0.15);
//	//top
//	glColor3f(1, 1, 1);
//	glVertex3f(-0.3, 0.6, -0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(-0.3, 0.6, 0.15);
//	glColor3f(1, 0, 0);
//	glVertex3f(0.3, 0.6, 0.15);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.3, 0.6, -0.15);
//	//bottom
//	glVertex3f(-0.3, 0.45, -0.15);
//	glVertex3f(-0.3, 0.45, 0.15);
//	glVertex3f(0.3, 0.45, 0.15);
//	glVertex3f(0.3, 0.45, -0.15);
//	glEnd();
//}

void duke_mouth() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);

	glBegin(GL_QUADS);
	glColor3f((float)105 / 255, (float)105 / 255, (float)105 / 255);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0.12);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.8, 0.12);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.12);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0.12);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0.12);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0.12);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.8, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.03, 0.8, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.8, 0.12);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.12);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);
	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0.12);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.8, 0.12);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.8, 0);
	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.68, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0.68, 0.12);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.12);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);

	glColor3f((float)0 / 255, (float)0 / 255, (float)0 / 255);
	//first
	glVertex3f(-0.02, 0.78, 0.125);
	glVertex3f(0.02, 0.78, 0.125);
	glVertex3f(0.02, 0.76, 0.125);
	glVertex3f(-0.02, 0.76, 0.125);

	//second
	glVertex3f(-0.02, 0.75, 0.125);
	glVertex3f(0.02, 0.75, 0.125);
	glVertex3f(0.02, 0.73, 0.125);
	glVertex3f(-0.02, 0.73, 0.125);

	//third
	glVertex3f(-0.02, 0.72, 0.125);
	glVertex3f(0.02, 0.72, 0.125);
	glVertex3f(0.02, 0.7, 0.125);
	glVertex3f(-0.02, 0.7, 0.125);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void duke_corn() {
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//front
	glVertex3f(-0.02, 0.85, 0.05);
	glVertex3f(0.02, 0.85, 0.05);
	glVertex3f(0.02, 0.8, 0.05);
	glVertex3f(-0.02, 0.8, 0.05);
	//left
	glVertex3f(-0.02, 0.95, -0.05);
	glVertex3f(-0.02, 0.9, 0.05);
	glVertex3f(-0.02, 0.8, 0.05);
	glVertex3f(-0.02, 0.8, -0.05);
	//back
	glVertex3f(-0.02, 0.95, -0.05);
	glVertex3f(0.02, 0.95, -0.05);
	glVertex3f(0.02, 0.8, -0.05);
	glVertex3f(-0.02, 0.8, -0.05);
	//right
	glVertex3f(0.02, 0.95, -0.05);
	glVertex3f(0.02, 0.9, 0.05);
	glVertex3f(0.02, 0.8, 0.05);
	glVertex3f(0.02, 0.8, -0.05);
	//top
	glVertex3f(-0.02, 0.95, -0.05);
	glVertex3f(-0.02, 0.9, 0.05);
	glVertex3f(0.02, 0.9, 0.05);
	glVertex3f(0.02, 0.95, -0.05);
	//bottom
	glVertex3f(-0.02, 0.8, -0.05);
	glVertex3f(-0.02, 0.8, 0.05);
	glVertex3f(0.02, 0.8, 0.05);
	glVertex3f(0.02, 0.8, -0.05);
	glEnd();
}

void duke_down_mask() {
	glEnable(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.9, 0.13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.9, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0.13);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.9, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0.9, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.9, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.9, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0);
	//right
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.9, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.03, 0.9, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);
	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.9, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.9, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.9, 0.13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.9, 0);
	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.68, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.68, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void duke_up_mask() {
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0.13);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.75, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0.13);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.75, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.68, 0);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.03, 0.75, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.03, 0.75, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);
	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0.8, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.75, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.75, 0);
	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.03, 0.68, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0.68, 0.13);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0.13);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.68, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void duke_shoulder() {
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 0, 0);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	gluQuadricTexture(sphere, GL_TRUE);
	gluSphere(sphere, 0.12, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

//void duke_lowerarm() {
//	glBegin(GL_QUADS);
//	glColor3f(1, 1, 1);
//	//front
//	glVertex3f(-0.45, 0.15, 0.05);
//	glVertex3f(-0.35, 0.15, 0.05);
//	glVertex3f(-0.35, -0.15, 0.05);
//	glVertex3f(-0.45, -0.15, 0.05);
//	//left
//	glVertex3f(-0.45, 0.15, -0.05);
//	glVertex3f(-0.45, 0.15, 0.05);
//	glVertex3f(-0.45, -0.15, 0.05);
//	glVertex3f(-0.45, -0.15, -0.05);
//	//back
//	glVertex3f(-0.45, 0.15, -0.05);
//	glVertex3f(-0.35, 0.15, -0.05);
//	glVertex3f(-0.35, -0.15, -0.05);
//	glVertex3f(-0.45, -0.15, -0.05);
//	//right
//	glVertex3f(-0.35, 0.15, -0.05);
//	glVertex3f(-0.35, 0.15, 0.05);
//	glVertex3f(-0.35, -0.15, 0.05);
//	glVertex3f(-0.35, -0.15, -0.05);
//	//top
//	glVertex3f(-0.45, 0.15, -0.05);
//	glVertex3f(-0.45, 0.15, 0.05);
//	glVertex3f(-0.35, 0.15, 0.05);
//	glVertex3f(-0.35, 0.15, -0.05);
//	//bottom
//	glVertex3f(-0.45, -0.15, -0.05);
//	glVertex3f(-0.45, -0.15, 0.05);
//	glVertex3f(-0.35, -0.15, 0.05);
//	glVertex3f(-0.35, -0.15, -0.05);
//	glEnd();
//}
void duke_lowerarm() {
	if (evolved) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[6]);
	}

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.15, 0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.35, 0.15, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, -0.15, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.45, -0.15, 0.05);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.15, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.45, 0.15, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.45, -0.15, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.45, -0.15, -0.05);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.15, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.35, 0.15, -0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, -0.15, -0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.45, -0.15, -0.05);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.35, 0.15, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.35, 0.15, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, -0.15, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.35, -0.15, -0.05);
	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.15, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.45, 0.15, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, 0.15, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.35, 0.15, -0.05);
	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, -0.15, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.45, -0.15, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, -0.15, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.35, -0.15, -0.05);
	glEnd();
	if (evolved) {
		glDisable(GL_TEXTURE_2D);
	}
}
void duke_upperarm() {
	if (evolved) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[6]);
	}

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.5, 0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.35, 0.5, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, 0.2, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.45, 0.2, 0.05);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.5, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.45, 0.5, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.45, 0.2, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.45, 0.2, -0.05);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.5, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.35, 0.5, -0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, 0.2, -0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.45, 0.2, -0.05);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.35, 0.5, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.35, 0.5, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, 0.2, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.35, 0.2, -0.05);
	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.5, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.45, 0.5, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, 0.5, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.35, 0.5, -0.05);
	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.45, 0.2, -0.05);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.45, 0.2, 0.05);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.35, 0.2, 0.05);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.35, 0.2, -0.05);
	glEnd();
	if (evolved) {
		glDisable(GL_TEXTURE_2D);
	}
}

void duke_weaapon() {

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 1, 1);
	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	glTranslatef(0.4, 0.1, 0);
	glRotatef(180, 0, 1, 1);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.13, 0.18, 0.2, 30, 30);
	gluDeleteQuadric(cylinder);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	/*glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);

	if (pos[1] == 1) {
		pos[0] = -1;
		pos[1] = 0;
		pos[2] = 0;
	}
	else if (pos[0] == -1) {
		pos[0] = 0;
		pos[1] = -1;
		pos[2] = 0;
	}
	else if (pos[1] == -1) {
		pos[0] = 1;
		pos[1] = 0;
		pos[2] = 0;
	}
	else if (pos[0] == 1) {
		pos[0] = 0;
		pos[1] = 1;
		pos[2] = 0;
	}
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	*/

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 1, 1);
	GLUquadricObj * cylinder2 = NULL;
	cylinder2 = gluNewQuadric();
	glTranslatef(0.4, -0.7, 0);
	glRotatef(180, 0, 1, 1);
	gluQuadricDrawStyle(cylinder2, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder2, GL_TRUE);
	gluCylinder(cylinder2, 0.0001, 0.13, 0.8, 30, 30);
	gluDeleteQuadric(cylinder2);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0.4, 0.26, 0);
	glRotatef(180, 0, 1, 1);
	duke_weapon_up_tape();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0.4, 0.1, 0);
	glRotatef(180, 0, 1, 1);
	duke_weapon_down_tape();
	glPopMatrix();
}

void duke_shield() {
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f((float)255 / 255, (float)255 / 255, (float)0 / 255);
	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	glTranslatef(-0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.45, 0.55, 0.09, 30, 30);
	gluDeleteQuadric(cylinder);
	glPopMatrix();


	glPushMatrix();
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	GLUquadricObj * cylinder2 = NULL;
	cylinder2 = gluNewQuadric();
	glTranslatef(-0.69, -0.04, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	gluQuadricDrawStyle(cylinder2, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder2, GL_TRUE);
	gluCylinder(cylinder2, 0, 0.46, 0.2, 30, 30);
	gluDeleteQuadric(cylinder2);
	glPopMatrix();

	glPushMatrix();
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	GLUquadricObj * cylinder3 = NULL;
	cylinder3 = gluNewQuadric();
	glTranslatef(-0.57, -0.04, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	gluQuadricDrawStyle(cylinder3, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder3, GL_TRUE);
	gluCylinder(cylinder3, 0.2, 0.2, 0.15, 30, 30);
	gluDeleteQuadric(cylinder3);
	glPopMatrix();

	glPushMatrix();
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	GLUquadricObj * cylinder4 = NULL;
	cylinder4 = gluNewQuadric();
	glTranslatef(-0.57, -0.04, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	gluQuadricDrawStyle(cylinder4, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	gluQuadricTexture(cylinder4, GL_TRUE);
	gluCylinder(cylinder4, 0.1, 0.1, 0.12, 30, 30);
	gluDeleteQuadric(cylinder4);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-0.4, 0, 0);
	glRotatef(180, 0, 1, 1);
	duke_shield_tape();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	duke_shield_lazer();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(90, 0, 0.1, 0);
	//glRotatef(-90, 0, 0, 0.1);

	glTranslatef(0, 0.1, -0.7);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glBegin(GL_TRIANGLES);
	//front
	glTexCoord2f(-1.0f, 1.0f);
	glVertex2f(-0.1, -0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.1, -0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.11, -0.1);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(-0.21, -0.23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(-0.01, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.11, -0.1);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(0.21, -0.23);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.01, -0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0, 0.04);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex2f(-0.1, -0.09);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.1, -0.09);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void duke_eyes() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.06, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}

void duke_eyeball() {
	glPushMatrix();
	glColor3f(1, 1, 0);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.05, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}

void duke_iris() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.015, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}

void duke_head() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	glTranslatef(0, 0.75, 0);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.115, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.65, 0.4, 0);
	glRotatef(70, 0, 0, 1);
	duke_mouth();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.65, 0.4, 0);
	glRotatef(-70, 0, 0, 1);
	duke_mouth();
	glPopMatrix();

	glPushMatrix();
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	glTranslatef(0, 0.54, 0);
	glRotatef(180, 0, 1, 1);
	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.115, 0.115, 0.2, 30, 30);
	gluDeleteQuadric(cylinder);
	glLoadIdentity();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.65, 0.53, 0);
	glRotatef(70, 0, 0, 1);
	duke_down_mask();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.65, 0.53, 0);
	glRotatef(-70, 0, 0, 1);
	duke_down_mask();
	glPopMatrix();

	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	glTranslatef(0.12, 0.14, -0.1);
	duke_up_mask();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20, 0, 0, 1);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.12, 0.14, 0);
	duke_up_mask();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.03, 0.75, 0.06);
	duke_eyes();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.03, 0.75, 0.06);
	duke_eyes();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.035, 0.75, 0.07);
	duke_eyeball();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.035, 0.75, 0.07);
	duke_eyeball();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.75, 0.105);
	duke_iris();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.05, 0.75, 0.105);
	duke_iris();
	glPopMatrix();
}

void duke_left_hand() {
	//glRotatef(-90, 1, 0, 0);

	glPushMatrix();
	glTranslatef(-0.4, 0.5, 0);
	duke_shoulder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, 0, 0);
	duke_upperarm();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.4, 0.19, 0);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.07, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 0.2, 0);
	glRotatef(weaponrotatecamy, 1, 0, 0);
	glTranslatef(0.4, -0.2, 0);
	glTranslatef(0.4, 0.2, 1);
	glRotatef(weaponrotatecamz, 0, 0, 1);
	glTranslatef(-0.4, -0.2, -1);

	glPushMatrix();
	glTranslatef(0.8, 0, 0);
	if (evo_success) {// adjust hand in here, i dk how to translate
		glTranslatef(-0.4, 0.2, 0);
		glRotatef(-45, 1, 1, 0);
		glTranslatef(0.4, -0.2, 0);
	}
	duke_lowerarm();
	duke_hand();
	glPopMatrix();

	if (!evo_success) {
		glPushMatrix();
		glTranslatef(0, -0.1, 0);

		duke_weaapon();
		glPopMatrix();
	}
	else {

		glPushMatrix();
		glRotatef(-45, 1, 1, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);//crimson- comment for normal
		glTranslatef(0, -0.25, -0.2);//crimson-comment for normal
		duke_weaapon();
		glPopMatrix();
		glPushMatrix();//crimson-comment for normal
		glRotatef(-90, 1, 0, 0);//crimson- comment for normal
		glTranslatef(0, 0.45, -0.2);//crimson-comment for normal
		glRotatef(180, 1, 0, 0);//crimson-comment for normal
		duke_weaapon();//crimson-comment for normal
		glPopMatrix();//crimson-comment for normal
		glPopMatrix();
	}
	glPopMatrix();
}

void duke_right_hand() {
	glPushMatrix();
	glTranslatef(0.4, 0.5, 0);
	duke_shoulder();
	glPopMatrix();

	glPushMatrix();
	duke_upperarm();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.4, 0.19, 0);
	GLUquadricObj * sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.07, 30, 30);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	glPushMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 0.2, 0);
	glRotatef(shieldrotatecamy, 1, 0, 0);
	glTranslatef(-0.4, -0.2, 0);
	glTranslatef(-0.4, 0.2, 1);
	glRotatef(shieldrotatecamz, 0, 0, 1);
	glTranslatef(0.4, -0.2, -1);
	glTranslatef(-0.4, 0, 1);
	glRotatef(shieldrotatecamx, 1, 0, 0);
	glTranslatef(0.4, 0, -1);
	if (evo_success == true) {
		glTranslatef(-0.4, 0.2, 0);
		glRotatef(30, 0, 1, 0);
		glTranslatef(0.4, -0.2, 0);
	}
	duke_lowerarm();
	duke_shield();
	duke_hand();
	glPopMatrix();
}

void duke_belt() {
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f((float)255 / 255, (float)0 / 255, (float)0 / 255);
	glTranslatef(0, 0.1, 0);
	glRotatef(180, 0, 1, 1);
	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, 0.07, 0.07, 0.08, 30, 30);
	gluDeleteQuadric(cylinder);
	glLoadIdentity();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void duke_body() {
	glPushMatrix();
	glColor3f((float)255 / 255, (float)255 / 255, (float)255 / 255);
	glTranslatef(0, 0.17, 0);
	glRotatef(180, 0, 1, 1);
	GLUquadricObj * cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.06, 0.06, 0.08, 30, 30);
	gluDeleteQuadric(cylinder);
	glLoadIdentity();
	glPopMatrix();
	glPushMatrix();
	if (evo_success == true) {
		duke_evo_chest();
	}
	else {
		duke_chest();
	}
	glPopMatrix();
}

void duke_cape() {
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);


	glColor3f(1, 0, 0);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1, 0.6, -0.15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.1, 0.6, -0.15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.3, -0.3, -0.3);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3, -0.3, -0.3);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.3, -0.3, -0.3);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.3, -0.3, -0.3);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.3, -0.6, -0.3);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.3, -0.6, -0.3);

	glEnd();

	glDisable(GL_TEXTURE_2D);

}
void duke_wing() {
	//glEnable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	//glTranslatef()
	//glBindTexture(GL_TEXTURE_2D, textures[1]);

	glColor3f(1, 0, 0);
	//front
	glVertex3f(0, 0.6, -0.15);
	glColor3f(1, 1, 1);
	glVertex3f(-0.8, 0.8, -0.8);
	glColor3f(0.2, 0, 0);
	glVertex3f(-0.2, 0.4, -0.3);
	glColor3f(1, 1, 1);
	glVertex3f(-0.6, 0.5, -0.8);
	glColor3f(0.3, 0, 0);
	glVertex3f(-0.2, 0.3, -0.3);
	glColor3f(1, 1, 1);
	glVertex3f(-0.6, 0.1, -0.8);
	glColor3f(0.4, 0, 0);
	glVertex3f(-0.2, 0.2, -0.3);
	glColor3f(1, 1, 1);
	glVertex3f(-0.8, -0.2, -0.8);
	glColor3f(0.5, 0, 0);
	glVertex3f(-0.2, 0, -0.2);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0.3, -0.15);

	glEnd();

	glBegin(GL_POLYGON);
	//glTranslatef()
	//glBindTexture(GL_TEXTURE_2D, textures[1]);

	glColor3f(1, 0, 0);
	//front
	glVertex3f(0, 0.6, -0.15);
	glColor3f(1, 1, 1);
	glVertex3f(0.8, 0.8, -0.8);
	glColor3f(0.2, 0, 0);
	glVertex3f(0.2, 0.4, -0.3);
	glColor3f(1, 1, 1);
	glVertex3f(0.6, 0.5, -0.8);
	glColor3f(0.3, 0, 0);
	glVertex3f(0.2, 0.3, -0.3);
	glColor3f(1, 1, 1);
	glVertex3f(0.6, 0.1, -0.8);
	glColor3f(0.4, 0, 0);
	glVertex3f(0.2, 0.2, -0.3);
	glColor3f(1, 1, 1);
	glVertex3f(0.8, -0.2, -0.8);
	glColor3f(0.5, 0, 0);
	glVertex3f(0.2, 0, -0.2);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0.3, -0.15);

	glEnd();



	//glDisable(GL_TEXTURE_2D);

}

void display()
{

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear background colour (default : black)
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff2);
	glLightfv(GL_LIGHT1, GL_POSITION, pos2);
	glMaterialfv(GL_BACK, GL_AMBIENT, amb2);
	glEnable(GL_LIGHT1);

	if (evolved) {
		glRotatef(evorotateCam, 0, 1, 0);
	}

	if (evo_success && !evolved) {
		glLoadIdentity();
		evolved = true;
		//glRotatef(0, 0, 1, 0);
	}
	if (!evo_success && evolved) {
		glLoadIdentity();
		evolved = false;
		//glRotatef(0, 0, 1, 0);
	}
	glRotatef(evorotateCam, 0, 1, 0);

	//rotateCam
	glPushMatrix();//4
	glTranslatef(walk_translatex, 0, walk_translatez);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glRotatef(evorotateCam, 0, 1, 0);
	glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);
	glRotatef(180, 0, 1, 0);
	glRotatef(rotateCam, 0, 1, 0);

	duke_lower_legs();
	glPushMatrix();//1
	duke_upper_legs();
	glPopMatrix();//1
	duke_foots();
	duke_waist();
	duke_belt();
	duke_body();
	duke_head();
	duke_corn();
	duke_left_hand();
	duke_right_hand();
	duke_evo_sphere();

	glPushMatrix();//2
	glRotatef(capeAngle, 1, 0, 0);
	glTranslatef(0, capeY, capeZ);

	glPopMatrix();//2
	glPushMatrix();//3
	//glTranslatef(1, 0, 0);
	if (evo_success == true) {
		duke_wing();
	}
	else {
		duke_cape();
	}

	glPopMatrix();//3

	glPopMatrix();//4
	glDisable(GL_LIGHT1);
	
	
		


	
	
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//-------------------------------- 

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//Step3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 24);

	//Step4: Assign texture to polygon
	glGenTextures(8, textures);
	loadTexture(textures[0], "mRed.bmp");
	loadTexture(textures[1], "mRedCotton.bmp");
	loadTexture(textures[2], "mGold.bmp");
	loadTexture(textures[3], "mMetal.bmp");
	loadTexture(textures[4], "mFire.bmp");
	loadTexture(textures[5], "mEvoFire.bmp");
	loadTexture(textures[6], "mDarkRed.bmp");


	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display(); //refresh new frame

		SwapBuffers(hdc);
	}

	DeleteObject(hBMP);
	glDeleteTextures(8, textures);


	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------