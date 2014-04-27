#ifndef TRANSFORM_NODE_H
#define TRANSFORM_NODE_H

#include "GroupNode.h"
#include "Transform.h"

namespace sg {
    
class TransformNode: public GroupNode
{
public:
    TransformNode();
    TransformNode(const Transform& transform);
    
    Transform& transform();
    void setTransform(const Transform& transform);
    
    virtual void render(Renderer* renderer);
    
private:
    Transform m_transform;
};
    
}

#endif // TRANSFORM_NODE_H