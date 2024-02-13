#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Resources/ResourceManager.h"


GLfloat point[] =
{
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

GLfloat colors[] =
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

GLfloat texCoords[] = {
	0.5f, 1.0f, 
	1.0f, 0.0f,
	0.0f, 0.0f 
};

int gl_windowWidth = 640;
int gl_windowHeight = 480;

void glfwWindowSizeCallBack(GLFWwindow* pWindow, int wigth, int height)
{
	gl_windowWidth = wigth;
	gl_windowHeight = height;
	glViewport(0, 0, gl_windowWidth, gl_windowHeight);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
}

int main(int arcg, char** argv)
{
	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "GLFW failled!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); Блокирует изменение размера экрана

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* pWindow = glfwCreateWindow(gl_windowWidth, gl_windowHeight, "Hello World", nullptr, nullptr);
	if (!pWindow)
	{
		std::cout << "glfwCreateWindow failled!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack);
	glfwSetKeyCallback(pWindow, glfwKeyCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}

	std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	//std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

	glClearColor(1, 1, 0, 1);

	{
		ResourceManager resourceManager(argv[0]);
		auto pDefaultShaderProgram = resourceManager.loadShaders("Defaulthader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
		if (!pDefaultShaderProgram)
		{
			std::cerr << "Can't create shader program: " << std::endl;
			return -1;
		}

		auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");

		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		GLuint points_vbo = 0;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

		GLuint texCoords_vbo = 0;
		glGenBuffers(1, &texCoords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, texCoords_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);


		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, texCoords_vbo);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		pDefaultShaderProgram->use();
		pDefaultShaderProgram->setInt("tex", 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(pWindow))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			pDefaultShaderProgram->use();
			glBindVertexArray(vao);
			tex->bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			/* Swap front and back buffers */
			glfwSwapBuffers(pWindow);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}