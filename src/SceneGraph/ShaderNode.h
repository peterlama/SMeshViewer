#ifndef SAHDER_NODE_H
#define SHADER_NODE_H

#include "Node.h"

namespace sg {

class ShaderNode : public Node
{
public:
	ShaderNode();
	ShaderNode(unsigned int programHandle);
	virtual ~ShaderNode();

	void setProgram(unsigned int programHandle);
	virtual void render(Renderer* renderer);
private:
	unsigned int m_programHandle;
};

}

#endif // SHADER_NODE_H