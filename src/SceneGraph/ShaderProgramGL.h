#ifndef SHADER_PROGRAM_GL_H
#define SHADER_PROGRAM_GL_H

#include <string>
#include <vector>

#include <GL/glew.h>

namespace sg {

class ShaderProgramGL
{
public:
	enum ShaderType {
		Vertex,
		Fragment
	};

	ShaderProgramGL();

	static ShaderProgramGL default();

	void addShaderStr(const std::string& srouce, ShaderType type);
	void addShaderFile(const char* filename, ShaderType type);
	
	GLuint build();
	GLuint handle();

private:
	GLuint m_handle;

	std::vector<std::string> m_vertShaderSrc;
	std::vector<std::string> m_fragShaderSrc;
};

} //namespace sg

#endif // SHADER_PROGRAM_GL_H