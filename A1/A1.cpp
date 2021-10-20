#include <gl/glut.h>
#include <random>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define ICOSAHEDRON_SCALE 2
#define ICOSAHEDRON_X .525731112119133606 * 2
#define ICOSAHEDRON_Z .850650808352039932 * ICOSAHEDRON_SCALE

#define CYLINDER_SIDES 50

#define WORLD_RADIUS 50

#define FOV 100

using namespace std;

void printInstructions()
{
	cout << "INSTRUCTIONS:\n";
	cout << "- You will find objects moving about inside of the imagnary spherical world that hs been created.\n";
	cout << "\tWhat you are looking at on the screen is the camera, that is initially positioned along (1, 0, 0)\n";
	cout << "\t\tIn order to move the camera, use the middle click button on your mouse.\n";
	cout << "\t\tHold down the middle click button and move your mouse - exactly like in blender\n";
	cout << "\t\tNOTE: The camera is always pointing at the center of the world (0,0,0)\n";
	cout << "\t\tand moves around on the surface of the world sphere.\n";
	cout << "- By clicking on any of the objects, you can select them, which will stop them from moving.\n";
	cout << "\tOnce the object is seleted, you can perform transformations on it:\n";
	cout << "\t1. To translate \tthe object, hit the `g` key.\n";
	cout << "\t2. To rotate \tthe object, hit the `r` key.\n";
	cout << "\t3. To scale \tthe object, hit the `s` key.\n";
	cout << "- Once you have selected the type of transformation you want to perform,\n";
	cout << "\tuse the number pad to perform the transformation : \n";
	cout << "\t1. X axis :  +ve = (6)\t -ve = (4)\n";
	cout << "\t2. Y axis :  +ve = (8)\t -ve = (2)\n";
	cout << "\t3. Z axis :  +ve = (1)\t -ve = (9)\n";
	cout << "\tNOTE: You will not be able to translate the object beyond the boundaries of the sphere\n";
	cout << "- IMAGINATION (10m): The object will change the hue of its color everytime you select & unselect it.\n";
	cout << "- After that, by clicking on any other object or in the empty space, the object will continue to move.\n";
	cout << "- The objects will bounce off of the inner surface of the sphere while it's randomly moving about.\n";
	cout << "- They will change the hue of their color each time they bounce.\n";
	cout << "\tNote that the bouce will occur only when the CENTER of the object goes beyond the radius of the sphere.\n";
	cout << "- The objects move and rotate randomly within the world\n";
	cout << "- The objects that you will find in the sphere are Cuboid (b), Icosahedron (i) or Cylinder (l)\n";
	cout << "\tWe will be using the representations provided in the parenthesis to refer to the objects.\n";
	cout << "\tYou can show/hide the objects, using the keys b, i and l each for the objects they represent.\n";
	cout << "- All objects are made purely of triangles, and even though all triangles belonging\n";
	cout << "\t to an object will have the same hue, each of them will have a random saturation and lightness\n";
	cout << "\tNOTE: We use the HSL color system for its practicality and then convert it to RGB.\n";
	cout << "\nThere are certain variables you can customize (in #defines):\n";
	cout << "1. CYLINDER_SIDES - the more, the smoother the cylinder\n";
	cout << "2. WORLD_RADIUS - radius of the world\n";
	cout << "3. FOV - the field of view of your camera\n";
	cout << "4. CYLINDER_HEIGHT, CYLINDER_RADIUS\n";
	cout << "5. winX, winY - The location of the Window on your desktop\n";
	cout << "6. winH, winW - The height and width of the window\n";
	cout << "7. ICOSAHEDRON_SCALE - scale the icosahedron by using a scale multiplier\n";
	cout << "8. const int DRAG - slow down the random movement and rotation speed by increasing this value\n";
	cout << "9. float diff - The amount by which transformations are applied to the objects, when you presss the keys\n";
	cout << "\tNOTE: You can look into the code if you wish to change other constants/presets (there are MANY!)\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";

}


const float CYLINDER_HEIGHT = 5.0f;
const float  CYLINDER_RADIUS = 2.5f;


/* Configurations */

// Tarun's config - comment out for small screens

//const int winX = 1600;
//const int winY = 0;
//
//const int winH = 960;
//const int winW = 960;


// Other's config - comment out for small screens

const int winX = 0;
const int winY = 0;

const int winH = 960;
const int winW = 960;

/* END Configurations */


float GetColorComponent(float temp1, float temp2, float temp3)
{
	if (temp3 < 0.0)
		temp3 += 1.0;
	else if (temp3 > 1.0)
		temp3 -= 1.0;

	if (temp3 < 1.0 / 6.0)
		return temp1 + (temp2 - temp1) * 6.0 * temp3;
	else if (temp3 < 0.5)
		return temp2;
	else if (temp3 < 2.0 / 3.0)
		return temp1 + ((temp2 - temp1) * ((2.0 / 3.0) - temp3) * 6.0);
	else
		return temp1;
}

/// <summary>
/// 
/// </summary>
/// <param name="h">Between 0 and 1; Do ((rand() % 360) / 360)</param>
/// <returns></returns>
glm::vec3 randColorf(float h)
{
	float s, l, above;

	//float above = 0.5f;
	//int aboveInt = (int)((1 - above) * 100);
	//s = ((((float)(rand() % aboveInt)) / aboveInt) + above);
	s = 0.5f + (float)(rand() % 100) / 200.0f;

	l = 0.3f + (float)(rand() % 100) / 250.0f;

	float r = 0, g = 0, b = 0;

	//h = (float)(rand() % 100) / 100.0f;

	if (l != 0.0f)
	{
		if (s == 0.0f)
			r = g = b = l;
		else
		{
			double temp2;
			if (l < 0.5f)
				temp2 = l * (1.0f + s);
			else
				temp2 = l + s - (l * s);

			double temp1 = 2.0f * l - temp2;

			r = GetColorComponent(temp1, temp2, h + 1.0f / 3.0f);
			g = GetColorComponent(temp1, temp2, h);
			b = GetColorComponent(temp1, temp2, h - 1.0f / 3.0f);
		}
	}

	return glm::vec3(r, g, b);
}

//TODO: return a normalized vector
glm::vec3 rand_vec()
{
	return glm::vec3(
		(((float)(rand() % 100)) / 300.0f),
		(((float)(rand() % 100)) / 300.0f),
		(((float)(rand() % 100)) / 300.0f)
	);
}

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

class GLTriangleStripFan {

public:
	glm::vec3 p, n;
	float r, g, b;

	GLTriangleStripFan () {}

	GLTriangleStripFan (
		glm::vec3 vertices[],
		int vp, int vn
	) :
		p(vertices[vp]),
		n(vertices[vn])
	{
		float h = (rand() % 360) / 360;
		glm::vec3 color = randColorf(h);
		r = color.x;
		g = color.y;
		b = color.z;
	}

	GLTriangleStripFan (
		glm::vec3 vertices[],
		int vp, int vn,
		float r, float g, float b
	) :
		p(vertices[vp]),
		n(vertices[vn]),
		r(r), g(g), b(b)
	{}
};

class GLTriangle {

public:
	glm::vec3 p1, p2, p3;
	float r, g, b;

	GLTriangle () {}

	GLTriangle(
		glm::vec3 vertices[],
		int v1, int v2, int v3
	) :
		p1(vertices[v1]),
		p2(vertices[v2]),
		p3(vertices[v3])
	{
		float h = (rand() % 360) / 360;
		glm::vec3 color = randColorf(h);
		r = color.x;
		g = color.y;
		b = color.z;
	}
	
	GLTriangle(
		glm::vec3 vertices[],
		int v1, int v2, int v3,
		float r, float g, float b
	) :
		p1(vertices[v1]),
		p2(vertices[v2]),
		p3(vertices[v3]),
		r(r), g(g), b(b)
	{}
};


glm::vec3 IcosahedronVertices[12];

GLTriangle IcosahedronFaces[20];

glm::vec3 CuboidVertices[8];

GLTriangle CuboidFaces[12];

glm::vec3 CylinderTopVertices[(CYLINDER_SIDES + 1) * 2];
glm::vec3 CylinderBottomVertices[(CYLINDER_SIDES + 1) * 2];

GLTriangleStripFan CylinderFaces[(CYLINDER_SIDES + 1) * 2];

float zoom = WORLD_RADIUS;

int prevX = 0, prevY = 0;
bool cameraRotationEnable = false;

float cub_tX = 10.0f, cub_tY = 0.0f, cub_tZ = 0.0f;
float cub_sX = 2.0f, cub_sY = 2.0f, cub_sZ = 2.0f;
float cub_rX = 0.0f, cub_rY = 0.0f, cub_rZ = 0.0f;

float ico_tX = 0.0f, ico_tY = 0.0f, ico_tZ = 5.0f;
float ico_sX = 2.0f, ico_sY = 2.0f, ico_sZ = 2.0f;
float ico_rX = 0.0f, ico_rY = 0.0f, ico_rZ = 0.0f;

float cyl_tX = 0.0f, cyl_tY = 10.0f, cyl_tZ = 0.0f;
float cyl_sX = 1.0f, cyl_sY = 1.0f, cyl_sZ = 1.0f;
float cyl_rX = 0.0f, cyl_rY = 0.0f, cyl_rZ = 0.0f;


float *tX = NULL, *tY = NULL, *tZ = NULL;
float *sX = NULL, *sY = NULL, *sZ = NULL;
float *rX = NULL, *rY = NULL, *rZ = NULL;

bool cub_rand_move = true;
bool cyl_rand_move = true;
bool ico_rand_move = true;

float cub_rand_tX = 0.0f, cub_rand_tY = 0.0f, cub_rand_tZ = 0.0f;
float cub_rand_rX = 0.0f, cub_rand_rY = 0.0f, cub_rand_rZ = 0.0f;

float ico_rand_tX = 0.0f, ico_rand_tY = 0.0f, ico_rand_tZ = 0.0f;
float ico_rand_rX = 0.0f, ico_rand_rY = 0.0f, ico_rand_rZ = 0.0f;

float cyl_rand_tX = 0.0f, cyl_rand_tY = 0.0f, cyl_rand_tZ = 0.0f;
float cyl_rand_rX = 0.0f, cyl_rand_rY = 0.0f, cyl_rand_rZ = 0.0f;

int selected = 0;

float angle = 0;

bool cub, ico, cyl;
float diff = 0.3;


/// <summary>
/// 0 - Scale
/// 1 - rotate
/// 2 - translate
/// </summary>
int transformType = 2;

glm::vec4 CameraEyeVec(1, 0, 0, 0);
glm::vec4 CameraUpVec(0, 1, 0, 0);
glm::vec4 VerRotVec(0, 0, 1, 0);
glm::vec3 vv3RotAxis(0.0f, 1.0f, 0.0f);

int timer = 1;

void createCub()
{
	CuboidVertices[0] = { 2.0f, 2.0f, 1.0f };
	CuboidVertices[1] = { 2.0f, 2.0f, -1.0f };
	CuboidVertices[2] = { 2.0f, -2.0f, 1.0f };
	CuboidVertices[3] = { 2.0f, -2.0f, -1.0f };
	CuboidVertices[4] = { -2.0f, 2.0f, -1.0f };
	CuboidVertices[5] = { -2.0f, 2.0f, 1.0f };
	CuboidVertices[6] = { -2.0f, -2.0f, -1.0f };
	CuboidVertices[7] = { -2.0f, -2.0f, 1.0f };

	float h = (float)(rand() % 100) / 100.0f;
	glm::vec3 color;

	color = randColorf(h);
	CuboidFaces[0] = GLTriangle(CuboidVertices, 1, 0, 2, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[1] = GLTriangle(CuboidVertices, 0, 1, 5, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[2] = GLTriangle(CuboidVertices, 5, 4, 6, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[3] = GLTriangle(CuboidVertices, 0, 5, 2, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[4] = GLTriangle(CuboidVertices, 4, 5, 1, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[5] = GLTriangle(CuboidVertices, 4, 1, 6, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[6] = GLTriangle(CuboidVertices, 7, 5, 6, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[7] = GLTriangle(CuboidVertices, 7, 2, 5, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[8] = GLTriangle(CuboidVertices, 7, 6, 2, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[9] = GLTriangle(CuboidVertices, 3, 1, 2, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[10] = GLTriangle(CuboidVertices, 3, 6, 1, color.x, color.y, color.z);
	color = randColorf(h);
	CuboidFaces[11] = GLTriangle(CuboidVertices, 3, 2, 6, color.x, color.y, color.z);
}

void createIco()
{
	IcosahedronVertices[0] = { -ICOSAHEDRON_X, 0.0, ICOSAHEDRON_Z };
	IcosahedronVertices[1] = { ICOSAHEDRON_X, 0.0, ICOSAHEDRON_Z };
	IcosahedronVertices[2] = { -ICOSAHEDRON_X, 0.0, -ICOSAHEDRON_Z };
	IcosahedronVertices[3] = { ICOSAHEDRON_X, 0.0, -ICOSAHEDRON_Z };
	IcosahedronVertices[4] = { 0.0, ICOSAHEDRON_Z, ICOSAHEDRON_X };
	IcosahedronVertices[5] = { 0.0, ICOSAHEDRON_Z, -ICOSAHEDRON_X };
	IcosahedronVertices[6] = { 0.0, -ICOSAHEDRON_Z, ICOSAHEDRON_X };
	IcosahedronVertices[7] = { 0.0, -ICOSAHEDRON_Z, -ICOSAHEDRON_X };
	IcosahedronVertices[8] = { ICOSAHEDRON_Z, ICOSAHEDRON_X, 0.0 };
	IcosahedronVertices[9] = { -ICOSAHEDRON_Z, ICOSAHEDRON_X, 0.0 };
	IcosahedronVertices[10] = { ICOSAHEDRON_Z, -ICOSAHEDRON_X, 0.0 };
	IcosahedronVertices[11] = { -ICOSAHEDRON_Z, -ICOSAHEDRON_X, 0.0 };

	float h = (float)(rand() % 100) / 100.0f;
	glm::vec3 color;

	color = randColorf(h);
	IcosahedronFaces[0] = GLTriangle(IcosahedronVertices, 0, 1, 4, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[1] = GLTriangle(IcosahedronVertices, 0, 4, 9, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[2] = GLTriangle(IcosahedronVertices, 9, 4, 5, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[3] = GLTriangle(IcosahedronVertices, 4, 8, 5, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[4] = GLTriangle(IcosahedronVertices, 4, 1, 8, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[5] = GLTriangle(IcosahedronVertices, 8, 1, 10, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[6] = GLTriangle(IcosahedronVertices, 8, 10, 3, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[7] = GLTriangle(IcosahedronVertices, 5, 8, 3, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[8] = GLTriangle(IcosahedronVertices, 5, 3, 2, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[9] = GLTriangle(IcosahedronVertices, 2, 3, 7, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[10] = GLTriangle(IcosahedronVertices, 7, 3, 10, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[11] = GLTriangle(IcosahedronVertices, 7, 10, 6, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[12] = GLTriangle(IcosahedronVertices, 7, 6, 11, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[13] = GLTriangle(IcosahedronVertices, 11, 6, 0, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[14] = GLTriangle(IcosahedronVertices, 0, 6, 1, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[15] = GLTriangle(IcosahedronVertices, 6, 10, 1, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[16] = GLTriangle(IcosahedronVertices, 9, 11, 0, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[17] = GLTriangle(IcosahedronVertices, 9, 2, 11, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[18] = GLTriangle(IcosahedronVertices, 9, 5, 2, color.x, color.y, color.z);
	color = randColorf(h);
	IcosahedronFaces[19] = GLTriangle(IcosahedronVertices, 7, 11, 2, color.x, color.y, color.z);
}

void renderRandomGLTriangle(GLTriangle triangle)
{
	glColor3f(triangle.r, triangle.g, triangle.b);
	glm::vec3 normal(glm::cross(triangle.p2 - triangle.p1, triangle.p3 - triangle.p1));
	glNormal3f(normal.x, normal.y, normal.z);
	//cout << normal.x << "," << normal.y << "," << normal.z << endl;
	glVertex3f(triangle.p1.x, triangle.p1.y, triangle.p1.z);
	glVertex3f(triangle.p2.x, triangle.p2.y, triangle.p2.z);
	glVertex3f(triangle.p3.x, triangle.p3.y, triangle.p3.z);
}

template <size_t N>
void renderAllTriangles(GLTriangle (&triangles)[N])
{
	glBegin(GL_TRIANGLES);
	for (GLTriangle triangle : triangles)
		renderRandomGLTriangle(triangle);
	glEnd();
}


void createCyl()
{
	float diff = (2 * glm::pi<float>()) / (float)CYLINDER_SIDES;
	float angle = 0;

	float h = (float)(rand() % 100) / 100.0f;
	glm::vec3 color;

	int i = 0;
	for (; i < CYLINDER_SIDES; i++)
	{
		float x2 = CYLINDER_RADIUS * cos(angle);
		float z2 = CYLINDER_RADIUS * sin(angle);

		// normal
		const float nf = 1.0f / sqrt(x2 * x2 + z2 * z2), xn = x2 * nf, zn = z2 * nf;

		CylinderTopVertices[i * 2] = { x2, 0, z2 };
		CylinderTopVertices[(i * 2) + 1] = { xn , 0 , zn };
		color = randColorf(h);
		CylinderFaces[i * 2] = GLTriangleStripFan(CylinderTopVertices,
			i * 2, (i * 2) + 1,
			color.x, color.y, color.z
		);

		CylinderBottomVertices[i * 2] = { x2, CYLINDER_HEIGHT, z2 };
		CylinderBottomVertices[(i * 2) + 1] = { xn , 0 , zn };
		color = randColorf(h);
		CylinderFaces[(i * 2) + 1] = GLTriangleStripFan(CylinderBottomVertices,
			i * 2, (i * 2) + 1,
			color.x, color.y, color.z
		);

		angle += diff;
	}

	color = randColorf(h);
	CylinderFaces[i * 2] = GLTriangleStripFan(CylinderTopVertices, 0, 1, color.x, color.y, color.z);
	color = randColorf(h);
	CylinderFaces[(i * 2) + 1] = GLTriangleStripFan(CylinderBottomVertices, 0, 1, color.x, color.y, color.z);
}

//TODO: refine renderStripes function to be more generic

void renderCylinderStripes(GLTriangleStripFan stripes[])
{
	// make the strip
	glBegin(GL_TRIANGLE_STRIP);

	for (int i = 0; i <= CYLINDER_SIDES; i++)
	{
		GLTriangleStripFan top = stripes[( i * 2 ) + 1];
		GLTriangleStripFan bottom = stripes[i * 2];

		glColor3f(top.r, top.g, top.b);

		glNormal3f(top.n.x, top.n.y, top.n.z);
		glVertex3f(top.p.x, top.p.y, top.p.z);

		glColor3f(bottom.r, bottom.g, bottom.b);

		glNormal3f(bottom.n.x, bottom.n.y, bottom.n.z);
		glVertex3f(bottom.p.x, bottom.p.y, bottom.p.z);
	}

	//glColor3f(randColorf(0.1), randColorf(0.3), randColorf(0.5));
	glEnd();
}

void renderCylinderFan(GLTriangleStripFan fans[])
{
	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0, 1, 0);
	glVertex3f(0, CYLINDER_HEIGHT, 0);

	for (int i = 0; i <= CYLINDER_SIDES; i++)
	{
		GLTriangleStripFan fan = fans[( i * 2 ) + 1];

		glColor3f(fan.r, fan.g, fan.b);

		glNormal3f(fan.n.x, fan.n.y, fan.n.z);
		glVertex3f(fan.p.x, fan.p.y, fan.p.z);
	}

	glEnd();

	
	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);

	for (int i = 0; i <= CYLINDER_SIDES; i++)
	{
		GLTriangleStripFan fan = fans[i * 2];

		glColor3f(fan.r, fan.g, fan.b);

		glNormal3f(fan.n.x, fan.n.y, fan.n.z);
		glVertex3f(fan.p.x, fan.p.y, fan.p.z);
	}

	glEnd();
}



void setRandMovement(int index)
{
	glm::vec3 vec = rand_vec();
	switch (index)
	{
	case 1:
		createCub();
		cub_rand_tX = cub_rand_rX = cub_tX < 0 ? vec.x : -vec.x;
		cub_rand_tY = cub_rand_rY = cub_tY < 0 ? vec.y : -vec.y;
		cub_rand_tZ = cub_rand_rZ = cub_tZ < 0 ? vec.z : -vec.z;
		break;
	case 2:
		createIco();
		ico_rand_tX = ico_rand_rX = ico_tX < 0 ? vec.x : -vec.x;
		ico_rand_tY = ico_rand_rY = ico_tY < 0 ? vec.y : -vec.y;
		ico_rand_tZ = ico_rand_rZ = ico_tZ < 0 ? vec.z : -vec.z;
		break;
	case 3:
		createCyl();
		cyl_rand_tX = cyl_rand_rX = cyl_tX < 0 ? vec.x : -vec.x;
		cyl_rand_tY = cyl_rand_rY = cyl_tY < 0 ? vec.y : -vec.y;
		cyl_rand_tZ = cyl_rand_rZ = cyl_tZ < 0 ? vec.z : -vec.z;
		break;
	default:
		break;
	}
}


/// <summary>
/// a callback function that is executed at regular intervals of time registered under 'glutIdleFunc'
/// </summary>
void idleCallBack()
{
	//change this value to slow down random movement
	const int DRAG = 200;

	//the timer must be implemented without blocking the thread
	if ((timer % DRAG) != 0)
	{
		timer++;
		return;
	}

	timer = 1;

	if (cub_rand_move)
	{
		if (sqrt((cub_tX * cub_tX) + (cub_tY * cub_tY) + (cub_tZ * cub_tZ)) > WORLD_RADIUS) setRandMovement(1);
		cub_tX += cub_rand_tX; cub_tY += cub_rand_tY; cub_tZ += cub_rand_tZ;
		cub_rX += cub_rand_rX; cub_rY += cub_rand_rY; cub_rZ += cub_rand_rZ;
	}										

	if (ico_rand_move)
	{
		if (sqrt((ico_tX * ico_tX) + (ico_tY * ico_tY) + (ico_tZ * ico_tZ)) > WORLD_RADIUS) setRandMovement(2);
		ico_tX += ico_rand_tX; ico_tY += ico_rand_tY; ico_tZ += ico_rand_tZ;
		ico_rX += ico_rand_rX; ico_rY += ico_rand_rY; ico_rZ += ico_rand_rZ;
	}

	if (cyl_rand_move)
	{
		if (sqrt((cyl_tX * cyl_tX) + (cyl_tY * cyl_tY) + (cyl_tZ * cyl_tZ)) > WORLD_RADIUS) setRandMovement(3);
		cyl_tX += cyl_rand_tX; cyl_tY += cyl_rand_tY; cyl_tZ += cub_rand_tZ;
		cyl_rX += cyl_rand_rX; cyl_rY += cyl_rand_rY; cyl_rZ += cub_rand_rZ;
	}

	//redisplay after the paramters are changed.
	glutPostRedisplay();
}

//TODO : deal with setMaterial

/// <summary>
/// This is the function that is called in order to render the world. (glutPostRedisplay calls this)
/// </summary>
void display_callback()
{
	//Clear the Windows
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Setup projection window/matrix that we will view
	glMatrixMode(GL_PROJECTION); // Select Projection Matrix

	// replace current matrix with identity matrix
	glLoadIdentity();

	//perspective graphic view for 3D - makes distant objects smaller. Includes FOV, aspect ratio, near, far [near and far are distances FROM the camera to the zNearPlane and zFarPlane]
	gluPerspective(FOV, 1, 0.5, WORLD_RADIUS * 3);


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
	//glutSolidTeapot(1);

	setMaterial(1, 1, 1, 0.8, 0.8, 0.8, 0.1, 0.1, 0.1, 0);

	glPushMatrix();

	glTranslatef(cub_tX, cub_tY, cub_tZ);
	glRotatef(cub_rX, 1, 0, 0);
	glRotatef(cub_rY, 0, 1, 0);
	glRotatef(cub_rZ, 0, 0, 1);
	glScalef(cub_sX, cub_sY, cub_sZ);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	if (cub) { renderAllTriangles(CuboidFaces); }
	glPopMatrix();


	glPushMatrix();

	glTranslatef(ico_tX, ico_tY, ico_tZ);
	glRotatef	(ico_rX, 1, 0, 0);
	glRotatef	(ico_rY, 0, 1, 0);
	glRotatef	(ico_rZ, 0, 0, 1);
	glScalef	(ico_sX, ico_sY, ico_sZ);

	glStencilFunc(GL_ALWAYS, 2, 0xFF);

	if (ico) { renderAllTriangles(IcosahedronFaces); }
	glPopMatrix();


	glPushMatrix();

	glTranslatef(cyl_tX, cyl_tY, cyl_tZ);
	glRotatef	(cyl_rX, 1, 0, 0);
	glRotatef	(cyl_rY, 0, 1, 0);
	glRotatef	(cyl_rZ, 0, 0, 1);
	glScalef	(cyl_sX, cyl_sY, cyl_sZ);
	glTranslatef(0, - CYLINDER_HEIGHT / 2, 0);

	glStencilFunc(GL_ALWAYS, 3, 0xFF);

	if (cyl) {
		renderCylinderStripes(CylinderFaces);
		renderCylinderFan(CylinderFaces);
	}
	glPopMatrix();


	glutSwapBuffers();
}

/// <summary>
/// This function handles all of the mouse clicks
/// </summary>
void mouseClickHandlerFunc(int button, int state, int x, int y)
{
	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);

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
		case GLUT_UP:
			break;
		case GLUT_DOWN:
			break;
		default:
			break;
		}
		break;

	case GLUT_LEFT_BUTTON:
		cub_rand_move = true;
		ico_rand_move = true;
		cyl_rand_move = true;
		switch (state)
		{
		case GLUT_UP:
			GLuint index;
			glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
			switch (index)
			{
			case 0:
				tX = NULL, tY = NULL, tZ = NULL;
				sX = NULL, sY = NULL, sZ = NULL;
				rX = NULL, rY = NULL, rZ = NULL;
				if (selected == 1) setRandMovement(1);
				if (selected == 2) setRandMovement(2);
				if (selected == 3) setRandMovement(3);
				selected = 0;
				break;
			case 1:
				tX = &cub_tX, tY = &cub_tY, tZ = &cub_tZ;
				sX = &cub_sX, sY = &cub_sY, sZ = &cub_sZ;
				rX = &cub_rX, rY = &cub_rY, rZ = &cub_rZ;
				if (selected == 2) setRandMovement(2);
				if (selected == 3) setRandMovement(3);
				selected = 1;
				cub_rand_move = false;
				break;
			case 2:
				tX = &ico_tX, tY = &ico_tY, tZ = &ico_tZ;
				sX = &ico_sX, sY = &ico_sY, sZ = &ico_sZ;
				rX = &ico_rX, rY = &ico_rY, rZ = &ico_rZ;
				if (selected == 1) setRandMovement(1);
				if (selected == 3) setRandMovement(3);
				selected = 2;
				ico_rand_move = false;
				break;
			case 3:
				tX = &cyl_tX, tY = &cyl_tY, tZ = &cyl_tZ;
				sX = &cyl_sX, sY = &cyl_sY, sZ = &cyl_sZ;
				rX = &cyl_rX, rY = &cyl_rY, rZ = &cyl_rZ;
				if (selected == 1) setRandMovement(1);
				if (selected == 2) setRandMovement(2);
				selected = 3;
				cyl_rand_move = false;
				break;
			default:
				break;
			}

			break;
		case GLUT_DOWN:
			break;
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


void customKeysFunc(unsigned char key, int x, int y)
{
	float ntX = tX != NULL ? *tX : NULL;
	float ntY = tY != NULL ? *tY : NULL;
	float ntZ = tZ != NULL ? *tZ : NULL;

	switch (key)
	{
	case 'b':
		cub = cub ? false : true;
		break;
	case 'i':
		ico = ico ? false : true;
		break;
	case 'l':
		cyl = cyl ? false : true;
		break;

	case 'g':
		transformType = 2;
		break;

	case 'r':
		transformType = 1;
		break;

	case 's':
		transformType = 0;
		break;

	case '6': //+X
		switch (transformType)
		{
		case 0:
			if (sX != NULL) *sX += diff;
			break;
		case 1:
			if (rX != NULL) *rX += diff;
			break;
		case 2:
			if (tX != NULL) ntX += diff;
			break;
		default:
			break;
		}
		break;
	case '4': //-X
		switch (transformType)
		{
		case 0:
			if (sX != NULL) *sX -= diff;
			break;
		case 1:
			if (rX != NULL) *rX -= diff;
			break;
		case 2:
			if (tX != NULL) ntX -= diff;
			break;
		default:
			break;
		}
		break;
	case '8': //+Y
		switch (transformType)
		{
		case 0:
			if (sY != NULL) *sY += diff;
			break;
		case 1:
			if (rY != NULL) *rY += diff;
			break;
		case 2:
			if (tY != NULL) ntY += diff;
			break;
		default:
			break;
		}
		break;
	case '2': //-Y
		switch (transformType)
		{
		case 0:
			if (sY != NULL) *sY -= diff;
			break;
		case 1:
			if (rY != NULL) *rY -= diff;
			break;
		case 2:
			if (tY != NULL) ntY -= diff;
			break;
		default:
			break;
		}
		break;
	case '1': //+Z
		switch (transformType)
		{
		case 0:
			if (sZ != NULL) *sZ += diff;
			break;
		case 1:
			if (rZ != NULL) *rZ += diff;
			break;
		case 2:
			if (tZ != NULL) ntZ += diff;
			break;
		default:
			break;
		}
		break;
	case '9': //-Z
		switch (transformType)
		{
		case 0:
			if (sZ != NULL) *sZ -= diff;
			break;
		case 1:
			if (rZ != NULL) *rZ -= diff;
			break;
		case 2:
			if (tZ != NULL) ntZ -= diff;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	if (sqrt((ntX * ntX) + (ntY * ntY) + (ntZ * ntZ)) < WORLD_RADIUS)
	{
		if (tX != NULL) *tX = ntX;
		if (tY != NULL) *tY = ntY;
		if (tZ != NULL) *tZ = ntZ;
	}

	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	/// Initialize GLUT using the command line parameters
	glutInit(&argc, argv);

	/// Setup the size of the opengl window using GLUT: GL Utility Toolkit
	glutInitWindowSize(winH, winW);
	glutInitWindowPosition(winX, winY);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GL_DOUBLE | GLUT_STENCIL);

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

	//gl stencil stuff
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	//set window background color to black
	glClearColor(0, 0, 0, 0);

	glClearStencil(0);

	printInstructions();

	setRandMovement(1);
	setRandMovement(2);
	setRandMovement(3);

	// init the cylinder
	createCub();
	createIco();
	createCyl();

	//enable all figures
	cub = true;
	cyl = true;
	ico = true;
	
	// Step4: defining a callback function for looping into the rasterizer.
	glutDisplayFunc(display_callback);
	

	/// If you enable the timerCallBack_camera, you will see the camera rotating
	/// define a "timer" callback function which is called over and voer again
	glutIdleFunc(idleCallBack);
	
	// define callback for keyboard interactions
	glutKeyboardFunc(customKeysFunc);
	//glutSpecialFunc(specialKeys);
	
	/// define a callback for mouse event
	glutMouseFunc(mouseClickHandlerFunc);
	
	
	// defining callback for mouse movement
	glutMotionFunc(moveAroundTheOnTheSphereUsingMouse);

	// Telling GLUT to go into a never returning loop and execute any callbacks (like glutIdleFunc)
	glutMainLoop();
}

