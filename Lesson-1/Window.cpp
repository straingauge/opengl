#include "Window.h"


Window::Window(const char* str, int width, int height){
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	
	window = SDL_CreateWindow(
		str,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	gl_context=SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1); //enable vsync
}

Window::~Window(){
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Window::isOpen(){
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym==SDLK_ESCAPE)
				return false;		
	}
	return true;
}

void Window::update(){
	glClearColor(0.15,0.2,0.3,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}


