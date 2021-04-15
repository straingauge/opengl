#pragma once
#include <SDL2/SDL.h>
#include <GLES3/gl3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

typedef struct {
	GLfloat position[3];
} Vertex;


typedef GLuint
	mesh_object_t;
	
class Window{
	SDL_Window *window;
	SDL_GLContext gl_context;
	SDL_Event event;
	GLuint program, v_shader, f_shader;
	std::map<GLuint, mesh_object_t> drawable_objects;
	
	
public:
	Window()=delete;
	Window(const char* str, int width,int height);
	~Window();
	bool isOpen();
	void update();
	GLuint createShader(const char* shader_file, GLenum shader_type);
	std::string readFile(const char* txt);
	void initOpenGL(const char * vertex_src, const char * fragment_src);
	GLuint addMesh(const GLfloat * vertices, GLuint num);
	
};
