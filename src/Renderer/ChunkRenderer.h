#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

const unsigned int CHUNK_WEDTH = 10;
const unsigned int CHUNK_HEIGHT = 128;

class ChunkRenderer
{
public:
	ChunkRenderer();
	void render(std::shared_ptr<Renderer::ShaderProgram>& shaderProgram);
	std::vector<glm::ivec3> getVerticies() { return m_verticies; }
	std::vector<int> getIndices() { return m_indices; }

private:
	int m_Blocks[CHUNK_WEDTH][CHUNK_HEIGHT][CHUNK_WEDTH];
	std::vector<glm::ivec3> m_verticies;
	std::vector<int> m_indices;

	void generateBlock();
	void generateFrontSide();
	void generateBackSide();
	void generateLeftSide();
	void generateRightSide();
	void generateBottomSide();
	void generateTopSide();
};