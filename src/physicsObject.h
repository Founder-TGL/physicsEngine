#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader;

class PhysicsObject {
public:
    PhysicsObject(glm::vec3 position, glm::vec3 velocity = {}, glm::vec3 acceleration = {});
    
    void Update(float deltaTime);
    glm::mat4 GetModelMatrix() const;
    void SetAcceleration(glm::vec3 newAccel);
    void SetVelocity(glm::vec3 newVel);
    glm::vec3 GetVelocity();
    void displayVelocity();
    glm::vec3 GetPosition() const;

private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
};

#endif