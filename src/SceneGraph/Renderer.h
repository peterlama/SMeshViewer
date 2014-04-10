#ifndef RENDERER_H
#define RENDERER_H

#include <stack>
#include <map>

#include <GL/glew.h>

#include "GenericDataArray.h"
#include "ShaderProgramGL.h"

namespace sg {

class RenderStateSet 
{
public:
    RenderStateSet();
	int nodeId;
	bool indexedDraw;
	int numVertices;
	int numIndices;
    GLuint vertexBufferHandle;
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

	void setIndexedDrawing(bool indexedDraw);
    void setVertices(const GenericDataArray<float>* vertices);
	void setIndices(const GenericDataArray<unsigned int>* indices);
	void setShaderProgram(GLuint programHandle);
	
	void init();
	void resizeViewport(unsigned int width, unsigned int height);
	void clearScreen();
	void renderTriangles();
private:
    GLuint uploadVertices(const GenericDataArray<float>* vertices);

	bool cacheHasEntry(int key);
	RenderStateSet& cacheGet(int key);
	void cacheAdd(int key, const RenderStateSet& value);

	ShaderProgramGL m_defaultShaderProgram;

	std::stack<RenderStateSet> m_renderState;
    std::map<int, RenderStateSet> m_cache;

};

} //namespace sg

#endif // RENDERER_H