#pragma once

#if !defined(WIN32) && !defined(_DEBUG)
#include <glm/glm.hpp>
#endif

#include "BaseComponent.h"
#include <vector>

// TEMP FIX FOR INTELLISENSE
#if defined(WIN32) && defined(_DEBUG)
#include "../../../../deps/glm/glm/detail/type_vec3.hpp"
#endif

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
