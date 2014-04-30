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

#include <vector>
#include <map>
#include <memory>

#include <GL/glew.h>

#include <QGLWidget>

#include "GenericDataArray.h"
#include "SceneGraph.h"
#include "ViewNavigator.h"
#include "Renderer.h"

class View3d : public QGLWidget 
{
    Q_OBJECT
public:
	View3d(const QGLFormat &format, QWidget *parent = 0);
    ~View3d();
    QSize sizeHint() const;

	ViewNavigator* viewNav();
	std::shared_ptr<sg::GroupNode> sceneGraphRoot();
	void setSceneGraph(const sg::SceneGraph& sceneGraph);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
    
private:
	void setupSceneGraph();
	void updateSceneGraph();

	ViewNavigator m_viewNav;

	sg::Renderer m_renderer;
	sg::SceneGraph m_sceneGraph;
};