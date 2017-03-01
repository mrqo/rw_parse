#include "stdafx.h"
#include "rwde_window.h"
#include <iostream>

RWDE::Window::Window(char* wndName, int windowHeight, int windowWidth) {
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->wndName = wndName;

	const int SCALE_FACTOR = 2;
	for (int j = -10; j < 10; j++) {
		for (int k = -10; k < 10; k++) {
			baseMatrix[0][j + 10][k + 10] = glm::vec3(j * SCALE_FACTOR, k * SCALE_FACTOR, 0);
			baseMatrix[1][j + 10][k + 10] = glm::vec3((j + 1) * SCALE_FACTOR, k * SCALE_FACTOR, 0);
			baseMatrix[2][j + 10][k + 10] = glm::vec3((j + 1) * SCALE_FACTOR, (k + 1) * SCALE_FACTOR, 0);
			baseMatrix[3][j + 10][k + 10] = glm::vec3(j * SCALE_FACTOR, (k + 1) * SCALE_FACTOR, 0);
		}
	}
}

RWDE::Window::~Window() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

bool RWDE::Window::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Coult not initialize SDL " << SDL_GetError() << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	window = SDL_CreateWindow(wndName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == NULL) {
		std::cout << "Could not create SDL window " << SDL_GetError() << std::endl;
	}

	glContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glContext);

	glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	
	if (res != GLEW_OK) {
		std::cout << "Could not initialize GLEW..." << glewGetErrorString(res) << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	return true;
}

void RWDE::Window::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//int w = 640;
	//int h = 480;
	////gluOrtho2D(0, w, h, 0);
	//glOrtho(0, w, h, 0, -1.0, 10.0);

	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadIdentity();
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glBegin(GL_QUADS);
	//glColor3b(255, 0, 0);
	//glVertex2f(0.0f, 0.0f);
	//glVertex2f(10.0f, 0.0f);
	//glVertex2f(10.0f, 10.0f);
	//glVertex2f(0.0, 10.0f);
	//glEnd();

	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);	
	//glPopMatrix();
	
	drawMatrixField();
}

void RWDE::Window::drawMatrixField() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			glBegin(GL_LINE_LOOP);
			glColor3f(0.0f, 0.0f, 0.0f);
			for (int k = 0; k < 4; k++) {
				glVertex3i(baseMatrix[k][i][j].x, baseMatrix[k][i][j].y, baseMatrix[k][i][j].z);
			}
			glEnd();
		}
	}
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void RWDE::Window::swapBuffers() {
	SDL_GL_SwapWindow(window);
}