#include "spacetimeGrid.h"
#include <cmath>
#include <iostream>

SpacetimeGrid::SpacetimeGrid(int res, float space, float warpSharpness) : resolution(res), spacing(space), warpSharpness(warpSharpness){
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
    glm::mat4 modelMatrix = this->GetModelMatrix();
    glm::mat4 invModel = glm::inverse(modelMatrix);

    for (int z = 0; z <= resolution; ++z) {
        for (int x = 0; x <= resolution; ++x) {
            int index = (z * (resolution + 1) + x) * 6;

            glm::vec3 localPos(
                vertices[index],
                vertices[index + 1],
                vertices[index + 2]
            );

            // Convert to world space
            glm::vec3 worldPos = glm::vec3(modelMatrix * glm::vec4(localPos, 1.0f));

            float yWarp = 0.0f;
            for (const auto& obj : objects) {
                glm::vec3 objPos = obj->GetPosition();
                float dx = worldPos.x - objPos.x;
                float dz = worldPos.z - objPos.z;
                float dist = sqrt(dx * dx + dz * dz);
                float falloff = exp(-dist * warpSharpness);
                yWarp += -obj->GetMass() * falloff * 0.1f;
            }

            worldPos.y += yWarp * 0.001f;

            // Convert back to local space
            glm::vec3 warpedLocal = glm::vec3(invModel * glm::vec4(worldPos, 1.0f));
            vertices[index + 1] = warpedLocal.y;
        }
    }
}

glm::mat4 SpacetimeGrid::GetModelMatrix() const {
    return glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)), glm::vec3(0.0f, -2.5f, 0.0f));
}

void SpacetimeGrid::dilateWarpSharpness(float warpSharpnessChange){warpSharpness += warpSharpnessChange; std::cout << "warp sharpness set to: " << warpSharpness << std::endl;}
