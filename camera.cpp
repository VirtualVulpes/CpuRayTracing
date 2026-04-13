#include "camera.h"

#include <format>
#include <iostream>

#include "color.h"
#include "ray.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <glm/gtx/norm.hpp>

#include "constants.h"
#include "material.h"
#include "random.h"
#include "stb_image_write.h"

Camera::Camera(uint32_t id, glm::ivec2 imageSize, float viewportWidth) : id_(id),
    imageSize_(imageSize), viewportSize_{
        viewportWidth,
        calculateViewportHeight(viewportWidth)
    },
    viewportPosition_{calculateViewportPosition()},
    pixelDeltas_(calculatePixelDeltas()) {}

void Camera::render(const std::vector<std::unique_ptr<Hittable> >& hittables) const {
    std::cout << std::format("Camera {} started.", id_) << std::endl;

    std::vector<Color> colors(imageSize_.x * imageSize_.y);

    for (int y = 0; y < imageSize_.y; ++y) {
        std::cout << std::format("\rScan lines remaining: {}", imageSize_.y - y) << std::flush;
        for (int x = 0; x < imageSize_.x; ++x) {
            int index = x + y * imageSize_.x;

            glm::vec3 worldPos = getPixelPosition({x, y});
            glm::vec3 color{0.0f};
            for (int i = 0; i < Config::NumSamples; ++i) {
                glm::vec3 offset{(Random::floatRange(0.0f, 1.0f) - 0.5f) * pixelDeltas_.x, (Random::floatRange(0.0f, 1.0f) - 0.5f) * pixelDeltas_.y, 0};
                Ray ray{position_, (worldPos + offset) - position_};

                color += getPixelColor(ray, 0, hittables);
            }
            color /= Config::NumSamples;

            colors.at(index) = ColorUtils::floatToInt(color);
        }
    }

    std::string fileName = std::format("output/camera_{}.png", id_);
    stbi_write_png(fileName.c_str(), imageSize_.x, imageSize_.y, 3, colors.data(),
                   imageSize_.x * static_cast<int>(sizeof(Color)));

    std::cout << std::format("\rCamera {} finished.", id_) << std::endl;
}

glm::vec3 Camera::getPixelColor(const Ray& ray, int depth, const std::vector<std::unique_ptr<Hittable> >& hittables) const {
    if (depth > Config::MaxBounces) return glm::vec3{0.0f};

    std::optional<HitInfo> info = std::nullopt;
    float closest{Constants::Infinity};
    for (const auto& hittable : hittables) {
        if (auto hitInfo = hittable->isHit(ray, 0.0f, Constants::Infinity)) {
            if (hitInfo->t < closest && hitInfo->t > 1e-4) {
                closest = hitInfo->t;
                info = hitInfo;
            }
        }
    }

    if (info.has_value()) {
        glm::vec3 direction = info->normal + Random::randomUnitVector();
        if (info->material) {

            return info->material->color * getPixelColor({info->position, direction}, depth + 1, hittables);
        }

        return glm::vec3{1.0f, 0.4f, 0.7f};
    }

    glm::vec3 direction = glm::normalize(ray.direction);
    float a = 0.5f * (direction.y + 1.0f);
    return (1.0f - a) * glm::vec3(1.0f, 1.0f, 1.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);
}

// return the world-space viewport height
float Camera::calculateViewportHeight(float viewportWidth) const {
    float aspectRatio = static_cast<float>(imageSize_.x) / imageSize_.y;
    return viewportWidth / aspectRatio;
}

// return the world-space position of the top-left corner of the viewport
glm::vec3 Camera::calculateViewportPosition() const {
    glm::vec3 center{position_ + viewDirection_ * focalLength_};
    glm::vec3 cornerOffset{-viewportSize_.x / 2.0f, viewportSize_.y / 2.0f, 0.0f};
    return center + cornerOffset;
}

// return world-space distance between pixels
glm::vec2 Camera::calculatePixelDeltas() const {
    return {viewportSize_.x / imageSize_.x, viewportSize_.y / imageSize_.y};
}

// return world-space position of pixel
glm::vec3 Camera::getPixelPosition(glm::vec2 pixelImagePosition) const {
    glm::vec3 pixelPosition = viewportPosition_ + glm::vec3{
                                  pixelDeltas_.x * pixelImagePosition.x, -pixelDeltas_.y * pixelImagePosition.y, 0.0f
                              };
    glm::vec3 halfPixel = {pixelDeltas_.x / 2.0f, -pixelDeltas_.y / 2.0f, 0.0f};
    return pixelPosition + halfPixel;
}
