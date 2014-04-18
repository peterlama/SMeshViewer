#include "NormalNode.h"
#include "Renderer.h"

namespace sg {

NormalNode::NormalNode()
    :m_normals(0)
{
}

NormalNode::NormalNode(GenericDataArray<float>* normals)
    :m_normals(normals)
{
}

NormalNode::~NormalNode()
{
}

void NormalNode::setNormals(GenericDataArray<float>* normals)
{
    m_normals = normals;
	setNeedsRendering(true);
}

void NormalNode::renderInit(Renderer* renderer)
{
	renderer->setNormals(m_normals);

	setNeedsRendering(false);
}

void NormalNode::render(Renderer* renderer)
{   
	if (needsRendering()) {
		renderer->setNormals(m_normals);

		setNeedsRendering(false);
	}
}

} // namespace sg