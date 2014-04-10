#ifndef MESH_H
#define MESH_H

#include <vector>

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<std::vector<float> >& vertices, const std::vector<std::vector<int> >& faces);

	unsigned int id();

	const std::vector<std::vector<float> >& vertices() const;
	const std::vector<std::vector<int> >& faces() const;
    void setVertices(const std::vector<std::vector<float> >& vertices);
    void setFaces(const std::vector<std::vector<int> >& faces);
    
private:
	unsigned int generateUid();

    std::vector<std::vector<float> > m_vertices;
    std::vector<std::vector<int> > m_faces;
	unsigned int m_id;
};

#endif // MESH_H
