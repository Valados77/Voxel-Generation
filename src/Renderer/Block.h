#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Renderer
{
	class Block
	{
	public:
		Block();
		//void render(std::shared_ptr<Renderer::ShaderProgram>& shaderProgram);
		void generateBlock();
	private:
		void generateFrontSide();
		void generateBackSide();
		void generateLeftSide();
		void generateRightSide();
		void generateBottomSide();
		void generateTopSide();

		std::vector<GLuint> m_indices;
		GLfloat cube[];
	};
}