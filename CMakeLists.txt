cmake_minimum_required(VERSION 3.0)
project(Test_CMAKE)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE source_executable      src/*.cpp)
file(GLOB_RECURSE source_lib_headers src/lib/*.h)
file(GLOB_RECURSE source_lib_impl src/lib/*.cpp)

file(GLOB_RECURSE glad_impl dependencies/glad/src/*.c)

file(GLOB_RECURSE glfw_impl dependencies/glfw/src/*.c)
file(GLOB_RECURSE glfw_include dependencies/glfw/include/*.h)

# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(main ${source_executable})
add_library(lib &{source_lib_impl})
add_library(glad ${glad_impl})
add_library(glfw ${glfw_impl})

target_link_libraries(lib glad glfw)

# just for example add some compiler flags
target_compile_options(main PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# this lets me include files relative to the root source directory with a <> pair
target_include_directories(example PUBLIC src/lib dependencies/glad/include dependencies/glfw/include)

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable


###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS main DESTINATION build)
# this is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell CMake that we want it
# in the package

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "TestCmake")
set(CPACK_PACKAGE_VERSION "1.0.0")

# This must be last
include(CPack)