#pragma once
#include <vector>

#include <glm/glm.hpp>


// We're going to assume all meshes will be 3 Dimensional
// There aren't many programs that produce 4D meshes.

namespace os
{
	struct vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
	};

	class Mesh
	{
		std::vector<vertex> vertices;
		std::vector<uint32_t> indices;
	public:
		std::vector<vertex>& getVertices();
		std::vector<uint32_t>& getIndices();
	};
}