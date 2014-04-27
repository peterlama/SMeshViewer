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