#include "IndexNode.h"
#include "Renderer.h"

namespace sg {

IndexNode::IndexNode()
    :m_indices(0)
{
}

IndexNode::IndexNode(GenericDataArray<unsigned int>* indices)
    :m_indices(indices)
{
}

IndexNode::~IndexNode()
{
}

void IndexNode::setIndices(GenericDataArray<unsigned int>* indices)
{
    m_indices = indices;
	setNeedsRendering(true);
}

void IndexNode::renderInit(Renderer* renderer)
{
	renderer->setIndices(m_indices);

	setNeedsRendering(false);
}

void IndexNode::render(Renderer* renderer)
{   
	if (needsRendering()) {
		renderer->setIndices(m_indices);

		setNeedsRendering(false);
	}
}

} // namespace sg