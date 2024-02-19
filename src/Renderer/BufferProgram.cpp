#include "BufferProgram.h"

namespace Renderer
{
	BufferProgram::BufferProgram()
	{
		glGenBuffers(1, &m_vertices_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertices_VBO);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	}

	void BufferProgram::BufferDataVBO(const float mass[])
	{
				glBufferData(GL_ARRAY_BUFFER, sizeof(mass), mass, GL_STATIC_DRAW);
	}

	void BufferProgram::BufferDataEBO(const float mass[])
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mass), mass, GL_STATIC_DRAW);
	}
}