#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

struct Mesh {
    unsigned int VAO, VBO, EBO;
    GLsizei count;
    bool useIndices;

    void draw() const;
};

// 메쉬 생성 함수 선언
Mesh createFloorMesh();
Mesh createCubeMesh();
Mesh createSphereMesh();
Mesh createStSphereMesh();
Mesh createCylinderMesh();
Mesh createConeMesh();
Mesh createRingMesh();
Mesh createAntennaMesh();
#endif