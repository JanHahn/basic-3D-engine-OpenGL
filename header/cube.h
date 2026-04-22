#ifndef CUBE_H
#define CUBE_H

class Cube {
private:
    float vertices_[144];
    static const unsigned int indices_[36];

    float absoluteCoordinates_[3];

public:
    Cube(float absoluteCoordinates[3]);
    Cube();

    const float* getAbsoluteCoordinates() const { return absoluteCoordinates_; }
    
    float* getVertices() { return vertices_; }
    static const unsigned int* getIndices() { return indices_; }

     

};

#endif