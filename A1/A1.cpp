#include <gl/glut.h>
#include <random>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace std;

/* Configurations */

// Tarun's config - comment out for small screens

const int winX = 1600;
const int winY = 0;

const int winH = 960;
const int winW = 960;


// Other's config - comment out for small screens

//const int winX = 0;
//const int winY = 0;
//
//const int winH = 960;
//const int winW = 960;

/* END Configurations */

float PI = 3.14;

/*

struct GLVec {
	GLfloat x, y, z;
};

struct GLPoint {
	GLfloat x, y;
};


float randColorf()
{
	return ((float)(rand() % 100)) / 100;
}

float PI = 3.14;

/// <summary>
/// ambient (r,g,b), diffuse (r,g,b), specular (r,g,b), reflectibility/shininess (0-128)
/// </summary>
void setMaterial(
	GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
	GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
	GLfloat specularR, GLfloat specularG, GLfloat specularB,
	int shine)
{
	///create "vectors" from the values for the light
	GLfloat ambient[] = { ambientR, ambientG, ambientB };
	GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
	GLfloat specular[] = { specularR, specularG, specularB };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); //sets how ambience should work for the material
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse); //sets how diffuse should work for the material
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); //sets how specular should work for the material
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

float zoom = 4;
float phi = 0, theta = PI / 2;

int axisX = 1, axisY = 0, axisZ = 0;
float tX = 0, tY = 0, tZ = 0;
float angle = 0;

/// <summary>
/// a callback function that is executed at regular intervals of time registered under 'glutIdleFunc'
/// </summary>
void timerCallBack_camera()
{
	angle += 0.5;

	Sleep(10);

	//redisplay after the paramters are changed.
	glutPostRedisplay();
}



void display_rotating_camera_view()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //you need to clear GL_DEPTH_BUFFER_BIT when depth is enabled

	// Setup projection window/matrix that we will view
	glMatrixMode(GL_PROJECTION); // Select Projection Matrix

	// replace current matrix with identity matrix
	glLoadIdentity();

	//perspective graphic view for 3D - makes distant objects smaller. Includes FOV, aspect ratio, near, far [near and far are distances FROM the camera to the zNearPlane and zFarPlane]
	gluPerspective(80, 1, 0.5, 50);


	// Sets the modelview matrix that helps you setup the matrix that the camera will "look" at
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	GLVec Vec = {
		zoom * cos(phi) * sin(theta),
		zoom * sin(phi) * sin(theta),
		zoom * cos(theta)
	};


	// set the vectors as: eyePosition, lookingAtPosition, RotateCameraVector (rotates around the vector from the camera towards the point it's looking)
	gluLookAt(Vec.x, Vec.y, Vec.z, 0, 0, 0, 0, 1, 0);

	glColor3f(0, 1, 1);
	//parametres: ambient (r,g,b), diffuse (r,g,b), specular (r,g,b), reflectibility/shininess (0-128)
	setMaterial(0.2, 0.2, 0.2, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, 40); //differnet intensities of white light
	//draw teapot
	glutSolidTeapot(1);


	// Insteda of glFlush(), Swap buffers are used when fast rendering of the screen needs to be done
	// they use two beffers which are written to/rendered alternatively
	// Only the modifed parts of one buffer as compared to the previous buffer are actually changed to save CPU/GPU
	//(make sure you have enabled GL_)
	glutSwapBuffers();
}


/// <summary>
/// 
/// </summary>
/// <param name="key">The key that was pressed on the keyboard</param>
/// <param name="x">Mouse pointer position x</param>
/// <param name="y">Mouse pointer position y</param>
void customKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '-': zoom++; break;
	case '=': zoom--; break;
	case 'x': axisX = 1, axisY = 0, axisZ = 0; break;
	case 'y': axisX = 0, axisY = 1, axisZ = 0; break;
	case 'z': axisX = 0, axisY = 0, axisZ = 1; break;
	case 'q': tZ -= 0.2; break;
	case 'e': tZ += 0.2; break;
	default:
		break;
	}

	glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN: tY -= 0.2; break;
	case GLUT_KEY_UP: tY += 0.2; break;
	case GLUT_KEY_LEFT:tX -= 0.2; break;
	case GLUT_KEY_RIGHT: tX += 0.2; break;
	default:
		break;
	}

	glutPostRedisplay();
}


void customMouseFunc(int button, int state, int x, int y)
{
	switch (button)
	{

	case GLUT_MIDDLE_BUTTON:
		switch (state)
		{
		case GLUT_UP: break;
		case GLUT_DOWN: break;
		default:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch (state)
		{
		case GLUT_UP:  break;
		case GLUT_DOWN: tZ += 0.2; break;
		default:
			break;
		}
		break;

	case GLUT_LEFT_BUTTON:
		switch (state)
		{
		case GLUT_UP: break;
		case GLUT_DOWN: tZ -= 0.2; break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

int prevX = 0, prevY = 0;

void customMotionFunc(int x, int y)
{
	theta += (x - prevX) * PI / 180;
	//phi += (y - prevY) * PI / 180;

	glutPostRedisplay();

	prevX = x;
	prevY = y;

	//cout << x << ", " << y << endl;
}

*/



/// <summary>
/// A 3D vector
/// </summary>
struct GLVec {
	GLfloat x, y, z;
};

/// <summary>
/// A 2D point
/// </summary>
struct GLPoint {
	GLfloat x, y;
};


float zoom = 5;
int prevX = 0, prevY = 0;
bool cameraRotationEnable = false;

int axisX = 1, axisY = 0, axisZ = 0;
float tX = 0, tY = 0, tZ = 0;
float angle = 0;

glm::vec4 CameraEyeVec(1, 0, 0, 0);
glm::vec4 CameraUpVec(0, 1, 0, 0);
glm::vec4 VerRotVec(0, 0, 1, 0);
glm::vec3 vv3RotAxis(0.0f, 1.0f, 0.0f);

/// <summary>
/// Create a random value between 0 and 1 (the values or A,R,G,B vary from 0 to 1)
/// </summary>
/// <returns></returns>
float randColorf()
{
	return ((float)(rand() % 100)) / 100;
}


/// <summary>
/// This is the function that is called in order to render the world. (glutPostRedisplay calls this)
/// </summary>
void display_callback()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup projection window/matrix that we will view
	glMatrixMode(GL_PROJECTION); // Select Projection Matrix

	// replace current matrix with identity matrix
	glLoadIdentity();

	//perspective graphic view for 3D - makes distant objects smaller. Includes FOV, aspect ratio, near, far [near and far are distances FROM the camera to the zNearPlane and zFarPlane]
	gluPerspective(80, 1, 0.5, 50);


	// Sets the modelview matrix that helps you setup the matrix that the camera will "look" at
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
	// set the vectors as: eyePosition, lookingAtPosition, RotateCameraVector (rotates around the vector from the /camera /towards the point it's looking)
	gluLookAt(
		zoom * CameraEyeVec.x, 
		zoom * CameraEyeVec.y, 
		zoom * CameraEyeVec.z, 
		0, 0, 0, 
		CameraUpVec.x, 
		CameraUpVec.y, 
		CameraUpVec.z
	);
	
	//draw teapot
	glutSolidTeapot(1);


	glutSwapBuffers();
}

/// <summary>
/// This function handles all of the mouse clicks
/// </summary>
void mouseClickHandlerFunc(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_MIDDLE_BUTTON:
		switch (state)
		{
		case GLUT_UP:
			cameraRotationEnable = false;
			break;
		case GLUT_DOWN:
			cameraRotationEnable = true;
			prevX = x;
			prevY = y;
			vv3RotAxis = glm::vec3(0.0f, (float)(CameraUpVec.y > 0 ? 1 : -1), 0.0f);
			break;
		default:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch (state)
		{
		case GLUT_UP:  break;
		case GLUT_DOWN: tZ += 0.2; break;
		default:
			break;
		}
		break;

	case GLUT_LEFT_BUTTON:
		switch (state)
		{
		case GLUT_UP: break;
		case GLUT_DOWN: tZ -= 0.2; break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}


/// <summary>
/// This function is called whenever the mouse moves on the screen.  
/// (0,0) is at the Top-Left corner.
/// X increases towards Right.
/// Y increases towards Down.
/// </summary>
void moveAroundTheOnTheSphereUsingMouse(int x, int y)
{
	if (cameraRotationEnable)
	{
		int dY = y - prevY;
		int dX = x - prevX;

		// horizontal movememnt (around vertical axis)
		float vangleRad = -dX * 0.01;
		glm::quat vquatRot = glm::angleAxis(vangleRad, vv3RotAxis);
		glm::mat4x4 vmatRot = glm::mat4_cast(vquatRot);
		CameraEyeVec = vmatRot * CameraEyeVec;
		CameraUpVec = vmatRot * CameraUpVec;

		// set axis for vertical rotaion
		VerRotVec = vmatRot * VerRotVec;

		// vertical movememnt (around horizontal axis)
		//angle = atan2f(CameraEyeVec.z, CameraEyeVec.x);
		//angle += glm::half_pi<float>();
		//glm::vec3 hv3RotAxis((float)cos(angle), 0.0f, (float)sin(angle));
		glm::vec3 hv3RotAxis(VerRotVec.x, VerRotVec.y, VerRotVec.z);
		float hangleRad = dY * 0.01;
		glm::quat hquatRot = glm::angleAxis(hangleRad, hv3RotAxis);
		glm::mat4x4 hmatRot = glm::mat4_cast(hquatRot);
		CameraEyeVec = hmatRot * CameraEyeVec;
		CameraUpVec = hmatRot * CameraUpVec;


		//cout << CameraEyeVec.x<< ", "  << CameraEyeVec.y<< ", "  << CameraEyeVec.z << endl;

		glutPostRedisplay();

		prevX = x;
		prevY = y;

		//cout << x << ", " << y << endl;
	}
}


int main(int argc, char* argv[])
{
	/// Initialize GLUT using the command line parameters
	glutInit(&argc, argv);

	/// Setup the size of the opengl window using GLUT: GL Utility Toolkit
	glutInitWindowSize(winH, winW);
	glutInitWindowPosition(winX, winY);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GL_DOUBLE);

	glutCreateWindow("3D Playsphere (Open GL Assignment 1)");

	cout << "Welcome to the 3D playshere!" << endl;
	cout << "window opened at: " << winX << ", " << winY << endl;

	//set up lighting for the scene
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	//This tells opengl to allow us to change the color of the material (without this, the lighting - GL_LIGHT0 - will //result in a grayscale view)
	glEnable(GL_COLOR_MATERIAL);
	
	//enable depth test - do depth comparisons and update the depth buffer
	glEnable(GL_DEPTH_TEST);
	
	//set window background color to black
	glClearColor(0, 0, 0, 0);
	
	
	// Step4: defining a callback function for looping into the rasterizer.
	glutDisplayFunc(display_callback);
	

	///// If you enable the timerCallBack_camera, you will see the camera rotating
	///// define a "timer" callback function which is called over and voer again
	//glutIdleFunc(timerCallBack_camera);
	//
	///// define callback for keyboard interactions
	//glutKeyboardFunc(customKeys);
	//glutSpecialFunc(specialKeys);
	
	/// define a callback for mouse event
	glutMouseFunc(mouseClickHandlerFunc);
	
	
	// defining callback for mouse movement
	glutMotionFunc(moveAroundTheOnTheSphereUsingMouse);

	// Telling GLUT to go into a never returning loop and execute any callbacks (like glutIdleFunc)
	glutMainLoop();
}

