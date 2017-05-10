#pragma once
#include "Mesh.h"
#include <string>


namespace os
{
	namespace OBJLoader
	{
		Mesh loadOBJ(std::string filePath);
		void parseVertex(std::string line, Mesh& mesh);
		void parseFace(std::string line, Mesh& mesh);
	};
}