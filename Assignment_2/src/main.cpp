// OpenGL Helpers to reduce the clutter
#include "Helpers.h"
// GLFW is necessary to handle the OpenGL context
#include <GLFW/glfw3.h>
// Linear Algebra Library
#include <Eigen/Core>
// Timer
#include <chrono>
// VertexBufferObject wrapper
VertexBufferObject VBO;

// Contains the vertex positions
Eigen::MatrixXf V(2,0);
Eigen::MatrixXf storeV(2,0);
// Global tracker for number of vertices
int vertices = 0;
double xworld;
double yworld;
double xoriginal;
double yoriginal;
int currentTriangle;
int closestVertex;

double xcenter;
double ycenter;

// function declarations
void key_callback(GLFWwindow*, int, int, int, int);
// end function declarations

void createSpace() {
	storeV.resize(2, vertices);
	for (int i = 0; i < vertices; i++)
		storeV.col(i) = V.col(i);
	V.resize(2, vertices + 1);
	for (int i = 0; i < vertices; i++)
		V.col(i) = storeV.col(i);
}

void changeStoredCurPos(GLFWwindow* window) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	xworld = ((xpos / double(width)) * 2) - 1;
	yworld = (((height - 1 - ypos) / double(height)) * 2) - 1; // NOTE: y axis is flipped in glfw
}

bool inTriangle(GLFWwindow* window) {
	double triA, triB, triC, triD;
	changeStoredCurPos(window);
	// finding area
	for (int i = 0; i < vertices - 2; i += 3) {
		triA = (V(0,i)*(V(1,i+1) - V(1,i+2))) + (V(0,i+1)*(V(1,i+2) - V(1,i))) + (V(0,i+2)*(V(1,i) - V(1,i+1)));
		triA = abs(triA / 2.0);
		triB = (xworld*(V(1,i+1) - V(1,i+2))) + (V(0,i+1)*(V(1,i+2) - yworld)) + (V(0,i+2)*(yworld - V(1,i+1)));
		triB = abs(triB / 2.0);
		triC = (V(0,i)*(yworld - V(1,i+2))) + (xworld*(V(1,i+2) - V(1,i))) + (V(0,i+2)*(V(1,i) - yworld));
		triC = abs(triC / 2.0);
		triD = (V(0,i)*(V(1,i+1) - yworld)) + (V(0,i+1)*(yworld - V(1,i))) + (xworld*(V(1,i) - V(1,i+1)));
		triD = abs(triD / 2.0);
		
		double triBCD = triB + triC + triD;
		int A = triA * 1000;
		int BCD = triBCD * 1000;
		if (A == BCD) {
			currentTriangle = i;
			return true;
		}
	}
	return false;
}

void findCenter() {
	//xcenter = 
	//ycenter = 
}

int closestVert(GLFWwindow* window) {
	changeStoredCurPos(window);
	
	int vertex = 0;
	double distance = sqrt( pow((V(0,0) - xworld),2) + pow((V(1,0) - yworld),2) );
	double nextDistance = 0;
	
	for (int i = 0; i < vertices - 1; i++) {
		nextDistance = sqrt(pow((V(0, i) - xworld), 2) + pow((V(1, i) - yworld), 2));
		if (distance > nextDistance) {
			distance = nextDistance;
			vertex = i;
		}
	}
	return vertex;
}

void insert(GLFWwindow* window, int button, int action, int mods)
{
	changeStoredCurPos(window);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		createSpace();
		V.col(vertices++) << xworld, yworld;
	}

    // Upload the change to the GPU
    VBO.update(V);
}

static void transHelp(GLFWwindow* window,double x,double y) {
	changeStoredCurPos(window);

	V(0, currentTriangle) += (xworld - xoriginal); V(1, currentTriangle) += (yworld - yoriginal);
	V(0, currentTriangle + 1) += (xworld - xoriginal); V(1, currentTriangle + 1) += (yworld - yoriginal);
	V(0, currentTriangle + 2) += (xworld - xoriginal); V(1, currentTriangle + 2) += (yworld - yoriginal);

	xoriginal = xworld;
	yoriginal = yworld;
	VBO.update(V);
}

void translate(GLFWwindow* window, int button, int action, int mods) {
	changeStoredCurPos(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (inTriangle(window)) {
			xoriginal = xworld;
			yoriginal = yworld;
			glfwSetCursorPosCallback(window,transHelp);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		glfwSetCursorPosCallback(window, 0);
	VBO.update(V);
}

void remove(GLFWwindow* window, int button, int action, int mods)
{
	changeStoredCurPos(window);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (inTriangle(window)) {
			int k = 0;
			storeV.resize(2, vertices - 3);
			for (int i = 0; i < currentTriangle; i++) {
				k++;
				storeV.col(i) = V.col(i);
			}
			for (int i = currentTriangle + 3; i < vertices; i++)
				storeV.col(k) = V.col(i);
			V.resize(2, vertices - 3);
			for (int i = 0; i < vertices - 3; i++)
				V.col(i) = storeV.col(i);
			vertices -= 3;
		}
	}
	VBO.update(V);
}

void chooseColor (GLFWwindow* window, int key, int action, int scancode, int mods){
	switch (key)
	{
		if (action == GLFW_RELEASE) {
			case GLFW_KEY_0:
				break;
			case GLFW_KEY_1:
				break;
			case GLFW_KEY_2:
				break;
			case GLFW_KEY_3:
				break;
			case GLFW_KEY_4:
				break;
			case GLFW_KEY_5:
				break;
			case GLFW_KEY_6:
				break;
			case GLFW_KEY_7:
				break;
			case GLFW_KEY_8:
				break;
			case GLFW_KEY_9:
				break;
			default:
				break;
		}
	}

	// Upload the change to the GPU
	VBO.update(V);
	glfwSetKeyCallback(window, key_callback);	// resetting key callback
}

void color(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		closestVertex = closestVert(window);
		glfwSetKeyCallback(window, chooseColor);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Update the position of the first vertex if the keys 1,2, or 3 are pressed
    switch (key)
    {
		if (action == GLFW_RELEASE) {
			case GLFW_KEY_I:
				glfwSetMouseButtonCallback(window, insert);
				printf("Insert Mode...\n");
				break;
			case GLFW_KEY_O:
				glfwSetMouseButtonCallback(window, translate);
				printf("Translate Mode...\n");
				break;
			case GLFW_KEY_P:
				glfwSetMouseButtonCallback(window, remove);
				printf("Delete Mode...\n");
				break;
			case GLFW_KEY_C:
				glfwSetMouseButtonCallback(window, color);
				break;
			default:
				break;
		}
    }
    // Upload the change to the GPU
    VBO.update(V);
}

int main(void)
{
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

    // Initialize the OpenGL Program
    // A program controls the OpenGL pipeline and it must contains
    // at least a vertex shader and a fragment shader to be valid
    Program program;
    const GLchar* vertex_shader =
            "#version 150 core\n"
                    "in vec2 position;"
                    "void main()"
                    "{"
                    "    gl_Position = vec4(position, 0.0, 1.0);"
                    "}";
    const GLchar* fragment_shader =
            "#version 150 core\n"
                    "out vec4 outColor;"
                    "uniform vec3 triangleColor;"
                    "void main()"
                    "{"
                    "    outColor = vec4(triangleColor, 1.0);"
                    "}";

    // Compile the two shaders and upload the binary to the GPU
    // Note that we have to explicitly specify that the output "slot" called outColor
    // is the one that we want in the fragment buffer (and thus on screen)
    program.init(vertex_shader,fragment_shader,"outColor");
    program.bind();

    // The vertex shader wants the position of the vertices as an input.
    // The following line connects the VBO we defined above with the position "slot"
    // in the vertex shader
    program.bindVertexAttribArray("position",VBO);

    // Save the current time --- it will be used to dynamically change the triangle color
    auto t_start = std::chrono::high_resolution_clock::now();

    // Register the keyboard callback
    glfwSetKeyCallback(window, key_callback);
	
	createSpace();
	vertices++;
    // Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		changeStoredCurPos(window);

		// Bind your VAO (not necessary if you have only one)
		VAO.bind();

		// Bind your program
		program.bind();

		// Clear the framebuffer
		glClearColor(0.47f, 0.78f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// storing cursor position every frame and printing its value
		V.col(vertices - 1) << xworld, yworld;
		printf("%f, ", V(0, vertices - 1));
		printf("%f\r", V(1, vertices - 1));

		// attempt at part 5
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			glClear(GL_COLOR_BUFFER_BIT);
			V.resize(2, 4);
			if (V(0,0) < 1) {
				V(0, 0) += 0.001;
				V(0, 1) += 0.001;
				V(0, 2) += 0.001;
			}
			else if (V(0, 0) > -1) {
				V(0, 0) -= 0.001;
				V(0, 1) -= 0.001;
				V(0, 2) -= 0.001;
			}
		}

		// Draw the triangles
		if (vertices != 0) {
			if ((vertices - 1) % 3 == 0) {
				//printf("ZERO \r");
				glDrawArrays(GL_TRIANGLES, 0, vertices);
			}
			else if ((vertices - 1) % 3 == 1) {
				//printf("ONE \r");
				glDrawArrays(GL_TRIANGLES, 0, vertices);
				glDrawArrays(GL_LINES, vertices - 2, 2);
			}
			else if ((vertices - 1) % 3 == 2) {
				//printf("TWO \r");
				glDrawArrays(GL_TRIANGLES, 0, vertices);
				glDrawArrays(GL_LINE_STRIP, vertices - 3, 2);
			}
		}

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

		VBO.update(V);
    }

    // Deallocate opengl memory
    program.free();
    VAO.free();
    VBO.free();

    // Deallocate glfw internals
    glfwTerminate();
    return 0;
}