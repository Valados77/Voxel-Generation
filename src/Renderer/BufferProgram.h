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
		void BufferDataVBO(const float mass[] );
		void BufferDataEBO(const float mass[]);
	private:
		GLuint m_vertices_VBO;
		GLuint m_VAO;
		GLuint m_EBO;
	};
}