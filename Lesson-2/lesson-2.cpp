#include <iostream>
#include "Window.h"
static const int WIDTH=400;
static const int HEIGHT=400;

int main(){
	static const Vertex triangle[]={ 
		-0.8f, -0.8f, 0.0f,
		 0.8f, -0.8f, 0.0f,
		 0.0f,  0.8f, 0.0f,
	};
										
						
	Window window("Hello, triangle!",WIDTH,HEIGHT);
	window.initOpenGL("vertex.glsl","fragment.glsl");
	window.addMesh((GLfloat *) triangle, sizeof(triangle)/sizeof(Vertex));
	

	while(window.isOpen()){
		window.update();
	}
}

