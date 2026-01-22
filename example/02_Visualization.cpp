#include <iostream>
#include <GLFW/glfw3.h>
#include "mujoco/mujoco.h"
#include "mujoco/mjui.h"

char error[1000];
mjModel *m = nullptr;
mjData *d = nullptr;
mjvScene scn;
mjvCamera cam;
mjvOption opt;
mjrContext con;
GLFWwindow *window = nullptr;

void init_visualization()
{
    if (!glfwInit())
    {
        std::cerr << "Could not initialize GLFW" << std::endl;
        exit(1);
    }

    window = glfwCreateWindow(1200, 900, "MuJoCo Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Could not create GLFW window" << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize visualization structures
    mjv_defaultCamera(&cam);
    mjv_defaultOption(&opt);
    mjr_defaultContext(&con);

    // Create scene and context
    mjv_makeScene(m, &scn, 1000);
    mjr_makeContext(m, &con, mjFONTSCALE_150);
}

int main(int argc, char **argv)
{
    // Load model
    m = mj_loadXML("FR3_Nohand/scene.xml", NULL, error, 1000);
    if (!m)
    {
        std::cout << "Could not load model: " << error << std::endl;
        return -1;
    }

    // Create data
    d = mj_makeData(m);

    // Initialize visualization
    init_visualization();

    std::cout << "Model loaded successfully" << std::endl;

    // Run simulation loop until time reaches 10 or window is closed
    while (!glfwWindowShouldClose(window) && d->time < 10)
    {
        // Advance simulation
        mj_step(m, d);

        // Update scene
        mjv_updateScene(m, d, &opt, NULL, &cam, mjCAT_ALL, &scn);

        // Render
        mjrRect viewport = {0, 0, 0, 0};
        glfwGetFramebufferSize(window, &viewport.width, &viewport.height);
        mjr_render(viewport, &scn, &con);

        // Swap buffers
        glfwSwapBuffers(window);

        // Process events
        glfwPollEvents();
    }

    std::cout << "Simulation finished" << std::endl;

    // Cleanup
    mjv_freeScene(&scn);
    mjr_freeContext(&con);
    glfwDestroyWindow(window);
    glfwTerminate();

    mj_deleteData(d);
    mj_deleteModel(m);

    return 0;
}