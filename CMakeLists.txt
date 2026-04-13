cmake_minimum_required(VERSION 4.1)
project(CpuRayTracing)

find_package(glm)
find_package(Stb)

set(CMAKE_CXX_STANDARD 20)

add_executable(CpuRayTracing main.cpp
        application.cpp
        application.h
        constants.h
        camera.cpp
        camera.h
        ray.h
        color.h
        hittable.h
        sphere.cpp
        sphere.h
)

target_precompile_headers(CpuRayTracing PRIVATE
        <cstdint>
        <glm/glm.hpp>
)

target_link_libraries(CpuRayTracing PRIVATE
        glm::glm
)

target_compile_definitions(CpuRayTracing PRIVATE
        GLM_ENABLE_EXPERIMENTAL
)