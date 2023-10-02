#include "object.h"

// Default constructor
Object::Object(){
	this->x = 0;
	this->y = 0;
	size = 1;
	transformOnce = true;
}

Object::Object(GLfloat x, GLfloat y, GLfloat xVel, GLfloat yVel) {
	this->x = x; this->y = y; // Object position
	this->xVel = xVel; this->yVel = yVel; // Object speed
}

// Destructor
Object::~Object(){
}

void Object::drawPoint(GLfloat x, GLfloat y, GLfloat size){
	// glPushMatrix();
	glPointSize(size); // Diameter of the dot.
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	// glPopMatrix();
}

void Object::drawLine(GLfloat x1, GLfloat y1,
					  GLfloat x2, GLfloat y2,
					  GLfloat thickness){
	glPushMatrix();
	glLineWidth(thickness);
	glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
	glEnd();
	glPopMatrix();
}

void Object::drawText(const char *text, GLint length,
					  GLint x, GLint y, void *font){
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	glPushMatrix();
		glLoadIdentity();
		glRasterPos2i(x,y);
		for(int i=0; i<length; i++){
			glutBitmapCharacter(font, (int)text[i]);
		}
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void Object::drawTriangle(GLfloat x1, GLfloat y1,
						  GLfloat x2, GLfloat y2,
						  GLfloat x3, GLfloat y3){
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glVertex2i(x3, y3);
	glEnd();
	glPopMatrix();
}

void Object::drawQuad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4){
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glVertex2i(x3, y3);
		glVertex2i(x4, y4);
	glEnd();
	glPopMatrix();
}

void Object::drawPentagon(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat x5, GLfloat y5){
	glPushMatrix();
	glBegin(GL_POLYGON);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glVertex2i(x3, y3);
		glVertex2i(x4, y4);
		glVertex2i(x5, y5);
	glEnd();
	glPopMatrix();
}

void Object::drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height){
	for(this->x=x; this->x<x+width; this->x++){
		// Left=black(0,0,0), right=red(1,0,0)
		// glColor3f((this->x - x)*1.0f/width, 0, 0);
		for(this->y=y; this->y<y+height; this->y++){
			// Bottom=yellow(1,1,0), top=green(0,1,0)
			glColor3f(1.0 - (this->y-y)*1.0f/height, 1, 0);
			this->drawPoint(this->x, this->y, 1);
		}
	}
}

void Object::drawRegularPolygon(GLfloat x, GLfloat y, GLfloat radius, GLint side, GLfloat orientation, GLfloat width, GLfloat height){
	if(side >= 3){
		// Render polygon
		// glPushMatrix();
		GLfloat xp, yp; // Interpolation points.
		glBegin(GL_POLYGON);
			for(int i=0; i<side; i++){
				xp = x + width*radius*cos(orientation + 2*3.14159265/side*i);
				yp = y + height*radius*sin(orientation + 2*3.14159265/side*i);
				glVertex2i(xp, yp);
			}
		glEnd();
		// glPopMatrix();
	}
	else{
		cerr<<"Could not render polygon with less than three sides."<<endl;
	}
}

void Object::drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat width, GLfloat height, bool halfCircle) {
	GLfloat xp, yp;	//interpolation points
	int side;

	if(halfCircle==true)	
		side = 100;		//half circle
	else	
		side = 200;		//full circle
	
	glBegin(GL_POLYGON);
		for(int i=0; i<=side; i++)
		{
			xp = x + width*radius*cos(2*3.14159265/200*i);
			yp = y + height*radius*sin(2*3.14159265/200*i);
			glVertex2i(xp, yp);
		}
	glEnd();
}

void Object::translate(GLfloat tX, GLfloat tY){
	this->x = this->x + tX;
	this->y = this->y + tY;
}

void Object::scale(GLfloat sX, GLfloat sY){
	this->sizeX = this->sizeX * sX;
	this->sizeY = this->sizeY * sY;
}

void Object::rotate(GLfloat degree, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis, GLfloat pivotX, GLfloat pivotY, GLfloat pivotZ){
	glTranslatef(pivotX, pivotY, pivotZ);
	glRotatef(degree, xAxis, yAxis, zAxis);
	glTranslatef(-pivotX, -pivotY, -pivotZ);
}

void Object::pRotate(GLfloat centerX, GLfloat centerY, GLfloat radius, GLfloat& angle, GLfloat stepSize) {
	this->x = centerX + radius*cos(angle*3.14159265/180);
	this->y = centerY + radius*sin(angle*3.14159265/180);
	if(angle < 360) {
		angle += stepSize; //Rotational movements
	} else {
		angle = 0.0;
	}
}

//void Object::clouds() {
//	cloud_x1 = x1;
//	cloud_y1 = y1;
//	cloud_x2 = x1 - 40;
//	cloud_y2 = y1 - 8;
//	cloud_x3 = x1 + 50;
//	cloud_y3 = y1 - 10;
//}

void Object::drawHouse(GLfloat x, GLfloat y, GLfloat size) {
	//Roof left
	glColor3ub(183, 181, 165);
	drawQuad((80+x)/size, (525+y)/size, (110+x)/size, (525+y)/size, (20+x)/size, (415+y)/size, (-5+x)/size, (415+y)/size);
	glColor3ub(209, 205, 203);
	drawQuad((-5+x)/size, (415+y)/size, (-7+x)/size, (420+y)/size, (80+x)/size, (525+y)/size, (85+x)/size, (525+y)/size);
		
	//Body Left
	glColor3ub(163, 43, 42);
	drawQuad((20+x)/size, (95+y)/size, (20+x)/size, (430+y)/size, (85+x)/size, (515+y)/size, (85+x)/size,(95+y)/size);
	drawQuad((85+x)/size, (95+y)/size, (85+x)/size, (515+y)/size, (325+x)/size, (290+y)/size, (325+x)/size, (95+y)/size);
	//Body Right
	glColor3ub(232, 72, 66);
	drawQuad((325+x)/size, (95+y)/size, (325+x)/size, (290+y)/size, (620+x)/size, (290+y)/size, (620+x)/size, (95+y)/size);
	glColor3ub(178, 46, 47);
	drawQuad((325+x)/size, (250+y)/size, (325+x)/size, (290+y)/size, (620+x)/size, (290+y)/size, (620+x)/size, (250+y)/size);
	glColor3ub(206, 66, 65);
	drawQuad((325+x)/size, (130+y)/size, (325+x)/size, (250+y)/size, (620+x)/size, (250+y)/size, (620+x)/size, (225+y)/size);
	
	//Roof
	glColor3ub(219, 217, 205);
	drawQuad((320+x)/size, (295+y)/size, (80+x)/size, (525+y)/size, (460+x)/size, (525+y)/size, (670+x)/size, (295+y)/size);
	glColor3ub(192, 176, 162);
	drawQuad((317+x)/size, (288+y)/size, (80+x)/size, (515+y)/size, (80+x)/size, (525+y)/size, (320+x)/size, (295+y)/size);
	glColor3ub(200, 181, 168);
	drawQuad((317+x)/size, (288+y)/size, (320+x)/size, (295+y)/size, (670+x)/size, (295+y)/size, (665+x)/size, (288+y)/size);
	
	//Left Window
	glColor3ub(91, 39, 40);
	drawQuad((75+x)/size, (380+y)/size, (75+x)/size, (395+y)/size, (105+x)/size, (395+y)/size, (105+x)/size, (380+y)/size);
	drawQuad((125+x)/size, (380+y)/size, (125+x)/size, (395+y)/size, (155+x)/size, (395+y)/size, (155+x)/size, (380+y)/size);
	
	drawQuad((60+x)/size, (150+y)/size, (60+x)/size, (280+y)/size, (280+x)/size, (280+y)/size, (280+x)/size, (150+y)/size);
	glColor3ub(128, 192, 212);
	drawQuad((80+x)/size, (170+y)/size, (80+x)/size, (260+y)/size, (260+x)/size, (260+y)/size, (260+x)/size, (170+y)/size);
	
	
	//Door
	glColor3ub(239, 239, 235);
	drawQuad((425+x)/size, (95+y)/size, (425+x)/size, (175+y)/size, (461+x)/size, (175+y)/size, (461+x)/size, (95+y)/size);
	glColor3ub(129, 56, 58);
	drawQuad((425+x)/size, (175+y)/size, (425+x)/size, (178+y)/size, (466+x)/size, (178+y)/size, (461+x)/size, (175+y)/size);
	glColor3ub(91, 39, 40);
	drawQuad((461+x)/size, (95+y)/size, (461+x)/size, (175+y)/size, (465+x)/size, (178+y)/size, (465+x)/size, (95+y)/size);
	//Door Peeker
	drawQuad((432+x)/size, (155+y)/size, (432+x)/size, (165+y)/size, (453+x)/size, (165+y)/size, (453+x)/size, (155+y)/size);
	
	//Door side window 1
	glColor3ub(239, 239, 239);
	drawQuad((487+x)/size, (158+y)/size, (487+x)/size, (178+y)/size, (533+x)/size, (178+y)/size, (533+x)/size, (158+y)/size);
	glColor3ub(91, 39, 40);
	drawQuad((490+x)/size, (160+y)/size, (490+x)/size, (175+y)/size, (530+x)/size, (175+y)/size, (530+x)/size, (160+y)/size);
	//Door side window 2
	glColor3ub(239, 239, 239);
	drawQuad((552+x)/size, (158+y)/size, (552+x)/size, (178+y)/size, (598+x)/size, (178+y)/size, (598+x)/size, (158+y)/size);
	glColor3ub(91, 39, 40);
	drawQuad((555+x)/size, (160+y)/size, (555+x)/size, (175+y)/size, (595+x)/size, (175+y)/size, (595+x)/size, (160+y)/size);
}

void Object::drawTree(GLfloat x, GLfloat y) {
	//Leaves
	glColor3ub(131, 128, 0);
	drawRegularPolygon(115+x, 300+y, 120, 100, 100, 1, 0.85);
	glColor3ub(97, 92, 0);
	drawRegularPolygon(115+x, 280+y, 110, 100, 100, 1, 0.7);
	glColor3ub(74, 54, 2);
	drawRegularPolygon(115+x, 250+y, 90, 100, 100, 1, 0.5);
	//Body branch
	glColor3ub(124, 63, 26);
	drawQuad(100+x, 0+y, 100+x, 150+y, 130+x, 170+y, 130+x, 0+y);
	//Left branch
	drawQuad(100+x, 140+y, 65+x, 200+y, 80+x, 210+y, 120+x, 150+y);
	drawQuad(65+x, 200+y, 55+x, 240+y, 70+x, 248+y, 80+x, 210+y);
	//Right branch
	drawQuad(115+x, 160+y, 125+x, 165+y, 145+x, 170+y, 130+x, 140+y);
	drawQuad(125+x, 165+y, 130+x, 225+y, 145+x, 230+y, 143+x, 165+y);
	drawQuad(130+x, 225+y, 140+x, 255+y, 160+x, 250+y, 145+x, 230+y);
}

void Object::drawBush1(GLfloat x, GLfloat y) {
	glColor3ub(162, 155, 55);
	drawRegularPolygon(610+x, 120+y, 40, 100, 100, 1, 0.75);
	drawRegularPolygon(620+x, 145+y, 23, 100, 100, 1, 1);
	drawRegularPolygon(650+x, 130+y, 50, 100, 100, 1, 0.90);
	drawRegularPolygon(700+x, 120+y, 40, 100, 100, 1, 0.75);
	glColor3ub(172, 170, 59);
	drawRegularPolygon(660+x, 120+y, 70, 100, 100, 1, 0.4);
	drawRegularPolygon(640+x, 135+y, 30, 100, 100, 1, 1);
	glColor3ub(187, 186, 70);
	drawRegularPolygon(640+x, 135+y, 25, 100, 100, 1, 0.9);
	drawRegularPolygon(660+x, 125+y, 20, 100, 100, 1, 0.8);
}

void Object::drawBush2(GLfloat x, GLfloat y) {
	glColor3ub(162, 155, 55);
	drawRegularPolygon(790+x, 150+y, 30, 100, 100, 1, 1);
	drawRegularPolygon(860+x, 160+y, 21, 100, 100, 1, 1);
	drawRegularPolygon(770+x, 120+y, 25, 100, 100, 1, 1);
	drawRegularPolygon(840+x, 130+y, 70, 100, 100, 1, 0.5);
	drawRegularPolygon(880+x, 115+y, 21, 100, 100, 1, 1);
	glColor3ub(187, 186, 70);
	drawRegularPolygon(790+x, 150+y, 25, 100, 100, 1, 0.9);
	drawRegularPolygon(840+x, 130+y, 60, 100, 100, 1, 0.5);	
}

void Object::drawBush3(GLfloat x, GLfloat y) {
	glColor3ub(162, 155, 55);
	drawRegularPolygon(1050+x, 160+y, 40, 100, 100, 1, 1);
	drawRegularPolygon(1100+x, 170+y, 40, 100, 100, 1, 1);
	drawRegularPolygon(1190+x, 160+y, 50, 100, 100, 1, 0.7);
	drawRegularPolygon(1100+x, 145+y, 100, 100, 100, 1, 0.5);
	drawRegularPolygon(1020+x, 130+y, 50, 100, 100, 1, 0.7);
	drawRegularPolygon(1180+x, 120+y, 40, 100, 100, 1, 0.7);
	glColor3ub(172, 170, 59);
	drawRegularPolygon(1100+x, 150+y, 70, 100, 100, 1, 0.5);
	drawRegularPolygon(1040+x, 130+y, 50, 100, 100, 1, 0.5);
	drawRegularPolygon(1170+x, 160+y, 35, 100, 100, 1, 0.8);
	drawRegularPolygon(1170+x, 120+y, 30, 100, 100, 1, 0.8);
	glColor3ub(187, 186, 70);
	drawRegularPolygon(1030+x, 130+y, 25, 100, 100, 1, 0.8);
	drawRegularPolygon(1090+x, 150+y, 60, 100, 100, 1, 0.5);	
}

void Object::drawFence(GLfloat x, GLfloat y, int loop) {
	int gap = 0;
	
	glColor3ub(255, 255, 255);
	if(loop != 0) {
		for(int i = 0; i < loop; i++) {
			drawQuad(0+x+gap, 90+y, 5+x+gap, 100+y, 20+x+gap, 100+y, 25+x+gap, 90+y);
			drawQuad(0+x+gap, 0+y, 0+x+gap, 90+y, 25+x+gap, 90+y, 25+x+gap, 0+y);
			gap += 44;
		}
	} else {
		drawQuad(0+x, 90+y, 5+x, 100+y, 20+x, 100+y, 25+x, 90+y);
		drawQuad(0+x, 0+y, 0+x, 90+y, 25+x, 90+y, 25+x, 0+y);
	}
}

void Object::drawStreetLamp(GLfloat x, GLfloat y, int loop, bool light) {
	//Pillar
	glColor3ub(188, 189, 192);
	drawQuad(0+x, 90+y, 0+x, 255+y, 20+x, 255+y, 20+x, 90+y);
	glColor3ub(174, 174, 174);
	drawQuad(0+x, 90+y, 0+x, 255+y, 7+x, 255+y, 7+x, 90+y);
	//Head
	glColor3ub(188, 189, 192);
	drawQuad(0+x, 255+y, -5+x, 280+y, 25+x, 280+y, 20+x, 255+y);
	glColor3ub(174, 174, 174);
	drawQuad(0+x, 255+y, -5+x, 280+y, 5+x, 280+y, 7+x, 255+y);
	//Ring
	glColor3ub(103, 111, 108);
	drawQuad(-5+x, 255+y, -5+x, 260+y, 25+x, 260+y, 25+x, 255+y);
	//Bulb
	glColor3ub(246, 246, 246);
	drawQuad(-5+x, 280+y, -5+x, 307+y, 25+x, 307+y, 25+x, 280+y);
	//Cap
	glColor3ub(127, 127, 128);
	drawQuad(-10+x, 307+y, -10+x, 317+y, 30+x, 317+y, 30+x, 307+y);
	
	if(light == true) {
		glColor3ub(249, 245, 163);
		drawQuad(-3+x, 280+y, -3+x, 307+y, 23+x, 307+y, 23+x, 280+y);
	}
}

void Object::drawPowerBox(GLfloat x, GLfloat y) {
	//Body
	glColor3ub(249, 252, 233);
	drawQuad(0+x, 90+y, 0+x, 260+y, 150+x, 260+y, 150+x, 90+y);
	glColor3ub(211, 213, 197);
	drawQuad(120+x, 90+y, 120+x, 260+y, 150+x, 260+y, 150+x, 90+y);
	
	//Yellow part
	glColor3ub(238, 192, 31);
	drawQuad(-5+x, 240+y, -5+x, 270+y, 150+x, 270+y, 150+x, 240+y);
	glColor3ub(213, 176, 43);
	drawQuad(117+x, 240+y, 117+x, 270+y, 153+x, 270+y, 153+x, 240+y);
	
	//Blue part
	glColor3ub(87, 81, 185);
	drawQuad(12+x, 180+y, 12+x, 230+y, 105+x, 230+y, 105+x, 180+y);
	
	glColor3ub(189, 69, 99);
	drawQuad(40+x, 130+y, 60+x, 170+y, 55+x, 130+y, 40+x, 130+y);
	drawQuad(55+x, 140+y, 70+x, 140+y, 50+x, 100+y, 55+x, 140+y);
}

void Object::drawBatteryCell(GLfloat x, GLfloat y) {
	//
	glColor3ub(198, 255, 249);
	drawQuad(0+x, 0+y, 0+x, 40+y, 27+x, 40+y, 27+x, 0+y);
	glColor3ub(170, 220, 215);
	drawQuad(20+x, 0+y, 20+x, 40+y, 27+x, 40+y, 27+x, 0+y);
	glColor3ub(255, 255, 255);
	drawQuad(8+x, 15+y, 8+x, 30+y, 13+x, 30+y, 13+x, 15+y);
}

void Object::drawBackground(GLfloat x, GLfloat y, GLfloat horizontal_length, GLfloat vertical_length){
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex2i(x, y); // vertex start from top left corner, move in clockwise
		glVertex2i(x + horizontal_length, y);
		glVertex2i(x + horizontal_length, y - vertical_length);
		glVertex2i(x, y - vertical_length);
	glEnd();
	glPopMatrix();
}

void Object::drawMountain(GLfloat x, GLfloat y){
	//Left Side
	glColor3ub(166, 197, 198);
	drawCircle(350+x, 80+y, 470, 1, 1, true);
	//Right Side
	glColor3ub(130, 164, 163);
	drawCircle(1100+x, 80+y, 500, 1, 1, true);
	
	//Darkest Color
	glColor3ub(86, 122, 120);
	drawCircle(1080+x, 80+y, 270, 1, 1, true);
	drawCircle(720+x, 80+y, 170, 1, 1, true);
}


void Object::turbine_fanSmall(GLfloat x, GLfloat y) {	
	glColor3ub(240, 240, 240);
	drawPentagon(0+x, 255+y, 0+x, 400+y, 10+x, 400+y, 10+x, 255+y, 1110, 525);
	glColor3ub(223, 228, 233);
	drawQuad(0+x, 290+y, -10+x, 310+y, 0+x, 400+y, 0+x, 300+y);
		
}

void Object::turbine_fanBig(GLfloat x, GLfloat y) {
	glColor3ub(240, 240, 240);
	drawPentagon(0+x, 285+y, 0+x, 430+y, 10+x, 430+y, 10+x, 285+y, 6+x, 535);
	glColor3ub(223, 228, 233);
	drawQuad(0+x, 300+y, -15+x, 330+y, 0+x, 430+y, 0+x, 300+y);
		
}

void Object::turbine_bodySmall(GLfloat x, GLfloat y) {
	glColor3ub(223, 228, 233);
	drawQuad(0+x, 95+y, 3+x, 510+y, 17+x, 510+y, 20+x, 95+y);
	glColor3ub(234, 239, 244);
	drawQuad(0+x, 95+y, 3+x, 510+y, 8+x, 510+y, 8+x, 95+y);

	glColor3ub(52, 115, 122);
	drawCircle(x+10, y+525, 15, 1, 1, false);
	glColor3ub(146, 215, 213);
	drawCircle(x+10, y+525, 7, 1, 1, false);
}

void Object::turbine_bodyBig(GLfloat x, GLfloat y, GLfloat sizeY) {
	glColor3ub(223, 228, 233);
	drawQuad(-10+x, 95+y, -2+x, 510+y+sizeY, 22+x, 510+y+sizeY, 30+x, 95+y);
	glColor3ub(234, 239, 244);
	drawQuad(-10+x, 95+y, -2+x, 510+y+sizeY, 5+x, 510+y+sizeY, 5+x, 95+y);
}

void Object::drawHouse_roomBG() {
	//Door Wall
	glColor3ub(188, 233, 229);
	drawQuad(1200, 275, 1200, 720, 1280, 720, 1280, 0);
	//Door
	glColor3ub(239, 239, 235);
	drawQuad(1230, 170, 1230, 550, 1280, 480, 1280, 0);
	//Door knob
	glColor3ub(73, 30, 7);
	drawRegularPolygon(1275, 250, 10, 48, 0, 0.7, 1);
	
	//Wall
	glColor3ub(217, 242, 242);
	drawQuad(0, 275, 0, 720, 1200, 720, 1200, 275);
	
	//Floor
	glColor3ub(59, 163, 170);
	drawQuad(0, 0, 0, 275, 1200, 275, 1280, 0);
}

void Object::drawSofa(GLfloat x, GLfloat y) {
	//Sofa Bottom
	glColor3ub(244, 37, 71);
	drawQuad(0+x, 100+y, 20+x, 170+y, 520+x, 170+y, 540+x, 100+y);
	glColor3ub(188, 0, 36);
	drawQuad(0+x, 20+y, 0+x, 100+y, 540+x, 100+y, 540+x, 20+y);
	//Sofa Side - Right
	glColor3ub(244, 37, 71);
//	drawQuad(520+x, 220+y, 512+x, 240+y, 560+x, 240+y, 570+x, 220+y);
	drawQuad(540+x, 160+y, 520+x, 220+y, 570+x, 220+y, 600+x, 160+y);
	glColor3ub(202, 26, 58);
	drawQuad(520+x, 170+y, 520+x, 220+y, 540+x, 160+y, 540+x, 100+y);
	glColor3ub(188, 0, 36);
	drawQuad(540+x, 20+y, 540+x, 160+y, 600+x, 160+y, 600+x, 20+y);
	
	//Sofa Side - Left
	glColor3ub(244, 37, 71);
	drawQuad(-60+x, 160+y, -25+x, 220+y, 20+x, 220+y, 0+x, 160+y);
	glColor3ub(202, 26, 58);
	drawQuad(0+x, 100+y, 0+x, 160+y, 20+x, 220+y, 20+x, 170+y);
	glColor3ub(188, 0, 36);
	drawQuad(-60+x, 20+y, -60+x, 160+y, 0+x, 160+y, 0+x, 20+y);
	//Sofa Top
	glColor3ub(244, 37, 71);
	drawQuad(20+x, 300+y, 30+x, 320+y, 510+x, 320+y, 520+x, 300+y);
	glColor3ub(188, 0, 36);
	drawQuad(20+x, 170+y, 20+x, 300+y, 520+x, 300+y, 520+x, 170+y);	
}

void Object::drawHouse_powerbox(GLfloat x, GLfloat y) {
	glColor3ub(211, 213, 197);
	drawQuad(0+x, 200+y, 5+x, 210+y, 145+x, 210+y, 150+x, 200+y);
	glColor3ub(249, 252, 233);
	drawQuad(0+x, 0+y, 0+x, 200+y, 150+x, 200+y, 150+x, 0+y);

	//Blue part
	glColor3ub(87, 81, 185);
	drawQuad(20+x, 20+y, 20+x, 90+y, 130+x, 90+y, 130+x, 20+y);
	
	//Lightning Logo
	glColor3ub(189, 69, 99);
	drawQuad(40+x, 130+y, 60+x, 170+y, 55+x, 130+y, 40+x, 130+y);
	drawQuad(55+x, 140+y, 70+x, 140+y, 50+x, 100+y, 55+x, 140+y);
	drawQuad(80+x, 130+y, 100+x, 170+y, 95+x, 130+y, 90+x, 130+y);
	drawQuad(95+x, 140+y, 110+x, 140+y, 90+x, 100+y, 95+x, 140+y);
}

void Object::drawLine(double x , double y , double angle) {
	glVertex2f(x , x);
	glVertex2f(y*cos(angle) , y*sin(angle) );
}
