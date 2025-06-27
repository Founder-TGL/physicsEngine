#include "PhysicsObject.h"
#include <iostream>
#include "shaderClass.h"
#include <glm/gtc/type_ptr.hpp>


PhysicsObject::PhysicsObject(float mass, glm::vec3 pos, Renderable* renderable ,glm::vec3 vel, glm::vec3 accel)
    : position(pos), velocity(vel), acceleration(accel), mass(mass), mesh(renderable) {}

PhysicsObject::PhysicsObject(const PhysicsObject& physObj) : position(physObj.position), velocity(physObj.velocity), acceleration(physObj.acceleration), mass(physObj.mass), mesh(physObj.mesh) {}


void PhysicsObject::Update(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

void PhysicsObject::displayVelocity() {
    std::cout << "velocity = (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")";
}

void PhysicsObject::ApplyForce(const glm::vec3& force){
    acceleration += force / mass;
}


void PhysicsObject::Draw(const Shader& shader) const {
    if (!mesh) return;
    glm::mat4 model = GetModelMatrix();
     glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
     mesh->Draw();
 }





glm::mat4 PhysicsObject::GetModelMatrix() const {
    return glm::translate(glm::mat4(1.0f), position);
}

void PhysicsObject::SetAcceleration(glm::vec3 newAccel) {
    acceleration = newAccel;
}

void PhysicsObject::SetVelocity(glm::vec3 newVel) {
    velocity = newVel;
}

glm::vec3 PhysicsObject::GetVelocity(){
    return velocity;
}

glm::vec3 PhysicsObject::GetPosition() const {
    return position;
}

float PhysicsObject::GetMass() const{
    return mass;
}
