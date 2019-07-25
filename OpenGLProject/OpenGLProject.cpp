#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vec4.h"
#include "Shader.h"
#include "matmath.h"
#include "Tests.h"

// Function Prototypes
GLFWwindow* setupGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// Consts
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	GLFWwindow* window = setupGLFW();
	mat4<> projection = perspective(90.0f, (float)SCR_WIDTH / SCR_HEIGHT, 0.05f, 10.0f);
	//testMat4();
	Shader shader("vertexShader.vs", "fragmentShader.fs");
	float vertices[] = { -0.5f, -0.5f, -0.5f,    //  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,    //  1.0f, 0.0f,
			0.5f, 0.5f, -0.5f,    //  1.0f, 1.0f,
			0.5f, 0.5f, -0.5f,    //  1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f,    //  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,    //  0.0f, 0.0f,

			-0.5f, -0.5f, 0.5f,    //  0.0f, 0.0f,
			0.5f, -0.5f, 0.5f,    //  1.0f, 0.0f,
			0.5f, 0.5f, 0.5f,    //  1.0f, 1.0f,
			0.5f, 0.5f, 0.5f,    //  1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f,    //  0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f,    //  0.0f, 0.0f,

			-0.5f, 0.5f, 0.5f,    //  1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f,    //  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,    //  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,    //  0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f,    //  0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f,    //  1.0f, 0.0f,

			0.5f, 0.5f, 0.5f,    //  1.0f, 0.0f,
			0.5f, 0.5f, -0.5f,    //  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,    //  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,    //  0.0f, 1.0f,
			0.5f, -0.5f, 0.5f,    //  0.0f, 0.0f,
			0.5f, 0.5f, 0.5f,    //  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,    //  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,    //  1.0f, 1.0f,
			0.5f, -0.5f, 0.5f,    //  1.0f, 0.0f,
			0.5f, -0.5f, 0.5f,    //  1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f,    //  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,    //  0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f,    //  0.0f, 1.0f,
			0.5f, 0.5f, -0.5f,    //  1.0f, 1.0f,
			0.5f, 0.5f, 0.5f,    //  1.0f, 0.0f,
			0.5f, 0.5f, 0.5f,    //  1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f,    //  0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f    //,  0.0f, 1.0f
	};

	/*float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};*/
	unsigned int cubeVBO, cubeVAO;
	glGenBuffers(1, &cubeVBO);
	glGenVertexArrays(1, &cubeVAO);
	
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Set up the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Set up the color attribute
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/
	shader.use();
	// Main game loop
	float deg = 0.0f;
	mat4<> view = translate(0.0f, 0.0f, -4.0f);
	shader.setMat4f("projection", projection);
	shader.setMat4f("view", view);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		mat4<> model = rotateAboutArbitraryAxis(vec3<>(0, 0.5, 0.3), vec3<>(0.5, 0.5, 0), deg);
		shader.setMat4f("model", model);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		deg = deg + 0.8f;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

GLFWwindow* setupGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLProject", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		throw -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw -1;
	}
	return window;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}