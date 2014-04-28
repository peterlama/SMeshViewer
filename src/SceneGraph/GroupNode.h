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

#ifndef GROUP_NODE_H
#define GROUP_NODE_H

#include <vector>

#include "Node.h"

namespace sg {
    
class GroupNode: public Node
{
public:
    bool hasChildren();
    std::vector<Node*> children();
    Node* nthChild(int n);
    void addChild(Node* child);
    void removeChild(Node* child);
    void replaceChild(Node* child);
    
	virtual void renderInit(Renderer* renderer);
    virtual void render(Renderer* renderer);
    
protected:
	void renderInitChildren(Renderer* renderer);
    void renderChildren(Renderer* renderer);
    
private:
    std::vector<Node*> m_children;
};
    
}

#endif // GROUP_NODE_H