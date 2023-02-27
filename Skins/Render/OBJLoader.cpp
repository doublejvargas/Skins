#include "OBJLoader.h"
#include <stdio.h>
#include "Log.h"


RawModel OBJLoader::LoadObjModel(const std::string& path, Loader& loader)
{
	// Open the file as read only
	FILE* file;
	if (fopen_s(&file, path.c_str(), "r") != 0)
	{
		printf("Failed to open: %s\n", path.c_str());
		ASSERT(file != 0); // stops program if file wasn't opened successfully.
	}

	// Storage variables
	std::vector<float> positions, texarray, normarray;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;

	char *type, *token, *stop = 0;
	char line[256];
	while (fgets(line, 256, file) != NULL)
	{
		token = NULL;
		type = strtok_s(line, " ", &token);
		// V is vertex positions
		if (type[0] == 'v' && type[1] == NULL)
		{
			// Store a new position
			positions.push_back(strtof(token, &stop));
			token = stop + 1; // move to next value
			positions.push_back(strtof(token, &stop));
			token = stop + 1;
			positions.push_back(strtof(token, &stop));
		}
		// Vt is vertex texture coordinates
		else if (type[0] == 'v' && type[1] == 't')
		{
			double x = strtod(token, &stop);
			token = stop + 1; // Move to next value
			double y = strtod(token, &stop);
			textures.push_back(glm::vec2(x, y));
		}
		// Vn is vertex normal vector
		else if (type[0] == 'v' && type[1] == 'n')
		{
			double x = strtod(token, &stop);
			token = stop + 1; // Move to next value
			double y = strtod(token, &stop);
			token = stop + 1;
			double z = strtod(token, &stop);
			token = stop + 1;

			normals.push_back(glm::vec3(x, y, z));
		}
		// F is the index list for face orientation
		else if (type[0] == 'f')
		{
			if (indices.size() == 0)
			{
				// Set the size of the arrays
				texarray.resize((positions.size() / 3) * 2);
				normarray.resize(positions.size());
			}
			ProcessVertices(token, indices, textures, texarray, normals, normarray);
		}
	}

	fclose(file);
	return loader.LoadToVAO(positions.data(), indices.data(), texarray.data(), positions.size(), indices.size(), texarray.size());
}

void OBJLoader::ProcessVertices(char *facedata, std::vector<int>& indices, std::vector<glm::vec2>& textures, 
	std::vector<float>& texarray, std::vector<glm::vec3>& normals, std::vector<float>& normarray)
{
	char* stop;
	unsigned int index;
	for (unsigned int i = 0; i < 3; i++) // 0 <= i <= 2
	{
		// Get and store index
		index = strtol(facedata, &stop, 10) - 1;
		indices.push_back(index);
		facedata = stop + 1; // Move to the next value

		// Get and store texture coordinates
		glm::vec2 texture = textures[(uint64_t)strtol(facedata, &stop, 10) - 1];
		texarray[(uint64_t)index * 2] = texture.x;
		texarray[(uint64_t)index * 2 + 1] = 1 - texture.y; //OpenGL starts textures at top left as opposed to bottom left.
		facedata = stop + 1;

		// Get and store normal vectors
		glm::vec3 normal = normals[(uint64_t)strtol(facedata, &stop, 10) - 1];
		normarray[(uint64_t)index * 3] = normal.x;
		normarray[(uint64_t)index * 3 + 1] = normal.y;
		normarray[(uint64_t)index * 3 + 2] = normal.z;
		facedata = stop + 1;
	}
}

