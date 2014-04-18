#ifndef NORMAL_NODE_H
#define NORMAL_NODE_H

#include "Node.h"
#include "../GenericDataArray.h"

namespace sg {
    
class NormalNode: public Node
{
public:
    NormalNode();
    NormalNode(GenericDataArray<float>* normals);
    virtual ~NormalNode();
    
    void setNormals(GenericDataArray<float>* normals);

	virtual void renderInit(Renderer* renderer);
    virtual void render(Renderer* renderer);
private:
    GenericDataArray<float>* m_normals;
};
    
}

#endif // NORMAL_NODE_H