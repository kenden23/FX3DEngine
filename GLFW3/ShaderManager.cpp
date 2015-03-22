#include <GL\glew.h>
#include "ShaderManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <list>
#include "MUtilities.h"
using std::string;
using std::list;

ShaderBuildable::ShaderBuildable():shaderProgram(0), shaders()
{
	shaderProgram = glCreateProgram();
	if (shaderProgram == 0) 
	{
		fprintf(stderr, "Error creating shader program\n");
		getchar(); exit(1);
	}
}

ShaderBuildable::~ShaderBuildable()
{

}

void ShaderBuildable::addShader(const char* pShaderText, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);
	if (!shaderObj) 
	{
		fprintf(stderr, "Error creating shader type %d\n", shaderType);
		getchar(); exit(0);
	}

	GLint len = strlen(pShaderText);
	glShaderSource(shaderObj, 1, &pShaderText, &len);
	glCompileShader(shaderObj);
	GLint suc;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &suc);
	if (!suc)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", 
			shaderType, infoLog);
		getchar(); exit(1);
	}
	glAttachShader(shaderProgram, shaderObj);
}

void ShaderBuildable::compileShader()
{
	list<ShaderFileNameType>::iterator i = shaders.begin();
	for ( ; i != shaders.end(); i++)
	{
		string strs = FileManager::read(i->name.c_str());
		if (strs.empty())
		{
			perror("Load shader file: "); 
			perror(i->name.c_str()); 
			perror(" error.");
			getchar(); exit(1);
		}
		switch (i->type)
		{
		case VERTEX_SHADER:
			addShader(strs.c_str(), GL_VERTEX_SHADER);
			break;
		case FRAGMENT_SHADER:
			addShader(strs.c_str(), GL_FRAGMENT_SHADER);
			break;
		}
	}
}

void ShaderBuildable::createShaderProgram()
{
	compileShader();

	GLint suc = 0;
	GLchar errorLog[1024] = {0};

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &suc);
	if (suc == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
		getchar(); exit(1);
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &suc);
	if (!suc)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
		getchar(); exit(1);
	}

	glUseProgram(shaderProgram);
}

//=================Shader Manager
ShaderManager::ShaderManager() : shader(NULL)
{
	shader = new ShaderBuildable;
}
ShaderManager::~ShaderManager()
{
	if (shader) delete shader, shader = NULL;
}