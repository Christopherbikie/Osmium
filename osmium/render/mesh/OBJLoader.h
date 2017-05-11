#pragma once
#include "Mesh.h"
#include <string>


namespace os
{
	namespace OBJLoader
	{
		std::shared_ptr<Mesh> loadOBJ(std::string filePath);
		inline void parseVertex(std::string line, std::shared_ptr<Mesh> mesh);
		inline void parseFace(std::string line, std::shared_ptr<Mesh> mesh);
	};
}