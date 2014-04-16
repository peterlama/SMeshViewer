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
