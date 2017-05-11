#pragma once

#include <map>
#include <cmath>
#include <unordered_map>

namespace os
{
	class VAO
	{
	public:
		VAO();
		~VAO();

		void bind() const;
		static void unbind();

		void storeInBuffer(uint32_t location, uint32_t componentsPerVertex, uint32_t vertexCount, float_t *data);
		void storeInElementBuffer(uint32_t vertexCount, uint32_t *data);

		void bindEBO() const;

		uint32_t getVertexCount() const;
		
	private:
		uint32_t mLocation;
		uint32_t mEBO;
		std::unordered_map<uint32_t, uint32_t> mVBOs;
		uint32_t mVertexCount = 0;
		
	};
}
