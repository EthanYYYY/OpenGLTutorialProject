#pragma once

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void Update();
	bool IsClosed();
	void Clear(float red, float green, float blue, float alpha);

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};
