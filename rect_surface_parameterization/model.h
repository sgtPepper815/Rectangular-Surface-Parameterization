#pragma once

#include <vector>

#include "vec.h"

// set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
const std::vector<Vec3> vertices = {
    Vec3(0.5f,  0.5f, 0.0f), // top right
    Vec3(0.5f, -0.5f, 0.0f),  // bottom right
    Vec3(-0.5f, -0.5f, 0.0f),  // bottom left
    Vec3(-0.5f,  0.5f, 0.0f)   // top left 
};

const std::vector<unsigned int> indices = {  // note that we start from 0 and go anti clockwise
    0, 3, 1,  // first Triangle
    1, 3, 2   // second Triangle
};