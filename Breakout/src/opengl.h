#ifndef OPENGL_H
#define OPENGL_H

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "shader.h"

// Defines definition

#define IMAGE_DIR std::string("./image/")
#define SHADE_DIR std::string("./shader/")


const GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes

// The MAIN function, from here we start the application and run the game loop
void* start(void *args);

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


// Functions prototypes ends
#endif
