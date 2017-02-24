#pragma once

#ifndef RWDE_WINDOW
#define RWDE_WINDOW

#include "GL\glew.h"
#include "SDL\SDL.h"

namespace RWDE {
	class Window {
	private:
		int windowHeight;
		int windowWidth;
		char* wndName;

		SDL_Window* window;
		SDL_GLContext glContext;
	public:
		Window(char* wndName, int windowHeight, int windowWidth);
		~Window();

		bool init();
		void clear(float r, float g, float b, float a);
		void swapBuffers();
	};
}

#endif