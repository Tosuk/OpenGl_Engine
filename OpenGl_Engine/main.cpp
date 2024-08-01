#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"
#include "Time.h"
#include "Buffer.h"
#include "Texture.h"
//#include "Model.h"



// Vertex data
float vertices[] =
{
	// positions          // normals           // texture coords	
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
	0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
	0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

	0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f), 
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


unsigned int VBO; // Vertex Buffer Object
unsigned int lightVAO; // Light VAO
unsigned int cubeVAO; // Cube VAO


int success;
char infoLog[512];

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Set the camera position
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Set the camera front
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Set the camera up

// callback function declarations	
void framebuffer_size_callback(GLFWwindow* window, int width, int height); // Window resize callback function declaration
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // Scroll callback function declaration
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn); // Mouse callback function declaration
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); // Key callback function declaration

// Function to process input (declaration)
void processInput(GLFWwindow* window);


// Mouse variables
float lastX = 400, lastY = 300;
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;

//Camera Settings
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//light 
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightPos2(-1.2f, 1.0f, -2.0f);
glm::vec3 lightdir = glm::vec3(-0.2f, -1.0f, -0.3f);
glm::vec3 ambientColor(0.1f, 0.1f, 0.1f);
glm::vec3 lightColor(0.5f, 0.5f, 0.5f);	
glm::vec3 specularColor(1.0f, 1.0f, 1.0f);

//Directional light
glm::vec3 dirAmbient(0.05f, 0.05f, 0.05f);
glm::vec3 dirDiffuse(0.4f, 0.4f, 0.4f);
glm::vec3 dirSpecular(0.5f, 0.5f, 0.5f);

//object color
glm::vec3 objectColor(1.0f, 0.5f, 0.31f);



// Main function
int main() 
{
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	////////////////////Setup////////////////////
	// Initialize GLFW
	if (!glfwInit())
		return -1;

	// Set the OpenGL version to 3.3 (Core Profile = Modern OpenGL without deprecated features)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(854, 480, "Hello World", NULL, NULL);
	glfwSetWindowAspectRatio(window, 16, 9);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;	
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;	
		glfwTerminate();
		return -1;
	}
	// Set the viewport size
	glViewport(0, 0, 854, 480);

	


	////////////////////Shaders////////////////////
	//Shader shader("C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/VertexShading.glsl", "C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/fragmentShading.glsl");

	Shader lightShader("C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/lightVertex.glsl", "C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/lightFragment.glsl");
	Shader lightCubeShader("C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/lightCubeVertex.glsl", "C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/lightCubeFragment.glsl");


	////////////////////Texture////////////////////
	Texture texture1("C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/container2.png");
	Texture texture2("C:/Users/tosuk/source/repos/OpenGl_Engine/OpenGl_Engine/container2_specular.png");

	////////////////////Buffers////////////////////
	
	Buffer buffer(GL_ARRAY_BUFFER, sizeof(vertices), vertices);
	glGenVertexArrays(1, &lightVAO); // Generate 1 vertex array object and store the ID in lightVAO

	
	// Specify the vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer.getID()); // Bind the buffer to the GL_ARRAY_BUFFER target	
	glBindVertexArray(lightVAO); // Generate 1 vertex array object and store the ID in lightVAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Specify the format of the vertex data
	glEnableVertexAttribArray(0); // Enable the vertex  attribute array
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Specify the format of the vertex data	
	glEnableVertexAttribArray(1); // Enable the vertex attribute array

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Specify the format of the vertex data	
	glEnableVertexAttribArray(2); // Enable the vertex attribute array

	glGenVertexArrays(1, &cubeVAO); // Generate 1 vertex array object and store the ID in VAO
	glBindVertexArray(cubeVAO); // Generate 1 vertex array object and store the ID in VAO
	glBindBuffer(GL_ARRAY_BUFFER, buffer.getID()); // Bind the buffer to the GL_ARRAY_BUFFER target

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Specify the format of the vertex data
	glEnableVertexAttribArray(0); // Enable the vertex attribute array
	

	//zbuffer
	glEnable(GL_DEPTH_TEST);


	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set the clear color

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	// Set the callback functions
	glfwSetCursorPosCallback(window, mouse_callback); // Set the mouse callback function
	glfwSetScrollCallback(window, scroll_callback);	// Set the scroll callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the window resize callback function
	glfwSetKeyCallback(window, key_callback); // Set the key callback function


	////////////////////Main Loop////////////////////
	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		Time::updateTime();

		// Process input
		processInput(window); 
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer and the depth buffer	

		//shader.use();
		lightShader.use();

		//Material
		lightShader.setInt("material.diffuse", 0);
		lightShader.setInt("material.specular", 1);
		lightShader.setFloat("material.shininess", 32.0f);

		//Spotlight
		lightShader.setVec3("spotLight.ambient", ambientColor);
		lightShader.setVec3("spotLight.diffuse", lightColor);
		lightShader.setVec3("spotLight.specular", specularColor);
		lightShader.setVec3("spotLight.position", camera.getPosition());
		lightShader.setFloat("spotLight.constant", 1.0f);
		lightShader.setFloat("spotLight.linear", 0.09f);
		lightShader.setFloat("spotLight.quadratic", 0.032f);
		lightShader.setVec3("spotLight.direction", camera.getFront());
		lightShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f))); 
		lightShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f))); 

		
		//Pointlight
		lightShader.setVec3("pointLights[0].ambient", ambientColor);
		lightShader.setVec3("pointLights[0].diffuse", lightColor);
		lightShader.setVec3("pointLights[0].specular", specularColor);
		lightShader.setVec3("pointLights[0].position", lightPos);
		lightShader.setFloat("pointLights[0].constant", 1.0f);
		lightShader.setFloat("pointLights[0].linear", 0.09f);
		lightShader.setFloat("pointLights[0].quadratic", 0.032f);

		//Directional light
		lightShader.setVec3("dirLight.ambient", dirAmbient);
		lightShader.setVec3("dirLight.diffuse", dirDiffuse);
		lightShader.setVec3("dirLight.specular", dirSpecular);
		lightShader.setVec3("dirLight.direction", lightdir);

		lightShader.setVec3("viewPos", camera.getPosition());


		glm::mat4 pers = glm::perspective(glm::radians(camera.getZoom()), (float)16/(float)9, 0.1f, 100.0f); // Create a perspective matrix
		glm::mat4 view = camera.getViewMatrix();
		for(int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f); // Create a 4x4 identity matrix
			model = glm::translate(model, cubePositions[i]); // Translate the matrix
			float angle = 20.0f * i; // Calculate the angle
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); // Rotate the matrix
			lightShader.setMat4("model", model); // Set the model uniform
			glBindVertexArray(lightVAO); // Bind the VAO
			texture1.Bind();
			texture2.Bind(1);
			glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the triangle
		}

		lightShader.setMat4("projection", pers); // Set the perspective uniform
		lightShader.setMat4("view", view); // Set the view uniform


		lightCubeShader.use();
		lightCubeShader.setMat4("projection", pers); // Set the perspective uniform
		lightCubeShader.setMat4("view", view); // Set the view uniform	
		
		glm::mat4 model = glm::mat4(1.0f); // Create a 4x4 identity matrix
		model = glm::translate(model, lightPos); // Translate the matrix
		model = glm::scale(model, glm::vec3(0.2f)); // Scale the matrix
		lightCubeShader.setMat4("model", model); // Set the model uniform

		glBindVertexArray(cubeVAO); // Bind the VAO
		glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the triangle


		



		// Swap the buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}


	////////////////////Cleanup////////////////////
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);
	texture1.~Texture();
	texture2.~Texture();


	// Terminate GLFW
	glfwTerminate();
	return 0;
}


// Callback function for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	std::cout << "Window resized to " << width << "x" << height << std::endl;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

// for Input prozessed once after key is pressed 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_F5) && action == GLFW_PRESS)
	{
		if (glfwGetWindowAttrib(window, GLFW_MAXIMIZED) == GLFW_TRUE)
		{
			glfwRestoreWindow(window);
		}
		else
		{
			glfwMaximizeWindow(window);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


// Function to process input every frame
void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_SPACE)== GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.SetSpeed(10.0f);	
	}
	else
	{
		camera.SetSpeed(2.5f);
	}
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, Time::deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, Time::deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(LEFT, Time::deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(RIGHT, Time::deltaTime);
	}
	
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}