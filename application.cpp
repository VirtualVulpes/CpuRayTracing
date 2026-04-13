#include "application.h"

#include "sphere.h"

void Application::createScene() {
    cameras_.emplace_back(0, glm::ivec2{400, 225}, 3.0f);
    cameras_.emplace_back(1, glm::ivec2{2250, 2250}, 5.0f);

    hittables_.emplace_back(std::make_unique<Sphere>(glm::vec3{0.0f, 0.0f, -1.0f}, 0.5f));
    hittables_.emplace_back(std::make_unique<Sphere>(glm::vec3{0.0f, -100.5f, -1.0f}, 100));
}

void Application::run() {
    createScene();

    for (const auto& camera : cameras_) {
        camera.render(hittables_);
    }
}
