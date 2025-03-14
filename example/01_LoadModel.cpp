#include <iostream>

#include "mujoco/mujoco.h"

char error[1000];
mjModel *m;
mjData *d;

int main(int arg, char **argv)
{
    // load model
    m = mj_loadXML("FR3_Nohand/scene.xml", NULL, error, 1000);
    if (!m)
    {
        std::cout << "Could not load model " << error << std::endl;
        return -1;
    }

    // make data corresponding to model
    d = mj_makeData(m);

    std::cout << "Model loaded successfully" << std::endl;

    // run simulation for 10 seconds
    while (d->time < 100)
        mj_step(m, d);

    std::cout << "Simulation finished" << std::endl;

    // free model and data
    mj_deleteData(d);
    mj_deleteModel(m);

    return 0;
}