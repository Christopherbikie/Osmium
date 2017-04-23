#pragma once

#include <cmath>
#include <glm/ext.hpp>

namespace physics
{
	/*
	 * vec is a glm vector e.g. dvec3
	 * type is a scalar type, e.g. double_t
	 * The scalar must be the same type as the vector, i.e. don't mix floats / doubles.
	 * This applies to all functions in this namespace.
	 */

	const double_t G = 6.67408e-11;

	template <typename vec, typename type>
	vec getGravityForce(type m1, type m2, const vec& p1, const vec& p2, float_t exp = -2)
	{
		vec r = p2 - p1;
		type rLen = glm::length(r);
		return G * m1 * m2 * pow(rLen, exp) * (r / rLen);
	}

	template <typename vec, typename type>
	vec getAcceleration(const vec& Fnet, type m)
	{
		return Fnet / m;
	}

	template <typename vec, typename type>
	vec getNextVelocity(type delta, const vec& a, const vec& u)
	{
		return u + a * delta;
	}

	template <typename vec, typename type>
	vec getNextPosition(type delta, const vec& p, const vec& v)
	{
		return p + v * delta;
	}

	template <typename type>
	type getStableOrbitVelocity(type m, type r)
	{
		return sqrt(G * m / r);
	};
}
