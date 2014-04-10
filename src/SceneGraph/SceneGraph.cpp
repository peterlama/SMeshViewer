#include "GroupNode.h"
#include "SceneGraph.h"

namespace sg {

SceneGraph::SceneGraph()
{
	m_root = new GroupNode;
}

SceneGraph::~SceneGraph()
{
	delete m_root;
}

GroupNode* SceneGraph::root()
{
	return m_root;
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