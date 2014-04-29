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
#include <vector>
#include <algorithm>

#include <QSize>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <QDebug>
#include <QMouseEvent>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "View3d.h"
#include "Mesh.h"

#include "GroupNode.h"
#include "GeometryNode.h"
#include "VertexNode.h"
#include "NormalNode.h"
#include "IndexNode.h"
#include "DrawMethodNode.h"
#include "CameraNode.h"
#include "LightDirectionalNode.h"

View3d::View3d(const QGLFormat &format, QWidget *parent)
    : QGLWidget(format, parent), m_viewNav(7.0f, 0.0f, 0.0f)
{
    //OpenGL context needs to be set up before initializing glew
    makeCurrent();

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
}

View3d::~View3d()
{

}

QSize View3d::sizeHint() const
{
    return QSize(500, 500);
}



ViewNavigator* View3d::viewNav()
{
	return &m_viewNav;
}

void View3d::update()
{
	updateSceneGraph();
	updateGL();
}

void View3d::setSceneGraph(const sg::SceneGraph& sceneGraph)
{
	m_sceneGraph = sceneGraph;
}

void View3d::initializeGL()
{
	m_sceneGraph.renderInit();
}

void View3d::paintGL()
{
	updateSceneGraph();
	m_sceneGraph.render();
}

void View3d::resizeGL(int width, int height)
{
	m_sceneGraph.resizeViewport(width, height);
}

void View3d::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
		m_viewNav.setStartPixel(event->pos().x(), event->pos().y());
	}
}

void View3d::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::LeftButton) && rect().contains(event->pos())) {
		m_viewNav.rotate(event->pos().x(), event->pos().y());
		//updateSceneGraph();
		updateGL();
	}
	else if ((event->buttons() & Qt::RightButton) && rect().contains(event->pos())) {
		m_viewNav.pan(event->pos().x(), event->pos().y());
		updateGL();
	}
	else {
		event->ignore();
	}
}

void View3d::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Vertical) {
		m_viewNav.zoom(event->delta() / -120);
		//updateSceneGraph();
		updateGL();
	}
	else {
		event->ignore();
	}
}

void View3d::updateSceneGraph()
{
	if (m_sceneGraph.camera() != 0) {
		m_sceneGraph.camera()->setOrigin(m_viewNav.origin());
		m_sceneGraph.camera()->setPosition(m_viewNav.position());
		m_sceneGraph.camera()->setRotation(m_viewNav.rotation());
	}
}
