#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string>




#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "interface.h"


/* The Global Variables
*/
float camPos[] = {0, 0, 3.42f};
int x;	//the size of the grid
clock_t t = clock();
int initX, initY, initHX, initHY;
int squareX, squareY;
int headX, headY;
bool options[4];

//to randomize the square for the inital start of the program
void randomizeSquare(){
	t = clock();
	srand(t);
	squareX = (rand() % x + 1) -1; //getting a random number from 1 to m
	squareY = (rand() % x + 1) -1;

	initX = squareX;
	initY = squareY;

}


//to find the valid moves for the robot
void getOptions(){
	for(int i=0;i<4; i++){
		options[i] = false;

	}

	if(squareX > 0){ options[0] = true;} //you can go left
	if(squareX < x-1){ options[2] = true;} //you can go right
	if(squareY > 0){ options[3] = true;} //you can go down
	if(squareY < x-1){ options[1] = true;} //you can go down
}

//to randomize the location of the head (at the initial run)
void randomizeHead(){
	int temp;
	do {temp = rand() % 4;} 	//randomize out of the options that are valid (within the grid)
	while(options[temp] == false);

	if(temp == 0){ 		//left
		headX = squareX -1;
		headY = squareY;
	} 	
	else if(temp == 1){	//up
		headX = squareX;
		headY = squareY +1;
	} 	
	else if(temp == 2){	//right
		headX = squareX + 1;
		headY = squareY ;
	} 	
	else{				//down
		headX = squareX;
		headY = squareY -1;
	}

	initHX = headX;
	initHY = headY;

}


//drawng the square (using the global variable for the square location)
void drawSquare(){
	float startX = (-1.0 + (squareX*(2/(float)x))); //draw from this starting x
	float endX = startX + (2/(float)x); //draw to this ending x
	float startY =(-1.0 + (squareY * (2/(float)x)));	//draw from this starting y
	float endY = startY + (2/(float)x);		//draw to this ending y
	for(float j = startY; j <=endY; j+=0.001){
		for(float i= startX; i <= endX; i +=0.001){
				glBegin(GL_POINTS);
				glColor3f(0,1,0);	//body is green
				glVertex2f(i, j);
				glEnd();
		}

	}

	//printf("here\n");
}

void drawHead(){
	float startX = (-1.0 + (headX*(2/(float)x))); //draw from this starting x
	float endX = startX + (2/(float)x); ///draw to this ending x
	float startY =(-1.0 + (headY * (2/(float)x))); //draw from this starting y
	float endY = startY + (2/(float)x); //draw to this ending y
	for(float j = startY; j <=endY; j+=0.001){
		for(float i= startX; i <= endX; i +=0.001){
				glBegin(GL_POINTS);
					glColor3f(1,0,0);	//red for the head
					glVertex2f(i, j);
				glEnd();
		}

	}

}



void drawgrid(){	//to draw the grid for the GUI
	float c = 0.0;
	float m = (float) x;
	float end = 2.0/m;
	float i, j;

	for(j = (1.0+end); c<=m; c++){
		j -= end;
		for(i = -1.0; i<=1.0; i += 0.001){
			glBegin(GL_POINTS);
			glColor3f(1,1,1);
			glVertex2f(i, j);
			glEnd();
		}
		
	}
    c = 0.0;
	for(i = (-1.0 - end); c<= m; c++){
		i+= end;
		//for(i = -1.0; i<=1.0; i+= end)
		for(j = 1.0; j>=-1; j-=0.001){
			glBegin(GL_POINTS);
			glColor3f(1,1,1);
			glVertex2f(i, j);
			glEnd();
		}
		
	}


}



void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,1,100);

	printf("Click the left mouse button to open the menu.\n");
	printf("You can turn the head of the robot by accessing the submenu (using left mouse click) and clicking on a command.\n");
	printf("The 'r' button will reset the location of the robot.\n");
	printf("The Esc button or 'q' key will exit the program.\n");



	drawgrid(); //draw the grid GUI
	randomizeSquare();	//randomize the square's location
	drawSquare();	//draw the square at its location
	getOptions();	//get the options for the head of the square
	randomizeHead();	//randomize which of the options to draw the head at
	drawHead();		//draw the head of the square

	//flush out to single buffer
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(1,1,1);
	glPointSize(1.0f);




	drawgrid(); //draw the grid GUI

	drawSquare();	//draw the square at its location
	drawHead();		//draw the head of the square

	//flush out to single buffer
	glFlush();

}

void reshape(int w, int h)
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45, (float)((w+0.0f)/h), 1, 100);


glMatrixMode(GL_MODELVIEW);
glViewport(0, 0, w, h);
}


void keyboard(unsigned char key, int xIn, int yIn){
	switch (key)
	{
		case 'q':
		case 27:	//27 is the esc key
			exit(0);
			break;
		case 'r':
			printf("resetting\n");
			squareX = initX;
			squareY =  initY;
			headX = initHX;
			headY = initHY;

			glutPostRedisplay();
			break;
		//glutPostRedisplay();

	}

}

void callBackInit(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(special);
	//glutMouseFunc(mouse);
	//glutMotionFunc(motion);
	//glutPassiveMotionFunc(passive);
	glutReshapeFunc(reshape);
	//glutTimerFunc(0 , FPS, 0);

}

void menuProc(int value){
	getOptions();
	if(value == 1){
		//printf("turn->right\n");
		if(headX > squareX & squareY != 0){
			headX -=1;
			headY -=1;
		}
		else if(headX < squareX & squareY !=(x-1)){
			headX +=1;
			headY +=1;
		}
		else if(headY > squareY & squareX !=(x-1)){
			headY -=1;
			headX +=1;
		}
		else if (headY < squareY & squareX != 0){
			headY +=1;
			headX -=1;
		}
	}
		

	if(value == 2){
		//printf("turn->left\n");
		if(headX > squareX & squareY != (x-1)){
			headX -=1;
			headY +=1;
		}
		else if(headX < squareX & squareY !=0){
			headX +=1;
			headY -=1;
		}
		else if(headY > squareY & squareX !=0){
			headY -=1;
			headX -=1;
		}
		else if (headY < squareY & squareX != (x-1)){
			headY +=1;
			headX +=1;
		}
	}
	if(value == 3 & headX != (x-1) & squareX != (x-1)){
		//printf("move->right\n");
		squareX +=1;
		headX +=1;
	}
	if(value == 4 & headX != 0 & squareX != 0){
		//printf("move->left\n");
		squareX -=1;
		headX -=1;
	}
	if(value == 5 & headY != (x-1) & squareY != (x-1)){
		//printf("move->up\n");
		squareY +=1;
		headY +=1;

	}
	if(value == 6 & headY !=0 & squareY !=0) {
		//printf("move->down\n");
		squareY -=1;
		headY -=1;
		
	}
	glutPostRedisplay();
}

void theMenu(){
	int turnSubMenu_id = glutCreateMenu(menuProc);
	glutAddMenuEntry("right",1);
	glutAddMenuEntry("left",2);


	int moveSubMenu_id = glutCreateMenu(menuProc);
	glutAddMenuEntry("right",3);
	glutAddMenuEntry("left",4);
	glutAddMenuEntry("up",5);
	glutAddMenuEntry("down",6);




	int main_id = glutCreateMenu(menuProc);
	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutAddSubMenu("turn",turnSubMenu_id);
	glutAddSubMenu("move",moveSubMenu_id);

}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);


	Interface natasha;
	x = natasha.getGridSize();

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Natasha's Assignment 1");	//creates the window

	callBackInit();
	theMenu();
	init();

	glutMainLoop();				//starts the event glutMainLoop

	return(0);	
}