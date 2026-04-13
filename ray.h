#pragma once

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;

    glm::vec3 at(float t) const {
        return origin + direction * t;
    }
};
