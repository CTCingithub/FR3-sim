#include <iostream>
#include <GLFW/glfw3.h>

#include "mujoco/mujoco.h"

int main(int argc, char **argv)
{
    // 加载模型
    char error[1000] = "";
    mjModel *m = mj_loadXML("FR3_Nohand/scene.xml", nullptr, error, 1000);
    if (!m)
    {
        std::cerr << "加载模型失败: " << error << std::endl;
        return 1;
    }
    mjData *d = mj_makeData(m);

    // 初始化GLFW
    if (!glfwInit())
    {
        std::cerr << "GLFW初始化失败" << std::endl;
        return 1;
    }
    GLFWwindow *window = glfwCreateWindow(1200, 900, "MuJoCo仿真", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // 初始化可视化对象
    // data structures
    mjvCamera cam;  // abstract camera
    mjvOption opt;  // visualization options
    mjvScene scn;   // abstract scene
    mjrContext con; // custom GPU context

    // initialize visualization data structures
    mjv_defaultCamera(&cam);
    mjv_defaultOption(&opt);
    mjv_defaultScene(&scn);
    mjr_defaultContext(&con);
    mjv_makeScene(m, &scn, 10000);             // space for 2000 objects
    mjr_makeContext(m, &con, mjFONTSCALE_150); // model-specific context

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 自定义控制律（示例：位置控制）
        for (int i = 0; i < m->nu; ++i)
        {
            // 自定义控制逻辑（例如：重力补偿+PD控制）
            double target_pos = 0.0;
            double kp = 4500.0; // 根据需求调整
            double kv = 450.0;  // 根据需求调整
            d->ctrl[i] = kp * (target_pos - d->qpos[i]) + kv * (-d->qvel[i]);
        }

        // 执行仿真步
        mj_step(m, d);

        // 更新场景
        mjv_updateScene(m, d, &cam, mjCAT_ALL, &scn);
        mjr_render(0, &scn, &con);

        // 交换缓冲区并处理事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
    mj_deleteData(d);
    mj_deleteModel(m);
    mjr_freeContext(&con);
    mjv_freeScene(&scn);
    glfwTerminate();

    return 0;
}