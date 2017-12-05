#pragma once

#include <glm/glm.hpp>

#include "BaseComponent.h"
#include "../../mesh/Mesh.h"
#include <vector>


namespace os
{
	class MeshComponent : public BaseComponent
	{
	public:
		MeshComponent(std::string objPath);

		void draw(std::shared_ptr<Shader> shader);

		const std::shared_ptr<Mesh> &get();

	private:
		std::shared_ptr<Mesh> mMesh;
	};
}
