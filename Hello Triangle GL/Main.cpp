#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

using namespace std;

void fbCallback(GLFWwindow* win, GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
}

const char* vertexShaderSource = "#version 330 core\n"
						"layout(location = 0) in vec3 aPos;\n"
						"void main() {\n"
						"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
						"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
									"out vec4 FragColor;\n"
									"void main() {\n"
									"	FragColor = vec4(1.0f, 0.0f, 1.0f);\n"
									"}\0";

// Two triangles
float vertexArray[] = {
	-0.5f, 1.0f, 0.0f, // Top left middle
	-1.0f, 0.0f, 0.0f, // Left bottom
	0.0f, 0.0f, 0.0f, // Origin
	0.5f, 1.0f, 0.0f, // Top right middle
	1.0f, 0.0f, 0.0f // Right bottom
};

unsigned int indices[] = {
	1, 0, 2, 2, 3, 4 
};

int main() {
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit()) {
		cout << "Failed to initialize GLFW. Exiting." << endl;
		return 0;
	}
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to load GLAD. Exiting." << endl;
		return 0;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, fbCallback);

	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertShader);

	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Main program loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	// Cleanup
	glfwDestroyWindow(window);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}