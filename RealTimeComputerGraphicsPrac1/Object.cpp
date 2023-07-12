#include "Object.h"

Object::Object() {

    vertexData = {
        // Front 
        -0.5f, -0.5f, 0.5f,   // bottom left
        0.5f, -0.5f, 0.5f,    // bottom right
        0.5f, 0.5f, 0.5f,     // top right
        -0.5f, 0.5f, 0.5f,    // top left

        // Back 
        -0.5f, -0.5f, -0.5f,  // bottom left
        0.5f, -0.5f, -0.5f,   // bottom right
        0.5f, 0.5f, -0.5f,    // top right
        -0.5f, 0.5f, -0.5f,   // top left
    };

    indexData = {
        // Front 
        0, 1, 2,
        2, 3, 0,
        // Right 
        1, 5, 6,
        1, 6, 2,
        // Top 
        3, 2, 6,
        3, 6, 7,
        // Bottom 
        0, 4, 5,
        0, 5, 1,
        // Back 
        4, 7, 6,
        4, 6, 5,
        // Left 
        0, 3, 7,
        0, 7, 4,
    };



}