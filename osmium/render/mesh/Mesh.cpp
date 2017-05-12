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
		
		std::vector<float_t> correctedVertices;
		std::vector<float_t> correctedNormals;
		std::vector<uint32_t> correctedTexCoords;


		tinyobj::LoadObj(&attrib, &shapes, &materials, &err, objPath, "res/materials/", true);

		
		std::vector<uint32_t> indices;

		// correctedVertices has to have an individual vertex for each vertex-normal pair
		// loop through the shapes and then loop through indices take the vertex index and the normal index as 'i'
		// take attrib.vertices[i] and attrib.normals[i]
		//

		std::map<std::pair<uint32_t, uint32_t>, uint32_t> uniquePairs;

		for (auto& shape : shapes)
		{
			Model::parsedshape newShape;
			newShape.name = shape.name;

			/*
			for (size_t it = 0; it < shape.mesh.indices.size(); it++)
			{
				glm::vec3 vertex;
				glm::vec3 normal;
				uint32_t combinedIndex = 0;


				uint32_t vertex_index = shape.mesh.indices[it].vertex_index;
				uint32_t normal_index = shape.mesh.indices[it].normal_index;
				
				if (uniquePairs[std::pair<uint32_t, uint32_t>(vertex_index, normal_index)])
				{
					combinedIndex = uniquePairs[std::pair<uint32_t, uint32_t>(vertex_index, normal_index)];
				}
				else
				{
					correctedVertices.push_back(attrib.vertices[vertex_index]);
					correctedNormals.push_back(attrib.normals[normal_index]);
					uniquePairs[std::pair<uint32_t, uint32_t>(vertex_index, normal_index)] = combinedIndex;
					
					combinedIndex = combinedIndex + 1;
				}
			*/

				for (auto& index : shape.mesh.indices)
					newShape.vertex_indices.push_back(shape.mesh.indices[index].vertex_index);
			}

			this->parsedShapes.push_back(newShape);
		}


		std::cout << objPath << " loaded with: " << std::endl;
		std::cout << "verts: " << attrib.vertices.size() << std::endl;
		//std::cout << "normals: " << correctedNormals.size() << std::endl;
		//std::cout << "texcoords: " << correctedTexCoords.size() << std::endl;

		this->meshVAO->bind();
		if (attrib.vertices.size() > 0)
			this->meshVAO->storeInBuffer(0, 3, attrib.vertices.size(), &attrib.vertices[0]);
		if (attrib.normals.size() > 0)
			this->meshVAO->storeInBuffer(1, 3, correctedNormals.size(), &correctedNormals[0]);
		if (attrib.texcoords.size() > 0)
			this->meshVAO->storeInBuffer(2, 2, attrib.texcoords.size(), &attrib.texcoords[0]);
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
