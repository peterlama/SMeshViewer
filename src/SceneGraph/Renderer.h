//-----------------------------------------------------------------------------
//Copyright (c) 2014 Peter Lama
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef RENDERER_H
#define RENDERER_H

#include <stack>
#include <map>
#include <memory>

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

/**
* Class for encapsulating OpenGL rendering funcionality. 
* For portablility, scene graph nodes should not use OpenGL rendering commands directly 
*/
class Renderer
{
public:
	Renderer();

	void push(int nodeId);
	void pop();
    void reset();

	void pushMatrix(const glm::mat4& matrix);
	void popMatrix();

	void setIndexedDrawing(bool indexedDraw);
	void setVertices(std::shared_ptr<GenericDataArray<float> > vertices);
	void setNormals(std::shared_ptr<GenericDataArray<float> > normals);
	void setIndices(std::shared_ptr<GenericDataArray<unsigned int> > indices);
	void setShaderProgram(GLuint programHandle);
	void setProjectionMatrix(const glm::mat4& matrix);
	void setViewMatrix(const glm::mat4& matrix);
	void addLightDirectional(const glm::vec3& direction, const glm::vec3& intensity);

	unsigned int viewWidth();
	unsigned int viewHeight();

	void init();
	void resizeViewport(unsigned int width, unsigned int height);
	void clearScreen();
	void renderTriangles();
private:
    GLuint uploadVertices(std::shared_ptr<GenericDataArray<float> > vertices);

	bool cacheHasEntry(int key);
	RenderStateSet& cacheGet(int key);
	void cacheAdd(int key, const RenderStateSet& value);

	unsigned int m_viewWidth;
	unsigned int m_viewHeight;

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