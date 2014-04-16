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