#pragma once
#include <vector>
#include <memory>


#include <glm/glm.hpp>
#include "../graphics/Shader.h"
#include "../graphics/VAO.h"
#include "Material.h"


// We're going to assume all meshes will be 3 Dimensional
// There aren't many programs that produce 4D meshes.

namespace os
{
	namespace Model
	{
		struct parsedshape
		{
			std::string name;
			std::vector<uint32_t> vertex_indices;
			Material material;
		};
	}
	class Mesh
	{
		std::shared_ptr<VAO> meshVAO;
		std::vector<Model::parsedshape> parsedShapes;
		bool isMeshLoaded = false;
	public:
		Mesh();
		Mesh(const char* objPath);
		~Mesh();
		void draw(std::shared_ptr<Shader> shader);

		std::vector<Model::parsedshape> &getParsedShapes();
	};
}
