#include <windows.h> // Load W32 window, console window.
#include <gl/glut.h> // OpenGL toolkit
#include "object.h"

using namespace std; // There is no need to specific the std prefix
                     // for I/O stream. e.g. std::cin, std::cout.

Window window;
Transform transform;

Object background = Object();
Object livingroom_floor = Object();
Object livingroom_powerbox;
Object livingroom_sofa;
Object livingroom_picture_frame;
Object grassFloor;	
Object house;
Object fence;	
Object tree;		
Object bush;
Object mountain;
Object streetLamp;
Object powerBox;
Object batteryCell;
Object turbine;
Object turbineFan_small;
Object turbineFan_big;
Object cloud1;
Object cloud2;
Object cloud3;

Object minion_left_forearm = Object();
Object minion_right_forearm = Object();
Object minion_left_leg = Object();
Object minion_right_leg = Object();

Object textObj;

GLfloat turbineAngle = 0.0;
GLfloat turbineAngle2 = 0.0;
GLfloat turbineAngle3 = 0.0;
GLfloat armLeftAngle = 0.0;
GLfloat armRightAngle = 0.0;

int minionOffsetX = 0;
int minionOffsetY = 0;
int minionPupilOffsetX = 0;
int minionLeftLegOffsetY = 0;
int minionRightLegOffsetY = 0;
int previousKey = 400;
int cellAmount = 0;
string text;
string text2;
string currentScene = "scene2";
string legAction = "none";
string armState = "none";


void windowSettings(){
	window.title = "CCG3013 Assignment 2";
	window.offsetX = 50;
	window.offsetY = 50;
	window.width = 1280;
	window.height = 720;
}

void init() {
	windowSettings();
	
	cloud1 = Object(0, 575, 0.8, 0.6);
	cloud2 = Object(0, 540, 0.5, 0.5);
	cloud3 = Object(0, 640, 0.3, 0.4); 
					
	turbineFan_small = Object(1105, 260, 0.01, 0.01);	
}

void renderFloor() {
	glColor3ub(222, 198, 66); //Base green
	grassFloor.drawQuad(0, 0, 0, 95, 1280, 95, 1280, 0);
	glColor3ub(187, 176, 50); //Darker green
	grassFloor.drawQuad(0, 90, 0, 95, 1280, 95, 1280, 90);
	grassFloor.drawQuad(0, 0, 0, 25, 1280, 25, 1280, 0);
	glColor3ub(243, 216, 80); //light green
	grassFloor.drawQuad(480, 70, 485, 85, 1280, 85, 1280, 70); 
	grassFloor.drawQuad(450, 50, 450, 70, 1280, 70, 1280, 50); 
	grassFloor.drawQuad(520, 36, 510, 50, 1280, 50, 1280, 36); 
	glColor3ub(69, 45, 33); //Brown
	grassFloor.drawQuad(0, 0, 0, 15, 1280, 15, 1280, 0);
}

void clouds() {
	glColor3ub(225, 225, 225);
	cloud1.translate(cloud1.xVel, 0.0);
	cloud1.drawRegularPolygon(cloud1.x, cloud1.y+70, 16, 100, 5, 3, 2.3);
	cloud1.drawRegularPolygon(cloud1.x+50, cloud1.y+60, 15, 500, 5, 2, 1.5);
	cloud1.drawRegularPolygon(cloud1.x-40, cloud1.y+50, 15, 500, 1, 2, 1.2);
	if(cloud1.x >= window.width+50) {
		cloud1.x = -50;
	}
	
	glColor3ub(225, 225, 225);
	cloud2.translate(cloud2.xVel, 0.0);
	cloud2.drawRegularPolygon(cloud2.x-40, cloud2.y+30, 10, 500, 1, 2, 1.5);
	cloud2.drawRegularPolygon(cloud2.x, cloud2.y+40, 11, 100, 5, 3, 2.3);
	cloud2.drawRegularPolygon(cloud2.x+30, cloud2.y+25, 10, 500, 5, 2, 1.5);
	if(cloud2.x >= window.width+50) {
		cloud2.x = -50;
	}
	
	glColor3ub(225, 225, 225);
	cloud3.translate(cloud3.xVel, 0.0);
	cloud3.drawRegularPolygon(cloud3.x-60, cloud3.y+30, 11, 500, 1, 2, 1.5);
	cloud3.drawRegularPolygon(cloud3.x-30, cloud3.y+25, 11, 500, 5, 2, 1.5);
	cloud3.drawRegularPolygon(cloud3.x-10, cloud3.y+40, 13, 100, 5, 3, 2.3);
	cloud3.drawRegularPolygon(cloud3.x+30, cloud3.y+25, 11, 500, 5, 2, 1.5);
	if(cloud3.x >= window.width+50) {
		cloud3.x = -50;
	}	
}

void render_minion_pupil() {
	Object minion_pupil = Object();
	glTranslated(minionPupilOffsetX, 0, 0);
	
	glColor3ub(166, 124, 82); //brown
	minion_pupil.drawRegularPolygon(34, 123, 7, 100, 5, 1.0, 1.0);
	glColor3ub(0,2,0); //black
	minion_pupil.drawRegularPolygon(34, 123, 7, 100, 5, 0.6, 0.6);
}

void render_minion_left_leg(GLfloat y) {
//	glTranslated(0, minionLeftLegOffsetY, 0);
	glColor3ub(255, 220, 50); //yellow
	minion_left_leg.drawQuad(15, 60+y, 15, 80+y, 25, 80+y, 25, 60+y);
	glColor3ub(47, 51, 54); //black
	minion_left_leg.drawQuad(15, 60+y, 15, 65+y, 25, 65+y, 25, 60+y);
}

void render_minion_right_leg(GLfloat y) {
//	glTranslated(0, minionRightLegOffsetY, 0);
	glColor3ub(255, 220, 50); //yellow
	minion_right_leg.drawQuad(34, 60+y, 34, 80+y, 44, 80+y, 44, 60+y);
	glColor3ub(47, 51, 54); //black
	minion_right_leg.drawQuad(34, 60+y, 34, 65+y, 44, 65+y, 44, 60+y);
	
}

void render_minion_left_arm() {
	glColor3ub(47, 51, 54); //black
	minion_left_forearm.drawCircle(10, 80, 5, 1, 1, false);
	
	glColor3ub(255, 220, 50); //yellow
	minion_left_forearm.drawPentagon(5, 80, 5, 100, 10, 105, 14, 100, 14, 80);
}

void render_minion_right_arm2() {
	glColor3ub(47, 51, 54); //black
	minion_right_forearm.drawCircle(49, 80, 5, 1, 1, false);
	
	glColor3ub(255, 220, 50); //yellow
	minion_right_forearm.drawPentagon(45, 80, 45, 100, 50, 105, 54, 100, 54, 80);
}

void minion_walk_leg(string state) {
	if(state == "left") {
		render_minion_left_leg(0);
		render_minion_right_leg(5);
	} else if (state == "right") {
		render_minion_left_leg(5);
		render_minion_right_leg(-5);
	} else {
		render_minion_left_leg(0);
		render_minion_right_leg(0);
	}
}

void minion_walk_arm(string state) {
	if(state == "left") {
		//Left arm
	    glPushMatrix();
	        minion_left_forearm.rotate(0, 0, 0, 1, 10, 105, 0);
			render_minion_left_arm();
	    glPopMatrix();
	    //Right arm
	    glPushMatrix();
	        minion_right_forearm.rotate(40, 0, 0, 1, 50, 105, 0);
			render_minion_right_arm2();
	    glPopMatrix();
	} else if (state == "right") {
	    glPushMatrix();
	        minion_left_forearm.rotate(-40, 0, 0, 1, 10, 105, 0);
			render_minion_left_arm();
	    glPopMatrix();
	    //Right arm
	    glPushMatrix();
	        minion_right_forearm.rotate(0, 0, 0, 1, 50, 105, 0);
			render_minion_right_arm2();
	    glPopMatrix();
	} else if (state == "grab") {	
	    glPushMatrix();
	        minion_left_forearm.rotate(-150, 0, 0, 1, 10, 105, 0);
			render_minion_left_arm();
	    glPopMatrix();
	    //Right arm
	    glPushMatrix();
	        minion_right_forearm.rotate(150, 0, 0, 1, 50, 105, 0);
			render_minion_right_arm2();
	    glPopMatrix();
	} else {
		//Left arm
	    glPushMatrix();
	        minion_left_forearm.rotate(0, 0, 0, 1, 10, 105, 0);
			render_minion_left_arm();
	    glPopMatrix();
	    //Right arm
	    glPushMatrix();
	        minion_right_forearm.rotate(0, 0, 0, 1, 50, 105, 0);
			render_minion_right_arm2();
	    glPopMatrix();
	}
}

void render_minion() {
	Object minion_head = Object();
	Object minion_eyes = Object();
	Object minion_body = Object();
	Object minion_left_arm = Object();
	Object minion_right_arm = Object();
	
	glTranslated(minionOffsetX, 0, 0);
	glTranslated(0, minionRightLegOffsetY, 0);

	//If mouse click on powerbox
	if(armState == "grab") {
	    glPushMatrix();
	        batteryCell.rotate(90, 0, 0, 1, 30, 163, 0);
			batteryCell.drawBatteryCell(17, 145);
	    glPopMatrix();
	}
	
	// Leg animation
	minion_walk_leg(legAction);

//	glColor3ub(0, 255, 0);
//	minion_body.drawPoint(30, 168, 2);
	
	//minion body
	glColor3ub(84,120,195); //blue
	minion_body.drawRegularPolygon(30, 90, 13, 100, 5, 1.5, 1.5);
	glColor3ub(255,220,50); //yellow
	minion_head.drawRegularPolygon(30, 130, 13, 100, 5, 1.5, 1.5);
	minion_body.drawQuad(10, 90, 10, 130, 50, 130, 50, 90);
	
	//minion mouth
	glColor3ub(47, 51, 54); //black
	minion_head.drawRegularPolygon(30, 108, 8, 100, 5, 1.2, 1.2);
	glColor3ub(255, 220, 50); //yellow
	minion_head.drawRegularPolygon(30, 111, 8, 100, 5, 1.2, 1.2);

	//minion eye
	glColor3ub(216, 220, 212); //grey
	minion_eyes.drawRegularPolygon(30, 125, 9, 100, 5, 1.5, 1.5);
	glColor3ub(255,255,255); //white
	minion_eyes.drawRegularPolygon(30, 125, 8, 100, 5, 1.3, 1.3);

	//Minion arms with animation
	minion_walk_arm(armState);
	//Minion eye pupil with animation
	render_minion_pupil();
	
	previousKey = 400;
}

void scene1() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720);
	glClear(GL_COLOR_BUFFER_BIT);	
	
	int cellGap = 0;
	
	livingroom_floor.drawHouse_roomBG();
	livingroom_sofa.drawSofa(160, 140);
	
	//Picture Frame
	glColor3ub(195, 150, 111);
	livingroom_picture_frame.drawQuad(50, 530, 50, 630, 150, 630, 150, 530);
	glColor3ub(224, 182, 134);
	livingroom_picture_frame.drawQuad(60, 540, 60, 620, 140, 620, 140, 540);
	
	livingroom_powerbox.drawHouse_powerbox(900, 350);
	
	// Insert cells into powerbox
	for(int i = 0; i < cellAmount; i++) {
		livingroom_powerbox.drawBatteryCell(cellGap+930, 385);
		cellGap += 32;
	}
	
	render_minion();
	
	glColor3ub(0, 0, 0);
	text = "Grab a Battery Cell, walk near the power box";
	text2 = "then put into the by clicking on it...";
	textObj.drawText(text.data(), text.size(), 510, 200, GLUT_BITMAP_8_BY_13);
	textObj.drawText(text2.data(), text.size(), 530, 185, GLUT_BITMAP_8_BY_13);

	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
	glFinish();
}

void scene2() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // RGBA
	// Canvas settings
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720); // Set canvas resolution to 800 by 600 pixels.
	glClear(GL_COLOR_BUFFER_BIT); // Load frame buffer.
	
	int treeGap = 0;
	double tickMarks = 0;

	// Background
	glColor3ub(227, 250, 251);
	background.drawBackground(0, 720, 1280, 720);
	
	clouds();
	mountain.drawMountain(0, 0);

    turbineAngle = turbineAngle+0.2;
    glPushMatrix();
        glTranslatef(125,400,0);
        glRotatef(turbineAngle,0.0,0.0,1.0);
        glTranslatef(-125,-400,0);
    glPopMatrix();
    glPushMatrix();
        turbineFan_small.rotate(turbineAngle+1, 0, 0, 1, 1110, 525, 0);
        turbineFan_small.turbine_fanSmall(1110, 290);
    glPopMatrix();
    
    glPushMatrix();
        turbineFan_small.rotate(turbineAngle+120, 0, 0, 1, 1110, 525, 0);
        turbineFan_small.turbine_fanSmall(1110, 290);
    glPopMatrix();

    glPushMatrix();
        turbineFan_small.rotate(turbineAngle-120, 0, 0, 1, 1110, 525, 0);
        turbineFan_small.turbine_fanSmall(1110, 290);
    glPopMatrix();
				
	turbine.turbine_bodySmall(1100, 0);
	for(int i = 0; i < 4; i++) {
		tree.drawTree(575+treeGap, 95);
		treeGap += 150;
	}
	
	bush.drawBush1(20, 0);
	bush.drawBush2(30, 0);
	bush.drawBush3(0, 0);
	
	// If 3 cells in the power box, turn on lights
	if(cellAmount == 3) {
		streetLamp.drawStreetLamp(750, 5, 0, true);
		streetLamp.drawStreetLamp(1050, 5, 0, true);
	} else {
		streetLamp.drawStreetLamp(750, 5, 0, false);
		streetLamp.drawStreetLamp(1050, 5, 0, false);
	}
	renderFloor();
	fence.drawFence(630, 95, 15);
	glColor3ub(254, 254, 254);
	fence.drawQuad(615, 130, 615, 160, 1280, 160, 1280, 130);
	house.drawHouse(0, -5, 1);
	
	render_minion();
	
	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
	glFinish();
}

void scene3() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720);
	glClear(GL_COLOR_BUFFER_BIT);	

	int treeGap = 0;
	int batteryGap = 0;
		
	// Background
	glColor3ub(227, 250, 251);
	background.drawBackground(0, 720, 1280, 720);

	clouds();
	mountain.drawMountain(0, 0);
	house.drawHouse(-20, 75, 1.8);
	for(int i = 0; i < 3; i++) {
		tree.drawTree(-120+treeGap, 95);
		treeGap += 300;
	}
	bush.drawBush1(180, 0);
	bush.drawBush1(50, 0);
	bush.drawBush2(-450, 0);
	bush.drawBush3(-550, 0);
	bush.drawBush3(-100, 0);
	bush.drawBush1(600, 0);
	bush.drawBush1(-450, 0);
	bush.drawBush2(-850, 0);
	
	// If 3 cells in the power box, turn on lights
	if(cellAmount == 3) {
		streetLamp.drawStreetLamp(430, 5, 0, true);
	} else {
		streetLamp.drawStreetLamp(430, 5, 0, false);
	}
	
	renderFloor();
	fence.drawFence(10, 95, 15);
	glColor3ub(254, 254, 254);
	fence.drawQuad(0, 130, 0, 160, 665, 160, 665, 130);
	
	
	// Turbine 1
	turbine.turbine_bodyBig(950, 0, 10);
	// Turbine 1 blade
    turbineAngle2 = turbineAngle2+0.4;
    glPushMatrix();
        glTranslatef(125,400,0);
        glRotatef(turbineAngle2,0.0,0.0,1.0);
        glTranslatef(-125,-400,0);
    glPopMatrix();
    glPushMatrix();
        turbineFan_big.rotate(turbineAngle2+1, 0, 0, 1, 961, 535, 0);
        turbineFan_big.turbine_fanBig(955, 260);
    glPopMatrix();

    glPushMatrix();
        turbineFan_big.rotate(turbineAngle2+120, 0, 0, 1, 961, 535, 0);
        turbineFan_big.turbine_fanBig(955, 260);
    glPopMatrix();

    glPushMatrix();
        turbineFan_big.rotate(turbineAngle2-120, 0, 0, 1, 961, 535, 0);
        turbineFan_big.turbine_fanBig(955, 260);
    glPopMatrix();
    
	//Turbine circle head
	glColor3ub(52, 115, 122);
	turbine.drawCircle(950+10, 10+525, 20, 1, 1, false);
	glColor3ub(146, 215, 213);
	turbine.drawCircle(950+10, 10+525, 10, 1, 1, false);
	
	// Turbine 2
	turbine.turbine_bodyBig(1150, 0, 0);
	// Turbine 2 blade
    turbineAngle3 = turbineAngle3+0.2;
    glPushMatrix();
        glTranslatef(125,400,0);
        glRotatef(turbineAngle3,0.0,0.0,1.0);
        glTranslatef(-125,-400,0);
    glPopMatrix();
    glPushMatrix();
        turbineFan_big.rotate(turbineAngle3+1, 0, 0, 1, 1160, 535, 0);
        turbineFan_big.turbine_fanBig(1155, 260);
    glPopMatrix();

    glPushMatrix();
        turbineFan_big.rotate(turbineAngle3+120, 0, 0, 1, 1160, 530, 0);
        turbineFan_big.turbine_fanBig(1155, 260);
    glPopMatrix();

    glPushMatrix();
        turbineFan_big.rotate(turbineAngle3-120, 0, 0, 1, 1160, 530, 0);
        turbineFan_big.turbine_fanBig(1155, 260);
    glPopMatrix();
	
	glColor3ub(52, 115, 122);
	turbine.drawCircle(1150+10, 0+525, 20, 1, 1, false);
	glColor3ub(146, 215, 213);
	turbine.drawCircle(1150+10, 0+525, 10, 1, 1, false);
	
	powerBox.drawPowerBox(800, 0);
	
	for(int i = 0; i < 3; i++) {
		powerBox.drawBatteryCell(814+batteryGap, 185);
		batteryGap += 30;
	}
	
	render_minion();

	glColor3ub(0, 0, 0);
	text = "Walk towards near the power box and click";
	text2 = "on it to grab a battery cell";
	textObj.drawText(text.data(), text.size(), 450, 275, GLUT_BITMAP_8_BY_13);
	textObj.drawText(text2.data(), text.size(), 470, 260, GLUT_BITMAP_8_BY_13);

	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
	glFinish();
}

void mouseClickInteraction(GLint x, GLint y){
//	GLint dX = x - transform.mouseX;
//	GLint dY = y - transform.mouseY;
	if(transform.leftMouseIsPressed && currentScene == "scene3" && minionOffsetX >= 750 && minionOffsetX <= 970 && x >= 795 && x <= 955) {
		armState = "grab";
		// print out instructions to console
		cout << "Grabbed Cell" << endl;
	} else if (transform.leftMouseIsPressed && currentScene == "scene1" && armState == "grab" && minionOffsetX >= 880 && minionOffsetX <= 1070 
	&& x >= 900 && x <= 1050 && y >= 350 && y <= 550) {
		armState = "none";
		if(cellAmount < 3) {
			cellAmount += 1; 
		}
	}
}

void mouseControl(GLint button, GLint state, GLint x, GLint y){
	y = window.height - y; // Switch from window coordinates to canvas coordinates.
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN && !transform.leftMouseIsPressed){
				transform.mouseX = x;
				transform.mouseY = y;
				transform.leftMouseIsPressed = true;
				
				mouseClickInteraction(x, y);
			}
			if(state == GLUT_UP && transform.leftMouseIsPressed){
				transform.leftMouseIsPressed = false;
			}
		break;
		case GLUT_RIGHT_BUTTON:
			if(state == GLUT_DOWN && !transform.rightMouseIsPressed){
				transform.mouseX = x;
				transform.mouseY = y;
				transform.rightMouseIsPressed = true;
			}
			if(state == GLUT_UP && transform.rightMouseIsPressed){
				transform.rightMouseIsPressed = false;
			}
		break;
	}
}

void keyboardSpecialKeyFn(int key, int x, int y){ 
	int offset = 10;
	previousKey = key;
	
	switch(key){ 
		case GLUT_KEY_LEFT: 
			minionOffsetX -= offset;
			
			if(currentScene == "scene2") {
				if(minionOffsetX == -30) {
					minionOffsetX = 1180;
					glutDisplayFunc(scene1);
					
					currentScene = "scene1";
				}
			} else if(currentScene == "scene3"){
				if(minionOffsetX == -30) {
					minionOffsetX = 1200;
					glutDisplayFunc(scene2);
					
					currentScene = "scene2";
				}
			}
			
			if(minionPupilOffsetX != -8) {
				minionPupilOffsetX = -8; 
			} else {
				minionPupilOffsetX = minionPupilOffsetX;
			}
			
			if(legAction == "right") {
				minionLeftLegOffsetY = 2;
				minionRightLegOffsetY = -2;
				legAction = "left";
				if(armState != "grab") {
					armState = "right";	
				}							
			} else if(legAction == "left") {
				minionLeftLegOffsetY = -2;
				minionRightLegOffsetY = 2;
				legAction = "right";
				if(armState != "grab") {
					armState = "left";	
				}		
			} else {
				minionLeftLegOffsetY = -2;
				minionRightLegOffsetY = 2;
				legAction = "right";
				if(armState != "grab") {
					armState = "right";	
				}			
			}	
		break;
		case GLUT_KEY_RIGHT:
			minionOffsetX += offset;
			
			if(currentScene == "scene2") {
				if(minionOffsetX == window.width-30) {
					minionOffsetX = 20;
					glutDisplayFunc(scene3);
					
					currentScene = "scene3";
				}
			} else if(currentScene == "scene1") {
				if(minionOffsetX == window.width-50) {
					minionOffsetX = 20;
					glutDisplayFunc(scene2);
					
					currentScene = "scene2";
				}
			}
			
			if(minionPupilOffsetX != 0) {
				minionPupilOffsetX = 0; 
			} else {
				minionPupilOffsetX = minionPupilOffsetX;
			}
			
			if(legAction == "right") {
				minionLeftLegOffsetY = 2;
				minionRightLegOffsetY = -2;
				legAction = "left";
				if(armState != "grab") {
					armState = "right";	
				}							
			} else if(legAction == "left") {
				minionLeftLegOffsetY = -2;
				minionRightLegOffsetY = 2;
				legAction = "right";
				if(armState != "grab") {
					armState = "left";	
				}		
			} else {
				minionLeftLegOffsetY = -2;
				minionRightLegOffsetY = 2;
				legAction = "right";
				if(armState != "grab") {
					armState = "right";	
				}			
			}		
		break;
	}
	glutPostRedisplay();
}

int main(){
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Single frame buffer
												 // with RGB colors.
	glutInitWindowSize(window.width, window.height); // OpenGL window size.
	glutInitWindowPosition(window.offsetX, window.offsetY); // Window position on the screen.
	glutCreateWindow(window.title.c_str()); // OpenGL window title.
	glutDisplayFunc(scene2); // Load render function.
	
	// Enable mouse button function
	glutMouseFunc(mouseControl);
	// Enable special keys control.
	glutSpecialFunc(keyboardSpecialKeyFn);
	
	glutMainLoop(); // Loop frame forever.
	
	system("PAUSE"); // Pause the frame.
	return 0; // Close program.
}
