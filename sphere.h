#include "hittable.h"


class Sphere : public Hittable {
public:
    Sphere(glm::vec3 center, float radius) : center_(center), radius_(radius) {}

    std::optional<HitInfo> isHit(const Ray& ray, float tMin, float tMax) const override;

private:
    glm::vec3 center_;
    float radius_;
};
