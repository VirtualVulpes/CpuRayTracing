#pragma once
#include <optional>

#include "ray.h"

struct Material;
struct Ray;

struct HitInfo {
    glm::vec3 position;
    glm::vec3 normal;
    float t;
    bool frontFace;
    const Material* material;

    void setFaceNormal(const Ray& ray, const glm::vec3 outwardNormal) {
        frontFace = glm::dot(ray.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual std::optional<HitInfo> isHit(const Ray& ray, float tMin, float tMax) const = 0;
};
