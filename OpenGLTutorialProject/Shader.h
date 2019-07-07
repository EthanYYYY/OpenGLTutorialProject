#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& fileName);
	~Shader();

	void Bind();

private:
	static const unsigned int NUM_SHADER = 2;
	GLuint m_pragmram;
	GLuint m_shader[NUM_SHADER];
};

