#include "Mesh.h"


namespace os
{
	std::vector<vertex>& Mesh::getVertices()
	{
		return this->vertices;
	}

	std::vector<uint32_t>& Mesh::getIndices()
	{
		return this->indices;
	}

	Mesh::Mesh()
	{
		this->meshVAO = std::make_shared<VAO>();
	}

	void Mesh::draw(Shader * shader)
	{
		if (!this->loaded)
		{
			this->loaded = true;
			std::vector<float_t> positions = std::vector<float_t>();
			for (vertex vert : this->vertices)
			{
				positions.push_back(vert.position.x);
				positions.push_back(vert.position.y);
				positions.push_back(vert.position.z);
			}

			this->meshVAO->bind();
			this->meshVAO->storeInBuffer(0, 3, positions.size(), &positions[0]);
			this->meshVAO->storeInElementBuffer(this->indices.size(), &this->indices[0]);
			this->meshVAO->unbind();
		}
		shader->use();
		this->meshVAO->bind();
		this->meshVAO->bindEBO();
		shader->drawElements(this->meshVAO->getVertexCount());
		this->meshVAO->unbind();
	}

	Mesh::~Mesh()
	{
	}

}