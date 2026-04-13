#pragma once
#include <random>
#include "glm/gtc/epsilon.hpp"

class Random {
public:
    static float floatRange(float min, float max) {
        return std::uniform_real_distribution(min, max)(engine());
    }

    static glm::vec3 vectorRange(float min, float max) {
        return {floatRange(min, max), floatRange(min, max), floatRange(min, max)};
    }

    static glm::vec3 randomUnitVector() {
        while (true) {
            glm::vec3 vector = vectorRange(-1.0f, 1.0f);
            float lengthSqr = glm::length2(vector);
            if (1e-40f < lengthSqr && lengthSqr <= 1) {
                return vector / std::sqrt(lengthSqr);
            }
        }
    }

    static glm::vec3 randomOnHemisphere(glm::vec3 normal) {
        glm::vec3 unitVector = randomUnitVector();

        return glm::dot(normal, unitVector) > 0.0f ? unitVector : -unitVector;
    }

private:
    static std::mt19937& engine() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }
};
