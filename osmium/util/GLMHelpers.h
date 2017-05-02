#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <glm/detail/precision.hpp>
#include <glm/gtx/string_cast.hpp>

template <int L, typename T, glm::precision P>
std::ostream &operator<< (std::ostream &out, const glm::vec<L, T, P> &vec)
{
	return out << glm::to_string(vec);
}

template <typename T>
glm::vec3 castToFloat(glm::vec<3, T> &vector)
{
	return glm::vec3((float) vector.x, (float) vector.y, (float) vector.z);
}
