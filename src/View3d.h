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
	std::map<unsigned int, GenericDataArray<unsigned int>* > m_indexBuffers;
};