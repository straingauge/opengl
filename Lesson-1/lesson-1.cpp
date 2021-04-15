#include "Window.h"
static const int WIDTH=400;
static const int HEIGHT=400;
int main(){
	Window window("Hello, SDL!",WIDTH,HEIGHT);
	while(window.isOpen()){
		window.update();
	}
}

