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
		MeshComponent(const char* objPath);

		void draw(Shader * shader);

	private:
		std::shared_ptr<Mesh> mMesh;
	};
}
