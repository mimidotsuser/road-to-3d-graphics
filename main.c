#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "main.h"

char *loadShader(char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {

        logger(stderr, "Could not open file %s", filename);
        exit(1);
    }

    unsigned int size = -1;
    if (fseek(file, 0, SEEK_END) == 0) {
        size = (int) ftell(file);
        if (size == -1) {
            logger(stderr, "Could not seek to end of file: %s: ", filename);
            exit(1);
        }
    }
    char *shaderContent = malloc(sizeof(char) * (size));

    if (fseek(file, 0L, SEEK_SET) != 0) {
        logger(stderr, "Could not seek to the start of file %s", filename);
        exit(1);
    }

    //read the file into the buffer
    fread(shaderContent, sizeof(char), size, file);
    fclose(file);
    return shaderContent;
}

static GLuint compileShader(GLuint shaderType, const char *source) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        // shader did not compiler successfully
        int errorLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);

        char *message = malloc(errorLength * sizeof(char));

        glGetShaderInfoLog(shader, errorLength, &errorLength, message);

        if (shaderType == GL_VERTEX_SHADER) {
            logger(stderr, "Failed to compile the vertex shader %s", source);
        } else {
            logger(stderr, "Failed to compile the fragment shader %s", source);
        }

        free(message);
        glDeleteShader(shader);
        exit(1);
    }

    return shader;
}

static GLuint createShader(const char *vertexShader, const char *fragmentShader) {

    //create a unique named buffer
    GLuint program = glCreateProgram();
    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glValidateProgram(program);

    //delete the shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}

void resizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

    if (!glfwInit()) {
        logger(stderr, "Cannot initialize GL");
        exit(1);
    }

    GLFWwindow *window = glfwCreateWindow(928, 692, "Mino Game", NULL, NULL);
    if (window == NULL) {
        logger(stderr, "Failed to create a GL window");
        glfwTerminate();
        exit(1);
    }

    glfwSetFramebufferSizeCallback(window, resizeCallback);

    glfwMakeContextCurrent(window); //create an OpenGL rendering context

    if (glewInit() != GLEW_OK) {
        logger(stderr, "Failed to initialize glew extension wrangler");
        exit(1);
    }

    float pos[] = {
            // X    Y
            0.5f, -0.5f,
            0.5f, 0.5f,
            0.0f, 0.5f,
            0.0f, -0.5f
    };

    //vertex indices
    GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    /*1. Create a vertex buffer object (VBO)*/
    GLuint buffer;
    glGenBuffers(1, &buffer); // generate a unique buffer on memory
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // bind the buffer to a constant symbol

    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW); //specify the buffer data and size

    /*2. Specify the layout of the vertex buffer above using vertex attribute object (VAO) */
    glEnableVertexAttribArray(0);  //enable the vertex attrib
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    /**3 Create and bind index buffers **/

    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    char *vertexShader = loadShader("resources/shaders/vertex.shader");

    char *fragmentShader = loadShader("resources/shaders/fragment.shader");

    GLuint shader = createShader(vertexShader, fragmentShader);

    glUseProgram(shader);

    while (glfwWindowShouldClose(window) == 0) {

        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw the triangle (DRAW CORE) */
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //cleanup
    glDeleteShader(shader);
    glfwTerminate();
    return 0;
}

