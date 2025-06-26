#ifndef SPACE_TIME_GRID_H
#define SPACE_TIME_GRID_H
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/constants.hpp>
#include "PhysicsObject.h"

class SpacetimeGrid {
public:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    int resolution;
    float spacing;

    SpacetimeGrid(int resolution = 100, float spacing = 0.2f);
    void Update(const std::vector<PhysicsObject*>& objects);
    glm::mat4 GetModelMatrix() const;
    
private:
    glm::vec3 position;
};

#endif