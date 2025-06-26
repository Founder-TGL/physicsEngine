#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include "stb_image.h"
#include "shapeData.h"
#include "Camera.h"
#include "PhysicsObject.h"


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <math.h>

const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL window ;3", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO pyramidVAO;
	pyramidVAO.Bind();

	// Generates Vertex Buffer Object and links it to pyramidVertices
	VBO pyramidVBO(pyramidVertices, pyramidVerticesSize);

	// Generates Element Buffer Object and links it to pyramidIndices
	EBO pyramidEBO(pyramidIndices, pyramidIndicesSize);

	// Links VBO to VAO
	pyramidVAO.LinkAttrib(pyramidVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	pyramidVAO.LinkAttrib(pyramidVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	pyramidVAO.Unbind();
	pyramidVBO.Unbind();
	pyramidEBO.Unbind();



	// Generates Vertex Array Object and binds it
	VAO cubeVAO;
	cubeVAO.Bind();

	// Generates Vertex Buffer Object and links it to pyramidVertices
	VBO cubeVBO(cubeVertices, cubeVerticesSize);
	// Generates Element Buffer Object and links it to pyramidIndices
	EBO cubeEBO(cubeIndices, cubeIndicesSize);

	// Links VBO to VAO
	cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	cubeVAO.Unbind();
	cubeVBO.Unbind();
	cubeEBO.Unbind();
	

	// Generates Vertex Array Object and binds it
	VAO sphereVAO;
	sphereVAO.Bind();

	// Generates Vertex Buffer Object and links it to pyramidVertices
	VBO sphereVBO(sphereVertices, sphereVerticesSize);
	// Generates Element Buffer Object and links it to pyramidIndices
	EBO sphereEBO(sphereIndices, sphereIndicesSize);

	// Links VBO to VAO
	sphereVAO.LinkAttrib(sphereVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	sphereVAO.LinkAttrib(sphereVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	sphereVAO.Unbind();
	sphereVBO.Unbind();
	sphereEBO.Unbind();


	// //texture (not working will trouble shoot later)
	

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Instantiate PhysicsObjects
	PhysicsObject pyramid(10, glm::vec3(-10.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.2, 0.1f));
	PhysicsObject cube(10, glm::vec3(10.0f, -1.0f, 0.0f), glm::vec3(0.0f, -0.1, -0.1f));

	PhysicsObject sphere1(100, glm::vec3(0,0,9));

	sphere1.SetAcceleration(glm::vec3(0.0f, -5.0f, 0.0f));  // simulate gravity

	float time = glfwGetTime();
	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{ 
		float currentTime = glfwGetTime();
		static float lastTime = currentTime;
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Update physics
		pyramid.Update(deltaTime);
		cube.Update(deltaTime);
		sphere1.Update(deltaTime);

		if (sphere1.GetPosition().y <= -20){
			sphere1.SetVelocity(glm::vec3(sphere1.GetVelocity().x, -1*(sphere1.GetVelocity().y), sphere1.GetVelocity().z));
		}


		glm::vec3 direction = cube.GetPosition() - pyramid.GetPosition();
		float distance = glm::length(direction);
		glm::vec3 forceDir = glm::normalize(direction);
		float forceMag = 0.001f * (cube.GetMass() * pyramid.GetMass()) / (distance * distance);
		glm::vec3 force = forceDir * forceMag;

		cube.ApplyForce(-force);
		pyramid.ApplyForce(force); 


		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		glm::mat4 model = glm::mat4(1.0f);
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");


		// Draw pyramid
		model = pyramid.GetModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pyramidVAO.Bind();
		glDrawElements(GL_TRIANGLES, pyramidIndicesSize / sizeof(int), GL_UNSIGNED_INT, 0);
		// Draw cube
		model = cube.GetModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cubeVAO.Bind();
		glDrawElements(GL_TRIANGLES, cubeIndicesSize / sizeof(int), GL_UNSIGNED_INT, 0);
		// Draw sphere
		model = sphere1.GetModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sphereVAO.Bind();
		glDrawElements(GL_TRIANGLES, sphereIndicesSize / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	pyramidVAO.Delete(); cubeVAO.Delete();
	pyramidVBO.Delete(); pyramidEBO.Delete();
	cubeVBO.Delete(); cubeEBO.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}