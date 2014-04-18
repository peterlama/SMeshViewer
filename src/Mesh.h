#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm/vec3.hpp>

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<std::vector<float> >& vertices, const std::vector<std::vector<int> >& faces);
	Mesh(const std::vector<std::vector<float> >& vertices, const std::vector<glm::vec3>& normals, const std::vector<std::vector<int> >& faces);

	unsigned int id();

	const std::vector<std::vector<float> >& vertices() const;
	const std::vector<glm::vec3>& normals() const;
	const std::vector<std::vector<int> >& faces() const;
    void setVertices(const std::vector<std::vector<float> >& vertices);
    void setFaces(const std::vector<std::vector<int> >& faces);
	void setNormals(const std::vector<glm::vec3>& normals);
    
private:
	void generateNormals();

	unsigned int generateUid();

    std::vector<std::vector<float> > m_vertices;
	std::vector<glm::vec3> m_normals;
    std::vector<std::vector<int> > m_faces;
	unsigned int m_id;
};

#endif // MESH_H
