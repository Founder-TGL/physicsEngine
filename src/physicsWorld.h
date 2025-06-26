#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <vector>
#include "PhysicsObject.h"

class PhysicsWorld {
public:

    PhysicsWorld(float gravityConst = 0.01f);

    void AddObject(PhysicsObject* obj);
    void Update(float deltaTime);

    void SetGravityConstant(float g);
    float GetGravityConstant() const;
    std::vector<PhysicsObject*> GetObjects();

private:
    std::vector<PhysicsObject*> objects;
    float gravitationalConstant;

    void ApplyMutualGravity(PhysicsObject* a, PhysicsObject* b);
};

#endif