#pragma once
#include <memory>

#include "hittable.h"

class Camera {
public:
    Camera(uint32_t id, glm::ivec2 imageSize, float viewportWidth);
    void render(const std::vector<std::unique_ptr<Hittable>>& hittables) const;
private:
    float calculateViewportHeight(float viewportWidth) const;
    glm::vec3 calculateViewportPosition() const;
    glm::vec2 calculatePixelDeltas() const;
    glm::vec3 getPixelPosition(glm::vec2 pixelImagePosition) const;
    glm::vec3 getPixelColor(const Ray& ray, int depth, const std::vector<std::unique_ptr<Hittable>>& hittables) const;

    uint32_t id_;

    glm::vec3 position_{0.0f, 0.0f, 0.0f};
    glm::vec3 viewDirection_{0.0f, 0.0f, -1.0f};

    float focalLength_{1.0f};

    glm::ivec2 imageSize_;

    glm::vec2 viewportSize_;
    glm::vec3 viewportPosition_;

    glm::vec2 pixelDeltas_;
};
