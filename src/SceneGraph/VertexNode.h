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

#ifndef VERTEX_NODE_H
#define VERTEX_NODE_H

#include <memory>

#include "Node.h"
#include "../GenericDataArray.h"

namespace sg {
    
class VertexNode: public Node
{
public:
    VertexNode();
	VertexNode(std::shared_ptr<GenericDataArray<float> > vertices);
    virtual ~VertexNode();
    
	void setVertices(std::shared_ptr<GenericDataArray<float> > vertices);

	virtual void renderInit(Renderer* renderer);
    virtual void render(Renderer* renderer);
private:
    std::shared_ptr<GenericDataArray<float> > m_vertices;
};
    
}

#endif // VERTEX_NODE_H