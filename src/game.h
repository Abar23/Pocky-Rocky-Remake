#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <future>
#include "shader.h"
#include "core/sound/Audio.h"
#include "stb/stb_image.h"
#include "core/utility/GlErrorCheck.h"

class Game {

	GLFWwindow* window;
	Shader* shader;

	inline static Game* event_handling_instance = nullptr;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	float cameraPosition[3] = { 0,0,0 };
	float deltaTime = 0;
	float lastFrame;
	GLuint          vao;
	GLuint          vbo;
	GLuint          ebo;

public:
	Game() 
	{
		event_handling_instance = this;

		bool success = createWindow();

		shader = new Shader("assets/shaders/gameShader.vs", "assets/shaders/gameShader.fs");

		initRenderer();
		initTextures();

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
		glCall(glDeleteVertexArrays, 1, &vao);
		glCall(glDeleteBuffers, 1, &vbo);

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

#ifdef DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

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

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// enable OpenGL debug context if context allows for debug context
		int flags; 
		glCall(glGetIntegerv, GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glCall(glEnable, GL_DEBUG_OUTPUT);
			glCall(glEnable, GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
			glCall(glDebugMessageCallback, glDebugOutput, nullptr);
			glCall(glDebugMessageControl, GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		return true;
	}

	void initRenderer() {
		float vertices[] = {
			//positions          //tex coords
			1.0f,  171.0f / 16.0f, 0.0f,   1.0f / 7.0f, 171.0f / 379.0f,// top right
			1.0f, -1.0f, 0.0f,   1.0f / 7.0f, 0.0f,// bottom right
		   -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,// bottom left
		   -1.0f,  171.0f / 16.0f, 0.0f,   0.0f, 171.0f / 379.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		glCall(glGenVertexArrays, 1, &vao);
		glCall(glGenBuffers, 1, &vbo);
		glCall(glGenBuffers, 1, &ebo);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glCall(glBindVertexArray, vao);

		glCall(glBindBuffer, GL_ARRAY_BUFFER, vbo);
		glCall(glBufferData, GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glCall(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ebo);
		glCall(glBufferData, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glCall(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glCall(glEnableVertexAttribArray, 0);

		glCall(glVertexAttribPointer, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glCall(glEnableVertexAttribArray, 1);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glCall(glBindBuffer, GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glCall(glBindVertexArray, 0);
	}

	void initTextures() {
		unsigned int mapTexture;

		glCall(glGenTextures, 1, &mapTexture);
		glCall(glBindTexture, GL_TEXTURE_2D, mapTexture);

		//wrapping
		glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		//filtering 
		glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);// flips y axis

		// load and generate the texture

		unsigned char* data = stbi_load("assets/sprite_sheets/level_one.png", &width, &height, &nrChannels, 0);


		if (data) {
			glCall(glTexImage2D, GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glCall(glGenerateMipmap, GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);


		shader->use();

		shader->setInt("mapTexture", 0);

		// bind textures on corresponding texture units
		glCall(glActiveTexture, GL_TEXTURE0);
		glCall(glBindTexture, GL_TEXTURE_2D, mapTexture);

	}


	void render() {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		processInput();
		glCall(glClearColor, 0.2f, 0.3f, 0.3f, 1.0f);
		glCall(glClear, GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		shader->use();

		glCall(glUniform3f, glGetUniformLocation(shader->ID, "camPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);

		glCall(glBindVertexArray, vao);

		glCall(glDrawElements, GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}





	void processInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPosition[1] += 1.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPosition[1] -= 1.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraPosition[0] -= 1.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPosition[0] += 1.5f * deltaTime;
		}

	}




	//callback functions
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glCall(glViewport, 0, 0, width, height);
	}

	// callback dispatchers
	static void framebuffer_size_callback_dispatch(GLFWwindow* window, int width, int height)
	{
		event_handling_instance->framebuffer_size_callback(window, width, height);
	}

};