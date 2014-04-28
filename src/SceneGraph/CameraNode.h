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

#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Node.h"

namespace sg {

class CameraNode : public Node
{
public:
    CameraNode();
    
    void setOrigin(const glm::vec3& origin);
	void setPosition(const glm::vec3& position);
    void setRotation(const glm::quat& rotation);
    
    void setFieldOfView(float angle);
    void setClippingNear(float distance);
    void setClippingFar(float distance);

    const glm::mat4& worldToCamera();
	const glm::mat4& projection();

	virtual void renderInit(Renderer* renderer);
	virtual void render(Renderer* renderer);

private:
	glm::vec3 m_origin;
	glm::vec3 m_position;
    glm::quat m_orientation;
    
	glm::mat4 m_worldToCamera;
	glm::mat4 m_projection;
    
    float m_clipNear;
    float m_clipFar;
    float m_fieldOfView;
    
    bool m_transformChanged;
    bool m_projectionChanged;
};

} //namespace sg

#endif // CAMERA_NODE_H
