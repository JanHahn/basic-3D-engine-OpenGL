#include "CubeGenerator.h"

CubeGenerator::CubeGenerator(const std::vector<Cube>& cubeVector): cubeVector_(cubeVector) {
    this->lastCoordX_ = 0.0f;
    this->vertecies_ = {};
}

void CubeGenerator::SetLastCoordX(float coordX) {
    this->lastCoordX_ = coordX;
}

float CubeGenerator::GetLastCoordX(void) const {
    return this->lastCoordX_;
} 

size_t CubeGenerator::getCubeNum(void){
    return this->cubeVector_.size();
}

void CubeGenerator::AddCube(void){
        float nextAbsolutCoordinateX = this->GetLastCoordX() + 40;
        float absCoords[3] = {0, 0, 80 + nextAbsolutCoordinateX};
        Cube nextCube(absCoords);
        this->cubeVector_.push_back(nextCube);
        this->SetLastCoordX(this->GetLastCoordX() + 40);
}

Cube& CubeGenerator::GetCube(size_t cubeIdx){
        return cubeVector_[cubeIdx];
}

unsigned int* CubeGenerator::GenerateIndices(void){
    size_t numCubes = this->cubeVector_.size();
    unsigned int* indices = new unsigned int[numCubes * 36];
    for (size_t cubeIdx = 0; cubeIdx < numCubes; cubeIdx++){
        unsigned int* destination = &indices[cubeIdx * 36];

        std::copy(Cube::getIndices(), Cube::getIndices() + 36, destination);

        unsigned int offset = cubeIdx * 24;
        for(int i = 0; i < 36; i++){
            destination[i] += offset;
        }
    }
    return indices;
}


float* CubeGenerator::GenerateVertexes(void){
    size_t numCubes = this->cubeVector_.size();
    float* vertexes = new float[numCubes * 144];
    for (size_t cubeIdx = 0; cubeIdx < numCubes; cubeIdx++){
        float* cubeVertexes = this->GetCube(cubeIdx).getVertices();
        std::copy(cubeVertexes, cubeVertexes + 144, vertexes + cubeIdx * 144);
    }
    return vertexes;
}

