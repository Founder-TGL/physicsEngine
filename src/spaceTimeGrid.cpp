#include "spacetimeGrid.h"
#include <cmath>

SpacetimeGrid::SpacetimeGrid(int res, float space) : resolution(res), spacing(space) {
    for (int z = 0; z <= resolution; ++z) {
        for (int x = 0; x <= resolution; ++x) {
            float xPos = (x - resolution / 2) * spacing;
            float zPos = (z - resolution / 2) * spacing;
            vertices.push_back(xPos);
            vertices.push_back(0.0f); // Initial Y (warp height)
            vertices.push_back(zPos);
            vertices.insert(vertices.end(), {0.2f, 0.2f, 0.5f}); // RGB
        }
    }

    for (int z = 0; z < resolution; ++z) {
        for (int x = 0; x < resolution; ++x) {
            int topLeft = z * (resolution + 1) + x;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + (resolution + 1);
            int bottomRight = bottomLeft + 1;

            indices.insert(indices.end(), { static_cast<GLuint>(topLeft), static_cast<GLuint>(bottomLeft),  static_cast<GLuint>(topRight)});
            indices.insert(indices.end(), { static_cast<GLuint>(topRight), static_cast<GLuint>(bottomRight),  static_cast<GLuint>(bottomLeft)});
        }
    }
}

void SpacetimeGrid::Update(const std::vector<PhysicsObject*>& objects) {
    for (int z = 0; z <= resolution; ++z) {
        for (int x = 0; x <= resolution; ++x) {
            int index = (z * (resolution + 1) + x) * 6;
            float xPos = vertices[index];
            float zPos = vertices[index + 2];

            float yWarp = 0.0f;
            for (const auto& obj : objects) {
                glm::vec3 pos = obj->GetPosition();
                float dx = xPos - pos.x;
                float dz = zPos - pos.z;
                float distSq = dx * dx + dz * dz + 0.1f;
                yWarp += -obj->GetMass() / distSq;
            }

            vertices[index + 1] = yWarp * 0.01f; // Apply scaled warp
        }
    }
}
glm::mat4 SpacetimeGrid::GetModelMatrix() const {
    return glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)), glm::vec3(0.0f, -2.5f, 0.0f));
}