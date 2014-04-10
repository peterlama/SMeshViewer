#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

#include "GroupNode.h"

namespace sg {
    
class GeometryNode: public GroupNode
{
public:
    virtual void render(Renderer* renderer);
};
    
}

#endif // GEOMETRY_NODE_H