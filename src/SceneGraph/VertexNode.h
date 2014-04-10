#ifndef VERTEX_NODE_H
#define VERTEX_NODE_H

#include "Node.h"
#include "../GenericDataArray.h"

namespace sg {
    
class VertexNode: public Node
{
public:
    VertexNode();
    VertexNode(GenericDataArray<float>* vertices);
    virtual ~VertexNode();
    
    void setVertices(GenericDataArray<float>* vertices);

	virtual void renderInit(Renderer* renderer);
    virtual void render(Renderer* renderer);
private:
    GenericDataArray<float>* m_vertices;
};
    
}

#endif // VERTEX_NODE_H