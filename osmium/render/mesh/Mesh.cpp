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

}