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

#include <iostream>

#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"


namespace sg {

RenderStateSet::RenderStateSet()
    : nodeId(0), indexedDraw(true), numVertices(0), numNormals(0), numIndices(0), vertexBufferHandle(0), indexBufferHandle(0), normalBufferHandle(0)
{
}

Renderer::Renderer()
{
	m_defaultShaderProgram = ShaderProgramGL::default();
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
	m_cache.clear();
	m_directionalLights.clear();
}

void Renderer::pushMatrix(const glm::mat4& matrix) 
{
	m_modelMatrixStack.push(m_modelMatrix);
	m_modelMatrix = matrix * m_modelMatrix;
}

void Renderer::popMatrix()
{
	m_modelMatrix = m_modelMatrixStack.top();
	m_modelMatrixStack.pop();
}

void Renderer::setIndexedDrawing(bool indexedDraw)
{
	m_renderState.top().indexedDraw = indexedDraw;
}

void Renderer::setVertices(std::shared_ptr<GenericDataArray<float> > vertices)
{
	if (m_renderState.top().vertexBufferHandle != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderState.top().vertexBufferHandle);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices->byteSize(), vertices->rawData());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else {
		m_renderState.top().numVertices = vertices->length();
		m_renderState.top().vertexBufferHandle = uploadArray(vertices);
		
    }
}

void Renderer::setNormals(std::shared_ptr<GenericDataArray<float> > normals)
{
	if (m_renderState.top().normalBufferHandle != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, m_renderState.top().vertexBufferHandle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, normals->byteSize(), normals->rawData());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {
		m_renderState.top().numNormals = normals->length();
		m_renderState.top().normalBufferHandle = uploadArray(normals);
	}
}

void Renderer::setIndices(std::shared_ptr<GenericDataArray<unsigned int> > indices)
{
	if (m_renderState.top().indexBufferHandle != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderState.top().indexBufferHandle);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices->byteSize(), indices->rawData());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else {
		GLuint handle;
		glGenBuffers(1, &handle);

		m_renderState.top().numIndices = indices->length() * indices->elementLength();
		m_renderState.top().indexBufferHandle = handle;
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->byteSize(), indices->rawData(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
	}
}

void Renderer::setShaderProgram(GLuint programHandle)
{
	m_renderState.top().programHandle = programHandle;
}

void Renderer::setProjectionMatrix(const glm::mat4& matrix)
{
	m_projectionMatrix = matrix;
}

void Renderer::setViewMatrix(const glm::mat4& matrix)
{
	m_viewMatrix = matrix;
}

void Renderer::addLightDirectional(const glm::vec3& direction, const glm::vec3& intensity)
{
	m_directionalLights.push_back(direction);
	m_directionalLights.push_back(intensity);
}

unsigned int Renderer::viewWidth()
{
	return m_viewWidth;
}

unsigned int Renderer::viewHeight()
{
	return m_viewHeight;
}

void Renderer::init()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	m_defaultShaderProgram.build();

	m_mvpMatrixHandle = glGetUniformLocation(m_defaultShaderProgram.handle(), "mvpMatrix");
	m_normalMatrixHandle = glGetUniformLocation(m_defaultShaderProgram.handle(), "normalMatrix");
	m_diffuseColorHandle = glGetUniformLocation(m_defaultShaderProgram.handle(), "diffuseColor");
	m_numLightsHandle = glGetUniformLocation(m_defaultShaderProgram.handle(), "numLights");
	m_directionalLightsHandle = glGetUniformLocation(m_defaultShaderProgram.handle(), "directionalLights");

}

void Renderer::resizeViewport(unsigned int width, unsigned int height)
{
	m_viewWidth = width;
	m_viewHeight = height;

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

	glUniformMatrix4fv(m_mvpMatrixHandle, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix * m_viewMatrix * m_modelMatrix));
	glm::mat3 normalMatrix(m_viewMatrix);
	glUniformMatrix3fv(m_normalMatrixHandle, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniform4f(m_diffuseColorHandle, 0.8f, 0.8f, 0.8f, 1.0f);
	glUniform1i(m_numLightsHandle, m_directionalLights.size() / 2);

	glUniform3fv(m_directionalLightsHandle, m_directionalLights.size(), glm::value_ptr(m_directionalLights[0]));
	
	glBindBuffer(GL_ARRAY_BUFFER, stateSet.vertexBufferHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, stateSet.normalBufferHandle);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

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

GLuint Renderer::uploadArray(std::shared_ptr<GenericDataArray<float> > data)
{
    GLuint handle;
    glGenBuffers(1, &handle);
    
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, data->byteSize(), data->rawData(), GL_STATIC_DRAW);
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