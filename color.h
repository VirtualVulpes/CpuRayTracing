#pragma once

#include <cstdint>
#include <glm/common.hpp>
#include <glm/vec3.hpp>

struct Color {
    uint8_t r{0};
    uint8_t g{0};
    uint8_t b{0};
};

namespace ColorUtils {
    // convert 0-1 color to 0-255
    inline Color floatToInt(glm::vec3 color) {
        glm::vec3 colorClamped = glm::clamp(color, 0.0f, 1.0f);
        return {
            static_cast<uint8_t>(round(colorClamped.r * 255)),
            static_cast<uint8_t>(round(colorClamped.g * 255)),
            static_cast<uint8_t>(round(colorClamped.b * 255))
        };
    }
}


