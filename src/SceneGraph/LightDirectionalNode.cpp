#include "LightDirectionalNode.h"
#include "Renderer.h"

namespace sg {

LightDirectionalNode::LightDirectionalNode()
    :m_direction(0.0f, -1.0f, 0.0f )
{
}

LightDirectionalNode::LightDirectionalNode(const glm::mat4& orientation, const glm::vec3& intensity)
    :m_intensity(intensity)
{
	setDirection(orientation);
}

LightDirectionalNode::~LightDirectionalNode()
{
}

void LightDirectionalNode::setDirection(const glm::mat4& orientation)
{
    //zero rotation points down
	glm::vec4 direction(0.0f, -1.0f, 0.0f, 0.0f);
	direction = orientation * direction;
	m_direction = glm::vec3(direction);
	setNeedsRendering(true);
}

void LightDirectionalNode::setIntensity(const glm::vec3& intensity)
{
    m_intensity = intensity;
	setNeedsRendering(true);
}

void LightDirectionalNode::renderInit(Renderer* renderer)
{
	renderer->addLightDirectional(m_direction, m_intensity);

	setNeedsRendering(false);
}

void LightDirectionalNode::render(Renderer* renderer)
{   
	if (needsRendering()) {
		renderer->addLightDirectional(m_direction, m_intensity);

		setNeedsRendering(false);
	}
}

} // namespace sg