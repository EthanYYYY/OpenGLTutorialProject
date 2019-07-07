#include "Display.h"
#include "GL/glew.h"

#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	// SDL初始化
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// 创建一个窗口
	m_window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!m_window) 
	{
		fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
		return;
	}

	m_glContext=SDL_GL_CreateContext(m_window);
	if (!m_glContext) 
	{
		fprintf(stderr, "Couldn't create context: %s\n", SDL_GetError());
		return;
	}

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Glew Init failure" << std::endl;
	}

	m_isClosed = false;
}

Display::~Display() 
{
	SDL_GL_DeleteContext(m_glContext);
	//关闭窗口，释放相关内存
	SDL_DestroyWindow(m_window);
	//关闭SDL
	SDL_Quit();
}

void Display::Update() 
{
	SDL_GL_SwapWindow(m_window);
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
	}
}

bool Display::IsClosed()
{
	return m_isClosed;
}

void Display::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}