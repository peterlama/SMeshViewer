#ifndef LIGHT_DIRECTIONAL_NODE_H
#define LIGHT_DIRECTIONAL_NODE_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Node.h"

namespace sg {
    
class LightDirectionalNode: public Node
{
public:
    LightDirectionalNode();
    LightDirectionalNode(const glm::mat4& orienation, const glm::vec3& intensity);
    virtual ~LightDirectionalNode();
    
    void setDirection(const glm::mat4& orientation);
    void setIntensity(const glm::vec3& intensity);

	virtual void renderInit(Renderer* renderer);
    virtual void render(Renderer* renderer);
private:
	glm::vec3 m_direction;
    glm::vec3 m_intensity;
};
    
}

#endif // LIGHT_DIRECTIONAL_NODE_H