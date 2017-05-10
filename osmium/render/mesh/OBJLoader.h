#pragma once
#include "Mesh.h"
#include <string>


namespace os {
	namespace OBJLoader
	{
		Mesh& loadOBJ();
		void parseVertex(std::string line, Mesh& mesh);
		void parseFace(std::string line, Mesh& mesh);
	};
}