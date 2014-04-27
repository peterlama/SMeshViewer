#include "TransformNode.h"
#include "Renderer.h"

namespace sg {

TransformNode::TransformNode()
{
}

TransformNode::TransformNode(const Transform& transform)
    :m_transform(transform)
{
}

Transform& TransformNode::transform()
{
    return m_transform;
}

void TransformNode::setTransform(const Transform& transform)
{
    m_transform = transform;
}

void TransformNode::render(Renderer* renderer)
{
	renderer->pushMatrix(m_transform.matrix());

	renderChildren(renderer);

	renderer->popMatrix();
}

} // namespace sg