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

#include <GL/glew.h>

#include <QGLWidget>

#include "GenericDataArray.h"
#include "SceneGraph.h"
#include "ViewNavigator.h"

class Mesh;

class View3d : public QGLWidget 
{
    Q_OBJECT
public:
	View3d(const QGLFormat &format, QWidget *parent = 0);
    ~View3d();
    QSize sizeHint() const;

    bool importObjMesh(const char* filename);
	ViewNavigator* viewNav();
	void update();

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

	void createBuffers();

	ViewNavigator m_viewNav;

	sg::SceneGraph m_sceneGraph;

    std::vector<Mesh*> m_meshes;
	std::map<unsigned int, GenericDataArray<float>* > m_vertexBuffers;
	std::map<unsigned int, GenericDataArray<float>* > m_normalBuffers;
	std::map<unsigned int, GenericDataArray<unsigned int>* > m_indexBuffers;
};