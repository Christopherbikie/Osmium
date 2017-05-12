#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <iostream>

namespace os
{

	struct vertexData
	{
		float_t vertX;
		float_t vertY;
		float_t vertZ;

		float_t normalX;
		float_t normalY;
		float_t normalZ;
	};

	Mesh::Mesh()
	{
		this->meshVAO = std::make_shared<VAO>();
	}

	Mesh::Mesh(const char * objPath)
	{
		this->meshVAO = std::make_shared<VAO>();
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;

		tinyobj::LoadObj(&attrib, &shapes, &materials, &err, objPath, "res/materials/", true);
		// correctedVertices has to have an individual vertex for each vertex-normal pair
		// loop through the shapes and then loop through indices take the vertex index and the normal index as 'i'
		// take attrib.vertices[i] and attrib.normals[i]
		//

		std::vector<glm::vec3> correctedVectors;
		std::vector<glm::vec3> correctedNormals;
		

		std::map<std::pair<uint32_t, uint32_t>, uint32_t> indexMap;
		size_t currentIndex;
		size_t nextIndex = 0;

		for (auto& shape : shapes)
		{
			
			Model::parsedshape newShape;

			newShape.name = shape.name;

			

			for (auto& index : shape.mesh.indices)
			{
				if (uint32_t foundIndex = indexMap[std::pair<uint32_t, uint32_t>(index.vertex_index, index.normal_index)])
				{
					currentIndex = foundIndex;
				}
				else
				{
					currentIndex = nextIndex;
					
					uint32_t vertIndex = index.vertex_index;
					uint32_t normIndex = index.normal_index;
					
					indexMap[std::pair<uint32_t, uint32_t>(vertIndex, normIndex)] = currentIndex;

					correctedVectors.push_back(glm::vec3(attrib.vertices[vertIndex * 3], attrib.vertices[vertIndex * 3 + 1], attrib.vertices[vertIndex * 3 + 2]));
					if (attrib.normals.size() > 0)
						correctedNormals.push_back(glm::vec3(attrib.normals[normIndex * 3], attrib.normals[normIndex * 3 + 1], attrib.normals[normIndex * 3 + 2]));
					nextIndex++;
				}

				newShape.vertex_indices.push_back(currentIndex);
			}

			this->parsedShapes.push_back(newShape);
		}


		std::cout << objPath << " loaded with: " << std::endl;
		std::cout << "verts: " << attrib.vertices.size() << std::endl;
		//std::cout << "normals: " << correctedNormals.size() << std::endl;
		//std::cout << "texcoords: " << correctedTexCoords.size() << std::endl;

		this->meshVAO->bind();
		if (attrib.vertices.size() > 0)
			this->meshVAO->storeInBuffer(0, 3, correctedVectors.size() * 3, &correctedVectors[0][0]);
		if (attrib.normals.size() > 0)
			this->meshVAO->storeInBuffer(1, 3, correctedNormals.size() * 3, &correctedNormals[0][0]);
		//if (attrib.texcoords.size() > 0)
		//	this->meshVAO->storeInBuffer(2, 2, attrib.texcoords.size(), &attrib.texcoords[0]);
		//this->meshVAO->storeInElementBuffer(indices.size(), &indices[0]);
		this->meshVAO->unbind();

		
	}

	void Mesh::draw(Shader * shader)
	{
		shader->use();
		this->meshVAO->bind();
		this->meshVAO->bindEBO();
		for (auto& shape : this->parsedShapes)
		{
			glDrawElements(GL_TRIANGLES, shape.vertex_indices.size(), GL_UNSIGNED_INT, &shape.vertex_indices[0]);
		}
			//shader->drawElements(this->meshVAO->getVertexCount());
		this->meshVAO->unbind();
	}

	Mesh::~Mesh()
	{
	}

}
