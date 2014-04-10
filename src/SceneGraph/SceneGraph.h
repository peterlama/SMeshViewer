#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Renderer.h"

namespace sg {

class GroupNode;

class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();

	GroupNode* root();

	void renderInit();
	void render();
	void resizeViewport(unsigned int width, unsigned int height);

private:
	

	GroupNode* m_root;
	Renderer m_renderer;
};

}  //namespace sg

#endif //SCENE_GRAPH_H