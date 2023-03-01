#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Loader.h"
#include "Model/RawModel.h"

class OBJLoader
{
public:
	static RawModel	LoadObjModel(const std::string& path, Loader& loader);

private:
	static void ProcessVertices(char* facedata, std::vector<unsigned int>& indices, std::vector<glm::vec2>& tempTextures,
		std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals);
};