#include "DrawMethodNode.h"
#include "Renderer.h"

namespace sg {

DrawMethodNode::DrawMethodNode()
    :m_drawMethod(Array)
{
}

DrawMethodNode::DrawMethodNode(DrawMethod method)
    :m_drawMethod(method)
{
}

void DrawMethodNode::setDrawMethod(DrawMethod method)
{
    m_drawMethod = method;
	setNeedsRendering(true);
}

void DrawMethodNode::render(Renderer* renderer)
{
	if (needsRendering()) {
		switch (m_drawMethod) {
		case Array:
			renderer->setIndexedDrawing(false);
			break;
		case Indexed:
			renderer->setIndexedDrawing(true);
			break;
		}

		setNeedsRendering(false);
	}
}

} // namespace sg