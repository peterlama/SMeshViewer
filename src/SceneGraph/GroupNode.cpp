//-----------------------------------------------------------------------------
//Copyright (c) 2014 Peter Lama
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-----------------------------------------------------------------------------

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

void GroupNode::replaceChild(Node* oldChild, Node* newChild)
{
    std::vector<Node*>::iterator it = std::find(m_children.begin(), m_children.end(), oldChild);
	if (it != m_children.end()) {
		*it = newChild;
		setNeedsRendering(true);
	}
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