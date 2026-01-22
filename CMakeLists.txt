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

# find_package(Eigen3 REQUIRED)
# find_package(Threads REQUIRED)
# find_package(glfw3 REQUIRED)
# find_package(OpenGL REQUIRED)

find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Build shared library
pybind11_add_module(FindConfig SHARED src/FindConfig.cpp)
target_link_libraries(FindConfig
    yaml-cpp::yaml-cpp
)

# Build executable
# add_executable(01_LoadModel example/01_LoadModel.cpp)
# target_link_libraries(01_LoadModel
#     ${MUJOCO_HOME}/lib/libmujoco.so
#     Threads::Threads
# )

# add_executable(02_Visualization example/02_Visualization.cpp)
# target_link_libraries(02_Visualization
#     ${MUJOCO_HOME}/lib/libmujoco.so
#     Threads::Threads
#     glfw
#     # OpenGL::GL
# )