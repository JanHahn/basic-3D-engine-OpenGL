#include "cube.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <random>

static const float baseVertices[144] = {
    // Przód
    -20.0f, -20.0f,  20.0f,   0.0f, 0.0f, 1.00f,
    20.0f, -20.0f,  20.0f,   0.0f, 0.0f, 1.00f,
    20.0f,  20.0f,  20.0f,   0.0f, 0.0f, 1.00f,
    -20.0f,  20.0f,  20.0f,   0.0f, 0.0f, 1.00f,

    // Tył
    -20.0f, -20.0f, -20.0f,   0.65f, 0.68f, 0.95f,
    20.0f, -20.0f, -20.0f,   0.65f, 0.68f, 0.95f,
    20.0f,  20.0f, -20.0f,   0.65f, 0.68f, 0.95f,
    -20.0f,  20.0f, -20.0f,   0.65f, 0.68f, 0.95f,

    // Góra
    -20.0f,  20.0f,  20.0f,   0.85f, 0.87f, 1.00f,
    20.0f,  20.0f,  20.0f,   0.85f, 0.87f, 1.00f,
    20.0f,  20.0f, -20.0f,   0.85f, 0.87f, 1.00f,
    -20.0f,  20.0f, -20.0f,   0.85f, 0.87f, 1.00f,

    // Dół
    -20.0f, -20.0f,  20.0f,   0.55f, 0.58f, 0.85f,
    20.0f, -20.0f,  20.0f,   0.55f, 0.58f, 0.85f,
    20.0f, -20.0f, -20.0f,   0.55f, 0.58f, 0.85f,
    -20.0f, -20.0f, -20.0f,   0.55f, 0.58f, 0.85f,

    // Prawa
    20.0f, -20.0f,  20.0f,   0.70f, 0.72f, 0.98f,
    20.0f,  20.0f,  20.0f,   0.70f, 0.72f, 0.98f,
    20.0f,  20.0f, -20.0f,   0.70f, 0.72f, 0.98f,
    20.0f, -20.0f, -20.0f,   0.70f, 0.72f, 0.98f,

    // Lewa
    -20.0f, -20.0f,  20.0f,   0.75f, 0.70f, 0.95f,
    -20.0f,  20.0f,  20.0f,   0.75f, 0.70f, 0.95f,
    -20.0f,  20.0f, -20.0f,   0.75f, 0.70f, 0.95f,
    -20.0f, -20.0f, -20.0f,   0.75f, 0.70f, 0.95f
};

const unsigned int Cube::indices_[36] = {
    0, 1, 2,  2, 3, 0,       
    4, 5, 6,  6, 7, 4,       
    8, 9, 10, 10, 11, 8,     
    12, 13, 14, 14, 15, 12,  
    16, 17, 18, 18, 19, 16,  
    20, 21, 22, 22, 23, 20   
};

Cube::Cube(float absoluteCoordinates[3]) {
    this->absoluteCoordinates_[0] = absoluteCoordinates[0];
    this->absoluteCoordinates_[1] = absoluteCoordinates[1];
    this->absoluteCoordinates_[2] = absoluteCoordinates[2];

    std::copy(baseVertices, baseVertices + 144, this->vertices_);

    for (size_t wallColor = 0; wallColor < 6; wallColor++) {
        for (size_t vert = 0; vert < 4; vert++) {
            std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            float colorR = dist(gen);
            float colorG = dist(gen);
            float colorB = dist(gen);

            size_t index = wallColor * 24 + vert * 6 + 3;
            this->vertices_[index] = colorR;       // R
            this->vertices_[index + 1] = colorG;   // G
            this->vertices_[index + 2] = colorB;   // B

            std::cout << "RANDOM TEST: " << this->vertices_[index] << std::endl;
        }
    }
}


Cube::Cube(){
    std::copy(baseVertices, baseVertices + 144, this->vertices_);

    for (size_t wallColor = 0; wallColor < 6; wallColor++) {
        for (size_t vert = 0; vert < 4; vert++) {
            std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            float colorR = dist(gen);
            float colorG = dist(gen);
            float colorB = dist(gen);

            size_t index = wallColor * 24 + vert * 6 + 3;
            this->vertices_[index] = colorR;       // R
            this->vertices_[index + 1] = colorG;   // G
            this->vertices_[index + 2] = colorB;   // B

            std::cout << "RANDOM TEST: " << this->vertices_[index] << std::endl;
        }
    }
}