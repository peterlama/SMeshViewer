#include "ShaderNode.h"
#include "Renderer.h"

namespace sg {

ShaderNode::ShaderNode()
    :m_programHandle(0)
{
}

ShaderNode::ShaderNode(unsigned int programHandle)
: m_programHandle(programHandle)
{
}

ShaderNode::~ShaderNode()
{
}

void ShaderNode::setProgram(unsigned int programHandle)
{
	m_programHandle = programHandle;
	setNeedsRendering(true);
}

void ShaderNode::render(Renderer* renderer)
{
	if (needsRendering()) {
		renderer->setShaderProgram(m_programHandle);

		setNeedsRendering(false);
	}
}

} // namespace sg