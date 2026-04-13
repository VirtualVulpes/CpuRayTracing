#include "application.h"

#include "sphere.h"

void Application::createScene() {
    //cameras_.emplace_back(1, glm::ivec2{160, 90}, 3.0f);
    cameras_.emplace_back(0, glm::ivec2{512, 288}, 1.4f);

    Material red {.color = {0.8f, 0.2f, 0.2f}};
    Material blue {.color = {0.2f, 0.2f, 0.8f}};
    Material pink {.color = {1.0f, 0.4f, 0.7f}};
    Material green {.color = {0.2f, 1.0f, 0.1f}};

    hittables_.emplace_back(std::make_unique<Sphere>(glm::vec3{0.0f, 0.0f, -2.0f}, 0.5f, red));
    hittables_.emplace_back(std::make_unique<Sphere>(glm::vec3{0.0f, -100.5f, -2.0f}, 100, blue));
    hittables_.emplace_back(std::make_unique<Sphere>(glm::vec3{-2.5f, -0.4f, -3.8f}, 0.7f, green));
    hittables_.emplace_back(std::make_unique<Sphere>(glm::vec3{1.4f, 1.0f, -2.5f}, 0.2f, pink));

}

void Application::run() {
    createScene();

    for (const auto& camera : cameras_) {
        camera.render(hittables_);
    }
}
