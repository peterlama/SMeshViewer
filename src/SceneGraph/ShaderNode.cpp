//-----------------------------------------------------------------------------
//Copyright (c) 2014 Peter Lama
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-----------------------------------------------------------------------------

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