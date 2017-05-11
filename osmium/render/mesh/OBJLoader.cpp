#include "OBJLoader.h"
#include <fstream>
#include <string>
#include <cassert>
#include <regex>
#include <sstream>
#include <algorithm>


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
			if (line.find("//") != std::string::npos) {
				const uint16_t numElements = 2;

				for (auto& c : line)
				{
					if (c == '/')
					{
						c = ' ';
					}
				}

				std::istringstream numParser(line.substr(1));

				for (int i = 0; i < 3 * numElements; i++) {
					if (i % numElements == 0) {
						uint32_t num;
						numParser >> num;
						mesh->getIndices().push_back(num - 1);
					}
					else
					{
						uint32_t temp;
						numParser >> temp;
					}
				}
			}
			else if (line.find("/") != std::string::npos) {
				/*
				 *	 f v1/vt1 v2/vt2 v3/vt3
				 *   f 3/1 4/2 5/3
				 *   
				 *   f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
				 *   f 6/4/1 3/5/3 7/6/5
				 */


				/*
				const uint16_t numElements = 3;
				
				for (auto& c : line)
				{
					if (c == '/')
					{
						c = ' ';
					}
				}

				std::istringstream numParser(line.substr(1));

				for (int i = 0; i < 3 * numElements; i++)
				{
					if (i % numElements == 0)
					{
						uint32_t num;
						numParser >> num;
						mesh->getIndices().push_back(num - 1);
					}
					else if (i % numElements == 1)
					{
						uint32_t num;
						numParser >> num;
					}
					else
					{
						uint32_t num;
						numParser >> num;
					}

				}
			}
			else {
				const uint16_t numElements = 1;
				std::istringstream numParser(line.substr(1));
				for (int i = 0; i < 3 * numElements; i++)
				{
					int num;
					numParser >> num;
					mesh->getIndices().push_back(num - 1);
				}
			}
				*/
		}
	};
}
