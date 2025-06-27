#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "spaceTimeGrid.h"
#include "physicsWorld.h"

#include "shaderClass.h"

class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;
	// if the simulation is paused
	bool paused = false;
	bool pausePressedLastFrame = false; 
	//if the mouse should be locked to the frame
	bool mouseLocked = false;
	//checks whether debug mode is enabled
	bool debugEnabled = false;
	bool debugPressedLastFrame = false; 
	//checks whether reset button was pressed
	bool resetPressedLastFrame = false; 
	//checks if spawn was pressed last frame
	Renderable* pyramidRenderable = nullptr;
	Renderable* cubeRenderable = nullptr;
	Renderable* sphereRenderable = nullptr;
	bool spawn1PressedLastFrame = false;
	bool spawn2PressedLastFrame = false;
	bool spawn3PressedLastFrame = false;


	//debug values
	SpacetimeGrid* grid;
	PhysicsWorld* physWorld;
	float spawnDistance = 5.0f;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.05f;
	float sensitivity = 10.0f;



	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position, PhysicsWorld* physWorld = nullptr, SpacetimeGrid* grid = nullptr);

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window, PhysicsWorld* overrideWorld = nullptr, SpacetimeGrid* overrideGrid = nullptr);
};
#endif