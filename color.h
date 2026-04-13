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
    inline float linearToGamma(float linearComponent) {
        if (linearComponent > 0) return std::sqrt(linearComponent);

        return 0;
    }

    inline glm::vec3 linearToGamma(glm::vec3 input) {
        glm::vec3 output {0.0f};

        if (input.x > 0.0f) { output.x = linearToGamma(input.x); }
        if (input.y > 0.0f) { output.y = linearToGamma(input.y); }
        if (input.z > 0.0f) { output.z = linearToGamma(input.z); }

        return output;
    }

    // convert 0-1 color to 0-255
    inline Color floatToInt(glm::vec3 color) {
        glm::vec3 result = glm::clamp(color, 0.0f, 1.0f);
        result = linearToGamma(result);

        return {
            static_cast<uint8_t>(round(result.r * 255)),
            static_cast<uint8_t>(round(result.g * 255)),
            static_cast<uint8_t>(round(result.b * 255))
        };
    }
}


