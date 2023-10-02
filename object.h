#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <iostream>
#include "math.h"
#include <gl/glut.h>

using namespace std;

class Object{
public:
	Object();
	Object(GLfloat x, GLfloat y, GLfloat xVel, GLfloat yVel);
	~Object();
	
	float Pi();
	
	GLfloat x, y;
	GLfloat xVel, yVel;
	GLfloat size, sizeX, sizeY;
	GLboolean transformOnce, enlarge; // Flags for motion and animation
	GLfloat cloud_x1, cloud_y1, cloud_x2, cloud_y2, cloud_x3, cloud_y3, cloudxVel;
	
	void drawPoint(GLfloat x, GLfloat y, GLfloat size);
	void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat thickness);
	void drawTriangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
	void drawQuad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
	void drawPentagon(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat x5, GLfloat y5);
	void drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	void drawRegularPolygon(GLfloat x, GLfloat y, GLfloat radius, GLint side, GLfloat orientation, GLfloat width, GLfloat height);
	void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat width, GLfloat height, bool halfCircle);

	// Text rendering
	void drawText(const char *text, GLint length, GLint x, GLint y, void *font);
	
	// Transformation functions
	void translate(GLfloat tX, GLfloat tY);
	void scale(GLfloat sX, GLfloat sY);
	void rotate(GLfloat degree, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis, GLfloat pivotX, GLfloat pivotY, GLfloat pivotZ);	
	void pRotate(GLfloat centerX, GLfloat centerY, GLfloat radius, GLfloat& angle, GLfloat stepSize);
	
	void drawHouse(GLfloat x, GLfloat y, GLfloat size);
	void drawTree(GLfloat x, GLfloat y);
	void drawBush1(GLfloat x, GLfloat y);
	void drawBush2(GLfloat x, GLfloat y);
	void drawBush3(GLfloat x, GLfloat y);
	void drawFence(GLfloat x, GLfloat y, int loop);
	void drawStreetLamp(GLfloat x, GLfloat y, int loop, bool light);
	void drawPowerBox(GLfloat x, GLfloat y);
	void drawBatteryCell(GLfloat x, GLfloat y);
	
	void drawMountain(GLfloat x, GLfloat y);
	void drawBackground(GLfloat x, GLfloat y, GLfloat horizontal_length, GLfloat vertical_length);
	
	void fan(GLfloat x, GLfloat y);
	void turbine(GLfloat x, GLfloat y);
	
	void turbine_bodySmall(GLfloat x, GLfloat y);
	void turbine_bodyBig(GLfloat x, GLfloat y, GLfloat sizeY);
	void turbine_fanSmall(GLfloat x, GLfloat y);
	void turbine_fanBig(GLfloat x, GLfloat y);
	
	void drawHouse_roomBG();
	void drawSofa(GLfloat x, GLfloat y);
	void drawHouse_powerbox(GLfloat x, GLfloat y);
	
	void drawLine(double x , double y , double angle);
};

struct Window{
	string title;
	GLint offsetX, offsetY;
	GLint width, height;
};

struct Transform{
	// for mouse and keyboard controls. 
	GLdouble displaceAmt; // Translation based on input
	GLdouble rotateAmt; // Rotation based on input
	GLint mouseX, mouseY;
	bool leftMouseIsPressed, rightMouseIsPressed;	
};

#endif

//void Object::drawHouse(GLfloat x, GLfloat y, GLfloat size) {
//	//Roof left
//	glColor3ub(183, 181, 165);
//	drawQuad(80+x, 525+y, 110+x, 525+y, 20+x, 415+y, -5+x, 415+y);
//	glColor3ub(209, 205, 203);
//	drawQuad(-5+x, 415+y, -7+x, 420+y, 80+x, 525+y, 85+x, 525+y);
//		
//	//Body Left
//	glColor3ub(163, 43, 42);
//	drawQuad(20+x, 95+y, 20+x, 430+y, 85+x, 515+y, 85+x, 95+y);
//	drawQuad(85+x, 95+y, 85+x, 515+y, 325+x, 290+y, 325+x, 95+y);
//	//Body Right
//	glColor3ub(232, 72, 66);
//	drawQuad(325+x, 95+y, 325+x, 290+y, 620+x, 290+y, 620+x, 95+y);
//	glColor3ub(178, 46, 47);
//	drawQuad(325+x, 250+y, 325+x, 290+y, 620+x, 290+y, 620+x, 250+y);
//	glColor3ub(206, 66, 65);
//	drawQuad(325+x, 130+y, 325+x, 250+y, 620+x, 250+y, 620+x, 225+y);
//	
//	//Roof
//	glColor3ub(219, 217, 205);
//	drawQuad(320+x, 295+y, 80+x, 525+y, 460+x, 525+y, 670+x, 295+y);
//	glColor3ub(192, 176, 162);
//	drawQuad(317+x, 288+y, 80+x, 515+y, 80+x, 525+y, 320+x, 295+y);
//	glColor3ub(200, 181, 168);
//	drawQuad(317+x, 288+y, 320+x, 295+y, 670+x, 295+y, 665+x, 288+y);
//	
//	//Left Window
//	glColor3ub(91, 39, 40);
//	drawQuad(75+x, 380+y, 75+x, 395+y, 105+x, 395+y, 105+x, 380+y);
//	drawQuad(125+x, 380+y, 125+x, 395+y, 155+x, 395+y, 155+x, 380+y);
//	
//	drawQuad(60+x, 150+y, 60+x, 280+y, 280+x, 280+y, 280+x, 150+y);
//	glColor3ub(128, 192, 212);
//	drawQuad(80+x, 170+y, 80+x, 260+y, 260+x, 260+y, 260+x, 170+y);
//	
//	
//	//Door
//	glColor3ub(239, 239, 235);
//	drawQuad(425+x, 95+y, 425+x, 175+y, 461+x, 175+y, 461+x, 95+y);
//	glColor3ub(129, 56, 58);
//	drawQuad(425+x, 175+y, 425+x, 178+y, 466+x, 178+y, 461+x, 175+y);
//	glColor3ub(91, 39, 40);
//	drawQuad(461+x, 95+y, 461+x, 175+y, 465+x, 178+y, 465+x, 95+y);
//	//Door window
//	drawQuad(432+x, 155+y, 432+x, 165+y, 453+x, 165+y, 453+x, 155+y);
//	//Door side window 1
//	glColor3ub(239, 239, 239);
//	drawQuad(487+x, 158+y, 487+x, 178+y, 533+x, 178+y, 533+x, 158+y);
//	glColor3ub(91, 39, 40);
//	drawQuad(490+x, 160+y, 490+x, 175+y, 530+x, 175+y, 530+x, 160+y);
//	//Door side window 2
//	glColor3ub(239, 239, 239);
//	drawQuad(552+x, 158+y, 552+x, 178+y, 598+x, 178+y, 598+x, 158+y);
//	glColor3ub(91, 39, 40);
//	drawQuad(555+x, 160+y, 555+x, 175+y, 595+x, 175+y, 595+x, 160+y);
//}
