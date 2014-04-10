#include "Renderer.h"
#include <iostream>

namespace sg {

RenderStateSet::RenderStateSet()
    : nodeId(0), indexedDraw(true), numVertices(0), numIndices(0), vertexBufferHandle(0), indexBufferHandle(0)
{
}

Renderer::Renderer()
{
	m_defaultShaderProgram = ShaderProgramGL::default();
}

Renderer::~Renderer()
{
}

void Renderer::push(int nodeId)
{
	RenderStateSet stateSet;

	if (cacheHasEntry(nodeId)) {
		stateSet = cacheGet(nodeId);
	}
	else {
		stateSet.nodeId = nodeId;
	}
	
	m_renderState.push(stateSet);
}

void Renderer::pop()
{
	cacheAdd(m_renderState.top().nodeId, m_renderState.top());
	return m_renderState.pop();
}

void Renderer::reset()
{
    //m_vertexBufferHandle = 0;
}

void Renderer::setIndexedDrawing(bool indexedDraw)
{
	m_renderState.top().indexedDraw = indexedDraw;
}

void Renderer::setVertices(const GenericDataArray<float>* vertices)
{
	if (m_renderState.top().vertexBufferHandle != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderState.top().vertexBufferHandle);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices->byteSize(), vertices->data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else {
		m_renderState.top().numVertices = vertices->length();
		m_renderState.top().vertexBufferHandle = uploadVertices(vertices);
		
    }
}

void Renderer::setIndices(const GenericDataArray<unsigned int>* indices)
{
	if (m_renderState.top().indexBufferHandle != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderState.top().indexBufferHandle);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices->byteSize(), indices->data());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else {
		GLuint handle;
		glGenBuffers(1, &handle);

		m_renderState.top().numIndices = indices->length() * indices->componentLength();
		m_renderState.top().indexBufferHandle = handle;
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->byteSize(), indices->data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
	}
}

void Renderer::setShaderProgram(GLuint programHandle)
{
	m_renderState.top().programHandle = programHandle;
}

void Renderer::init()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	m_defaultShaderProgram.build();
}

void Renderer::resizeViewport(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height);
}

void Renderer::clearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderTriangles()
{
	RenderStateSet stateSet = m_renderState.top();

	glUseProgram(m_defaultShaderProgram.handle());

	glBindBuffer(GL_ARRAY_BUFFER, stateSet.vertexBufferHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if (stateSet.indexedDraw) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, stateSet.indexBufferHandle);
		glDrawElements(GL_TRIANGLES, stateSet.numIndices, GL_UNSIGNED_INT, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, stateSet.numVertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

GLuint Renderer::uploadVertices(const GenericDataArray<float>* vertices)
{
    GLuint handle;
    glGenBuffers(1, &handle);
    
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, vertices->byteSize(), vertices->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return handle;
}

bool Renderer::cacheHasEntry(int key)
{
    return (m_cache.count(key) > 0) ? true : false;
}

RenderStateSet& Renderer::cacheGet(int key)
{
    return m_cache.find(key)->second;
}

void Renderer::cacheAdd(int key, const RenderStateSet& value)
{
    m_cache[key] = value;
}

} //namespace sg