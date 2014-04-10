#ifndef INDEX_NODE_H
#define INDEX_NODE_H

#include "Node.h"
#include "../GenericDataArray.h"

namespace sg {
    
class IndexNode: public Node
{
public:
    IndexNode();
    IndexNode(GenericDataArray<unsigned int>* indices);
    virtual ~IndexNode();
    
    void setIndices(GenericDataArray<unsigned int>* indices);

	virtual void renderInit(Renderer* renderer);
    virtual void render(Renderer* renderer);
private:
    GenericDataArray<unsigned int>* m_indices;
};
    
}

#endif // INDEX_NODE_H