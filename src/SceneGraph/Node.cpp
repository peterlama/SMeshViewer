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