#pragma once

#include <glm/glm.hpp>

#include "BaseComponent.h"
#include <vector>


namespace os
{

	template <int D, typename T>
	class Mesh : public BaseComponent {
	private:
		std::vector<glm::vec<D, T>> vertices;
	public:
		void draw()
		{
			
		}
	};
}
