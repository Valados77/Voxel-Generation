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

	void BufferProgram::BufferDataVBO(GLsizeiptr size, const GLfloat* mass)
	{
				glBufferData(GL_ARRAY_BUFFER, size, mass, GL_STATIC_DRAW);
	}

	void BufferProgram::BufferDataEBO(GLsizeiptr size, const GLuint* mass)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, mass, GL_STATIC_DRAW);
	}

	void BufferProgram::VertexAttribPointer(const int& layout, const int& attribCount, const int& buffSize, const int& firstBuff)
	{
		glEnableVertexAttribArray(layout);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertices_VBO);
		glVertexAttribPointer(layout, attribCount, GL_FLOAT, GL_FALSE, buffSize * sizeof(GLfloat), (GLvoid*)(firstBuff * sizeof(GLfloat)));
	}

	void BufferProgram::Bind()
	{
		glBindVertexArray(m_VAO);
	}
}