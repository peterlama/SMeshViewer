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

#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <vector>

#include "GenericDataArray.h"
#include "Mesh.h"
#include "SceneGraph.h"

namespace sg {
	class GroupNode;
	class GeometryNode;
	class VertexNode;
	class NormalNode;
	class IndexNode;
}

class MeshManager
{
public:
	MeshManager();

	/**
	* Imports triangle meshes from a .obj file
	*/
	bool importObjMesh(const char* filename);
	
	std::shared_ptr<sg::GroupNode> geometryRootNode();

	/**
	* Generate averaged normals
	*/
	static std::shared_ptr<GenericDataArray<float> > generateNormals(
		std::shared_ptr<GenericDataArray<float> > vertices,
		std::shared_ptr<GenericDataArray<unsigned int> > indices);
private:
	sg::GeometryNode* createGeometryNode(
		std::shared_ptr<GenericDataArray<float> > vertices,
		std::shared_ptr<GenericDataArray<float> > normals,
		std::shared_ptr<GenericDataArray<unsigned int> > indices);

	std::shared_ptr<sg::GroupNode> m_geomRoot;
};

#endif // MESH_MANAGER_H