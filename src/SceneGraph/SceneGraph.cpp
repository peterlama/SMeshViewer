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

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "GroupNode.h"
#include "LightDirectionalNode.h"
#include "CameraNode.h"
#include "SceneGraph.h"

namespace sg {

SceneGraph::SceneGraph()
:m_camera(0)
{
	m_root = std::make_shared<GroupNode>();
}

SceneGraph::~SceneGraph()
{
}

std::shared_ptr<GroupNode> SceneGraph::root()
{
	return m_root;
}

void SceneGraph::setRoot(std::shared_ptr<GroupNode> node)
{
	m_root = node;
}

std::shared_ptr<CameraNode> SceneGraph::camera()
{
	return m_camera;
}

void SceneGraph::addDefaultCamera()
{
	m_camera = std::make_shared<CameraNode>();
	m_root->addChild(m_camera.get());
}

void SceneGraph::addDefaultLights()
{
	glm::mat4 lightTransform;
	lightTransform = glm::rotate(lightTransform, 60.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	lightTransform = glm::rotate(lightTransform, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_root->addChild(new LightDirectionalNode(lightTransform, glm::vec3(1.0f, 1.0f, 1.0f)));

	lightTransform = glm::mat4();
	lightTransform = glm::rotate(lightTransform, 120.0f, glm::vec3(1.0f, 0.0f, 1.0f));
	lightTransform = glm::rotate(lightTransform, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_root->addChild(new LightDirectionalNode(lightTransform, glm::vec3(0.1f, 0.1f, 0.1f)));
}

void SceneGraph::renderInit(Renderer* renderer)
{
	m_root->renderInit(renderer);
}

void SceneGraph::render(Renderer* renderer)
{
	m_root->render(renderer);
}

} //namespace sg