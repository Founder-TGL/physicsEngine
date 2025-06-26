#include "PhysicsWorld.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <algorithm>
#include <cmath>

PhysicsWorld::PhysicsWorld(float gravityConst)
    : gravitationalConstant(gravityConst) {}

void PhysicsWorld::AddObject(PhysicsObject* obj) {
    objects.push_back(obj);
}

void PhysicsWorld::SetGravityConstant(float g) {
    gravitationalConstant = g;
}

float PhysicsWorld::GetGravityConstant() const {
    return gravitationalConstant;
}

std::vector<PhysicsObject*> PhysicsWorld::GetObjects(){return objects;}


void PhysicsWorld::Update(float deltaTime) {
    // Reset accelerations
    for (PhysicsObject* obj : objects) {
        obj->SetAcceleration(glm::vec3(0.0f));
    }

    // Apply mutual gravitational forces
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            ApplyMutualGravity(objects[i], objects[j]);
        }
    }

    // Update motion for each object
    for (PhysicsObject* obj : objects) {
        obj->Update(deltaTime);
    }
}

void PhysicsWorld::ApplyMutualGravity(PhysicsObject* a, PhysicsObject* b) {
    glm::vec3 direction = b->GetPosition() - a->GetPosition();
    float distance = glm::length(direction);
    float epsilon = 0.001f; // Prevent division by zero or extreme forces
    if (distance < epsilon) return;

    glm::vec3 unitDir = glm::normalize(direction);
    float forceMag = gravitationalConstant * (a->GetMass() * b->GetMass()) / (distance * distance);
    glm::vec3 force = unitDir * forceMag;

    a->ApplyForce(force);
    b->ApplyForce(-force);
}