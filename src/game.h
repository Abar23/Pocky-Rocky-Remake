#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "locators/EcsLocator.h"
#include "core/ecs/framework/EcsManager.h"
#include "core/ecs/components/Gravity.h"
#include "core/ecs/components/Transform.h"
#include "core/ecs/components/RigidBody.h"
#include "core/ecs/components/SpriteRenderer.h"
#include "core/ecs/systems/PhysicsSystem.h"
#include "core/ecs/systems/RenderSystem.h"
#include "core/ecs/framework/EcsTypes.h"
#include "math/Vec3.h"
#include <memory>

#include "shader.h"
#include "ComponentGenerator.h"

#include "stb/stb_image.h"

class Game {
	GLFWwindow* window;

	EcsManager ecsManager;
	std::shared_ptr<RenderSystem> renderSystem;
	std::vector<Entity> entities;
	Entity pockyEntity;
	Entity mapEntity;


	
	// # of pixels in x,y for each map part
	// not much use now but will be needed later
	float  mapPixels[2] = { 1792, 3032 }; 
	float section1Pixels[2] = { 256, 1368 };
	float section2Pixels[2] = { 1280, 216 };
	float section3Pixels[2] = { 256, 3032 };
	int screenPixels[2] = { 256, 216 };
	

	inline static Game* event_handling_instance = nullptr;
	const unsigned int SCR_WIDTH = 3* screenPixels[0];
	const unsigned int SCR_HEIGHT = 3* screenPixels[1];

	vec3 cameraPosition;
	float deltaTime = 0;
	float lastFrame;

public:

	Game() {
		event_handling_instance = this;

		bool success = createWindow();

		ComponentGenerator::init();

		initTextures();
		initECS();
		initEntities();
		

		lastFrame = (float)glfwGetTime();
	}

	void run() {
		while (!glfwWindowShouldClose(window))
		{
			render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void shutdown() {
		// now that vao is in a component, i dont think its being free'd anymore 
		// (should probably look into that at some point but thats a future problem for future me)
		//glDeleteVertexArrays(1, &vao);
		//glDeleteBuffers(1, &vbo);

		glfwDestroyWindow(window);
		glfwTerminate();
	}

private:

	bool createWindow() {
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// glfw window creation
		// --------------------
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_dispatch);

		glfwSetWindowSizeLimits(window, 2* screenPixels[0], 2* screenPixels[1], GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowAspectRatio(window, screenPixels[0], screenPixels[1]);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		return true;
	} 

	void initTextures() {
		unsigned int mapTexture;

		glGenTextures(1, &mapTexture);
		glBindTexture(GL_TEXTURE_2D, mapTexture);

		//wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		//filtering 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);// flips y axis

		// load and generate the map texture
		unsigned char* data = stbi_load("src/sprites/tempMap.png", &width, &height, &nrChannels, 0);


		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		

		unsigned int pockyTexture;

		glGenTextures(1, &pockyTexture);
		glBindTexture(GL_TEXTURE_2D, pockyTexture);

		//filtering 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load and generate the pocky texture
		data = stbi_load("assets/sprite_sheets/bunnyPocky.png", &width, &height, &nrChannels, 0);


		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);


		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mapTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pockyTexture);
	}
	
	void initECS() {
		// ecs setup
		EcsLocator::provide(&ecsManager);

		ecsManager.RegisterComponent<Transform>();
		ecsManager.RegisterComponent<SpriteRenderer>();


		renderSystem = ecsManager.RegisterSystem<RenderSystem>();

		Signature signature;
		signature.set(ecsManager.GetComponentType<Transform>());
		signature.set(ecsManager.GetComponentType<SpriteRenderer>());
		ecsManager.SetSystemSignature<RenderSystem>(signature);
	}

	void initEntities() {
		//creates map
		mapEntity = ecsManager.CreateEntity();
		entities.push_back(mapEntity);

		ecsManager.AddComponent(
			mapEntity,
			Transform{
				.position = vec3(-1.0f, -1.0f, 0.0f),
				.rotation = vec3(0.0f, 0.0f, 0.0f),
				.scale = vec3(1.0f, 1.0f, 1.0f)
			});

		ecsManager.AddComponent(mapEntity, ComponentGenerator::genSpriteRenderer(ComponentGenerator::Map));

		//creates pocky
		pockyEntity = ecsManager.CreateEntity();
		entities.push_back(pockyEntity);

		ecsManager.AddComponent(
			pockyEntity,
			Transform{
				.position = vec3(0.0f, 0.0f, 0.0f),
				.rotation = vec3(0.0f, 0.0f, 0.0f),
				.scale = vec3(1.0f, 1.0f, 1.0f)
			});

		ecsManager.AddComponent(pockyEntity, ComponentGenerator::genSpriteRenderer(ComponentGenerator::Player));
	}

	// this will be in a PlayerController class later
	int _currentFrame = 0;
	float frameTime = 0.2f;
	float frameCounter = 0.0f;
	void PockyStuff() {
		// updates the frame
		frameCounter += deltaTime;
		if (frameCounter >= frameTime) {
			frameCounter = 0;
			_currentFrame++;
			if (_currentFrame == 131) _currentFrame = 0;
		}
		ecsManager.GetComponent<SpriteRenderer>(pockyEntity).currentFrame = _currentFrame;

		ecsManager.GetComponent<SpriteRenderer>(pockyEntity).cameraPosition = cameraPosition;
		ecsManager.GetComponent<Transform>(pockyEntity).position = cameraPosition;
	}
	

	void render() {

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		processInput();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//update entity data
		PockyStuff();
		ecsManager.GetComponent<SpriteRenderer>(mapEntity).cameraPosition = cameraPosition;

		// renders entities
		renderSystem->Update(deltaTime);
	}



	void processInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPosition.y += 1.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPosition.y -= 1.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraPosition.x -= 1.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPosition.x += 1.5f * deltaTime;
		}

	}

	//callback functions
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	// callback dispatchers
	static void framebuffer_size_callback_dispatch(GLFWwindow* window, int width, int height)
	{
		event_handling_instance->framebuffer_size_callback(window, width, height);
	}
};