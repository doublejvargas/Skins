#include "OBJLoader.h"
#include <stdio.h>
#include "Log.h"
#include <time.h>


RawModel OBJLoader::LoadObjModel(const std::string& path, Loader& loader)
{
	clock_t start_time = clock();
	// Open the file as read only
	FILE* file;
	if (fopen_s(&file, path.c_str(), "r") != 0)
	{
		printf("Failed to open: %s\n", path.c_str());
		ASSERT(file != 0); // stops program if file wasn't opened successfully.
	}

	// Storage variables
	std::vector<glm::vec2> textures, tempTextures;
	std::vector<glm::vec3> positions, normals, tempNormals;
	std::vector<unsigned int> indices;

	char *type, *token, *stop = 0;
	float x, y, z;
	char line[256];
	while (fgets(line, 256, file) != NULL)
	{
		token = NULL;
		type = strtok_s(line, " ", &token);
		// V is vertex positions
		if (type[0] == 'v' && type[1] == NULL)
		{
			x = strtof(token, &stop);
			token = stop + 1; // move to next value
			y = strtof(token, &stop);
			token = stop + 1;
			z = strtof(token, &stop);
			// Store a new position
			positions.push_back(glm::vec3(x, y, z));
		}
		// Vt is vertex texture coordinates
		else if (type[0] == 'v' && type[1] == 't')
		{
			x = strtof(token, &stop);
			token = stop + 1; // Move to next value
			y = 1 - strtof(token, &stop);
			// Store a new texture coordinate
			tempTextures.push_back(glm::vec2(x, y));
		}
		// Vn is vertex normal vector
		else if (type[0] == 'v' && type[1] == 'n')
		{
			x = strtof(token, &stop);
			token = stop + 1; // Move to next value
			y = strtof(token, &stop);
			token = stop + 1;
			z = strtof(token, &stop);
			token = stop + 1;
			// Store a new normal vector
			tempNormals.push_back(glm::vec3(x, y, z));
		}
		// F is the index list for face orientation
		else if (type[0] == 'f')
		{
			if (indices.size() == 0)
			{
				// Set the size of the arrays
				textures.resize(positions.size());
				normals.resize(positions.size());
			}
			ProcessVertices(token, indices, tempTextures, textures, tempNormals, normals);
		}
	}

	fclose(file);
	printf("Loaded model: %s in time: %dms\n", path.c_str(), clock() - start_time);

	return loader.LoadToVAO(positions, textures, normals, indices);
}

void OBJLoader::ProcessVertices(char* facedata, std::vector<unsigned int>& indices, std::vector<glm::vec2>& tempTextures,
	std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals)
{
	char* stop;
	int index;
	for (unsigned int i = 0; i < 3; i++) // 0 <= i <= 2
	{
		// Get and store index
		index = strtol(facedata, &stop, 10) - 1;
		indices.push_back(index);
		facedata = stop + 1; // Move to the next value

		// Get and store texture coordinates
		textures[index] = tempTextures[(uint64_t)strtol(facedata, &stop, 10) - 1];
		facedata = stop + 1;

		// Get and store normal vectors
		normals[index] = tempNormals[(uint64_t)strtol(facedata, &stop, 10) - 1];
		facedata = stop + 1;
	}
}

