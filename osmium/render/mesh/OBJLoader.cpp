#include "OBJLoader.h"
#include <fstream>
#include <string>
#include <cassert>
#include <regex>
#include <sstream>


namespace os {
	namespace OBJLoader
	{
		Mesh loadOBJ(std::string filePath)
		{
			std::ifstream objFile;
			objFile.open(filePath);

			std::string lineToParse = "";
			auto generatedMesh = Mesh();
			while (getline(objFile, lineToParse))
			{
				if (lineToParse.length() <= 0)
					continue;

				auto c = lineToParse[0];

				assert(c != EOF);

				switch (c)
				{
				case '#':
					break;
				case 'f':
					parseFace(lineToParse, generatedMesh);
					break;
				case 'v':
					parseVertex(lineToParse, generatedMesh);
					break;
				default:
					break;
				}
			}

			objFile.close();

			return generatedMesh;
		}

		void parseVertex(std::string line, Mesh& mesh)
		{
			assert(line.size() > 0);
			assert(line[0] == 'v');

			std::regex vertexRegex("v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)");
			std::smatch vertexMatch;

			if (std::regex_match(line, vertexMatch, vertexRegex))
			{
				vertex newVertex;

				double_t x, y, z;

				std::istringstream xPosStream(vertexMatch[1]);
				std::istringstream yPosStream(vertexMatch[2]);
				std::istringstream zPosStream(vertexMatch[3]);

				if (!(xPosStream >> newVertex.position.x)) {
					assert(false);
				}
				if (!(yPosStream >> newVertex.position.y))
				{
					assert(false);
				}
				if (!(zPosStream >> newVertex.position.z))
				{
					assert(false);
				}

				mesh.getVertices().push_back(newVertex);
			}
		}

		void parseFace(std::string line, Mesh& mesh)
		{
			std::regex indexNormalRegex("f (\\d+)//\\d+ (\\d+)//\\d+ (\\d+)//\\d+");
			std::regex indexNormalTexRegex("f (\\d+)/\\d+/\\d+ (\\d+)/\\d+/\\d+ (\\d+)/\\d+/\\d+");
			std::regex indexRegex("f (\\d+) (\\d+) (\\d+)");
			std::smatch indexMatch;


			if (std::regex_match(line, indexMatch, indexNormalRegex))
			{
				
				for (size_t i = 1; i < 4; i++)
				{
					std::istringstream numConverter(indexMatch[i]);

					uint32_t index;
					numConverter >> index;
					mesh.getIndices().push_back(index);
				}
			}
			else if (std::regex_match(line, indexMatch, indexRegex)) {
				for (size_t i = 1; i < 4; i++)
				{
					std::istringstream numConverter(indexMatch[i]);

					uint32_t index;
					numConverter >> index;
					mesh.getIndices().push_back(index);
				}
			}
			else if (std::regex_match(line, indexMatch, indexNormalTexRegex)) {
				for (size_t i = 1; i < 4; i++)
				{
					std::istringstream numConverter(indexMatch[i]);

					uint32_t index;
					numConverter >> index;
					mesh.getIndices().push_back(index);
				}
			}
		}
	};
}
