cmake_minimum_required(VERSION 3.4)

# Avoid std::optional not declared error
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

project(FrankaRobotStates)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Add include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${MUJOCO_HOME}/include
)
link_directories(
    ${MUJOCO_HOME}/lib
)

# Load dependencies
find_package(yaml-cpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)

# Build shared library

# Build executable
add_executable(01_LoadModel example/01_LoadModel.cpp)
target_link_libraries(01_LoadModel
    ${MUJOCO_HOME}/lib/libmujoco.so
    Threads::Threads
)