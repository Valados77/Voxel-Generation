#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
{
	for (int y = 0; y < CHUNK_HEIGHT; y++)
	{
		for (int x = 0; x < CHUNK_WEDTH; x++)
		{
			for (int z = 0; z < CHUNK_WEDTH; z++)
			{
				m_Blocks[x][y][z] = 0;
			}
		}
	}
}

void ChunkRenderer::render(std::shared_ptr<Renderer::ShaderProgram>& shaderProgram)
{
	m_Blocks [0][0][0] = 1;

	for (int y = 0; y < CHUNK_HEIGHT; y++)
	{
		for (int x = 0; x < CHUNK_WEDTH; x++)
		{
			for (int z = 0; z < CHUNK_WEDTH; z++)
			{
				if (m_Blocks[x][y][z] == 1)
				{
					generateBlock();
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(x, y, z));
					shaderProgram->setMat4f("model", model);


				}
			}
		}
	}
}

void ChunkRenderer::generateBlock()
{
	generateFrontSide();
	generateBackSide();
	generateLeftSide();
	generateRightSide();
	generateBottomSide();
	generateTopSide();
}

void ChunkRenderer::generateFrontSide()
{
	m_verticies.push_back(glm::ivec3(0, 0, 0));
	m_verticies.push_back(glm::ivec3(0, 1, 0));
	m_verticies.push_back(glm::ivec3(1, 1, 0));
	m_verticies.push_back(glm::ivec3(1, 0, 0));

	m_indices.push_back(m_verticies.size() - 4);
	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 1);

	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 2);
	m_indices.push_back(m_verticies.size() - 1);
}

void ChunkRenderer::generateBackSide()
{
	m_verticies.push_back(glm::ivec3(0, 0, 1));
	m_verticies.push_back(glm::ivec3(1, 0, 1));
	m_verticies.push_back(glm::ivec3(1, 1, 1));
	m_verticies.push_back(glm::ivec3(0, 1, 1));

	m_indices.push_back(m_verticies.size() - 4);
	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 1);

	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 2);
	m_indices.push_back(m_verticies.size() - 1);
}

void ChunkRenderer::generateLeftSide()
{
	m_verticies.push_back(glm::ivec3(0, 1, 1));
	m_verticies.push_back(glm::ivec3(0, 1, 0));
	m_verticies.push_back(glm::ivec3(0, 0, 0));
	m_verticies.push_back(glm::ivec3(0, 0, 1));

	m_indices.push_back(m_verticies.size() - 4);
	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 1);

	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 2);
	m_indices.push_back(m_verticies.size() - 1);
}

void ChunkRenderer::generateRightSide()
{
	m_verticies.push_back(glm::ivec3(1, 1, 1));
	m_verticies.push_back(glm::ivec3(1, 0, 1));
	m_verticies.push_back(glm::ivec3(1, 0, 0));
	m_verticies.push_back(glm::ivec3(0, 0, 1));

	m_indices.push_back(m_verticies.size() - 4);
	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 1);

	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 2);
	m_indices.push_back(m_verticies.size() - 1);
}

void ChunkRenderer::generateBottomSide()
{
	m_verticies.push_back(glm::ivec3(0, 0, 0));
	m_verticies.push_back(glm::ivec3(1, 0, 0));
	m_verticies.push_back(glm::ivec3(1, 0, 1));
	m_verticies.push_back(glm::ivec3(0, 0, 1));

	m_indices.push_back(m_verticies.size() - 4);
	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 1);

	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 2);
	m_indices.push_back(m_verticies.size() - 1);
}

void ChunkRenderer::generateTopSide()
{
	m_verticies.push_back(glm::ivec3(0, 1, 0));
	m_verticies.push_back(glm::ivec3(0, 1, 1));
	m_verticies.push_back(glm::ivec3(1, 1, 1));
	m_verticies.push_back(glm::ivec3(1, 1, 0));

	m_indices.push_back(m_verticies.size() - 4);
	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 1);

	m_indices.push_back(m_verticies.size() - 3);
	m_indices.push_back(m_verticies.size() - 2);
	m_indices.push_back(m_verticies.size() - 1);
}