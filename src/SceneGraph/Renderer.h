#ifndef RENDERER_H
#define RENDERER_H

#include <stack>
#include <map>

#include <GL/glew.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "GenericDataArray.h"
#include "ShaderProgramGL.h"

namespace sg {

struct DirectionalLight 
{
	glm::vec3 direction;
	glm::vec3 intensity;
};

class RenderStateSet 
{
public:
    RenderStateSet();
	int nodeId;
	bool indexedDraw;
	int numVertices;
	int numNormals;
	int numIndices;
    GLuint vertexBufferHandle;
	GLuint normalBufferHandle;
    GLuint indexBufferHandle;
	GLuint programHandle;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void push(int nodeId);
	void pop();
    void reset();

	void pushMatrix(const glm::mat4& matrix);
	void popMatrix();

	void setIndexedDrawing(bool indexedDraw);
    void setVertices(const GenericDataArray<float>* vertices);
	void setNormals(const GenericDataArray<float>* normals);
	void setIndices(const GenericDataArray<unsigned int>* indices);
	void setShaderProgram(GLuint programHandle);
	void setProjectionMatrix(const glm::mat4& matrix);
	void setViewMatrix(const glm::mat4& matrix);
	void addLightDirectional(const glm::vec3& direction, const glm::vec3& intensity);

	void init();
	void resizeViewport(unsigned int width, unsigned int height);
	void clearScreen();
	void renderTriangles();
private:
    GLuint uploadVertices(const GenericDataArray<float>* vertices);

	bool cacheHasEntry(int key);
	RenderStateSet& cacheGet(int key);
	void cacheAdd(int key, const RenderStateSet& value);

	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	std::stack<glm::mat4> m_modelMatrixStack;

	GLuint m_mvpMatrixHandle;
	GLuint m_normalMatrixHandle;
	GLuint m_diffuseColorHandle;
	GLuint m_numLightsHandle;
	GLuint m_directionalLightsHandle;

	ShaderProgramGL m_defaultShaderProgram;
	std::vector<glm::vec3> m_directionalLights;

	std::stack<RenderStateSet> m_renderState;
    std::map<int, RenderStateSet> m_cache;

};

} //namespace sg

#endif // RENDERER_H