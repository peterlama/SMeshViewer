#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Transform
{
public:
    Transform();
    
    glm::mat4 matrix();
    
    glm::vec3 position();
    void setPosition(const glm::vec3& position);
    
    void rotate(const glm::quat& rotation);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    
    void scale(const glm::vec3& scale);
    
    void translate(const glm::vec3& translation);
    
private:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
};

#endif TRANSFORM_H