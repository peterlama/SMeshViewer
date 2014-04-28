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
