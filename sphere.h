#include "hittable.h"
#include "material.h"


class Sphere : public Hittable {
public:
    Sphere(glm::vec3 center, float radius, const Material& material);

    std::optional<HitInfo> isHit(const Ray& ray, float tMin, float tMax) const override;

    const Material& getMaterial() const { return material_; }

private:
    glm::vec3 center_;
    float radius_;
    Material material_;
};
