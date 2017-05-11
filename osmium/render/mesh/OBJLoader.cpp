#include "OBJLoader.h"
#include <fstream>
#include <string>
#include <cassert>
#include <regex>
#include <sstream>


namespace os {
	namespace OBJLoader
	{
		std::shared_ptr<Mesh> loadOBJ(std::string filePath)
		{
			std::ifstream objFile;
			objFile.open(filePath);

			std::string lineToParse = "";
			auto generatedMesh = std::make_shared<Mesh>();
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
					if (lineToParse[1] != ' ')
						break;
					parseVertex(lineToParse, generatedMesh);
					break;
				default:
					break;
				}
			}

			objFile.close();

			return generatedMesh;
		}

		void parseVertex(std::string line, std::shared_ptr<Mesh> mesh)
		{
			assert(line.size() > 0);
			assert(line[0] == 'v');
			assert(line[1] == ' ');

			line = line.substr(1);
			std::istringstream posStream(line);

			vertex newVertex;

			if (!(posStream >> newVertex.position.x))
			{
				assert(false);
			}
			if (!(posStream >> newVertex.position.y))
			{
				assert(false);
			}
			if (!(posStream >> newVertex.position.z))
			{
				assert(false);
			}

			mesh->getVertices().push_back(newVertex);
		}

		void parseFace(std::string line, std::shared_ptr<Mesh> mesh)
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
					index--;
					mesh->getIndices().push_back(index);
				}
			}
			else if (std::regex_match(line, indexMatch, indexRegex)) {
				for (size_t i = 1; i < 4; i++)
				{
					std::istringstream numConverter(indexMatch[i]);

					uint32_t index;
					numConverter >> index;
					index--;
					mesh->getIndices().push_back(index);
				}
			}
			else if (std::regex_match(line, indexMatch, indexNormalTexRegex)) {
				for (size_t i = 1; i < 4; i++)
				{
					std::istringstream numConverter(indexMatch[i]);

					uint32_t index;
					numConverter >> index;
					index--;
					mesh->getIndices().push_back(index);
				}
			}
		}
	};
}
