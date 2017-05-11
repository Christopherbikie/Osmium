#pragma once
#include <vector>
#include <memory>


#include <glm/glm.hpp>
#include "../graphics/Shader.h"
#include "../graphics/VAO.h"


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
		std::shared_ptr<VAO> meshVAO;
		bool loaded = false;
	public:
		Mesh();
		~Mesh();
		std::vector<vertex>& getVertices();
		std::vector<uint32_t>& getIndices();
		void draw(Shader * shader);
	};
}