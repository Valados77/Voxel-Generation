#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>


namespace Renderer
{
	class ShaderProgram
	{
	private:
		bool m_isCompiled;
		GLuint m_ID = 0;

		bool createShader(const std::string& source, const GLuint shaderType, GLuint& shaderID);

	public:
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgram(ShaderProgram&&) noexcept;
		~ShaderProgram();
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&) noexcept;

		bool isCompilled() const { return m_isCompiled; }
		void use() const;
		void setInt(const std::string& name, const GLint value);
	};
}
