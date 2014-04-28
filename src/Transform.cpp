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

#include "Transform.h"

Transform::Transform()
{

}
    
glm::mat4 Transform::matrix()
{
    glm::mat4 rotate = glm::rotate(glm::mat4(), glm::angle(m_rotation), glm::axis(m_rotation));
    glm::mat4 scale = glm::scale(glm::mat4(), m_scale);
    glm::mat4 translate = glm::translate(glm::mat4(), m_position);
    
    glm::mat4 transform = translate * scale * rotate;
    
    return transform;
}
    
glm::vec3 Transform::position()
{
    return m_position;
}

void Transform::setPosition(const glm::vec3& position)
{
    m_position = position;
}
    
void Transform::rotate(const glm::quat& rotation)
{
    m_rotation = rotation * m_rotation;
}

void Transform::rotateX(float angle)
{
    m_rotation = glm::angleAxis(angle, glm::vec3(1.0f, 0.0f, 0.0f)) * m_rotation;
}

void Transform::rotateY(float angle)
{
    m_rotation = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f)) * m_rotation;
}

void Transform::rotateZ(float angle)
{
    m_rotation = glm::angleAxis(angle, glm::vec3(0.0f, 0.0f, 1.0f)) * m_rotation;
}

void Transform::scale(const glm::vec3& scale)
{
    m_scale = m_scale * scale;
}

void Transform::translate(const glm::vec3& translation)
{
    m_position = m_position + translation;
}