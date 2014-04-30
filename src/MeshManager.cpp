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

#include <QElapsedTimer>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <glm/geometric.hpp>

#include "GroupNode.h"
#include "GeometryNode.h"
#include "DrawMethodNode.h"
#include "VertexNode.h"
#include "NormalNode.h"
#include "IndexNode.h"

#include "MeshManager.h"

MeshManager::MeshManager()
{
	m_geomRoot = std::make_shared<sg::GroupNode>();
}

bool MeshManager::importObjMesh(const char* filename)
{
	QElapsedTimer timer;
	timer.start();
	QFile objFile(filename);

	if (!objFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		std::cerr << "could not find file: " << filename;
		return false;
	}

	QTextStream stream(&objFile);

	std::shared_ptr<GenericDataArray<float> > vertices = std::make_shared<GenericDataArray<float> >();
	std::shared_ptr<GenericDataArray<unsigned int> > faces = std::make_shared<GenericDataArray<unsigned int> >();
	std::shared_ptr<GenericDataArray<float> > uniqueNormals = std::make_shared<GenericDataArray<float> >();
	std::vector<int> normalIndices;

	while (!stream.atEnd()) {
		QString linePrefix;
		stream >> linePrefix;

		QString line(stream.readLine());

		if (linePrefix != "#") {
			QStringList elements = line.split(' ', QString::SkipEmptyParts);

			//read vertices
			if (linePrefix == "v") {
				GenericDataArray<float>::value_type vertexPosition;
				vertexPosition[0] = elements.takeFirst().toFloat();
				vertexPosition[1] = elements.takeFirst().toFloat();
				vertexPosition[2] = elements.takeFirst().toFloat();

				vertices->push_back(vertexPosition);
			}

			//read normals
			if (linePrefix == "vn") {
				GenericDataArray<float>::value_type normal;
				normal[0] = elements.takeFirst().toFloat();
				normal[1] = elements.takeFirst().toFloat();
				normal[2] = elements.takeFirst().toFloat();

				uniqueNormals->push_back(normal);
			}

			//read faces
			else if (linePrefix == "f"){
				GenericDataArray<unsigned int>::value_type face;

				int i = 0;
				while (!elements.isEmpty() && i < 3) {
					QStringList faceElements = elements.takeFirst().split('/', QString::SkipEmptyParts);
					if (faceElements.size() == 2) {
						face[i] = faceElements.takeFirst().toInt() - 1;
						normalIndices.push_back(faceElements.takeFirst().toInt() - 1);
					}
					else {
						face[i] = faceElements.takeFirst().toInt() - 1;
					}

					++i;
				}

				faces->push_back(face);
			}
		}
	}

	std::shared_ptr<GenericDataArray<float> > normals; 

	//rearrange normals so that they can be accessed by the same index as vertices
	if (!uniqueNormals->empty()) {
		normals = std::make_shared<GenericDataArray<float> >(vertices->length());
		for (unsigned int i = 0; i < faces->length(); ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				int vertexIndex = faces->at(i, j);
				int normalIndex = normalIndices[i * 3 + j];
				normals->at(vertexIndex) = uniqueNormals->at(normalIndex);
			}
		}
	}
	else {
		normals = generateNormals(vertices, faces);
	}

	m_geomRoot = std::make_shared<sg::GroupNode>();
	m_geomRoot->addChild(createGeometryNode(vertices, normals, faces));

	std::cout << "Time: " << timer.elapsed() / 1000.0 << std::endl;
	std::cout << "Vertices: " << vertices->length() << std::endl;
	std::cout << "Faces: " << faces->length() << std::endl;

	return true;

}

std::shared_ptr<sg::GroupNode> MeshManager::geometryRootNode()
{
	return m_geomRoot;
}

sg::GeometryNode* MeshManager::createGeometryNode(
	std::shared_ptr<GenericDataArray<float> > vertices, 
	std::shared_ptr<GenericDataArray<float> > normals, 
	std::shared_ptr<GenericDataArray<unsigned int> > indices)
{
	sg::GeometryNode* geom = new sg::GeometryNode;
	geom->addChild(new sg::DrawMethodNode(sg::DrawMethodNode::Indexed));
	geom->addChild(new sg::VertexNode(vertices));
	geom->addChild(new sg::NormalNode(normals));
	geom->addChild(new sg::IndexNode(indices));

	return geom;
}

std::shared_ptr<GenericDataArray<float> > MeshManager::generateNormals(
	std::shared_ptr<GenericDataArray<float> > vertices,
	std::shared_ptr<GenericDataArray<unsigned int> > indices)
{
	std::vector<glm::vec3> normalsVec(vertices->length());
	std::shared_ptr<GenericDataArray<float> > normals = std::make_shared<GenericDataArray<float> >(vertices->length());

	for (unsigned int i = 0; i < indices->length(); ++i) {
		unsigned int vertexIndex = indices->at(i, 0);
		glm::vec3 vertex1(vertices->at(vertexIndex, 0), vertices->at(vertexIndex, 1), vertices->at(vertexIndex, 2));

		vertexIndex = indices->at(i, 1);
		glm::vec3 vertex2(vertices->at(vertexIndex, 0), vertices->at(vertexIndex, 1), vertices->at(vertexIndex, 2));

		vertexIndex = indices->at(i, 2);
		glm::vec3 vertex3(vertices->at(vertexIndex, 0), vertices->at(vertexIndex, 1), vertices->at(vertexIndex, 2));

		glm::vec3 edge1 = vertex2 - vertex1;
		glm::vec3 edge2 = vertex3 - vertex1;

		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

		for (unsigned int j = 0; j < 3; ++j) {
			if (normalsVec.at(indices->at(i, j)) != glm::vec3()) {
				normalsVec.at(indices->at(i, j)) = glm::normalize(normalsVec.at(indices->at(i, j)) + normal);
			}
			else {
				normalsVec.at(indices->at(i, j)) = normal;
			}
		}
	}

	for (unsigned int i = 0; i < normalsVec.size(); ++i) {
		normals->at(i) = GenericDataArray<float>::value_type(&normalsVec[i][0]);
	}

	return normals;
}