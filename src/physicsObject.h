#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader;

class PhysicsObject {
public:
    PhysicsObject(float mass, glm::vec3 position, glm::vec3 velocity = {}, glm::vec3 acceleration = {});
    
    void Update(float deltaTime);
    void displayVelocity();
    void ApplyForce(const glm::vec3& force);


    glm::mat4 GetModelMatrix() const;
    void SetAcceleration(glm::vec3 newAccel);
    void SetVelocity(glm::vec3 newVel);
    glm::vec3 GetVelocity();
    glm::vec3 GetPosition() const;
    float GetMass() const;

private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;
};

#endif