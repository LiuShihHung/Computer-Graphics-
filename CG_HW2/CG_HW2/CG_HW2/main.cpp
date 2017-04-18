#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <GL/glew.h>
#include <freeglut/glut.h>
#include "textfile.h"
#include "glm.h"

#include "Matrices.h"

int callback = 0;

#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "freeglut.lib")

#ifndef GLUT_WHEEL_UP
# define GLUT_WHEEL_UP   0x0003
# define GLUT_WHEEL_DOWN 0x0004
#endif

#ifndef GLUT_KEY_ESC
# define GLUT_KEY_ESC 0x001B
#endif

#ifndef max
# define max(a,b) (((a)>(b))?(a):(b))
# define min(a,b) (((a)<(b))?(a):(b))
#endif

# define Z 0x7A
# define X 0x78
# define H 0x68
# define W 0x77	
# define C 0x63
# define G 0x67
# define S1 0x73
# define T1 0x74
# define R1 0x72
# define E 0x65
#define L 0x6C
#define P1 0x70
#define O 0x6F

// Shader attributes
GLint iLocPosition;
GLint iLocColor;
GLint iLocMVP;

GLfloat move_x = 0.0;
GLfloat move_y = 0.0;

GLfloat scale_x = 0.0;
GLfloat scale_y = 0.0;

GLfloat rotate_x = 0.0;
GLfloat rotate_y = 0.0;

GLfloat e_x = 0.0;
GLfloat e_y = 0.0;

GLfloat p_x = 0.0;
GLfloat p_y = 0.0;

GLfloat p2_x = 0.0;
GLfloat p2_y = 0.0;

GLfloat l_x = 0.0;
GLfloat l_y = 0.0;

GLint move_x1 = 0;
GLint move_y1 = 0;

GLint scale_x1 = 0;
GLint scale_y1 = 0;

GLint rotate_x1 = 0;
GLint rotate_y1 = 0;

GLint e_x1 = 0;
GLint e_y1 = 0;

GLint p_x1 = 0;
GLint p_y1 = 0;

GLfloat p2_x1 = 0.0;
GLfloat p2_y1 = 0.0;

GLint l_x1 = 0;
GLint l_y1 = 0;

GLfloat move_x2 = 0;
GLfloat move_y2 = 0;

GLfloat scale_x2 = 1;
GLfloat scale_y2 = 1;

GLfloat rotate_x2 = 0;
GLfloat rotate_y2 = 0;

GLfloat rotate_z2 = 0;
GLfloat move_z2 = 0;
GLfloat scale_z2 = 1;

GLfloat e_x2 = 0;
GLfloat e_y2 = 0;
GLint index = 0;

GLint t = 1;
GLint s = 0;
GLint r = 0;
GLint e = 0;
GLint l = 0;
GLint p = 0;
GLint p2 = 0;
GLfloat tx = 0;
GLfloat ty = 0;
GLfloat tz = 0;
GLfloat td = 0;



GLint perspective = 0 ;


GLint decide_move = 0;
char *filename = "ColorModels/bunny5KC.obj";
char *filename1 = "ColorModels/boxC.obj";
GLMmodel* OBJ;
GLMmodel* OBJ1;
GLfloat* vertices;
GLfloat* colors;
GLfloat* vertices_1;
GLfloat* colors_1;


GLint RGBs;


float scale , scale_1;
float m_x, m_y, m_z, m_x1, m_y1, m_z1;
float mid_x, mid_y, mid_z , mid_x1, mid_y1, mid_z1;



void traverseColorModel()
{
	int i;
	int times = 0;
	GLfloat maxVal[3];
	GLfloat minVal[3];

	// TODO:
	//// You should traverse the vertices and the colors of each triangle, and 
	//// then normalize the model to unit size. i.e. Each vertex should be 
	//// bounded in [-1, 1], which will fit the camera clipping window.


	// number of triangles
	OBJ->numtriangles;

	// number of vertices
	OBJ->numvertices;

	// The center position of the model 
	OBJ->position[0] = 0;
	OBJ->position[1] = 0;
	OBJ->position[2] = 0;

	int flag = 0;
	int flag_1 = 0;

	vertices = new float[(OBJ->numtriangles) * 9];
	colors = new float[(OBJ->numtriangles) * 9];

	vertices_1 = new float[(OBJ1->numtriangles) * 9];
	colors_1 = new float[(OBJ1->numtriangles) * 9];

	for (i = 0; i<(int)OBJ->numtriangles; i++)
	{
		// the index of each vertex
		int indv1 = OBJ->triangles[i].vindices[0];
		int indv2 = OBJ->triangles[i].vindices[1];
		int indv3 = OBJ->triangles[i].vindices[2];

		//printf("%d\n", indv1);
		// the index of each color
		int indc1 = indv1;
		int indc2 = indv2;
		int indc3 = indv3;

		// vertices
		GLfloat vx, vy, vz;
		vertices[i * 9] = OBJ->vertices[indv1 * 3];
		vertices[i * 9 + 1] = OBJ->vertices[indv1 * 3 + 1];
		vertices[i * 9 + 2] = OBJ->vertices[indv1 * 3 + 2];
		vertices[i * 9 + 3] = OBJ->vertices[indv2 * 3];
		vertices[i * 9 + 4] = OBJ->vertices[indv2 * 3 + 1];
		vertices[i * 9 + 5] = OBJ->vertices[indv2 * 3 + 2];
		vertices[i * 9 + 6] = OBJ->vertices[indv3 * 3];
		vertices[i * 9 + 7] = OBJ->vertices[indv3 * 3 + 1];
		vertices[i * 9 + 8] = OBJ->vertices[indv3 * 3 + 2];


		if (flag == 0) {
			maxVal[0] = OBJ->vertices[indv1 * 3 + 0];
			maxVal[1] = OBJ->vertices[indv1 * 3 + 1];
			maxVal[2] = OBJ->vertices[indv1 * 3 + 2];
			minVal[0] = OBJ->vertices[indv1 * 3 + 0];
			minVal[1] = OBJ->vertices[indv1 * 3 + 1];
			minVal[2] = OBJ->vertices[indv1 * 3 + 2];

			flag = 9999;
		}

		if (flag != 0) {
			//x max
			if (OBJ->vertices[indv1 * 3 + 0] > maxVal[0]) maxVal[0] = OBJ->vertices[indv1 * 3 + 0];
			if (OBJ->vertices[indv2 * 3 + 0] > maxVal[0]) maxVal[0] = OBJ->vertices[indv2 * 3 + 0];
			if (OBJ->vertices[indv3 * 3 + 0] > maxVal[0]) maxVal[0] = OBJ->vertices[indv3 * 3 + 0];
			//y max
			if (OBJ->vertices[indv1 * 3 + 1] > maxVal[1]) maxVal[1] = OBJ->vertices[indv1 * 3 + 1];
			if (OBJ->vertices[indv2 * 3 + 1] > maxVal[1]) maxVal[1] = OBJ->vertices[indv2 * 3 + 1];
			if (OBJ->vertices[indv3 * 3 + 1] > maxVal[1]) maxVal[1] = OBJ->vertices[indv3 * 3 + 1];
			//z max
			if (OBJ->vertices[indv1 * 3 + 2] > maxVal[2]) maxVal[2] = OBJ->vertices[indv1 * 3 + 2];
			if (OBJ->vertices[indv2 * 3 + 2] > maxVal[2]) maxVal[2] = OBJ->vertices[indv2 * 3 + 2];
			if (OBJ->vertices[indv3 * 3 + 2] > maxVal[2]) maxVal[2] = OBJ->vertices[indv3 * 3 + 2];



			//x min
			if (OBJ->vertices[indv1 * 3 + 0] < minVal[0]) minVal[0] = OBJ->vertices[indv1 * 3 + 0];
			if (OBJ->vertices[indv2 * 3 + 0] < minVal[0]) minVal[0] = OBJ->vertices[indv2 * 3 + 0];
			if (OBJ->vertices[indv3 * 3 + 0] < minVal[0]) minVal[0] = OBJ->vertices[indv3 * 3 + 0];
			//y min
			if (OBJ->vertices[indv1 * 3 + 1] < minVal[1]) minVal[1] = OBJ->vertices[indv1 * 3 + 1];
			if (OBJ->vertices[indv2 * 3 + 1] < minVal[1]) minVal[1] = OBJ->vertices[indv2 * 3 + 1];
			if (OBJ->vertices[indv3 * 3 + 1] < minVal[1]) minVal[1] = OBJ->vertices[indv3 * 3 + 1];
			//z min
			if (OBJ->vertices[indv1 * 3 + 2] < minVal[2]) minVal[2] = OBJ->vertices[indv1 * 3 + 2];
			if (OBJ->vertices[indv2 * 3 + 2] < minVal[2]) minVal[2] = OBJ->vertices[indv2 * 3 + 2];
			if (OBJ->vertices[indv3 * 3 + 2] < minVal[2]) minVal[2] = OBJ->vertices[indv3 * 3 + 2];



		}
		colors[i * 9] = OBJ->colors[indv1 * 3];
		colors[i * 9 + 1] = OBJ->colors[indv1 * 3 + 1];
		colors[i * 9 + 2] = OBJ->colors[indv1 * 3 + 2];
		colors[i * 9 + 3] = OBJ->colors[indv2 * 3];
		colors[i * 9 + 4] = OBJ->colors[indv2 * 3 + 1];
		colors[i * 9 + 5] = OBJ->colors[indv2 * 3 + 2];
		colors[i * 9 + 6] = OBJ->colors[indv3 * 3];
		colors[i * 9 + 7] = OBJ->colors[indv3 * 3 + 1];
		colors[i * 9 + 8] = OBJ->colors[indv3 * 3 + 2];

	}

	m_x = (maxVal[0] + minVal[0]) / 2;
	m_y = (maxVal[1] + minVal[1]) / 2;
	m_z = (maxVal[2] + minVal[2]) / 2;

	mid_x = (maxVal[0] - minVal[0]) / 2;
	mid_y = (maxVal[1] - minVal[1]) / 2;
	mid_z = (maxVal[2] - minVal[2]) / 2;


	scale = (maxVal[0] - minVal[0]) / 2;

	scale = max(max(mid_x, mid_y), mid_z);
	
	for (i = 0; i<(int)OBJ1->numtriangles; i++)
	{
		// the index of each vertex
		int indv1 = OBJ1->triangles[i].vindices[0];
		int indv2 = OBJ1->triangles[i].vindices[1];
		int indv3 = OBJ1->triangles[i].vindices[2];
	
		//printf("%d\n", indv1);
		// the index of each color
		int indc1 = indv1;
		int indc2 = indv2;
		int indc3 = indv3;

		// vertices
		GLfloat vx, vy, vz;
		vertices_1[i * 9] = OBJ1->vertices[indv1 * 3];
		vertices_1[i * 9 + 1] = OBJ1->vertices[indv1 * 3 + 1];
		vertices_1[i * 9 + 2] = OBJ1->vertices[indv1 * 3 + 2];
		vertices_1[i * 9 + 3] = OBJ1->vertices[indv2 * 3];
		vertices_1[i * 9 + 4] = OBJ1->vertices[indv2 * 3 + 1];
		vertices_1[i * 9 + 5] = OBJ1->vertices[indv2 * 3 + 2];
		vertices_1[i * 9 + 6] = OBJ1->vertices[indv3 * 3];
		vertices_1[i * 9 + 7] = OBJ1->vertices[indv3 * 3 + 1];
		vertices_1[i * 9 + 8] = OBJ1->vertices[indv3 * 3 + 2];


		if (flag_1 == 0) {
			maxVal[0] = OBJ1->vertices[indv1 * 3 + 0];
			maxVal[1] = OBJ1->vertices[indv1 * 3 + 1];
			maxVal[2] = OBJ1->vertices[indv1 * 3 + 2];
			minVal[0] = OBJ1->vertices[indv1 * 3 + 0];
			minVal[1] = OBJ1->vertices[indv1 * 3 + 1];
			minVal[2] = OBJ1->vertices[indv1 * 3 + 2];

			flag_1 = 9999;
		}

		if (flag_1 != 0) {
			//x max
			if (OBJ1->vertices[indv1 * 3 + 0] > maxVal[0]) maxVal[0] = OBJ1->vertices[indv1 * 3 + 0];
			if (OBJ1->vertices[indv2 * 3 + 0] > maxVal[0]) maxVal[0] = OBJ1->vertices[indv2 * 3 + 0];
			if (OBJ1->vertices[indv3 * 3 + 0] > maxVal[0]) maxVal[0] = OBJ1->vertices[indv3 * 3 + 0];
			//y max
			if (OBJ1->vertices[indv1 * 3 + 1] > maxVal[1]) maxVal[1] = OBJ1->vertices[indv1 * 3 + 1];
			if (OBJ1->vertices[indv2 * 3 + 1] > maxVal[1]) maxVal[1] = OBJ1->vertices[indv2 * 3 + 1];
			if (OBJ1->vertices[indv3 * 3 + 1] > maxVal[1]) maxVal[1] = OBJ1->vertices[indv3 * 3 + 1];
			//z max
			if (OBJ1->vertices[indv1 * 3 + 2] > maxVal[2]) maxVal[2] = OBJ1->vertices[indv1 * 3 + 2];
			if (OBJ1->vertices[indv2 * 3 + 2] > maxVal[2]) maxVal[2] = OBJ1->vertices[indv2 * 3 + 2];
			if (OBJ1->vertices[indv3 * 3 + 2] > maxVal[2]) maxVal[2] = OBJ1->vertices[indv3 * 3 + 2];



			//x min
			if (OBJ1->vertices[indv1 * 3 + 0] < minVal[0]) minVal[0] = OBJ1->vertices[indv1 * 3 + 0];
			if (OBJ1->vertices[indv2 * 3 + 0] < minVal[0]) minVal[0] = OBJ1->vertices[indv2 * 3 + 0];
			if (OBJ1->vertices[indv3 * 3 + 0] < minVal[0]) minVal[0] = OBJ1->vertices[indv3 * 3 + 0];
			//y min
			if (OBJ1->vertices[indv1 * 3 + 1] < minVal[1]) minVal[1] = OBJ1->vertices[indv1 * 3 + 1];
			if (OBJ1->vertices[indv2 * 3 + 1] < minVal[1]) minVal[1] = OBJ1->vertices[indv2 * 3 + 1];
			if (OBJ1->vertices[indv3 * 3 + 1] < minVal[1]) minVal[1] = OBJ1->vertices[indv3 * 3 + 1];
			//z min
			if (OBJ1->vertices[indv1 * 3 + 2] < minVal[2]) minVal[2] = OBJ1->vertices[indv1 * 3 + 2];
			if (OBJ1->vertices[indv2 * 3 + 2] < minVal[2]) minVal[2] = OBJ1->vertices[indv2 * 3 + 2];
			if (OBJ1->vertices[indv3 * 3 + 2] < minVal[2]) minVal[2] = OBJ1->vertices[indv3 * 3 + 2];



		}
		colors_1[i * 9] = OBJ1->colors[indv1 * 3];
		colors_1[i * 9 + 1] = OBJ1->colors[indv1 * 3 + 1];
		colors_1[i * 9 + 2] = OBJ1->colors[indv1 * 3 + 2];
		colors_1[i * 9 + 3] = OBJ1->colors[indv2 * 3];
		colors_1[i * 9 + 4] = OBJ1->colors[indv2 * 3 + 1];
		colors_1[i * 9 + 5] = OBJ1->colors[indv2 * 3 + 2];
		colors_1[i * 9 + 6] = OBJ1->colors[indv3 * 3];
		colors_1[i * 9 + 7] = OBJ1->colors[indv3 * 3 + 1];
		colors_1[i * 9 + 8] = OBJ1->colors[indv3 * 3 + 2];

	}
	m_x1 = (maxVal[0] + minVal[0]) / 2;
	m_y1 = (maxVal[1] + minVal[1]) / 2;
	m_z1 = (maxVal[2] + minVal[2]) / 2;

	mid_x1 = (maxVal[0] - minVal[0]) / 2;
	mid_y1 = (maxVal[1] - minVal[1]) / 2;
	mid_z1 = (maxVal[2] - minVal[2]) / 2;


	scale_1 = (maxVal[0] - minVal[0]) / 2;

	scale_1 = max(max(mid_x1, mid_y1), mid_z1);
	

}

void loadOBJModel()
{
	// read an obj model here
	if (OBJ != NULL && OBJ1!=NULL) {
		free(OBJ);
		free(OBJ1);
	}
	OBJ = glmReadOBJ(filename);

	OBJ1 = glmReadOBJ(filename1);


	// traverse the color model
	traverseColorModel();
}

void onIdle()
{
	glutPostRedisplay();
}

Vector3 center;
Vector3 up(0, 1, 0);
Vector3 up_vector;
Vector3 Rx(0, 0, 0);
Vector3 Ry(0, 0, 0);	
Vector3 Rz(0, 0, 1);
GLfloat eye_x = 0;
GLfloat eye_y = 0;
GLfloat eye_z = 5;

GLfloat center_x = 0;
GLfloat center_y = 0;
GLfloat center_z = -1;
Vector3 eye(eye_x, eye_y, eye_z);
Vector3 Forward;
Vector3 Right;
GLfloat left = -1.0;
GLfloat right = 1.0;
GLfloat bottom = -1.0;
GLfloat top = 1.0;
GLfloat near1 = 1.0;
GLfloat far1 = 10.0;





void onDisplay(void)

{
	// clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(iLocPosition);
	glEnableVertexAttribArray(iLocColor);

	static GLfloat triangle_color[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};


	static GLfloat triangle_vertex[] = {
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};
	// TODO:
	//// Please define the model transformation matrix, viewing transformation matrix, 
	//// projection transformation matrix

	//T*S*R*N

	//MVP
	Matrix4 T;
	Matrix4 S;
	Matrix4 R;
	Matrix4 N;




	Matrix4 scales = Matrix4(1/scale, 0, 0, 0,
		0, 1/scale, 0, 0,
		0, 0, 1/scale, 0,
		0, 0, 0, 1);
	Matrix4 trans = Matrix4(1, 0, 0, -1 * m_x,
		0, 1, 0, -1 * m_y,
		0, 0, 1, -1 * m_z,
		0, 0, 0, 1);

	N = scales * trans;

	S = Matrix4(scale_x2, 0, 0, 0,
		0, scale_y2, 0, 0,
		0, 0, scale_z2, 0,
		0, 0, 0, 1);

	T = Matrix4(1, 0, 0, move_x2,
		0, 1, 0, move_y2,
		0, 0, 1, move_z2,
		0, 0, 0, 1);

	float sinX = sin(rotate_y2);
	float cosX = cos(rotate_y2);

	Matrix4 Rotate_x = Matrix4(1, 0, 0, 0,
		0, cosX, -1 * sinX, 0,
		0, sinX, cosX, 0,
		0, 0, 0, 1);

	float sinY = sin(rotate_x2);
	float cosY = cos(rotate_x2);

	Matrix4 Rotate_y = Matrix4(cosY, 0, sinY, 0,
		0, 1, 0, 0,
		-1 * sinY, 0, cosY, 0,
		0, 0, 0, 1);

	float sinZ = sin(rotate_z2);
	float cosZ = cos(rotate_z2);

	Matrix4 Rotate_z = Matrix4(cosZ, -1 * sinZ, 0, 0,
		sinZ, cosZ, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	R = Rotate_z* Rotate_y * Rotate_x;

	Matrix4  M = T*S*R*N;

	Matrix4 V = Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	/*********************************************************************************/
	/*********************************************************************************/
	/*********************************************************************************/


	eye = Vector3(eye_x, eye_y, eye_z);
	center = Vector3(center_x, center_y, center_z);

	up = Vector3(0, 1, 0);
    Vector3 t_x = Vector3(eye_x, 0, 0);
	Forward = center - eye;
	Right = Forward.cross(up);
	up_vector = Right.cross(Forward) ;
	
	up = eye + up_vector ;


	//printf("%f\n", eye.length());
	Rz = (center - eye) / (center - eye).length();
	Rx = (center - eye).cross(up - eye) / ((center - eye).cross(up - eye)).length();
	Ry = Rx.cross(Rz);

	Matrix4 Vr;
	Vr.setRow(0, Rx);
	Vr.setRow(1, Ry);
	Vr.setRow(2, -Rz);
	Vr.setRow(3, Vector4(0.0f, 0.0f, 0.0f, 1.0f));

	Matrix4 T0 = Matrix4(
		1, 0, 0, -eye_x,
		0, 1, 0, -eye_y,
		0, 0, 1, -eye_z,
		0, 0, 0, 1);

	V = Vr * T0;





	/*********************************************************************************/
	/*********************************************************************************/
	/*********************************************************************************/

	Matrix4 P = Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, -1, 0,
		0, 0, 0, 1);
	
	if (perspective % 2 == 1) {
		tx = ((right + left) / (right - left));
		ty = ((top + bottom) / (top - bottom));
		tz = -((far1 + near1) / (far1 - near1));
		td = -((2 * far1*near1) / (far1 - near1));

		P = Matrix4(
			2 * near1 / (right - left), 0, tx, 0,
			0, 2 * near1 / (top - bottom), ty, 0,
			0, 0, tz, td,
			0, 0, -1, 0);

	}
	else {
		tx = -((right + left) / (right - left));
		ty = -((top + bottom) / (top - bottom));
		tz = -((far1 + near1) / (far1 - near1));

		P = Matrix4(
			2 / (right - left), 0, 0, tx,
			0, 2 / (top - bottom), 0, ty,
			0, 0, -2 / (far1 - near1), tz,
			0, 0, 0, 1);

	}

	Matrix4 MVP = P*V*M;

	GLfloat mvp[16];
	// row-major ---> column-major
	mvp[0] = MVP[0];  mvp[4] = MVP[1];   mvp[8] = MVP[2];    mvp[12] = MVP[3];
	mvp[1] = MVP[4];  mvp[5] = MVP[5];   mvp[9] = MVP[6];    mvp[13] = MVP[7];
	mvp[2] = MVP[8];  mvp[6] = MVP[9];   mvp[10] = MVP[10];   mvp[14] = MVP[11];
	mvp[3] = MVP[12]; mvp[7] = MVP[13];  mvp[11] = MVP[14];   mvp[15] = MVP[15];

	// bind array pointers to shader
	glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(iLocColor, 3, GL_FLOAT, GL_FALSE, 0, colors);

	// bind uniform matrix to shader
	glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, mvp);

	// draw the array we just bound
	glDrawArrays(GL_TRIANGLES, 0, (OBJ->numtriangles) * 3);
	
	

	Matrix4 scales_1 = Matrix4(1 / scale_1, 0, 0, 0,
		0, 0.1, 0, 0,
		0, 0, 1 / scale_1, 0,
		0, 0, 0, 1);
	Matrix4 trans_1 = Matrix4(1, 0, 0, -1 * m_x1,
		0, 1, 0, -10,
		0, 0, 1, -1 * m_z1,
		0, 0, 0, 1);

	M = scales_1 * trans_1;	

    MVP = P*V*M;

	mvp[0] = MVP[0];  mvp[4] = MVP[1];   mvp[8] = MVP[2];    mvp[12] = MVP[3];
	mvp[1] = MVP[4];  mvp[5] = MVP[5];   mvp[9] = MVP[6];    mvp[13] = MVP[7];
	mvp[2] = MVP[8];  mvp[6] = MVP[9];   mvp[10] = MVP[10];   mvp[14] = MVP[11];
	mvp[3] = MVP[12]; mvp[7] = MVP[13];  mvp[11] = MVP[14];   mvp[15] = MVP[15];

	
	glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices_1);
	glVertexAttribPointer(iLocColor, 3, GL_FLOAT, GL_FALSE, 0, colors_1);
	glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, mvp);

	// draw the array we just bound
	glDrawArrays(GL_TRIANGLES, 0, (OBJ1->numtriangles) * 3);
	
	glutSwapBuffers();
}

void showShaderCompileStatus(GLuint shader, GLint *shaderCompiled)
{
	glGetShaderiv(shader, GL_COMPILE_STATUS, shaderCompiled);
	if (GL_FALSE == (*shaderCompiled))
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character.
		GLchar *errorLog = (GLchar*)malloc(sizeof(GLchar) * maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		fprintf(stderr, "%s", errorLog);

		glDeleteShader(shader);
		free(errorLog);
	}
}

void setShaders()
{
	GLuint v, f, p;
	char *vs = NULL;
	char *fs = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("shader.vert");
	fs = textFileRead("shader.frag");

	glShaderSource(v, 1, (const GLchar**)&vs, NULL);
	glShaderSource(f, 1, (const GLchar**)&fs, NULL);

	free(vs);
	free(fs);

	// compile vertex shader
	glCompileShader(v);
	GLint vShaderCompiled;
	showShaderCompileStatus(v, &vShaderCompiled);
	if (!vShaderCompiled) system("pause"), exit(123);

	// compile fragment shader
	glCompileShader(f);
	GLint fShaderCompiled;
	showShaderCompileStatus(f, &fShaderCompiled);
	if (!fShaderCompiled) system("pause"), exit(456);

	p = glCreateProgram();

	// bind shader
	glAttachShader(p, f);
	glAttachShader(p, v);

	// link program
	glLinkProgram(p);

	iLocPosition = glGetAttribLocation(p, "av4position");
	iLocColor = glGetAttribLocation(p, "av3color");
	iLocMVP = glGetUniformLocation(p, "mvp");
	RGBs = glGetUniformLocation(p, "rgbcolor");



	glUseProgram(p);
}


void onMouse(int who, int state, int x, int y)
{
	printf("%18s(): (%d, %d) ", __FUNCTION__, x, y);
	move_x = 0;
	move_y = 0;
	scale_x = 0;
	scale_y = 0;
	rotate_x = 0;
	rotate_y = 0;
	e_x = 0;
	e_y = 0;
	l_x1 = 0;
	l_y1 = 0;
	p_x = 0;
	p_y = 0;
	p2_x = 0;
	p2_y = 0;
	//p_z = 0;
	switch (who)
	{
	case GLUT_LEFT_BUTTON: {
		printf("left button   ");
		move_x1 = x;
		move_y1 = y;
		scale_x1 = x;
		scale_y1 = y;
		rotate_x1 = x;
		rotate_y1 = y;
		e_x1 = x;
		e_y1 = y;
		l_x1 = x;
		l_y1 = y;
		p_x1 = x;
		p_y1 = y;
		p2 = 0;
		break;
	}
	case GLUT_MIDDLE_BUTTON: {

		printf("middle button "); break;
	}
	case GLUT_RIGHT_BUTTON: {

		printf("right button  "); 
		p2 = 1;
		p2_x1 = x;
		p2_y1 = y;
		break; 
	}
	case GLUT_WHEEL_UP:
	{
		printf("wheel up      ");
		if (r == 1)rotate_z2 += 0.01;
	    if (t == 1)move_z2 += 0.01;
		if (s == 1)scale_z2 += 0.01;
		if (e == 1)eye_z += 0.1;
		break;
	}
	case GLUT_WHEEL_DOWN:
	{
		printf("wheel down    ");
		if (r == 1)rotate_z2 -= 0.01;
		if (t == 1)move_z2 -= 0.01;
		if (s == 1 && scale_z2 > 0.05)scale_z2 -= 0.01;
		if (e == 1)eye_z -= 0.1;
		break;

	}
	default:                 printf("0x%02X          ", who); break;
	}

	switch (state)
	{
	case GLUT_DOWN: printf("start "); break;
	case GLUT_UP:   printf("end   "); break;
	}

	printf("\n");
}

void onMouseMotion(int x, int y)
{

	move_x = (x - move_x1);
	move_x = move_x / 1000;
	move_y = -(y - move_y1);
	move_y = move_y / 1000;
	if (t == 1) {
		move_x2 += move_x;
		move_y2 += move_y;

	}
	move_x1 = x;
	move_y1 = y;


	scale_y = -(y - scale_y1);
	scale_y = scale_y / 1000;
	scale_x = (x - scale_x1);
	scale_x = scale_x / 1000;
	if (s == 1) {
		if (scale_x2 + scale_x > 0.05)
			scale_x2 += scale_x;
		if (scale_y2 + scale_y > 0.05)
			scale_y2 += scale_y;
	}
	scale_x1 = x;
	scale_y1 = y;

	rotate_x = (x - rotate_x1);
	rotate_x = rotate_x / 1000;
	rotate_y = -(y - rotate_y1);
	rotate_y = rotate_y / 1000;
	if (r == 1) {
		rotate_x2 += rotate_x;
		rotate_y2 += rotate_y;
	}
	rotate_x1 = x;
	rotate_y1 = y;
	
	e_x = (x - e_x1);
	e_y = -(y - e_y1);
	if (e == 1) {

	eye_x += (e_x / 1000);
	eye_y += (e_y / 1000);

	}
	e_x1 = x;
	e_y1 = y;

	l_x = (x - l_x1);
	l_y = -(y - l_y1);
	if (l == 1) {

		center_x += (l_x / 1000);
		center_y += (l_y / 1000);

	}
	l_x1 = x;
	l_y1 = y;

	p_x = (x - p_x1);
	p_y = -(y - p_y1);
	if (p == 1 && p2 == 0) {

	    right += (p_x / 100);
	    left -= (p_x / 100);	
		top += (p_y / 100);
		bottom -= (p_y / 100);

	}
	p_x1 = x;
	p_y1 = y;


	p2_x = (x - p2_x1);
	p2_y = -(y - p2_y1);

	if (p == 1 && p2 == 1 ) {
		near1 += (p2_x/100);
		far1 += (p2_y/100);
	}
	p2_x1 = x;
	p2_y1 = y;
	

	printf("%18s(): (%d, %d) mouse move\n", __FUNCTION__, x, y);


}
int count = 0;
int switchs = 0;
int c = 0;
int g = 1;
int o = 0;


void onKeyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_ESC: /* the Esc key */
		exit(0);
		break;
	case X:
		count++;
		printf("move to next model \n");
		printf("load model form : %s \n", filename);
		if (count % 3 == 0)
			filename = "ColorModels/bunny5KC.obj";
		else if (count % 3 == 1 || count % 3 == -1)
			filename = "ColorModels/ziggs.obj";
		else
			filename = "ColorModels/blitzcrank_incognito.obj";
		break;
	case Z:
		count--;
		printf("move to previous model \n");
		printf("load model form : %s \n" , filename);
		if (count % 3 == 0)
			filename = "ColorModels/bunny5KC.obj";
		else if (count % 3 == 1 || count % 3 == -1)
			filename = "ColorModels/ziggs.obj";
		else
			filename = "ColorModels/blitzcrank_incognito.obj";

		break;

	case H:
		printf("\n----------Help Menu----------\n\n");
		printf("\n**********keyboard control**********\n\n");
		printf("h: show help menu\n");
		printf("w: switch with solid : wired rendering mode\n");
		printf("z: move to previous model\n");
		printf("x: move to next model\n");
		printf("v: show author information\n");
		printf("c: switch RGB colors\n");
		printf("o: switch between orthogonal / perspective projection\n");
		printf("i: show current model name and current control model\n");
		printf("\n**********mouse switch**********\n\n");
		printf("s: go to OBJECT scale mode \n");
		printf("t: go to OBJECT translate mode \n");
		printf("r: go to OBJECT rotate mode \n");
		printf("l: go to CENTER(look at) translate mode \n");
		printf("e: go to EYE translate mode \n");
		printf("p: go to PROJECTION mode \n");
	
		printf("\n----------Help Menu----------\n\n");
		break;

	case W:
		if (switchs == 0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			printf("stwitch to wired model\n");
			switchs = 1;

		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			switchs = 0;
			printf("stwitch to solid model\n");
		}

		break;
	case C:
		printf("filter index %d\n", (index % 4)+1);

		c++;
		glUniform1i(RGBs, c);
		index++;
		break;
	case G:
		g = 1;
		e = 0;
		l = 0;
		p = 0;
		o = 0;
		printf("forward vector = (%f , %f ,%f)\n" , Forward.x , Forward.y, Forward.z);
		break;
	case E:
		e = 1;
		g = 0;
		t = 0;
		s = 0;
		r = 0;
		l = 0;
		o = 0;
		p = 0;
		printf("mode : eye translate\n");
		break;

	case S1:
		
			t = 0;
			s = 1;
			e = 0;
			l = 0;
			p = 0;
			r = 0;
			o = 0;
			printf("mode : object scaling\n");
		break;
	case T1:
	
	
			t = 1;
			s = 0;
			e = 0;
			l = 0;
			p = 0;
			r = 0;
			o = 0;
			printf("mode : object translate\n");
	
		break;
	case R1:
	
			t = 0;
			s = 0;
			e = 0;
			l = 0;
			p = 0;
			r = 1;
			o = 0;
			printf("mode : object rotation\n");
		break;
	case L :
		
			l = 1;
			e = 0;
			o = 0;
			p = 0;
			s = 0;
			t = 0;
			r = 0;
			printf("mode :look at translate\n");

		
		break;
	case P1 :
		p = 1;
		e = 0;
		g = 0;
		t = 0;
		s = 0;
		r = 0;
		l = 0;
		o = 0;
		printf("mode :projection contorl\n");
		break;


	case O :
		perspective += 1;
		o = 1;
		printf("switch projection moede\n");
			break;
	case 'i':
		printf("model name : %s\n", filename);
		printf("active action mode :");
		if (t == 1) printf("object translation\n");
		else if (r == 1) printf("object rotation\n");
		else if (s == 1)printf("object scaling\n");
		else if (e == 1)printf("eye translation\n");
		else if (p == 1)printf("projection control\n");
		else if (o == 1)printf("projection control\n");
		else if (l == 1)printf("cneter(look at) translation\n");
		else
		break;

	}
	loadOBJModel();
	printf("\n");
}


void onKeyboardSpecial(int key, int x, int y) {
	printf("%18s(): (%d, %d) ", __FUNCTION__, x, y);
	switch (key)
	{
	case GLUT_KEY_LEFT:
		printf("key: LEFT ARROW");
		break;

	case GLUT_KEY_RIGHT:
		printf("key: RIGHT ARROW");
		break;

	default:
		printf("key: 0x%02X      ", key);
		break;
	}
	printf("\n");
}


void onWindowReshape(int width, int height)
{
	printf("%18s(): %dx%d\n", __FUNCTION__, width, height);
}

int main(int argc, char **argv)
{
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// create window
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("10420 CS550000 CG HW1 TA");

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0")) {
		printf("Ready for OpenGL 2.0\n");
	}
	else {
		printf("OpenGL 2.0 not supported\n");
		system("pause");
		exit(1);
	}

	// load obj models through glm
	loadOBJModel();

	// register glut callback functions
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutSpecialFunc(onKeyboardSpecial);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);
	glutReshapeFunc(onWindowReshape);
	// set up shaders here
	setShaders();

	glEnable(GL_DEPTH_TEST);

	// main loop
	glutMainLoop();

	// free
	glmDelete(OBJ);


	return 0;
}

