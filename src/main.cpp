#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Camera.h"
#include "Resources/ResourceManager.h"



float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

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

GLuint indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

int gl_windowWidth = 640;
int gl_windowHeight = 640;

GLfloat lastX = 400, lastY = 300;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
bool firstMouse = true;

GLfloat fov = 45.f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

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
		auto pDefaultShaderProgram = resourceManager.loadShaders("Defaulthader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
		if (!pDefaultShaderProgram)
		{
			std::cerr << "Can't create shader program: " << std::endl;
			return -1;
		}

		auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/container.jpg");

		GLuint vertices_vbo = 0;
		glGenBuffers(1, &vertices_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		pDefaultShaderProgram->use();
		pDefaultShaderProgram->setInt("ourTexture", 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(pWindow))
		{
			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			pDefaultShaderProgram->use();
			glBindVertexArray(vao);
			tex->bind();

			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			glm::vec3 front = glm::vec3(1.0f);
			front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
			front.y = sin(glm::radians(pitch));
			front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
			cameraFront = glm::normalize(front);

			view = camera.GetViewMatrix();
			projection = glm::perspective(camera.Zoom, static_cast<float>(gl_windowWidth / gl_windowHeight), 0.1f, 1000.0f);
			pDefaultShaderProgram->setMat4f("view", view);
			pDefaultShaderProgram->setMat4f("projection", projection);			

			glEnable(GL_DEPTH_TEST);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			for (GLuint i = 0; i < 10; i++)
			{
				// Calculate the model matrix for each object and pass it to shader before drawing
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				pDefaultShaderProgram->setMat4f("view", view);
				pDefaultShaderProgram->setMat4f("projection", projection);
				pDefaultShaderProgram->setMat4f("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
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

	GLfloat cameraSpeed = 0.01f;
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