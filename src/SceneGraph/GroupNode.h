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