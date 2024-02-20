#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer
{
	class BufferProgram
	{
	public:
		BufferProgram();
		void BufferDataVBO(GLsizeiptr size, const GLfloat* mass);
		void BufferDataEBO(GLsizeiptr size, const GLuint* mass);
		void VertexAttribPointer(const int& layout, const int& attribCount, const int& buffSize, const int& firstBuff);
		void Bind();
	private:
		GLuint m_vertices_VBO;
		GLuint m_VAO;
		GLuint m_EBO;
	};
}