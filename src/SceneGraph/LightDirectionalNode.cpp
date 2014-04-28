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

#include "LightDirectionalNode.h"
#include "Renderer.h"

namespace sg {

LightDirectionalNode::LightDirectionalNode()
    :m_direction(0.0f, -1.0f, 0.0f )
{
}

LightDirectionalNode::LightDirectionalNode(const glm::mat4& orientation, const glm::vec3& intensity)
    :m_intensity(intensity)
{
	setDirection(orientation);
}

LightDirectionalNode::~LightDirectionalNode()
{
}

void LightDirectionalNode::setDirection(const glm::mat4& orientation)
{
    //zero rotation points down
	glm::vec4 direction(0.0f, -1.0f, 0.0f, 0.0f);
	direction = orientation * direction;
	m_direction = glm::vec3(direction);
	setNeedsRendering(true);
}

void LightDirectionalNode::setIntensity(const glm::vec3& intensity)
{
    m_intensity = intensity;
	setNeedsRendering(true);
}

void LightDirectionalNode::renderInit(Renderer* renderer)
{
	renderer->addLightDirectional(m_direction, m_intensity);

	setNeedsRendering(false);
}

void LightDirectionalNode::render(Renderer* renderer)
{   
	if (needsRendering()) {
		renderer->addLightDirectional(m_direction, m_intensity);

		setNeedsRendering(false);
	}
}

} // namespace sg