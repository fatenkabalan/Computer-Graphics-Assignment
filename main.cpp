#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <glut.h>
#include <math.h>

#define imageWidth 32
#define imageHeight 32
static GLubyte checkImage[imageHeight][imageWidth][3];
static GLuint texName;
int element;
void maketexture();
//for rotation
static GLfloat spin = 0;

// angle of rotation for the camera
float angle = 0.0;
// camera's direction
float lx = 0.0f, lz = -1.0f;
//position of the camera
float x = 0.0f, z = 5.0f;
float red = 1.0f;

void display(void)
{

	//Shading, lighting and shine arrays

	GLfloat sun_light_position[] = { 0.9, 0.9, 1.0, 0.0 };
	GLfloat mat_specular[] = { 1.0 ,1.0 , 1.0 , 1.0 };
	GLfloat mat_shine[] = { 50 };
	GLfloat light_position[] = { 1 , 1 ,1 ,0 };
	GLfloat white_light[] = { 1 ,1 , 1 , 1 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1 ,0.1 ,1 };

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //set lighting modifiers
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.1f, 0.1f, 0.13f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Color and Depth Buffers
	glMatrixMode(GL_MODELVIEW);


	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shine);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light); //simulates the directional impact a light object has on an object
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light); //simulates the bright spot of a light that appears on shiny objects
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //even when it is dark there is usually still some light somewhere



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gluLookAt(x, 0.0f, z,           //to reset camera coordinates
		x + lx, 0.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	//enabling texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);

	//sun
	glPushMatrix();

	glColor3f(1.0f, 1.0f, 0.2f);
	glutSolidSphere(0.25, 20, 20);


	glPopMatrix();

	//mercury
	glPushMatrix();
	glColor3f(0.8f, 0.6f, 0.5f);
	glRotatef(spin * 3, 0, 1, 0);
	
	glTranslatef(0.5, 0, 0.5);

	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	//venus
	glPushMatrix();
	glColor3f(1.0f, 0.3f, 0.0f);
	glRotatef(spin * 4, 0, 1, 0);

	glTranslatef(0.65, 0, 0.8);

	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	//earth
	glPushMatrix();
	glColor3f(0.2f, 0.6f, 0.5f);
	glRotatef(spin * 2, 0, 1, 0);

	glTranslatef(0.8, 0, 0.5);

	glutSolidSphere(0.07, 20, 20);
	glPopMatrix();

	//mars
	glPushMatrix();
	glColor3f(0.9f, 0.9f, 0.6f);
	glRotatef(spin * 4, 0, 1, 0);

	glTranslatef(0.9, 0, 0.8);

	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();

	//jupiter
	glPushMatrix();
	glColor3f(0.9f, 0.8f, 0.6f);
	glRotatef(spin * 3, 0, 1, 0);

	glTranslatef(0.85, 0, 0.9);

	glutSolidSphere(0.09, 20, 20);
	glPopMatrix();

	//uranus
	glPushMatrix();
	glColor3f(0.9f, 0.8f, 0.6f);
	glRotatef(spin * 5, 0, 1, 0);

	glTranslatef(1, 0, 0.9);

	glutSolidSphere(0.09, 20, 20);
	glPopMatrix();

	//neptune
	glPushMatrix();
	glColor3f(0.2f, 0.8f, 0.7f);
	glRotatef(spin * 4, 0, 1, 0);
	glTranslatef(1.2, 0, 1.2);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();

	//pluto
	glPushMatrix();
	glColor3f(0.2f, 0.7f, 0.8f);
	maketexture();
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glRotatef(spin * 5, 0, 1, 0);
	glTranslatef(1.5, 0, 1.5);
	glutSolidSphere(0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	{
		glOrtho(500, 100, 0, 100, 7, 2);
		glMatrixMode(GL_MODELVIEW);
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(2);
		glBegin(GL_POINTS);
		for (int i = 1; i < 5000; i++)
		{
			int xs = rand() % 800;
			int ys = rand() % 600;
			int zs = rand() % 300;
			glVertex3i(xs, ys, zs);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();

}


void changeSize(GLsizei w, GLsizei h) {
	
	if (h == 0)        // (you cant make a window of zero width).
		h = 1;
	GLfloat ratio = w * 1.0 / h;
	glViewport(0, 0, w, h);   // Set the viewport to cover the new window
	glMatrixMode(GL_PROJECTION);   
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // Set the correct perspective for the camera view
	glMatrixMode(GL_MODELVIEW);
}
void processNormalKeys(unsigned char key, int x, int y) {//link the Esc keyboard button with ending the project

	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {  //link arrows with camera movemnets

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

void rotate() {   //planets orbiting around the sun

	spin = spin + 0.06;
	if (spin >= 360) {
		spin = 0;
	}
	display();
}

void mouse(int button, int state, int x, int y) {  //link the mouse clicks with movements
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			glutIdleFunc(rotate);
			break;
		}
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			glutIdleFunc(NULL); break;

		}
	default: break;
	}
}

void maketexture() 
{
	for (size_t i = 0; i < imageHeight; i++)
	{
		for (size_t j = 0; j < imageWidth; j++)
		{
			element = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)element;
			checkImage[i][j][1] = (GLubyte)element;
			checkImage[i][j][2] = (GLubyte)element;
		}
	}
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);              //Initialize glut Library
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);    //Set Windows Position
	glutInitWindowSize(700,600);       //Set Windows Size
	glutCreateWindow("Solar System animation");      //Create Window WIth Title 
	glutDisplayFunc(display);            //Display Drawing Function
	glutIdleFunc(rotate);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(mouse);
	sndPlaySound("interstellar.wav", SND_ASYNC);  //to play sounds in the background,the sound implemented in the project folder
	glutMainLoop();                        //To Keep Showing The Window

}