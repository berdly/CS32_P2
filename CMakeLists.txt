cmake_minimum_required(VERSION 2.8.12.2)
project(SpaceShooter)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB_RECURSE source_executable      src/*.cpp)
file(GLOB_RECURSE source_lib_headers src/lib/*.h)
file(GLOB_RECURSE source_lib_impl src/lib/*.cpp)

file(GLOB_RECURSE glfw_impl dependencies/glfw/src/*.c)
file(GLOB_RECURSE glfw_include dependencies/glfw/include/*.h)

add_executable(main ${source_executable})
add_library(lib ${source_lib_impl})
add_library(glad dependencies/glad/src/glad.c)
add_library(glfw ${glfw_impl})

target_link_libraries(main PUBLIC lib glad glfw)
target_link_libraries(lib PUBLIC glad glfw)

add_compile_options(main PUBLIC -std=c++17)
add_compile_options(lib PUBLIC -std=c++17)

target_include_directories(main PUBLIC src/lib dependencies/glad/include dependencies/glfw/include dependencies/headers dependencies/headers/glm)
target_include_directories(lib PUBLIC src/lib dependencies/glad/include dependencies/glfw/include dependencies/headers dependencies/headers/glm)

target_include_directories(glad PUBLIC dependencies/glad/include)
target_include_directories(glfw PUBLIC dependencies/glfw/include)

install(TARGETS main DESTINATION ./build)

set(CPACK_PACKAGE_NAME "SpaceShooter")
set(CPACK_PACKAGE_VERSION "1.0.0")

# This must be last
include(CPack)
