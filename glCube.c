#include <GL/glut.h>	// Header file for the GLUT library
#include <GL/gl.h>	// Header file for the OpenGL32 library
#include <GL/glu.h>	// Header file for the GLu32 library
#include <unistd.h>	// Header file for sleeping
#include <time.h>		// Header file for random generation of the game
#include <string.h>	// Header file for string operations
#include <stdio.h>	// Header file for sprintf function

/* Number of the GLUT window */
int window;

/* Arrays defining colored/not colored grid/cube squares */
int gridColors[16];
int cubeColors[6];

/* Cube initial psition */
int cubePos;

/* State of the game, finished/not finished */
int finish;

/* Number of moves made */
int moves;

/* Angle and direction of the cube's rotation */
struct rot_state {

	float angle;
	int direction;
} cube_state;

/* Draws a rectangle with colors 'r', 'g', 'b' and size l by h*/
void drawRectangle(float r, float g, float b, float l, float h) {

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(-l/2, h/2, 0.0f);
	glVertex3f( l/2, h/2, 0.0f);
	glVertex3f( l/2,-h/2, 0.0f);
	glVertex3f(-l/2,-h/2, 0.0f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(-l/2, h/2, 0.0f);
	glVertex3f( l/2, h/2, 0.0f);
	glVertex3f( l/2,-h/2, 0.0f);
	glVertex3f(-l/2,-h/2, 0.0f);
	glEnd();
}

/* Draws a 4 by 4 grid with it's respective gridColors */
void drawGrid() {

	int i, j;
	glPushMatrix();
	for (i=0; i<4; i++) {
		glPushMatrix();
		for (j=0; j<4; j++) {
			if (gridColors[i*4+j] == 0) {
				drawRectangle(0.0f,0.0f, 0.0f, 1.0f, 1.0f);
			} else {
				drawRectangle(0.0f,0.0f, 1.0f, 1.0f, 1.0f);
			}
			glTranslatef(1.0f,0.0f,0.0f);
		}
		glPopMatrix();
		glTranslatef(0.0f,-1.0f,0.0f);
	}
	glPopMatrix();
}

/* Rotates the cube given the direction and angle */
void rotateCube() {

	switch (cube_state.direction) {
	case 0:
		glTranslatef(cubePos%4, -cubePos/4+0.5f, 0.0f);
		glRotatef(-cube_state.angle,1.0f,0.0f,0.0f);
		glTranslatef(0.0f, -0.5f, 0.5f);
		break;
	case 1:
		glTranslatef(cubePos%4, -cubePos/4-0.5f, 0.0f);
		glRotatef(cube_state.angle,1.0f,0.0f,0.0f);
		glTranslatef(0.0f, 0.5f, 0.5f);
		break;
	case 2:
		glTranslatef(cubePos%4-0.5f, -cubePos/4, 0.0f);
		glRotatef(-cube_state.angle,0.0f,1.0f,0.0f);
		glTranslatef(0.5f, 0.0f, 0.5f);
		break;
	case 3:
		glTranslatef(cubePos%4+0.5f, -cubePos/4, 0.0f);
		glRotatef(cube_state.angle,0.0f,1.0f,0.0f);
		glTranslatef(-0.5f, 0.0f, 0.5f);
		break;
	default:
		glTranslatef(cubePos%4, -cubePos/4, 0.5f);
		break;
	}
}

void printToScene(char *string) {

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 0);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
}

void printText() {

	glPushMatrix();
	glTranslatef(-2.8f,0.5f,0.0f);
	printToScene("Use arrow keys to move the cube and colect all the paint.");
	glTranslatef(0.0f,-0.1f,0.0f);
	printToScene("Press 'n' for new game.");
	glTranslatef(0.0f,-0.1f,0.0f);
	printToScene("Press 'Esc' to exit.");
	glTranslatef(0.0f,-0.1f,0.0f);
	char strMoves[15];
	sprintf(strMoves,"Moves: %d",moves);
	printToScene(strMoves);
	glPopMatrix();
}

void drawCube() {

	rotateCube();
	
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	if (cubeColors[2] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glTranslatef(0.0f,0.0f,-1.0f);
	if (cubeColors[0] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90,0.0f,1.0f,0.0f);
	glTranslatef(0.0f,0.0f,0.5f);
	if (cubeColors[5] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glTranslatef(0.0f,0.0f,-1.0f);
	if (cubeColors[4] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(0.0f,0.0f,0.5f);
	if (cubeColors[1] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glTranslatef(0.0f,0.0f,-1.0f);
	if (cubeColors[3] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();
}

void action(void) {

	// Animate the rotation
	float increment = 0.8f;
	int i, last;
	switch (cube_state.direction) {
	case 0:
		if (cube_state.angle <= 89.0f) {
			cube_state.angle += increment;
		} else {
			cube_state.angle = 0.0f;
			cubePos -= 4;
			moves++;
			cube_state.direction = -1;
			last = cubeColors[3];
			for (i=3; i>0; i--) {
				cubeColors[i] = cubeColors[i-1];
			}
			if (finish==0) {
				cubeColors[0] = gridColors[cubePos];
				gridColors[cubePos] = last;
			} else {
				cubeColors[0] = last;
			}
		}
		break;
	case 1:
		if (cube_state.angle <= 89.0f) {
			cube_state.angle += increment;
		} else {
			cube_state.angle = 0.0f;
			cubePos += 4;
			cube_state.direction = -1;
			moves++;
			last = cubeColors[0];
			if (finish==0) {
				cubeColors[0] = gridColors[cubePos];
				gridColors[cubePos] = cubeColors[1];
			} else {
				cubeColors[0] = cubeColors[1];
			}
			for (i=1; i<3; i++) {
				cubeColors[i] = cubeColors[i+1];
			}
			cubeColors[3] = last;
		}
		break;
	case 2:
		if (cube_state.angle <= 89.0f) {
			cube_state.angle += increment;
		} else {
			cube_state.angle = 0.0f;
			cubePos -= 1;
			cube_state.direction = -1;
			moves++;
			last = cubeColors[0];
			if (finish==0) {
				cubeColors[0] = gridColors[cubePos];
				gridColors[cubePos] = cubeColors[4];
			} else {
				cubeColors[0] = cubeColors[4];
			}
			cubeColors[4] = cubeColors[2];
			cubeColors[2] = cubeColors[5];
			cubeColors[5] = last;
		}
		break;
	case 3:
		if (cube_state.angle <= 89.0f) {
			cube_state.angle += increment;
		} else {
			cube_state.angle = 0.0f;
			cubePos += 1;
			cube_state.direction = -1;
			moves++;
			last = cubeColors[0];
			if (finish==0) {
				cubeColors[0] = gridColors[cubePos];
				gridColors[cubePos] = cubeColors[5];
			} else {
				cubeColors[0] = cubeColors[5];
			}
			cubeColors[5] = cubeColors[2];
			cubeColors[2] = cubeColors[4];
			cubeColors[4] = last;
			cube_state.direction = -1;
		}
		break;
	default:
		break;
	}
	last = 1;
	for (i=0; i<6;i++) {
		last = last && cubeColors[i];
	}
	finish = last;
	glutPostRedisplay();
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height) {

	// Initializes cube_state
	cube_state.direction = -1;
	cube_state.angle = 0.0f;
	
	// Clear the background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Clearing of the depth buffer
	glClearDepth(1.0);
	// The type of depth test to do
	glDepthFunc(GL_LESS);
	// Depth testing
	glEnable(GL_DEPTH_TEST);
	// Smooth color shading
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	// Reset the projection matrix
	glLoadIdentity();

	// Calculates the aspect ratio of the window
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
}

/* Function called when the window is resized */
void ReSizeGLScene(int Width, int Height) {

	// Prevents a divide by zero if the window is too small
	if (Height == 0) {
		Height = 1;
	}
	
	// Reset the current viewport and perspective transformation
	glViewport(0, 0, Width, Height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
}

/* Main drawing function */
void DrawGLScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glTranslatef(-1.5f,1.5f,-6.0f);
	printText();
	drawGrid();
	drawCube();

	glPopMatrix();
	glutSwapBuffers();
}

void newGame() {

	srand(time(NULL));
	int i, n;
	finish = 0;
	moves = 0;
	for (i=0; i<16; i++) {
		gridColors[i] = 0;
	}
	for (i=0; i<6; i++) {
		cubeColors[i] = 0;
	}
	i = 0;
	while (i!=7) {
		n = rand() % 16;
		if (gridColors[n] == 0) {
			if (i == 6) {
				cubePos = n;
			} else {
				gridColors[n] = 1;
			}
			i++;
		}
	}
}

/* Function called whenever a key is pressed */
void keyPressed(unsigned char key, int x, int y) {

	switch (key) {
	case 27:
		glutDestroyWindow(window); 
		exit(0);
		break;
	case 'n':
		newGame();
		glutPostRedisplay();
	default:
		break;
	}
}

/* Function called whenever a special key is pressed */
void specialPressed(int key, int x, int y) {

	usleep(100);
	switch (key) {
	case GLUT_KEY_UP:
		if (cubePos > 3) {
			cube_state.direction = 0;
		}
		break;
	case GLUT_KEY_DOWN:
		if (cubePos < 12) {
			cube_state.direction = 1;
		}
		break;
	case GLUT_KEY_LEFT:
		if (cubePos%4 != 0) {
			cube_state.direction = 2;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (cubePos%4 != 3) {
			cube_state.direction = 3;
		}
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	newGame();
	// Initialize GLUT state
	glutInit(&argc, argv);
	
	// Select type of display mode:
	// Double buffer
	// RGBA color
	// Alpha components supported
	// Depth buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	
	// Get a 640 x 480 window
	glutInitWindowSize(640, 480);
	
	// Window starts at the upper left corner of the screen
	glutInitWindowPosition(0, 0);
	
	// Open a window
	window = glutCreateWindow("glCube");
	
	// Register the function to do the OpenGL drawing
	glutDisplayFunc(&DrawGLScene);
	
	// Go fullscreen
	glutFullScreen();
	
	// Redraw the gl scene
	glutIdleFunc(&action);
	
	// Register the function called when the window is resized
	glutReshapeFunc(&ReSizeGLScene);
	
	// Register the function called when the keyboard is pressed
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(specialPressed);
	
	// Initialize the window
	InitGL(640, 480);
	
	// Start event processing engine
	glutMainLoop();
	
	return 1;
}
