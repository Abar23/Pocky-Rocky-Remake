#include "core/ecs/components/SpriteRenderer.h"
#include "shader.h"

class ComponentGenerator {
public:
	enum EntityTypes { Player, Map };

	inline static const float  mapPixels[2] = { 1792, 3032 };
	inline static const int screenPixels[2] = { 256, 216 };

	inline static Shader* entityShader;

	static void init() {
		entityShader = new Shader("src/shaders/entityShader.vs", "src/shaders/entityShader.fs");

	}
	static SpriteRenderer genSpriteRenderer(EntityTypes type) {
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		float vertices[20] = {
			//positions            //tex coords
			1.0f,  1.0f,  0.0f,    1.0f, 1.0f,  // top right
			1.0f,  -1.0f, 0.0f,    1.0f, 0.0f,  // bottom right
			-1.0f, -1.0f, 0.0f,    0.0f, 0.0f,  // bottom left
			-1.0f, 1.0f,  0.0f,    0.0f, 1.0f  // top left 
		};
		int _textureID = 0;

		int _columns = 1;
		float _frameWidth = 1;
		float _frameHeight = 1;
		vec3 _cameraPosition = {0,0,0};
		switch (type)
		{
		case Player:
		{
			std::cout << "player" << std::endl;
			float xScale = 34.0f / screenPixels[0];
			float yScale = 42.0f / screenPixels[1];
			float playerVertices[] = {
				//positions            //tex coords
				xScale,  yScale,  0.0f,    1.0f/26.0f, 1.0f,  // top right
				xScale,  -yScale, 0.0f,    1.0f / 26.0f, 5.0f/6.0f,  // bottom right
				-xScale, -yScale, 0.0f,    0.0f, 5.0f / 6.0f,  // bottom left
				-xScale, yScale,  0.0f,    0.0f, 1.0f  // top left 
			};
			std::copy(playerVertices, playerVertices + 20, vertices);

			_textureID = 1;
			_columns = 26;
			_frameWidth = 1.0f / 26.0f;
			_frameHeight = 1.0 / 6.0f;
			break;
		}
		case Map:
		{
			std::cout << "map" << std::endl;
			float mapWidth = 2 * (mapPixels[0] / screenPixels[0]);
			float mapHeight = 2 * (mapPixels[1] / screenPixels[1]);
			float mapVertices[] = {
				//positions                            //tex coords
				mapWidth, mapHeight, 0.0f,    1.0f, 1.0f,  // top right
				mapWidth, 0,            0.0f,    1.0f, 0.0f,  // bottom right
				0,      0,            0.0f,    0.0f, 0.0f,  // bottom left
				0,      mapHeight , 0.0f,    0.0f, 1.0f   // top left 
			};
			std::copy(mapVertices, mapVertices + 20, vertices);
			_textureID = 0;
		}
			break;
		default:
			std::cout << "???" << std::endl;
		}
		

		unsigned int indices[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3,   // second Triangle
		};


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		
		return SpriteRenderer{
				.shader = entityShader,
				.vao = VAO,
				.textureID = _textureID,
				.columns = _columns,
				.currentFrame = 0,
				.frameWidth = _frameWidth,
				.frameHeight = _frameHeight,
				.cameraPosition = _cameraPosition
		};
	}
};