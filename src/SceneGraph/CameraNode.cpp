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

#include <glm/gtc/matrix_transform.hpp>

#include "CameraNode.h"
#include "Renderer.h"

namespace sg {

CameraNode::CameraNode()
    :m_clipNear(0.1f), m_clipFar(100.0f), m_fieldOfView(60.0f), m_transformChanged(true), m_projectionChanged(true)
{
}
    
void CameraNode::setOrigin(const glm::vec3& origin)
{
    m_origin = origin;
    m_transformChanged = true;
	setNeedsRendering(true);
}

void CameraNode::setPosition(const glm::vec3& position)
{
    m_position = position;
    m_transformChanged = true;
	setNeedsRendering(true);
}

void CameraNode::setRotation(const glm::quat& rotation)
{
    m_orientation = rotation;
    m_transformChanged = true;
	setNeedsRendering(true);
}

void CameraNode::setFieldOfView(float angle)
{
    m_fieldOfView = angle;
    m_projectionChanged = true;
	setNeedsRendering(true);
}

void CameraNode::setClippingNear(float distance)
{
    m_clipNear = distance;
    m_projectionChanged = true;
	setNeedsRendering(true);
}

void CameraNode::setClippingFar(float distance)
{
    m_clipFar = distance;
    m_projectionChanged = true;
	setNeedsRendering(true);
}

const glm::mat4& CameraNode::worldToCamera()
{
    if (m_transformChanged) {
		//set to idenity
		m_worldToCamera = glm::mat4();
        
		m_worldToCamera = glm::translate(m_worldToCamera, m_position);
		m_worldToCamera = glm::translate(m_worldToCamera, m_origin);
		m_worldToCamera = glm::rotate(m_worldToCamera, glm::angle(m_orientation), glm::axis(m_orientation));
	    
        m_transformChanged = false;
    }

    return m_worldToCamera;
}

const glm::mat4& CameraNode::projection()
{
    if (m_projectionChanged) {
        m_projection = glm::perspective(m_fieldOfView, 1.0f, m_clipNear, m_clipFar);
        
        m_projectionChanged = false;
    }
    
    return m_projection;
}

void CameraNode::renderInit(Renderer* renderer)
{
		renderer->setProjectionMatrix(projection());
		renderer->setViewMatrix(worldToCamera());

		setNeedsRendering(false);
}

void CameraNode::render(Renderer* renderer)
{
	if (needsRendering()) {
		renderer->setProjectionMatrix(projection());
		renderer->setViewMatrix(worldToCamera());

		setNeedsRendering(false);
	}
}

} //namespace sg