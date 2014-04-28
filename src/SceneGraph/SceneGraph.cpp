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

#include "GroupNode.h"
#include "CameraNode.h"
#include "SceneGraph.h"

namespace sg {

SceneGraph::SceneGraph()
{
	m_root = new GroupNode;
	m_camera = new CameraNode;

	m_root->addChild(m_camera);
}

SceneGraph::~SceneGraph()
{
	delete m_root;
}

GroupNode* SceneGraph::root()
{
	return m_root;
}

CameraNode* SceneGraph::camera()
{
	return m_camera;
}

void SceneGraph::renderInit()
{
	m_renderer.init();
	m_root->renderInit(&m_renderer);
}

void SceneGraph::render()
{
	m_renderer.clearScreen();
	m_root->render(&m_renderer);
}

void SceneGraph::resizeViewport(unsigned int width, unsigned int height)
{
	m_renderer.resizeViewport(width, height);
}

} //namespace sg