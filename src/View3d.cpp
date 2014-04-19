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
    : QGLWidget(format, parent), m_viewNav(3.0f, 0.0f, 0.0f)
{
    //OpenGL context needs to be set up before initializing glew
    makeCurrent();

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}

	importObjMesh("C:\\Users\\Peter\\norm.obj");

	//m_viewNav.setDefaultDistance(5.0f);
}

View3d::~View3d()
{

}

QSize View3d::sizeHint() const
{
    return QSize(500, 500);
}

bool View3d::importObjMesh(const char* filename)
{
	QElapsedTimer timer;
	timer.start();
	QFile objFile(filename);

	if (!objFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "could not find file: " << filename;
		return false;
	}

	QTextStream stream(&objFile);

	std::vector<std::vector<float> > vertices;
	std::vector<std::vector<int> > faces;
	std::vector<glm::vec3> uniqueNormals;
	std::vector<int> normalIndices;

	while (!stream.atEnd()) {
		QString linePrefix;
		stream >> linePrefix;

		QString line(stream.readLine());

		if (linePrefix != "#") {
			QStringList elements = line.split(' ', QString::SkipEmptyParts);

			//object
			if (linePrefix == "o") {
				if (!vertices.empty()) {
					m_meshes.push_back(new Mesh(vertices, faces));
					vertices.clear();
					faces.clear();
				}
			}
			//read vertices
			if (linePrefix == "v") {
				std::vector<float> vertexPosition;
				vertexPosition.push_back(elements.takeFirst().toFloat());
				vertexPosition.push_back(elements.takeFirst().toFloat());
				vertexPosition.push_back(elements.takeFirst().toFloat());

				vertices.push_back(vertexPosition);
			}

			//read normals
			if (linePrefix == "vn") {
				glm::vec3 normal;
				normal.x = elements.takeFirst().toFloat();
				normal.y = elements.takeFirst().toFloat();
				normal.z = elements.takeFirst().toFloat();

				uniqueNormals.push_back(normal);
			}

			//read faces
			else if (linePrefix == "f"){
				std::vector<int> face;

				//only support tries, so stop at three regardless
				while (!elements.isEmpty() && face.size() <= 3) {
					QStringList faceElements = elements.takeFirst().split('/', QString::SkipEmptyParts);
					if (faceElements.size() == 2) {
						face.push_back(faceElements.takeFirst().toInt() - 1);
						normalIndices.push_back(faceElements.takeFirst().toInt() - 1);
					}
					else {
						face.push_back(faceElements.takeFirst().toInt() - 1);
					}
				}				
				
				faces.push_back(face);
			}
		}
	}

	//rearrange normals so that they can be accessed by the same index as vertices
	if (!uniqueNormals.empty()) {
		std::vector<glm::vec3> normals(vertices.size());

		for (unsigned int i = 0; i < faces.size(); ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				int vertexIndex = faces[i][j];
				int normalIndex = normalIndices[i * 3 + j];
				normals[vertexIndex] = uniqueNormals[normalIndex];
			}
		}

		m_meshes.push_back(new Mesh(vertices, normals, faces));
	}
    else {
		m_meshes.push_back(new Mesh(vertices, faces));
	}
	std::cout << timer.elapsed() << std::endl;

	createBuffers();
	setupSceneGraph();

	return true;

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
	if (event->button() == Qt::LeftButton) {
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

void View3d::setupSceneGraph()
{
	sg::GroupNode* root = m_sceneGraph.root();
	Mesh* mesh;

	glm::mat4 lightTransform;
	lightTransform = glm::rotate(lightTransform, 60.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	lightTransform = glm::rotate(lightTransform, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	root->addChild(new sg::LightDirectionalNode(lightTransform, glm::vec3(1.0f, 1.0f, 1.0f)));

	lightTransform = glm::mat4();
	lightTransform = glm::rotate(lightTransform, 120.0f, glm::vec3(1.0f, 0.0f, 1.0f));
	lightTransform = glm::rotate(lightTransform, 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	root->addChild(new sg::LightDirectionalNode(lightTransform, glm::vec3(0.1f, 0.1f, 0.1f)));

	for (std::vector<Mesh*>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it) {
		mesh = *it;
		sg::GeometryNode* geom = new sg::GeometryNode;
		geom->addChild(new sg::DrawMethodNode(sg::DrawMethodNode::Indexed));
		geom->addChild(new sg::VertexNode(m_vertexBuffers[mesh->id()]));
		geom->addChild(new sg::NormalNode(m_normalBuffers[mesh->id()]));
		geom->addChild(new sg::IndexNode(m_indexBuffers[mesh->id()]));
		root->addChild(geom);
	}
}


void View3d::updateSceneGraph()
{
	m_sceneGraph.camera()->setOrigin(m_viewNav.origin());
	m_sceneGraph.camera()->setPosition(m_viewNav.position());
	m_sceneGraph.camera()->setRotation(m_viewNav.rotation());
}

void View3d::createBuffers()
{
	//QElapsedTimer timer;
	//timer.start();
	for (std::vector<Mesh*>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it) {
		Mesh* mesh = *it;
		
		GenericDataArray<float>* vertexBuffer = new GenericDataArray<float>(mesh->vertices().size(), 3);
		for (unsigned int i = 0; i < mesh->vertices().size(); ++i) {
			for (int j = 0; j < 3; ++j) {
				vertexBuffer->at(i, j) = mesh->vertices()[i][j];
			}
		}

		GenericDataArray<float>* normalBuffer = new GenericDataArray<float>(mesh->normals().size(), 3);
		for (unsigned int i = 0; i < mesh->normals().size(); ++i) {
			for (int j = 0; j < 3; ++j) {
				normalBuffer->at(i, j) = mesh->normals()[i][j];
			}
			//std::cout << "(" << normalBuffer->at(i, 0) << ", " << normalBuffer->at(i, 1) << ", " << normalBuffer->at(i, 2) << ")" << std::endl;
		}

		GenericDataArray<unsigned int>* indexBuffer = new GenericDataArray<unsigned int>(mesh->faces().size(), 3);
		for (unsigned int i = 0; i < mesh->faces().size(); ++i) {
			for (int j = 0; j < 3; ++j) {
				indexBuffer->at(i, j) = mesh->faces()[i][j];
			}
			//std::cout << "(" << indexBuffer->at(i, 0) << ", " << indexBuffer->at(i, 1) << ", " << indexBuffer->at(i, 2) << ")" << std::endl;
		}

		m_vertexBuffers[mesh->id()] = vertexBuffer;
		m_normalBuffers[mesh->id()] = normalBuffer;
		m_indexBuffers[mesh->id()] = indexBuffer;
	}

	//std::cout << timer.elapsed() << std::endl;
}