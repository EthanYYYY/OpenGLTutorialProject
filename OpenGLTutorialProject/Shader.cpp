#include "Shader.h"
#include <fstream>
#include <iostream>

static GLuint CreateShader(const std::string& text, GLenum shaderTye);

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);

Shader::Shader(const std::string& fileName)
{
	m_pragmram = glCreateProgram();

	m_shader[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shader[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(m_pragmram, m_shader[i]);
	}

	glLinkProgram(m_pragmram);
	CheckShaderError(m_pragmram, GL_LINK_STATUS, true, "Error: Progma Linking invalid");

	//验证
	glValidateProgram(m_pragmram);
	CheckShaderError(m_pragmram, GL_VALIDATE_STATUS, true, "Error: Progma Validate invalid");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(m_pragmram, m_shader[i]);
		glDeleteShader(m_shader[i]);
	}

	glDeleteProgram(m_pragmram);
}

void Shader::Bind()
{
	glUseProgram(m_pragmram);
}


static GLuint CreateShader(const std::string& text, GLenum shaderTye) 
{
	GLuint shader = glCreateShader(shaderTye);

	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failure" <<  std::endl;
	}

	const GLchar* shaderSourceString[1];

	GLint shaderSourceStringLength[1];

	shaderSourceString[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	return shader;
}

//检测着色器是否存在错误，输出错误信息
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = {0};

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ";'" << error << "'" << std::endl;
	}
}

//加载着色器文件，并返回着色器的所有内容
static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName<< std::endl;
	}

	return output;
}