#ifndef CUBEGEN_H
#define CUBEGEN_H

#include <vector>
#include <iostream>
#include "cube.h"
#include <algorithm>

class CubeGenerator {
private:
    std::vector<Cube> cubeVector_;
    std::vector<float> vertecies_;
    float lastCoordX_;


public:
    CubeGenerator(){}
    CubeGenerator(const std::vector<Cube>& cubeVector);

    void SetLastCoordX(float coordX);
    float GetLastCoordX(void) const;

    size_t getCubeNum(void);

    void AddCube(void);
    Cube& GetCube(size_t cubeIdx);

    unsigned int* GenerateIndices(void);
    float* GenerateVertexes(void);

};

#endif