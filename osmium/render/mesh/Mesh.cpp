#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <iostream>
#include "../graphics/Texture.h"

namespace os
{

	typedef std::tuple<uint32_t, uint32_t, uint32_t> indexMapType;

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

		std::string basePath = "res/materials/";

		std::string err;

		tinyobj::LoadObj(&attrib, &shapes, &materials, &err, objPath, basePath.c_str(), true);
		// correctedVertices has to have an individual vertex for each vertex-normal pair
		// loop through the shapes and then loop through indices take the vertex index and the normal index as 'i'
		// take attrib.vertices[i] and attrib.normals[i]
		//


		// Default material is put last
		materials.push_back(tinyobj::material_t());

		std::vector<Material> parsedMaterials;


		// TODO: Optimise so that we don't have to load textures more than once
		for (auto& mat : materials)
		{
			Material newMaterial;

			if (mat.diffuse_texname.size() > 0)
			{
				newMaterial.setDiffuseMap(basePath + mat.diffuse_texname);
				newMaterial.setAmbientMap(basePath + mat.ambient_texname);
				newMaterial.setSpecularMap(basePath + mat.specular_texname);
				newMaterial.setSpecularHighlightsMap(basePath + mat.specular_highlight_texname);
			}
			else
			{
				newMaterial.setDiffuseMap("res/images/default.png");
			}

			parsedMaterials.push_back(newMaterial);
		}

		std::vector<glm::vec3> correctedVectors;
		std::vector<glm::vec3> correctedNormals;
		std::vector<glm::vec2> correctedTexcoords;
		std::vector<glm::vec3> diffuseColors;

		std::map<indexMapType, uint32_t> indexMap;
		size_t currentIndex;
		size_t nextIndex = 0;


		size_t shapeIndex = 0;
		for (auto& shape : shapes)
		{
			shapeIndex++;
			Model::parsedshape newShape;

			newShape.name = shape.name;

			if (shape.mesh.material_ids.size() > 0 && shape.mesh.material_ids.size() > shapeIndex)
			{
				newShape.material = parsedMaterials[shape.mesh.material_ids[shapeIndex]];
			}
			else
			{
				newShape.material = parsedMaterials[materials.size() - 1];
			}

			for (size_t i = 0; i < shape.mesh.indices.size(); i++)
			{
				auto index = shape.mesh.indices[i];
				size_t currentMaterialId = shape.mesh.material_ids[i / 3];
				
				if (currentMaterialId < 0 || (currentMaterialId > materials.size()))
					currentMaterialId = materials.size() - 1;

				if (i % 3 == 0)
					diffuseColors.push_back(glm::vec3(materials[currentMaterialId].diffuse[0],
						materials[currentMaterialId].diffuse[1],
						materials[currentMaterialId].diffuse[2]));
				
				if (uint32_t foundIndex = indexMap[indexMapType(index.vertex_index, index.normal_index, index.texcoord_index)])
				{
					currentIndex = foundIndex;
				}
				else
				{
					currentIndex = nextIndex;
					
					uint32_t vertIndex = index.vertex_index;
					uint32_t normIndex = index.normal_index;
					uint32_t texcoordIndex = index.texcoord_index;

					indexMap[indexMapType(vertIndex, normIndex, texcoordIndex)] = currentIndex;

					correctedVectors.push_back(glm::vec3(attrib.vertices[vertIndex * 3], attrib.vertices[vertIndex * 3 + 1], attrib.vertices[vertIndex * 3 + 2]));
					if (attrib.normals.size() > 0)
						correctedNormals.push_back(glm::vec3(attrib.normals[normIndex * 3], attrib.normals[normIndex * 3 + 1], attrib.normals[normIndex * 3 + 2]));
					if (attrib.texcoords.size() > 0 && attrib.texcoords.size() > texcoordIndex * 2 + 1)
						correctedTexcoords.push_back(glm::vec2(attrib.texcoords[texcoordIndex * 2], attrib.texcoords[texcoordIndex * 2 + 1]));
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
		if (correctedTexcoords.size() > 0)
			this->meshVAO->storeInBuffer(2, 2, correctedTexcoords.size(), &correctedTexcoords[0][0]);
		//this->meshVAO->storeInElementBuffer(indices.size(), &indices[0]);
		this->meshVAO->unbind();

		
	}

	void Mesh::draw(Shader * shader)
	{
		shader->use();
		this->meshVAO->bind();
		this->meshVAO->bindEBO();
		
		//Texture * tex = new Texture("res/materials/SP_LUK.jpg");
		for (auto& shape : this->parsedShapes)
		{
			shape.material.bind(shader);
			//tex->bind(shader, "diffuse");
			glDrawElements(GL_TRIANGLES, shape.vertex_indices.size(), GL_UNSIGNED_INT, &shape.vertex_indices[0]);
			//tex->unbind();
			shape.material.unbind();
		}

		//delete tex;
			//shader->drawElements(this->meshVAO->getVertexCount());
		this->meshVAO->unbind();
	}

	Mesh::~Mesh()
	{
	}

}
