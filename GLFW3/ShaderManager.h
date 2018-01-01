#pragma once
#include <stdio.h>
#include <array>
#include <list>
#include <string>
#include <assert.h>
using std::list;
using std::string;

enum SHADERTYPES
{
	VERTEX_SHADER, TESSELLATION_SHADER,
	GEOMETRY_SHADER, FRAGMENT_SHADER, COMPUTE_SHADER
};

struct ShaderFileNameType
{
	string name;
	SHADERTYPES type;
	ShaderFileNameType(const string n = "", SHADERTYPES t = VERTEX_SHADER)
		:name(n), type(t){}
};

/*
Using Builder design pattern. But we can improve that.
*/

//Builder design pattern class 1
class ShaderBuildableBase
{
public:
	// for some situation, this interface is good enought.
	virtual void addShader(const char* pShaderText, GLenum shaderType) = 0;
	virtual void compileShader() = 0;
	virtual void createShaderProgram() = 0;
};

//Builder design pattern class 2
class ShaderBuildable : public ShaderBuildableBase
{
	list<ShaderFileNameType> shaders;
	GLuint shaderProgram;
public:
	ShaderBuildable();
	~ShaderBuildable();

	void loadShaders(list<ShaderFileNameType> &shs)
	{
		shaders.clear();
		shaders = shs;
	}

	inline GLuint getShaderProgram()
	{
		return shaderProgram;
	}

	void addShader(const char* pShaderText, GLenum shaderType);
	void compileShader();
	void createShaderProgram();
};

//Builder design pattern class 3
class ShaderManagerBase
{
public:
	virtual void addVertexShader(string) = 0;
	virtual void addTessellationShader(string) = 0;
	virtual void addGeometryShader(string) = 0;
	virtual void addFragmentShader(string) = 0;	
	virtual void addComputeShader(string) = 0;
	virtual void createShaderProgram() = 0;
	virtual GLuint getShaderProgram() = 0;
	virtual void mapToShaderStringName(GLuint &location, char *name) = 0;
	virtual void setUniformMat4x4ToShader(GLuint location, float **m, int size = 1, bool rowFirst = true) = 0;
};

//Builder design pattern class 4
class ShaderManager : public ShaderManagerBase
{
	ShaderBuildable *shader;
	list<ShaderFileNameType> shaderList;

	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager *getInstance()
	{
		static ShaderManager shm;
		return &shm;
	}

	void addVertexShader(string fileName)
	{
		ShaderFileNameType sft(fileName, VERTEX_SHADER);
		shaderList.push_back(sft);
	}

	void addFragmentShader(string fileName)
	{
		ShaderFileNameType sft(fileName, FRAGMENT_SHADER);
		shaderList.push_back(sft);
	}

	void addGeometryShader(string fileName)
	{
		ShaderFileNameType sft(fileName, GEOMETRY_SHADER);
		shaderList.push_back(sft);
	}

	void addComputeShader(string fileName)
	{
		ShaderFileNameType sft(fileName, COMPUTE_SHADER);
		shaderList.push_back(sft);
	}

	void addTessellationShader(string fileName)
	{
		ShaderFileNameType sft(fileName, TESSELLATION_SHADER);
		shaderList.push_back(sft);
	}

	void createShaderProgram()
	{
		shader->loadShaders(shaderList);
		shader->createShaderProgram();
	}

	GLuint getShaderProgram()
	{
		return shader->getShaderProgram();
	}

	void mapToShaderStringName(GLuint &location, char *name)
	{
		GLuint shaderProgram = getShaderProgram();
		location = glGetUniformLocation(shaderProgram, name);
		assert(~location);
	}

	void setUniformMat4x4ToShader(GLuint location, float **m, int size = 1, bool rowFirst = true)
	{
		glUniformMatrix4fv(location, size, rowFirst, (const GLfloat*)m);
	}
};
