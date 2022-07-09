#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"

#include "stb/stb_image.h"

class Game {

	GLFWwindow* window;
	Shader* mapShader;
	Shader* pockyShader;

	// # of pixels in x,y for each map part
	// mostly unused, for now
	float  mapPixels[2] = { 1792, 3032 }; 
	float section1Pixels[2] = { 256, 1368 };
	float section2Pixels[2] = { 1280, 216 };
	float section3Pixels[2] = { 256, 3032 };
	int screenPixels[2] = { 256, 216 };


	inline static Game* event_handling_instance = nullptr;
	const unsigned int SCR_WIDTH = 3* screenPixels[0];
	const unsigned int SCR_HEIGHT = 3* screenPixels[1];

	float cameraPosition[3] = { 0,0,0 };
	float deltaTime = 0;
	float lastFrame;
	GLuint          vao;
	GLuint          vbo;
	GLuint          ebo;

	GLuint          vaoPocky;
	GLuint          vboPocky;
	GLuint          eboPocky;

public:
	Game() {
		event_handling_instance = this;

		bool success = createWindow();

		mapShader = new Shader("src/shaders/mapShader.vs", "src/shaders/mapShader.fs");
		pockyShader = new Shader("src/shaders/entityShader.vs", "src/shaders/entityShader.fs");

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
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);

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

	void initRenderer() {

		float mapWidth = 2 * (mapPixels[0] / screenPixels[0]);
		float mapHeight = 2 * (mapPixels[1] / screenPixels[1]);
		float vertices[] = {
			//positions                            //tex coords
			mapWidth-1, mapHeight - 1.0f, 0.0f,    1.0f, 1.0f,  // top right
			mapWidth-1, -1.0f,            0.0f,    1.0f, 0.0f,  // bottom right
			-1.0f,      -1.0f,            0.0f,    0.0f, 0.0f,  // bottom left
			-1.0f,      mapHeight - 1.0f, 0.0f,    0.0f, 1.0f   // top left 
		};

		unsigned int indices[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3,   // second Triangle
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);



		// Setup for pocky entity 
		// not its final location, just putting logic in place
		int cellCount[] = { 26,6 };

		float verticesPocky[] = {
			//positions            //tex coords
			1.0f,  1.0f,  0.0f,    1.0f/cellCount[0], 1.0f,  // top right
			1.0f,  -1.0f, 0.0f,    1.0f/cellCount[0], 1.0f - (1.0f / cellCount[1]),  // bottom right
			-1.0f, -1.0f, 0.0f,    0.0f, 1.0f - (1.0f / cellCount[1]),  // bottom left
			-1.0f, 1.0f,  0.0f,    0.0f, 1.0f  // top left 
		};

		unsigned int indicesPocky[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3,   // second Triangle
		};

		glGenVertexArrays(1, &vaoPocky);
		glGenBuffers(1, &vboPocky);
		glGenBuffers(1, &eboPocky);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(vaoPocky);

		glBindBuffer(GL_ARRAY_BUFFER, vboPocky);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPocky), verticesPocky, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboPocky);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPocky), indicesPocky, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		pockyShader->use();
		glUniform2f(glGetUniformLocation(pockyShader->ID, "scale"), 34.0f/screenPixels[0], 42.0f / screenPixels[1]);



	}

	void setPockySprite(int frameID) {
		int row = frameID / 26;
		int column = frameID % 26;
		pockyShader->use();

		pockyShader->setInt("entityTexture", 1);
		glUniform2f(glGetUniformLocation(pockyShader->ID, "FrameOffset"), column / 26.0f, -row / 6.0f);
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


		mapShader->use();

		mapShader->setInt("mapTexture", 0);

		


		unsigned int pockyTexture;

		glGenTextures(1, &pockyTexture);
		glBindTexture(GL_TEXTURE_2D, pockyTexture);

		//filtering 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load and generate the pocky texture
		data = stbi_load("assets/sprite_sheets/bunnyPocky.png", &width, &height, &nrChannels, 0);


		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);



		pockyShader->use();

		pockyShader->setInt("entityTexture", 1);


		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mapTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pockyTexture);

	}
	
	int currentFrame = 0;
	float frameTime = 0.2f;
	float frameCounter = 0.0f;
	void PockyStuff() {
		frameCounter += deltaTime;
		if (frameCounter >= frameTime) {
			frameCounter = 0;
			currentFrame++;
			if (currentFrame == 131) currentFrame = 0;
		}
		setPockySprite(currentFrame);
	}

	void render() {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		processInput();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draws the map
		mapShader->use();

		glUniform3f(glGetUniformLocation(mapShader->ID, "camPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);

		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// draws pocky
		pockyShader->use();

		glUniform3f(glGetUniformLocation(pockyShader->ID, "camPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);
		glUniform2f(glGetUniformLocation(pockyShader->ID, "entityPos"), cameraPosition[0], cameraPosition[1]);

		PockyStuff();

		glBindVertexArray(vaoPocky);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
		glViewport(0, 0, width, height);
	}

	// callback dispatchers
	static void framebuffer_size_callback_dispatch(GLFWwindow* window, int width, int height)
	{
		event_handling_instance->framebuffer_size_callback(window, width, height);
	}

};