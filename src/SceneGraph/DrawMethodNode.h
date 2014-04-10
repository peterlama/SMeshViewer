#ifndef DRAW_METHOD_NODE_H
#define DRAW_METHOD_NODE_H

#include "Node.h"

namespace sg {
    
class DrawMethodNode: public Node
{
public:
    enum DrawMethod {
		Array,
		Indexed
	};
    
	DrawMethodNode();
	DrawMethodNode(DrawMethod method);

    void setDrawMethod(DrawMethod method);
    virtual void render(Renderer* renderer);
    
private:
    DrawMethod m_drawMethod;
};
    
}

#endif // DRAW_METHOD_NODE_H