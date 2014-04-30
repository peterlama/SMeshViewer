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

#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include <memory>

#include "Renderer.h"

namespace sg {

class GroupNode;
class CameraNode;

class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();

	std::shared_ptr<GroupNode> root();
	void setRoot(std::shared_ptr<GroupNode> node);

	std::shared_ptr<CameraNode> camera();

	void addDefaultCamera();
	void addDefaultLights();

	void renderInit(Renderer* renderer);
	void render(Renderer* renderer);

private:
	std::shared_ptr<GroupNode> m_root;
	std::shared_ptr<CameraNode> m_camera;
};

}  //namespace sg

#endif //SCENE_GRAPH_H