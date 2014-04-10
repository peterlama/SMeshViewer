#include <algorithm>

#include "GroupNode.h"
#include "Renderer.h"

namespace sg {

bool GroupNode::hasChildren()
{
    return ! m_children.empty();
}

std::vector<Node*> GroupNode::children()
{
    return m_children;
}

Node* GroupNode::nthChild(int n)
{
    return m_children.at(n);
}

void GroupNode::addChild(Node* child)
{
	child->setParent(this);
    m_children.push_back(child);
	setNeedsRendering(true);
}

void GroupNode::removeChild(Node* child)
{
    std::vector<Node*>::iterator it = std::find(m_children.begin(), m_children.end(), child);
    m_children.erase(it);
	setNeedsRendering(true);
}

void GroupNode::replaceChild(Node* child)
{
    std::vector<Node*>::iterator it = std::find(m_children.begin(), m_children.end(), child);
    *it = child;
	setNeedsRendering(true);
}

void GroupNode::renderInit(Renderer* renderer)
{
	renderer->push(id());

	renderInitChildren(renderer);

	renderer->pop();
}

void GroupNode::render(Renderer* renderer)
{
	renderer->push(id());

	renderChildren(renderer);

	renderer->pop();
}

void GroupNode::renderInitChildren(Renderer* renderer)
{
	for (std::vector<Node*>::iterator it = m_children.begin(); it != m_children.end(); ++it) {
		(*it)->renderInit(renderer);
	}
}

void GroupNode::renderChildren(Renderer* renderer)
{
    for (std::vector<Node*>::iterator it = m_children.begin(); it != m_children.end(); ++it) {
        (*it)->render(renderer);
    }
}

} // namespace sg