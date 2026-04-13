#include "sphere.h"

#include "glm/gtx/norm.hpp"

#include "ray.h"

Sphere::Sphere(glm::vec3 center, float radius, const Material& material) : center_(center), radius_(radius), material_(material) {}

std::optional<HitInfo> Sphere::isHit(const Ray& ray, float tMin, float tMax) const {
    glm::vec3 oc = center_ - ray.origin;
    auto a = glm::length2(ray.direction);
    auto h = dot(ray.direction, oc);
    auto c = glm::length2(oc) - radius_ * radius_;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
        return std::nullopt;

    auto sqrtD = std::sqrt(discriminant);

    // find the nearest root that lies in the acceptable range
    auto root = (h - sqrtD) / a;
    if (root <= tMin || tMax <= root) {
        root = (h + sqrtD) / a;
        if (root <= tMin || tMax <= root)
            return std::nullopt;
    }

    HitInfo hit{
        .position = ray.at(root),
        .normal = ray.at(root) - center_ / radius_,
        .t = root,
        .material = &material_
    };
    hit.setFaceNormal(ray, (hit.position - center_) / radius_);

    return hit;
}
