// This example is heavily based on the tutorial at https://open.gl
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Helpers.h"	// OpenGL Helpers to reduce the clutter
#include <GLFW/glfw3.h>	// GLFW is necessary to handle the OpenGL context
#include <Eigen/Core>	// Linear Algebra Library
#include <Eigen/Dense>	// So I can use cross();
#include <chrono>		// Timer
#define PI 3.14159265f
// VertexBufferObject wrapper
VertexBufferObject VBO;
VertexBufferObject VBO_C;
VertexBufferObject VBO_N;
// Model Matrix: Contains the vertex positions
Eigen::MatrixXf V(3,36);
// Contains the per-vertex color
Eigen::MatrixXf C(3,36);
// Contains the per face normals
Eigen::MatrixXf N(3,36);
// Model, View, and Perspective matrices
Eigen::Affine3f model;
Eigen::Matrix4f view(4,4);
Eigen::Matrix4f perspective(4,4);

//struct Object { int start; int numVertices; int numFaces;};
//Object objects[];
int numVert = 0;

// Function that initiallizes the perspective matrix. Dominick Aiudi reffered me to this website for assisstance:
// http://spointeau.blogspot.com/2013/12/hello-i-am-looking-at-opengl-3.html
// I also used this website as a reference: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/#the-model-view-and-projection-matrices
void makePerspective() {
	double FoV = 50.0f / (PI * 180.0f);
	double aspect = 4.0f / 3.0f;
	double nearClip = 0.1f;
	double farClip = 100.0f;

	double tanHalfFoV = tan(FoV / 2.0);
	perspective(0,0) = 1.0 / (aspect * tanHalfFoV);
	perspective(1,1) = 1.0 / (tanHalfFoV);
	perspective(2,2) = -(farClip + nearClip) / (farClip - nearClip);
	perspective(3,2) = -1.0;
	perspective(2,3) = -(2.0*farClip*nearClip) / (farClip - nearClip);
}

// Function that initiallizes the view matrix. Dominick Aiudi reffered me to this website for assisstance:
// http://spointeau.blogspot.com/2013/12/hello-i-am-looking-at-opengl-3.html
// I also used this website as a reference: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/#the-model-view-and-projection-matrices
void lookAt() {
	Eigen::Vector3f camPos(4,3,3);	// camera is at 4,3,3 in world space
	Eigen::Vector3f lookTo(0,0,0);	// camera looks towards the origin
	Eigen::Vector3f head(0,1,0);	// head is up (set to 0,-1,0 to Look upside down)

	Eigen::Vector3f	f = (lookTo - camPos).normalized();
	Eigen::Vector3f u = head.normalized();
	Eigen::Vector3f s = f.cross(u).normalized();
	u = s.cross(f);

	view <<
		s.x(), s.y(), s.z(), -s.dot(camPos),
		u.x(), u.y(), u.z(), -u.dot(camPos),
		-f.x(), -f.y(), -f.z(), f.dot(camPos),
		0, 0, 0, 1;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // Get the position of the mouse in the window
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Get the size of the window
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Convert screen position to world coordinates
    double xworld = ((xpos/double(width))*2)-1;
    double yworld = (((height-1-ypos)/double(height))*2)-1; // NOTE: y axis is flipped in glfw

    // Upload the change to the GPU
    VBO.update(V);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int i = numVert;
    // Update the position of the first vertex if the keys 1,2, or 3 are pressed
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		V.conservativeResize(3, numVert + 36);
		V.col(i) << -1.0, -1.0, -1.0;
		V.col(i + 1) << -1.0, -1.0, 1.0;
		V.col(i + 2) << -1.0, 1.0, 1.0;
		V.col(i + 3) << 1.0, 1.0, -1.0;
		V.col(i + 4) << -1.0, -1.0, -1.0;
		V.col(i + 5) << -1.0, 1.0, -1.0;
		V.col(i + 6) << 1.0, -1.0, 1.0;
		V.col(i + 7) << -1.0, -1.0, -1.0;
		V.col(i + 8) << 1.0, -1.0, -1.0;
		V.col(i + 9) << 1.0, 1.0, -1.0;
		V.col(i + 10) << 1.0, -1.0, -1.0;
		V.col(i + 11) << -1.0, -1.0, -1.0;
		V.col(i + 12) << -1.0, -1.0, -1.0;
		V.col(i + 13) << -1.0, 1.0, 1.0;
		V.col(i + 14) << -1.0, 1.0, -1.0;
		V.col(i + 15) << 1.0, -1.0, 1.0;
		V.col(i + 16) << -1.0, -1.0, 1.0;
		V.col(i + 17) << -1.0, -1.0, -1.0;
		V.col(i + 18) << -1.0, 1.0, 1.0;
		V.col(i + 19) << -1.0, -1.0, 1.0;
		V.col(i + 20) << 1.0, -1.0, 1.0;
		V.col(i + 21) << 1.0, 1.0, 1.0;
		V.col(i + 22) << 1.0, -1.0, -1.0;
		V.col(i + 23) << 1.0, 1.0, -1.0;
		V.col(i + 24) << 1.0, -1.0, -1.0;
		V.col(i + 25) << 1.0, 1.0, 1.0;
		V.col(i + 26) << 1.0, -1.0, 1.0;
		V.col(i + 27) << 1.0, 1.0, 1.0;
		V.col(i + 28) << 1.0, 1.0, -1.0;
		V.col(i + 29) << -1.0, 1.0, -1.0;
		V.col(i + 30) << 1.0, 1.0, 1.0;
		V.col(i + 31) << -1.0, 1.0, -1.0;
		V.col(i + 32) << -1.0, 1.0, 1.0;
		V.col(i + 33) << 1.0, 1.0, 1.0;
		V.col(i + 34) << -1.0, 1.0, 1.0;
		V.col(i + 35) << 1.0, -1.0, 1.0;
		C.conservativeResize(3, numVert + 36);
		/*C.col(i) << 0.583f, 0.771f, 0.014f;
		C.col(i + 1) << 0.609f, 0.115f, 0.436f;
		C.col(i + 2) << 0.327f, 0.483f, 0.844f;
		C.col(i + 3) << 0.822f, 0.569f, 0.201f;
		C.col(i + 4) << 0.435f, 0.602f, 0.223f;
		C.col(i + 5) << 0.310f, 0.747f, 0.185f;
		C.col(i + 6) << 0.597f, 0.770f, 0.761f;
		C.col(i + 7) << 0.559f, 0.436f, 0.730f;
		C.col(i + 8) << 0.359f, 0.583f, 0.152f;
		C.col(i + 9) << 0.483f, 0.596f, 0.789f;
		C.col(i + 10) << 0.559f, 0.861f, 0.639f;
		C.col(i + 11) << 0.195f, 0.548f, 0.859f;
		C.col(i + 12) << 0.014f, 0.184f, 0.576f;
		C.col(i + 13) << 0.771f, 0.328f, 0.970f;
		C.col(i + 14) << 0.406f, 0.615f, 0.116f;
		C.col(i + 15) << 0.676f, 0.977f, 0.133f;
		C.col(i + 16) << 0.971f, 0.572f, 0.833f;
		C.col(i + 17) << 0.140f, 0.616f, 0.489f;
		C.col(i + 18) << 0.997f, 0.513f, 0.064f;
		C.col(i + 19) << 0.945f, 0.719f, 0.592f;
		C.col(i + 20) << 0.543f, 0.021f, 0.978f;
		C.col(i + 21) << 0.279f, 0.317f, 0.505f;
		C.col(i + 22) << 0.167f, 0.620f, 0.077f;
		C.col(i + 23) << 0.347f, 0.857f, 0.137f;
		C.col(i + 24) << 0.055f, 0.953f, 0.042f;
		C.col(i + 25) << 0.714f, 0.505f, 0.345f;
		C.col(i + 26) << 0.783f, 0.290f, 0.734f;
		C.col(i + 27) << 0.722f, 0.645f, 0.174f;
		C.col(i + 28) << 0.302f, 0.455f, 0.848f;
		C.col(i + 29) << 0.225f, 0.587f, 0.040f;
		C.col(i + 30) << 0.517f, 0.713f, 0.338f;
		C.col(i + 31) << 0.053f, 0.959f, 0.120f;
		C.col(i + 32) << 0.393f, 0.621f, 0.362f;
		C.col(i + 33) << 0.673f, 0.211f, 0.457f;
		C.col(i + 34) << 0.820f, 0.883f, 0.371f;
		C.col(i + 35) << 0.982f, 0.099f, 0.879f;*/
		for (int k = i; k < i + 36; k++)
			C.col(k) << static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		numVert += 36;
		printf("CUBE\n");
		std::cout << V << std::endl;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		std::string file = "C:/Users/ragry/Documents/GitHub/Assignment_3-pyrokuna/data/bumpy_cube.off";
		std::ifstream inFile(file);
		std::string currLine;
		if (!inFile)
			std::cout << "Unable to open the .off file!" << std::endl;
		else {
			float vertices[3][502];
			int faces[3][1000];
			std::string tempVert;
			std::getline(inFile, currLine);
			std::getline(inFile, currLine);
			for (int k = 0; k < 502; k++) {
				inFile >> tempVert;
				vertices[0][k] = stof(tempVert);
				inFile >> tempVert;
				vertices[1][k] = stof(tempVert);
				inFile >> tempVert;
				vertices[2][k] = stof(tempVert);
			}
			for (int k = 0; k < 1000; k++) {
				inFile >> tempVert >> tempVert;
				faces[0][k] = stof(tempVert);
				inFile >> tempVert;
				faces[1][k] = stof(tempVert);
				inFile >> tempVert;
				faces[2][k] = stof(tempVert);
			}
			V.conservativeResize(3, numVert + 3000);
			for (int k = 0; k < 1000; k++) {
				int vert1 = faces[0][k];
				int vert2 = faces[1][k];
				int vert3 = faces[2][k];

				int j = 0;
				V.col(j + numVert + 0) << vertices[0][vert1 - 1] * 0.1, vertices[1][vert1 - 1] * 0.2, vertices[2][vert1 - 1] * 0.2;
				V.col(j + numVert + 1) << vertices[0][vert2 - 1] * 0.1, vertices[1][vert2 - 1] * 0.2, vertices[2][vert2 - 1] * 0.2;
				V.col(j + numVert + 2) << vertices[0][vert3 - 1] * 0.1, vertices[1][vert3 - 1] * 0.2, vertices[2][vert3 - 1] * 0.2;
				j += 3;

				//std::cout << vertices[0][vert1 - 1] << " " << vertices[1][vert1 - 1] << " " << vertices[2][vert1 - 1] << std::endl;
				//std::cout << vertices[0][vert2 - 1] << " " << vertices[1][vert2 - 1] << " " << vertices[2][vert2 - 1] << std::endl;
				//std::cout << vertices[0][vert3 - 1] << " " << vertices[1][vert3 - 1] << " " << vertices[2][vert3 - 1] << std::endl;
			}
			numVert += 3000;
		}
		printf("BUMPY CUBE\n");
		//std::cout << V << std::endl;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		std::string file = "C:/Users/ragry/Documents/GitHub/Assignment_3-pyrokuna/data/bunny.off";
		std::ifstream inFile(file);
		std::string currLine;
		if (!inFile)
			std::cout << "Unable to open the .off file!" << std::endl;
		else {
			float vertices[3][502];
			int faces[3][1000];
			std::string tempVert;
			std::getline(inFile, currLine);
			std::getline(inFile, currLine);
			for (int k = 0; k < 502; k++) {
				inFile >> tempVert;
				vertices[0][k] = stof(tempVert);
				inFile >> tempVert;
				vertices[1][k] = stof(tempVert);
				inFile >> tempVert;
				vertices[2][k] = stof(tempVert);
			}
			for (int k = 0; k < 1000; k++) {
				inFile >> tempVert >> tempVert;
				faces[0][k] = stof(tempVert);
				inFile >> tempVert;
				faces[1][k] = stof(tempVert);
				inFile >> tempVert;
				faces[2][k] = stof(tempVert);
			}
			V.conservativeResize(3, numVert + 3000);
			for (int k = 0; k < 1000; k++) {
				int vert1 = faces[0][k];
				int vert2 = faces[1][k];
				int vert3 = faces[2][k];

				int j = 0;
				V.col(j + numVert + 0) << vertices[0][vert1 - 1] * 4.0, vertices[1][vert1 - 1] * 4.0, vertices[2][vert1 - 1] * 4.0;
				V.col(j + numVert + 1) << vertices[0][vert2 - 1] * 4.0, vertices[1][vert2 - 1] * 4.0, vertices[2][vert2 - 1] * 4.0;
				V.col(j + numVert + 2) << vertices[0][vert3 - 1] * 4.0, vertices[1][vert3 - 1] * 4.0, vertices[2][vert3 - 1] * 4.0;
				j += 3;

				//std::cout << vertices[0][vert1 - 1] << " " << vertices[1][vert1 - 1] << " " << vertices[2][vert1 - 1] << std::endl;
				//std::cout << vertices[0][vert2 - 1] << " " << vertices[1][vert2 - 1] << " " << vertices[2][vert2 - 1] << std::endl;
				//std::cout << vertices[0][vert3 - 1] << " " << vertices[1][vert3 - 1] << " " << vertices[2][vert3 - 1] << std::endl;
			}
			numVert += 3000;
		}
		printf("BUNNY\n");
		//std::cout << V << std::endl;
    }
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		printf("WIREFRAME MODE\n");
	}
	else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		printf("FLAT SHADING MODE\n");
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		printf("PHONG SHADING MODE\n");
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		int k = 0;
		while (k < numVert)
			V(1, k++) += 0.1;
		printf("WENT UP\n");
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		int k = 0;
		while (k < numVert)
			V(1, k++) -= 0.1;
		printf("WENT DOWN\n");
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		int k = 0;
		while (k < numVert)
			V(0, k++) -= 0.1;
		printf("WENT LEFT\n");
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		int k = 0;
		while (k < numVert)
			V(0, k++) += 0.1;
		printf("WENT RIGHT\n");
	}
	else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		printf("ROTATE ON X\n");
	}
	else if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		printf("ROTATE ON Y\n");
	}
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		printf("ROTATE ON Z\n");
	}
	else if (key == GLFW_KEY_DELETE && action == GLFW_PRESS /*&& triangleIsSelected()*/) {
		printf("DELETE SELECTED TRIANGLE\n");
	}
	else if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		printf("MOVE CAMERA UP\n");
	}
	else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		printf("MOVE CAMERA DOWN\n");
	}
	else if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		printf("MOVE CAMERA LEFT\n");
	}
	else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		printf("MOVE CAMERA RIGHT\n");
	}
	else if (key == GLFW_KEY_B && action == GLFW_PRESS /*&& triangleIsSelected()*/) {
		printf("SCALE ITEM TO BE BIGGER\n");
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS /*&& triangleIsSelected()*/) {
		printf("SCALE ITEM TO BE SMALLER\n");
	}

    // Upload the change to the GPU
    VBO.update(V);
	VBO_C.update(C);
}

void assignModel(float maxX, float minX, float maxY, float minY, float maxZ, float minZ) {
	float aX = (maxX + minX) / 2;
	float aY = (maxY + minY) / 2;
	float aZ = (maxZ + minZ) / 2;
	Eigen::Vector3f center(aX,aY,aZ);
	Eigen::Vector3f	offset = Eigen::Vector3f(0, 0, 0) - center;
	Eigen::Translation3f translation(offset);

	double temp = (PI / 180.0);
	Eigen::AngleAxisf rotation(temp, Eigen::Vector3f(0, 0, 1));

	float sX = (float)2 / (abs(maxX - minX));
	float sY = (float)2 / (abs(maxY - minY));
	float sZ = (float)2 / (abs(maxZ - minZ));
	Eigen::AlignedScaling3f scale = Eigen::AlignedScaling3f(sX, sY, sZ);

	model = translation * rotation * scale;
}

int main(void)
{
	// seeding a random number generator
	srand(static_cast <unsigned> (time(0)));

    GLFWwindow* window;
    // Initialize the library
    if (!glfwInit())
        return -1;
    // Activate supersampling
    glfwWindowHint(GLFW_SAMPLES, 8);
    // Ensure that we get at least a 3.2 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // On apple we have to load a core profile with forward compatibility
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    #ifndef __APPLE__
      glewExperimental = true;
      GLenum err = glewInit();
      if(GLEW_OK != err)
      {
        /* Problem: glewInit failed, something is seriously wrong. */
       fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      }
      glGetError(); // pull and savely ignonre unhandled errors like GL_INVALID_ENUM
      fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    #endif

    int major, minor, rev;
    major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    rev = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
    printf("OpenGL version recieved: %d.%d.%d\n", major, minor, rev);
    printf("Supported OpenGL is %s\n", (const char*)glGetString(GL_VERSION));
    printf("Supported GLSL is %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Initialize the VAO
    // A Vertex Array Object (or VAO) is an object that describes how the vertex
    // attributes are stored in a Vertex Buffer Object (or VBO). This means that
    // the VAO is not the actual object storing the vertex data,
    // but the descriptor of the vertex data.
    VertexArrayObject VAO;
    VAO.init();
    VAO.bind();

    // Initialize the VBO with the vertices data
    // A VBO is a data container that lives in the GPU memory
    VBO.init();
	VBO.update(V);
	// Second VBO for colors
	VBO_C.init();
	VBO_C.update(C);

    // Initialize the OpenGL Program
    // A program controls the OpenGL pipeline and it must contains
    // at least a vertex shader and a fragment shader to be valid
	Program program;
	const GLchar* vertex_shader =
		"#version 150 core\n"
		"in vec2 position;"				// for when projection is removed
		//"in vec3 position;"			// NEED TO CHANGE TO vec3 WHEN DEALING WITH CAMERA
		"in vec3 color;"
		"out vec3 f_color;"
		"out vec3 tempPos;"
		""
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 perspective;"
		""
		"void main()"
		"{"
		//"	tempPos = vec3(model * vec4(position, 1.0));"
		//"	gl_Position =  view * perspective * vec4(tempPos, 1.0);"	// REMOVE 0.0 WHEN DEALING WITH CAMERA
		"	gl_Position = vec4(position, 0.0, 1.0);"	// for when projection is removed
		"	f_color = color;"
		"}";
	const GLchar* fragment_shader =
		"#version 150 core\n"
		"in vec3 f_color;"
		"out vec4 outColor;"
		"uniform vec3 triangleColor;"
		"void main()"
		"{"
		"    outColor = vec4(f_color, 1.0);"
		"}";

	// setting projection and view matrices
	/*perspective = Eigen::Matrix4f::Zero();
	makePerspective();
	lookAt();
	assignModel(1.0,-1.0,1.0,-1.0,1.0,-1.0);*/

	// to make sure things closest to the camera are displayed first
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    // Compile the two shaders and upload the binary to the GPU
    // Note that we have to explicitly specify that the output "slot" called outColor
    // is the one that we want in the fragment buffer (and thus on screen)
    program.init(vertex_shader,fragment_shader,"outColor");
    program.bind();

    // The vertex shader wants the position of the vertices as an input.
    program.bindVertexAttribArray("position",VBO);
	// The following line connects the VBO we defined above with the position "slot"
	// in the vertex shader
	program.bindVertexAttribArray("color", VBO_C);
	//program.bindVertexAttribArray("color", VBO_N);

    // Register the keyboard callback
    glfwSetKeyCallback(window, key_callback);

    // Register the mouse callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
		// sending the appropriate matrices to the vertex shader
		/*glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, model.data());
		glUniformMatrix4fv(program.uniform("view"), 1, GL_FALSE, view.data());
		glUniformMatrix4fv(program.uniform("perspective"), 1, GL_FALSE, perspective.data());*/

        // Bind your VAO (not necessary if you have only one)
        VAO.bind();
        // Bind your program
        program.bind();
        // Clear the framebuffer
        glClearColor(0.9f, 0.9f, 0.9f, 0.9f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Draw a cube
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    // Deallocate opengl memory
    program.free();
    VAO.free();
    VBO.free();

    // Deallocate glfw internals
    glfwTerminate();
    return 0;
}

	// Set the uniform value depending on the time difference
		/*auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		glUniform3f(program.uniform("triangleColor"), (float)(sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);*/
	// Save the current time --- it will be used to dynamically change the triangle color
		//auto t_start = std::chrono::high_resolution_clock::now();