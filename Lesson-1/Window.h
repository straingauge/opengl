#pragma once
#include <SDL2/SDL.h>
#include <GLES3/gl3.h>

class Window{
	SDL_Window *window;
	SDL_GLContext gl_context;
	SDL_Event event;
public:
	Window()=delete;
	Window(const char* str, int width,int height);
	~Window();
	bool isOpen();
	void update();
};
