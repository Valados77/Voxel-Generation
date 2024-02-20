#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Camera.h"
#include "Renderer/BufferProgram.h"
#include "Resources/ResourceManager.h"


float vertices[] = {
	0, 0, 0,  0.0f, 1.0f,	//0	//bottom
	0, 0, 1,  1.0f, 1.0f,	//1
	1, 0, 1,  1.0f, 0.0f,	//2
	1, 0, 0,  0.0f, 0.0f,	//3

	0,  1, 0,  0.0f, 1.0f,	//4	//top
	0,  1, 1,  0.0f, 0.0f,	//5
	1,  1, 1,  1.0f, 0.0f,	//6
	1,  1, 0,  1.0f, 1.0f,	//7
};


GLuint indices[] = {  // note that we start from 0!
	0, 4, 7,	//front
	7, 3, 0,    

	2, 6, 5,	//back
	5, 1, 2,    

	0, 1, 5,	//left
	5, 4, 0,    

	2, 3, 7,	//right
	7, 6, 2,    

	2, 1, 0,	//bottom
	0, 3, 2,    

	5, 6, 7,	//top
	7, 4, 5    
};

//float vertices[] = {
//	0, 0,  0,  0.0f, 0.0f,	//front
//	0,  1,  0,  0.0f, 1.0f,
//	 1,  1,  0,  1.0f, 1.0f,
//	 1, 0,  0,  1.0f, 0.0f,
//
//	0, 0, 1,  0.0f, 0.0f,	//back
//	 1, 0, 1,  1.0f, 0.0f,
//	 1,  1, 1,  1.0f, 1.0f,
//	0,  1, 1,  0.0f, 1.0f,
//
//	0,  1,  1,  1.0f, 0.0f,	//left
//	0,  1, 0,  1.0f, 1.0f,
//	0, 0, 0,  0.0f, 1.0f,
//	0, 0,  1,  0.0f, 0.0f,
//
//	 1,  1,  1,  1.0f, 0.0f,	//right
//	 1, 0,  1,  0.0f, 0.0f,
//	 1, 0, 0,  0.0f, 1.0f,
//	 1,  1, 0,  1.0f, 1.0f,
//
//	0, 0, 0,  0.0f, 1.0f,	//bottom
//	 1, 0, 0,  1.0f, 1.0f,
//	 1, 0,  1,  1.0f, 0.0f,
//	0, 0,  1,  0.0f, 0.0f,
//
//	0,  1, 0,  0.0f, 1.0f,	//top
//	0,  1,  1,  0.0f, 0.0f,
//	 1,  1,  1,  1.0f, 0.0f,
//	 1,  1, 0,  1.0f, 1.0f,
//};
//
//GLuint indices[] = {  // note that we start from 0!
//	0, 1, 3,   // first triangle
//	1, 2, 3,    // second triangle
//
//	4, 5, 7,   // first triangle
//	5, 6, 7,    // second triangle
//
//	8, 9, 11,   // first triangle
//	9, 10, 11,    // second triangle
//
//	12, 13, 15,   // first triangle
//	13, 14, 15,    // second triangle
//
//	16, 17, 19,   // first triangle
//	17, 18, 19,    // second triangle
//
//	20, 21, 23,   // first triangle
//	21, 22, 23,    // second triangle
//};


glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
};

int gl_windowWidth = 640;
int gl_windowHeight = 640;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = gl_windowWidth / 2.0f;
float lastY = gl_windowHeight / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void glfwWindowSizeCallBack(GLFWwindow* pWindow, int wigth, int height);
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode);
void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

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
	glfwSetCursorPosCallback(pWindow, glfwCursorPosCallback);
	glfwSetScrollCallback(pWindow, glfwScrollCallback);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
		Renderer::BufferProgram bufferProgram;

		auto pDefaultShaderProgram = resourceManager.loadShaders("Defaulthader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
		if (!pDefaultShaderProgram)
		{
			std::cerr << "Can't create shader program: " << std::endl;
			return -1;
		}

		auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/container.jpg");

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		bufferProgram.BufferDataVBO(sizeof(vertices), vertices);
		bufferProgram.BufferDataEBO(sizeof(indices), indices);

		bufferProgram.VertexAttribPointer(0, 3, 5, 0);
		bufferProgram.VertexAttribPointer(1, 2, 5, 3);

		pDefaultShaderProgram->use();
		pDefaultShaderProgram->setInt("ourTexture", 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(pWindow))
		{
			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			pDefaultShaderProgram->use();
			bufferProgram.Bind();
			tex->bind();

			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			view = camera.GetViewMatrix();
			projection = glm::perspective(camera.Zoom, static_cast<float>(gl_windowWidth / gl_windowHeight), 0.1f, 100.0f);
			pDefaultShaderProgram->setMat4f("view", view);
			pDefaultShaderProgram->setMat4f("projection", projection);			

			glEnable(GL_DEPTH_TEST);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			for (GLuint i = 0; i < 10; i++)
			{
				// Calculate the model matrix for each object and pass it to shader before drawing
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				pDefaultShaderProgram->setMat4f("view", view);
				pDefaultShaderProgram->setMat4f("projection", projection);
				pDefaultShaderProgram->setMat4f("model", model);

				//glDrawArrays(GL_TRIANGLES, 0, 36);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			}

			/* Swap front and back buffers */
			glfwSwapBuffers(pWindow);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}

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

	if (key == GLFW_KEY_W)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (key == GLFW_KEY_S)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (key == GLFW_KEY_A)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (key == GLFW_KEY_D)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}