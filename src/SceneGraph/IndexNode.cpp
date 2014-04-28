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