#include <algorithm>
#include <iostream>

#include "ShaderProgramGL.h"

namespace sg {

const char* defaultVertexShader = "#version 330\n"
    "const int MAX_LIGHTS = 8;\n"
	"const int NUM_LIGHT_ATTRS = 2;\n"
    "layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec3 normal;\n"
	"uniform vec3 directionalLights[MAX_LIGHTS * NUM_LIGHT_ATTRS];\n"
	"uniform int numLights;\n"
	"uniform vec4 diffuseColor;\n"
	"uniform mat4 mvpMatrix;\n"
	"uniform mat3 normalMatrix;\n"
	"smooth out vec4 color;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = mvpMatrix * vec4(position, 1.0);\n"
	"    vec3 normCamSpace = normalize(normalMatrix * normal);\n"
	"    int i;\n"
	"    for (i = 0; i < numLights * NUM_LIGHT_ATTRS; i += NUM_LIGHT_ATTRS) {\n"
	"        float angleIncidence = clamp(dot(normCamSpace, -directionalLights[i]), 0, 1);\n"
	"        color += vec4(directionalLights[i+1], 1.0) * diffuseColor * angleIncidence;\n"
	"    }\n"
	"}\n"
;

const char* defaultFragmentShader = "#version 330\n"
    "smooth in vec4 color;\n"
    "out vec4 outputColor;\n"
    "void main()\n"
    "{\n"
    "    outputColor = color;\n"
    "}\n"
;

void printShaderCompileLog(GLuint shaderHandle)
{
	GLint status;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE){
		GLint infoLogLength;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shaderHandle, infoLogLength, NULL, infoLog);

		std::cerr << infoLog << std::endl;

		delete[] infoLog;
	}
}

void printProgramCompileLog(GLuint programHandle)
{
	GLint status;
	glGetProgramiv(programHandle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE){
		GLint infoLogLength;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(programHandle, infoLogLength, NULL, infoLog);

		std::cerr << infoLog << std::endl;

		delete[] infoLog;
	}
}

ShaderProgramGL::ShaderProgramGL()
    :m_handle(0)
{

}

ShaderProgramGL ShaderProgramGL::default()
{
	ShaderProgramGL defaultProgram;

	defaultProgram.addShaderStr(std::string(defaultVertexShader), Vertex);

	defaultProgram.addShaderStr(std::string(defaultFragmentShader), Fragment);

	return defaultProgram;
}

void ShaderProgramGL::addShaderStr(const std::string& source, ShaderType type)
{
	if (type == Vertex) {
		m_vertShaderSrc.push_back(source);
	}
	else if (type == Fragment) {
		m_fragShaderSrc.push_back(source);
	}
}

GLuint ShaderProgramGL::build()
{
	m_handle = glCreateProgram();

	std::vector<GLuint> shaderList;

	for (std::vector<std::string>::iterator it = m_vertShaderSrc.begin(); it != m_vertShaderSrc.end(); ++it) {
		GLuint shaderHandle = glCreateShader(GL_VERTEX_SHADER);
		const char* shaderSource = it->c_str();
		glShaderSource(shaderHandle, 1, &shaderSource, 0);

		glCompileShader(shaderHandle);
		printShaderCompileLog(shaderHandle);

		shaderList.push_back(shaderHandle);
	}

	for (std::vector<std::string>::iterator it = m_fragShaderSrc.begin(); it != m_fragShaderSrc.end(); ++it) {
		GLuint shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
		const char* shaderSource = it->c_str();
		glShaderSource(shaderHandle, 1, &shaderSource, 0);

		glCompileShader(shaderHandle);
		printShaderCompileLog(shaderHandle);

		shaderList.push_back(shaderHandle);
	}

	for (std::vector<GLuint>::iterator it = shaderList.begin(); it != shaderList.end(); ++it) {
		glAttachShader(m_handle, *it);
	}

	glLinkProgram(m_handle);
	printProgramCompileLog(m_handle);

	//clean up -- not needed anymore
	for (std::vector<GLuint>::iterator it = shaderList.begin(); it != shaderList.end(); ++it) {
		glDetachShader(m_handle, *it);
	}
	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

	return m_handle;
}

GLuint ShaderProgramGL::handle()
{
	return m_handle;
}

} //namespace sg