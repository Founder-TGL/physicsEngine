#include "shapeData.h"

GLfloat pyramidVertices[] = {
    -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
    -0.5f, 0.0f, -0.5f,  0.83f, 0.70f, 0.44f,
     0.5f, 0.0f, -0.5f,  0.83f, 0.70f, 0.44f,
     0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
     0.0f, 0.8f,  0.0f,  0.92f, 0.86f, 0.76f
};

GLuint pyramidIndices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

const int pyramidVerticesSize = sizeof(pyramidVertices);
const int pyramidIndicesSize = sizeof(pyramidIndices);

GLfloat cubeVertices[] = {
        // positions         // colors
    -0.5f,  0.0f, -0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  0.0f, -0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  1.0f, -0.5f,  0.6f, 0.3f, 0.2f,
    -0.5f,  1.0f, -0.5f,  0.6f, 0.3f, 0.2f,
    -0.5f,  0.0f,  0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  0.0f,  0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  1.0f,  0.5f,  0.6f, 0.3f, 0.2f,
    -0.5f,  1.0f,  0.5f,  0.6f, 0.3f, 0.2f

};
GLuint cubeIndices[] = {
    // back face
    0, 1, 2,
    2, 3, 0,
    // front face
    4, 5, 6,
    6, 7, 4,
    // left face
    4, 0, 3,
    3, 7, 4,
    // right face
    1, 5, 6,
    6, 2, 1,
    // top face
    3, 2, 6,
    6, 7, 3,
    // bottom face
    4, 5, 1,
    1, 0, 4

};
const int cubeVerticesSize = sizeof(cubeVertices);
const int cubeIndicesSize = sizeof(cubeIndices);