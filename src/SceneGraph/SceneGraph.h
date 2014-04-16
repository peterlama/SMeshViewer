#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Renderer.h"

namespace sg {

class GroupNode;
class CameraNode;

class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();

	GroupNode* root();
	CameraNode* camera();

	void renderInit();
	void render();
	void resizeViewport(unsigned int width, unsigned int height);

private:
	GroupNode* m_root;
	CameraNode* m_camera;

	Renderer m_renderer;
};

}  //namespace sg

#endif //SCENE_GRAPH_H