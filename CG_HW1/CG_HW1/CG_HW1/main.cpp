#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <freeglut/glut.h>
#include "textfile.h"
#include "glm.h"


#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "freeglut.lib")

#ifndef GLUT_WHEEL_UP
# define GLUT_WHEEL_UP   0x0003
# define GLUT_WHEEL_DOWN 0x0004
#endif

#ifndef GLUT_KEY_ESC
# define GLUT_KEY_ESC 0x001B
#endif


# define Z 0x7A



# define X 0x78



# define H 0x68




# define W 0x77



# define C 0x63


#ifndef max
# define max(a,b) (((a)>(b))?(a):(b))
# define min(a,b) (((a)<(b))?(a):(b))
#endif

// Shader attributes
GLint iLocPosition;
GLint iLocColor;
GLint RGBs;

char *filename = "ColorModels/bunny5KC.obj";
GLMmodel* OBJ;
GLfloat* vertices;
GLfloat* colors ;	



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

	int flag = 0 ;  
	float m_x, m_y, m_z;
	float mid_x, mid_y, mid_z;

    vertices = new float[(OBJ->numtriangles) * 9];
	colors = new float[(OBJ->numtriangles) * 9];

	for(i=0; i<(int)OBJ->numtriangles; i++)
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
		vertices[i * 9 + 3] = OBJ->vertices[indv2 * 3 ];
		vertices[i * 9 + 4] = OBJ->vertices[indv2 * 3 + 1];
		vertices[i * 9 + 5] = OBJ->vertices[indv2 * 3 + 2];
		vertices[i * 9 + 6] = OBJ->vertices[indv3 * 3 ];
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
		

		// colors
		/*
		GLfloat c1, c2, c3;
		c1 = OBJ->colors[indv1*3+0];
		c2 = OBJ->colors[indv1*3+1];
		c3 = OBJ->colors[indv1*3+2];

		c1 = OBJ->colors[indv2*3+0];
		c2 = OBJ->colors[indv2*3+1];
		c3 = OBJ->colors[indv2*3+2];

		c1 = OBJ->colors[indv3*3+0];
		c2 = OBJ->colors[indv3*3+1];
		c3 = OBJ->colors[indv3*3+2];
		*/


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

	m_x = (maxVal[0] + minVal[0]) / 2 ; 
	m_y = (maxVal[1] + minVal[1]) / 2 ;
	m_z = (maxVal[2] + minVal[2]) / 2 ;

	mid_x = (maxVal[0] - minVal[0]) / 2;
	mid_y = (maxVal[1] - minVal[1]) / 2;
	mid_z = (maxVal[2] - minVal[2]) / 2;

	for (int j = 0; j < (OBJ->numtriangles) * 3; j++)
	{
		vertices[j*3] -= m_x;
		vertices[j*3+ 1] -= m_y;
		vertices[j*3 + 2] -= m_z;

		
	}
	
	
	/*printf("%f\n", maxVal[0]);
	printf("%f\n", maxVal[1]);
	printf("%f\n", maxVal[2]);
	printf("%f\n", minVal[0]);
	printf("%f\n", minVal[1]);
	printf("%f\n", minVal[2]);*/

	float scale = (maxVal[0] - minVal[0]) / 2 ; 

	scale = max(max(mid_x, mid_y),mid_z);

//	printf("%f\n", scale);

	for (i = 0; i < (OBJ->numtriangles)*9; i++) {
		vertices[i] /= scale;
	}
	
}

void loadOBJModel()
{
	// read an obj model here
	if(OBJ != NULL){
		free(OBJ);
	}
	OBJ = glmReadOBJ(filename);
	printf("%s\n", filename);

	// traverse the color model
	traverseColorModel();
}

void onIdle()
{
	glutPostRedisplay();
}

void onDisplay(void)
{
	// clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(iLocPosition);
	glEnableVertexAttribArray(iLocColor);

	// organize the arrays
	static GLfloat triangle_color[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	static GLfloat triangle_vertex[] = {
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	// bind array pointers to shader
	glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(   iLocColor, 3, GL_FLOAT, GL_FALSE, 0, colors);
	
	// draw the array we just bound
	glDrawArrays(GL_TRIANGLES, 0, (OBJ->numtriangles)*3);

	glutSwapBuffers();
}

void showShaderCompileStatus(GLuint shader, GLint *shaderCompiled)
{
	glGetShaderiv(shader, GL_COMPILE_STATUS, shaderCompiled);
	if(GL_FALSE == (*shaderCompiled))
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character.
		GLchar *errorLog = (GLchar*) malloc(sizeof(GLchar) * maxLength);
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
	if(!vShaderCompiled) system("pause"), exit(123);

	// compile fragment shader
	glCompileShader(f);
	GLint fShaderCompiled;
	showShaderCompileStatus(f, &fShaderCompiled);
	if(!fShaderCompiled) system("pause"), exit(456);

	p = glCreateProgram();

	// bind shader
	glAttachShader(p, f);
	glAttachShader(p, v);

	// link program
	glLinkProgram(p);

	iLocPosition = glGetAttribLocation (p, "av4position");
	iLocColor    = glGetAttribLocation (p, "av3color");
	RGBs = glGetUniformLocation(p, "rgbcolor");

	glUseProgram(p);
}


void onMouse(int who, int state, int x, int y)
{
	printf("%18s(): (%d, %d) ", __FUNCTION__, x, y);

	switch(who)
	{
		case GLUT_LEFT_BUTTON:   printf("left button   "); break;
		case GLUT_MIDDLE_BUTTON: printf("middle button "); break;
		case GLUT_RIGHT_BUTTON:  printf("right button  "); break; 
		case GLUT_WHEEL_UP:      printf("wheel up      "); break;
		case GLUT_WHEEL_DOWN:    printf("wheel down    "); break;
		default:                 printf("0x%02X          ", who); break;
	}

	switch(state)
	{
		case GLUT_DOWN: printf("start "); break;
		case GLUT_UP:   printf("end   "); break;
	}

	printf("\n");
}

void onMouseMotion(int x, int y)
{
	printf("%18s(): (%d, %d) mouse move\n", __FUNCTION__, x, y);
}

int count = 0;
int switchs = 0;
int c = 0;

void onKeyboard(unsigned char key, int x, int y) 
{
	printf("%18s(): (%d, %d) key: %c(0x%02X) ", __FUNCTION__, x, y, key, key);
	switch(key) 
	{
		case GLUT_KEY_ESC: /* the Esc key */ 
			exit(0); 
			break;
		case X:
			count++;
			if (count % 3 == 0)
				filename = "ColorModels/bunny5KC.obj";
			else if (count % 3 == 1 || count % 3 == -1)
				filename = "ColorModels/ziggs.obj";
			else
				filename = "ColorModels/blitzcrank_incognito.obj";
			break;
		case Z:
			count--;
			
			if (count % 3 == 0)
				filename = "ColorModels/bunny5KC.obj";
			else if (count % 3 == 1 || count%3 == -1)
				filename = "ColorModels/ziggs.obj";
			else
				filename = "ColorModels/blitzcrank_incognito.obj";

			break;

		case H:
			printf("\n----------Help Menu----------\n\n");
			printf("h: show help menu\n");
			printf("w: switch with solid : wired rendering mode\n");
			printf("z: move to previous model\n");
			printf("x: move to next model\n");
			printf("m: open/close mouse callback messages\n");
			printf("s: show author information\n");
			printf("c: switch RGB colors\n");
			printf("\n----------Help Menu----------\n\n");
			break;

		case W:
			if (switchs == 0) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				switchs = 1;

			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				switchs = 0;
			}

			break;
		case C:
			c++;
			glUniform1i( RGBs , c );
			break;
	}
	loadOBJModel();
	printf("\n");
}

void onKeyboardSpecial(int key, int x, int y){
	printf("%18s(): (%d, %d) ", __FUNCTION__, x, y);
	switch(key)
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
	if(glewIsSupported("GL_VERSION_2_0")){
		printf("Ready for OpenGL 2.0\n");
	}else{
		printf("OpenGL 2.0 not supported\n");
		system("pause");
		exit(1);
	}

	// load obj models through glm
	loadOBJModel();

	// register glut callback functions
	glutDisplayFunc (onDisplay);
	glutIdleFunc    (onIdle);
	glutKeyboardFunc(onKeyboard);
	glutSpecialFunc (onKeyboardSpecial);
	glutMouseFunc   (onMouse);
	glutMotionFunc  (onMouseMotion);
	glutReshapeFunc (onWindowReshape);
	// set up shaders here
	setShaders();
	
	glEnable(GL_DEPTH_TEST);

	// main loop
	glutMainLoop();

	// free
	glmDelete(OBJ);


	return 0;
}

