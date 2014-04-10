#include "Mesh.h"


Mesh::Mesh()
{
	m_id = generateUid();
}

Mesh::Mesh(const std::vector<std::vector<float> >& vertices, const std::vector<std::vector<int> >& faces)
    : m_vertices(vertices), m_faces(faces)
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
}

unsigned int Mesh::generateUid()
{
	static unsigned int uid = 0;
	return ++uid;
}