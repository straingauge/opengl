
#include "Window.h"


Window::Window(const char* str, int width, int height){

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	
	window = SDL_CreateWindow(
		str,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	gl_context=SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1); //enable vsync
	glClearColor(0.15,0.2,0.3,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

}

Window::~Window(){
	glDetachShader(program, v_shader);
	glDeleteShader(v_shader);
	glDetachShader(program, f_shader);
	glDeleteShader(f_shader);
	
	glDeleteProgram(program);
	
	
	for(auto& [id, val]:drawable_objects)
		glDeleteBuffers(1, &id);
		
	
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
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& [id, num_vertex]:drawable_objects ) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				
		glDrawArrays(GL_TRIANGLES, 0, num_vertex);
		
		if (glGetError() != GL_NO_ERROR) std::cout<<"UI Draw error\n";
		glDisableVertexAttribArray(0);
	}
	SDL_GL_SwapWindow(window);
}


GLuint Window::createShader(const char* shader_file, GLenum shader_type){
	//read contents of vertex shader file
	std::string src=readFile(shader_file);
	GLuint shader=0;

	shader = glCreateShader(shader_type);
	if(shader==0) {
		std::cerr<<"Failed to create shader type: "
		<<shader_type<<std::endl;
		exit(1);
	}
	
	const char *c_str = src.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);
	
	GLint compiled=0;
	
	glGetShaderiv(shader, GL_COMPILE_STATUS,&compiled);
	if(!compiled){
		GLint length=0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar * Log = new GLchar[length];

		glGetShaderInfoLog(shader, length, &length, Log);
		std::cerr<<Log<<std::endl;
		delete [] Log;
		exit(1);
	}
	return shader;
}

std::string Window::readFile(const char* txt){
	std::ifstream file_in(txt);
	if(!file_in){
		std::cerr<<"Could not open file!"<<std::endl;
		std::cerr<<"Error code: "<<strerror(errno)<<std::endl;
		exit(1);
	}
	
	std::string output_str((std::istreambuf_iterator<char>(file_in)), 
							std::istreambuf_iterator<char>());
	return output_str;
}

void Window::initOpenGL(const char * vertex_src, const char * fragment_src){
	v_shader=createShader(vertex_src, GL_VERTEX_SHADER);
	f_shader=createShader(fragment_src, GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	glAttachShader(program, v_shader);
	glAttachShader(program, f_shader);
	
	glLinkProgram(program);
	int linked=0;
	glGetProgramiv(program, GL_LINK_STATUS,&linked);
	if(!linked){
		GLint length=0;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar * Log = new GLchar[length];
		glGetProgramInfoLog(program, length, &length, Log);
		std::cerr<<"Linkinng of shader files failed.\n"<<Log<<std::endl;
		delete [] Log;
		exit(1);
	}
	glValidateProgram(program);
	int validate=0;
	glGetProgramiv(program, GL_VALIDATE_STATUS,&validate);
	if(!validate){
		GLint length=0;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar * Log = new GLchar[length];
		glGetProgramInfoLog(program, length, &length, Log);
		std::cerr<<"Validation of shader files failed.\n"<<Log<<std::endl;
		delete [] Log;
		exit(1);
	}
	glUseProgram(program);
	
}


GLuint Window::addMesh(const GLfloat * vertices, GLuint num) {
	GLuint vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* num, vertices,
	GL_STATIC_DRAW);
	
	if( glGetError()!= GL_NO_ERROR) {
		std::cerr<<"Failed to create VBO\n";
		exit(1);
	}
	
	drawable_objects.insert( {vbo, num});
	return vbo;
}
