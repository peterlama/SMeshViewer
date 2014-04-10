#include "GeometryNode.h"
#include "Renderer.h"

namespace sg {

void GeometryNode::render(Renderer* renderer)
{
	renderer->push(id());

	renderChildren(renderer);
	renderer->renderTriangles();

	renderer->pop();
}

} // namespace sg