#pragma once
#include <memory>

#include "camera.h"
#include "hittable.h"

class Application {
public:
    void createScene();
    void run();
private:
    std::vector<Camera> cameras_{};
    std::vector<std::unique_ptr<Hittable>> hittables_{};
};
