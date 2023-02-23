#include "OBJLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

RawModel OBJLoader::LoadObjModel(const std::string& path, Loader& loader)
{
	// Open the file
	std::ifstream file;
	file.open(path);

	std::vector<float> posarray, texarray, normarray;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<char32_t> indices;

	if (file.is_open())
	{
		// temp read variables
		std::string line;
		std::vector<std::string> linearray;
		// Load file and get a line
		while (std::getline(file, line))
		{
			// Split the string
			linearray = SplitString(line, ' ');
			// strings that start with 'v' are vertex positions
			if (linearray[0] == "v")
			{
				// store a new vertex position vec3(stod converts string to double)
				glm::vec3 pos(std::stod(linearray[1]), std::stod(linearray[2]), std::stod(linearray[3]));
				positions.push_back(pos);
			}
			// strings that start with "vt" are vertex texture coordinates
			else if (linearray[0] == "vt")
			{
				// store a new vertex texture coord vec2(stod converts string to double)
				glm::vec2 uv(std::stod(linearray[1]), std::stod(linearray[2]));
				textures.push_back(uv);
			}
			// strings that start with "vn" are vertex normals
			else if (linearray[0] == "vn")
			{
				// store a new vertex normal vec3(stod converts string to double)
				glm::vec3 norm(std::stod(linearray[1]), std::stod(linearray[2]), std::stod(linearray[3]));
				normals.push_back(norm);
			}
			// strings that start with "F" are the faces (indices orientations)
			else if (linearray[0] == "f")
			{
				if (posarray.size() == 0)
				{
					texarray.resize(positions.size() * 2);
					normarray.resize(positions.size() * 3);
				}
				// Process set of vertex data
				ProcessVertices(linearray, indices, textures, texarray, normals, normarray);
			}
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file: " << path << std::endl;
	}

	for (glm::vec3 pos : positions)
	{
		posarray.push_back(pos.x);
		posarray.push_back(pos.y);
		posarray.push_back(pos.z);
	}

	return loader.LoadToVAO(posarray.data(), indices.data(), texarray.data(), posarray.size(), indices.size(), texarray.size());
}

std::vector<std::string> OBJLoader::SplitString(const std::string& string, char delim)
{
	// temp vector
	std::vector<std::string> strvec;
	// create a stream from the string
	std::stringstream ss(string);
	std::string item;
	// Go through each word in the string
	while (std::getline(ss, item, delim))
		strvec.push_back(item);

	return strvec;
}

void OBJLoader::ProcessVertices(std::vector<std::string>& facedata, std::vector<char32_t>& indices, std::vector<glm::vec2>& textures, 
	std::vector<float>& texarray, std::vector<glm::vec3>& normals, std::vector<float>& normarray)
{
	for (unsigned int i = 1; i < 4; i++) // 1 <= i <= 3
	{
		// Get and store vertex data from string input "facedata" eg. "f 58/58/58 67/67/67 54/54/54" where element "58/58/58" is accessed when i = 1.
		std::vector<std::string> vertexdata;
		vertexdata = SplitString(facedata[i], '/'); // this would be "58 58 58" for i = 1.
		// Get and store vertex index
		int index = std::stoi(vertexdata[0]) - 1;   // 0-based indexing.
		indices.push_back(index);
		// Get and store texture coordinates
		glm::vec2 texture = textures.at((int64_t)std::stoi(vertexdata[1]) - 1);
		texarray[(int64_t)index * 2] = texture.x;
		texarray[(int64_t)index * 2 + 1] = 1 - texture.y; // opengl starts from top left corner of texture, blender starts from bottom left.
		// Get and store normal vector data
		glm::vec3 normal = normals.at((int64_t)std::stoi(vertexdata[2]) - 1);
		normarray.at((int64_t)index * 3) = normal.x;
		normarray.at((int64_t)index * 3 + 1) = normal.y;
		normarray.at((int64_t)index * 3 + 2) = normal.z;
	}
}

