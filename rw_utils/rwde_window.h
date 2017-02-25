#pragma once

#ifndef RWDE_WINDOW
#define RWDE_WINDOW

#include "glm\glm.hpp"
#include "GL\glew.h"
#include "SDL\SDL.h"

namespace RWDE {
	class Window {
	private:
		int windowHeight;
		int windowWidth;
		char* wndName;
		glm::vec3 baseMatrix[4][20][20];

		SDL_Window* window;
		SDL_GLContext glContext;
	public:
		Window(char* wndName, int windowHeight, int windowWidth);
		~Window();

		bool init();
		void clear(float r, float g, float b, float a);
		void drawMatrixField();
		void swapBuffers();
	};
}

#endif