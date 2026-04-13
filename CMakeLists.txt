cmake_minimum_required(VERSION 4.1)
project(CpuRayTracing)

find_package(glm)

if(WIN32)
find_package(Stb)
elseif(UNIX)
find_path(STB_INCLUDE_DIR stb_image.h PATH_SUFFIXES stb)
endif()

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
        random.h
        material.h
)

target_precompile_headers(CpuRayTracing PRIVATE
        <cstdint>
        <glm/glm.hpp>
)

if(UNIX)
target_include_directories(CpuRayTracing PRIVATE ${STB_INCLUDE_DIR})
endif()

target_link_libraries(CpuRayTracing PRIVATE
        glm::glm
)

target_compile_definitions(CpuRayTracing PRIVATE
        GLM_ENABLE_EXPERIMENTAL
)