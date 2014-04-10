#include "VertexNode.h"
#include "Renderer.h"

namespace sg {

VertexNode::VertexNode()
    :m_vertices(0)
{
}

VertexNode::VertexNode(GenericDataArray<float>* vertices)
    :m_vertices(vertices)
{
}

VertexNode::~VertexNode()
{
}

void VertexNode::setVertices(GenericDataArray<float>* vertices)
{
    m_vertices = vertices;
	setNeedsRendering(true);
}

void VertexNode::renderInit(Renderer* renderer)
{
	renderer->setVertices(m_vertices);

	setNeedsRendering(false);
}

void VertexNode::render(Renderer* renderer)
{   
	if (needsRendering()) {
		renderer->setVertices(m_vertices);

		setNeedsRendering(false);
	}
}

} // namespace sg