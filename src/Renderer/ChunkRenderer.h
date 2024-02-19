#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int chunkWedth = 10;
const unsigned int chunkHeight = 128;

class ChunkRenderer
{
public:
	int Blocks[chunkWedth][chunkHeight][chunkWedth];
	void start();

private:
	std::vector<glm::vec3> verticies;
	std::vector<int> triangles;

};