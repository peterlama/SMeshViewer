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

#include <glm/geometric.hpp>

#include "Mesh.h"


Mesh::Mesh()
{
	m_id = generateUid();
}

Mesh::Mesh(const std::vector<std::vector<float> >& vertices, const std::vector<std::vector<int> >& faces)
    : m_vertices(vertices), m_faces(faces), m_normals(vertices.size())
{
	m_id = generateUid();

	generateNormals();
}

Mesh::Mesh(const std::vector<std::vector<float> >& vertices, const std::vector<glm::vec3>& normals, const std::vector<std::vector<int> >& faces)
    : m_vertices(vertices), m_faces(faces), m_normals(normals)
{
	m_id = generateUid();
}

unsigned int Mesh::id()
{
	return m_id;
}

const std::vector<std::vector<float> >& Mesh::vertices() const 
{ 
    return m_vertices; 
}

const std::vector<glm::vec3>& Mesh::normals() const
{
	return m_normals;
}

const std::vector<std::vector<int> >& Mesh::faces() const 
{ 
    return m_faces;
}

void Mesh::setVertices(const std::vector<std::vector<float> >& vertices) 
{
    m_vertices = vertices;
}

void Mesh::setFaces(const std::vector<std::vector<int> >& faces)
{
    m_faces = faces;

	m_normals = std::vector<glm::vec3>(m_vertices.size());
}

void Mesh::setNormals(const std::vector<glm::vec3>& normals)
{

	m_normals = normals;
}

void Mesh::generateNormals()
{
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		unsigned int vertexIndex = m_faces[i][0];
		glm::vec3 vertex1(m_vertices[vertexIndex][0], m_vertices[vertexIndex][1], m_vertices[vertexIndex][2]);

		vertexIndex = m_faces[i][1];
		glm::vec3 vertex2(m_vertices[vertexIndex][0], m_vertices[vertexIndex][1], m_vertices[vertexIndex][2]);

		vertexIndex = m_faces[i][2];
		glm::vec3 vertex3(m_vertices[vertexIndex][0], m_vertices[vertexIndex][1], m_vertices[vertexIndex][2]);

		glm::vec3 edge1 = vertex2 - vertex1;
		glm::vec3 edge2 = vertex3 - vertex1;

		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

		for (unsigned int j = 0; j < 3; ++j) {
			if (m_normals[m_faces[i][j]] != glm::vec3()) {
				m_normals[m_faces[i][j]] = glm::normalize(m_normals[m_faces[i][j]] + normal);
			}
			else {
				m_normals[m_faces[i][j]] = normal;
			}
		}
	}
	
}

unsigned int Mesh::generateUid()
{
	static unsigned int uid = 0;
	return ++uid;
}