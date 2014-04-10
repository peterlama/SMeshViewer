#ifndef NODE_H
#define NODE_H

namespace sg {
   
class Renderer;

class Node 
{
public:
    Node();
    virtual ~Node();
    
    unsigned int id();
    
    Node* parent();
	void setParent(Node* parent);

	virtual void renderInit(Renderer* renderer);
    virtual void render(Renderer* renderer) = 0;

protected:
	bool needsRendering();
	void setNeedsRendering(bool needsRendering);
    
private:
	unsigned int generateUid();

    Node* m_parent;

	bool m_needsRendering;
    
    unsigned int m_id;
};
    
}

#endif // NODE_H