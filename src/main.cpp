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
#include"spaceTimeGrid.h"
#include"physicsWorld.h"
#include <math.h>

const unsigned int width = 1500;
const unsigned int height = 1000;


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
	
	/* spaceTimeGrid */
	SpacetimeGrid grid(100, 1.0f); 
	VAO gridVAO;// Generates Vertex Array Object and binds it
	gridVAO.Bind();
	VBO gridVBO(grid.vertices.data(), grid.vertices.size() * sizeof(float));// Generates Vertex Buffer Object and links it to pyramidVertices
	EBO gridEBO(grid.indices.data(), grid.indices.size() * sizeof(GLuint));// Generates Element Buffer Object and links it to pyramidIndices
	gridVAO.LinkAttrib(gridVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);	// Links VBO to VAO
	gridVAO.LinkAttrib(gridVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	gridVAO.Unbind();	// Unbind all to prevent accidentally modifying them
	gridVBO.Unbind();
	gridEBO.Unbind();
	

	glEnable(GL_DEPTH_TEST);

	Renderable pyramidMesh(pyramidVertices, pyramidVerticesSize, pyramidIndices, pyramidIndicesSize);
	Renderable cubeMesh(cubeVertices, cubeVerticesSize, cubeIndices, cubeIndicesSize);
	Renderable sphereMesh(sphereVertices, sphereVerticesSize, sphereIndices, sphereIndicesSize);
	// Instantiate PhysicsObjects		
	PhysicsObject pyramid(500, glm::vec3(-10.0f, 1.0f, 0.0f), &pyramidMesh);
	PhysicsObject cube(1000, glm::vec3(10.0f, -1.0f, 0.0f), &cubeMesh);
	PhysicsObject sphere(3000, glm::vec3(0,0,9), &sphereMesh);

	float time, currentTime = glfwGetTime();
	PhysicsWorld world;
	world.AddObject(&pyramid);
	world.AddObject(&cube);
	world.AddObject(&sphere);	

	Camera camera(width, height, glm::vec3(0.0f, 3.0f, 30.0f), &world , &grid);
	camera.pyramidRenderable = &pyramidMesh;
	camera.cubeRenderable = &cubeMesh;
	camera.sphereRenderable = &sphereMesh;


	float lastTime = glfwGetTime();



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{ 
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		if (!camera.paused)		//pauses the simmulation
		{
			world.Update(deltaTime);
			grid.Update(world.GetObjects()); // Apply spacetime warping

			glBindBuffer(GL_ARRAY_BUFFER, gridVBO.ID);
			glBufferSubData(GL_ARRAY_BUFFER, 0, grid.vertices.size() * sizeof(float), grid.vertices.data());
		}
		if (camera.mouseLocked )		//locks the mouse to the center of screen
		{
			double mouseX;
            double mouseY;

            glfwGetCursorPos(window, &mouseX, &mouseY);

			if((mouseX < (width/2)-50) || (mouseX > (width/2)+50) || (mouseY < (height/2)-50) || (mouseY > (height/2)+50)){
				glfwSetCursorPos(window, (width / 2), (height / 2));
			}

		}
		
		glClearColor(0.0f, 0.0f, 0.01f, 1.0f);		// Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clean the back buffer and assign the new color to it
		shaderProgram.Activate();		// Tell OpenGL which Shader Program we want to use

		
		camera.Inputs(window, &world, &grid);
		camera.Matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix");

		glm::mat4 model = glm::mat4(1.0f);
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//sets the draw to be solid object (as its set else for the spacetime grid)

		for (PhysicsObject* obj : world.GetObjects()) {
			obj->Draw(shaderProgram);
		}

		/* grid */
		// std::cout << "Drawing grid with " << grid.indices.size() / 3 << " triangles\n";
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//sets the draw to only do edges (for a more graphy feel)
		model = grid.GetModelMatrix();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		gridVAO.Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(grid.indices.size()), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);		// Swap the back buffer with the front buffer
		glfwPollEvents();		// Take care of all GLFW events
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}