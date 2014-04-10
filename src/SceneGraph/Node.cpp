#include "Node.h"
#include "Renderer.h"

#include <iostream>

namespace sg {

Node::Node()
    : m_parent(0), m_needsRendering(true)
{
    m_id = generateUid();
}

Node::~Node()
{
}

unsigned int Node::generateUid()
{
	static unsigned int uid = 0;
	return ++uid;
}

unsigned int Node::id()
{
    return m_id;
}

void Node::renderInit(Renderer* renderer)
{
	//default -- do nothing
}

Node* Node::parent()
{
    return m_parent;
}

void Node::setParent(Node* parent)
{
    m_parent = parent;
}

bool Node::needsRendering()
{
	return m_needsRendering;
}

void Node::setNeedsRendering(bool needsRendering)
{
	m_needsRendering = needsRendering;

	if (parent() != 0) {
		parent()->setNeedsRendering(needsRendering);
	}
}

} // namespace sg