#include "Mesh.h"
#include <vector>
#include <cmath>

#define M_PI 3.1415026535

// 정점 속성 설정 헬퍼
void setMeshAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    if (useIndices) {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }
    glBindVertexArray(0);
}
// 평면 메쉬
Mesh createFloorMesh() {
    float floorVertices[] = {
        -10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  10.0f,
         10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   10.0f, 10.0f,
         10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,   10.0f, 0.0f,
        -10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  10.0f,
         10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,   10.0f, 0.0f,
        -10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f
    };
    Mesh mesh;
    mesh.count = 6;
    mesh.useIndices = false;
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
    setMeshAttributes();
    return mesh;
}
// 정육면체 메쉬
Mesh createCubeMesh() {
    float cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    Mesh mesh;
    mesh.count = 36;
    mesh.useIndices = false;
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    setMeshAttributes();
    return mesh;
}
// 구 메쉬
Mesh createSphereMesh() {
    Mesh mesh;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    const int X_SEGMENTS = 64;
    const int Y_SEGMENTS = 64;

    for (int y = 0; y <= Y_SEGMENTS; ++y) {
        for (int x = 0; x <= X_SEGMENTS; ++x) {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
            float yPos = std::cos(ySegment * M_PI);
            float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

            vertices.push_back(xPos); vertices.push_back(yPos); vertices.push_back(zPos);
            vertices.push_back(xPos); vertices.push_back(yPos); vertices.push_back(zPos);
            vertices.push_back(xSegment); vertices.push_back(ySegment);
        }
    }
    for (int y = 0; y < Y_SEGMENTS; ++y) {
        for (int x = 0; x < X_SEGMENTS; ++x) {
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            indices.push_back(y * (X_SEGMENTS + 1) + x);
            indices.push_back(y * (X_SEGMENTS + 1) + (x + 1));
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            indices.push_back(y * (X_SEGMENTS + 1) + (x + 1));
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + (x + 1));
        }
    }
    mesh.count = (GLsizei)indices.size();
    mesh.useIndices = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    setMeshAttributes();
    return mesh;
}

Mesh createStSphereMesh() {
    Mesh mesh;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    const int X_SEGMENTS = 64;
    const int Y_SEGMENTS = 64;

    for (int y = 0; y <= Y_SEGMENTS; ++y) {
        for (int x = 0; x <= X_SEGMENTS; ++x) {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
            float yPos = std::cos(ySegment * M_PI);
            float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

            vertices.push_back(xPos); vertices.push_back(yPos); vertices.push_back(zPos);
            vertices.push_back(-xPos); vertices.push_back(-yPos); vertices.push_back(-zPos);
            vertices.push_back(xSegment); vertices.push_back(ySegment);
        }
    }
    for (int y = 0; y < Y_SEGMENTS; ++y) {
        for (int x = 0; x < X_SEGMENTS; ++x) {
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            indices.push_back(y * (X_SEGMENTS + 1) + x);
            indices.push_back(y * (X_SEGMENTS + 1) + (x + 1));
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            indices.push_back(y * (X_SEGMENTS + 1) + (x + 1));
            indices.push_back((y + 1) * (X_SEGMENTS + 1) + (x + 1));
        }
    }
    mesh.count = (GLsizei)indices.size();
    mesh.useIndices = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    setMeshAttributes();
    return mesh;
}

// 원기둥 메쉬
Mesh createCylinderMesh() {
    Mesh mesh;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float radius = 0.5f;
    float height = 1.0f;
    int segments = 64;

    // 옆면 정점
    for (int i = 0; i <= segments; i++) {
        float theta = (float)i / segments * 2.0f * M_PI;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        // 아래쪽 원 둘레
        vertices.push_back(x); vertices.push_back(0.0f); vertices.push_back(z);
        vertices.push_back(x); vertices.push_back(0.0f); vertices.push_back(z);
        vertices.push_back((float)i / segments); vertices.push_back(0.0f);

        // 위쪽 원 둘레
        vertices.push_back(x); vertices.push_back(height); vertices.push_back(z);
        vertices.push_back(x); vertices.push_back(0.0f); vertices.push_back(z);
        vertices.push_back((float)i / segments); vertices.push_back(1.0f);
    }

    // 옆면 인덱스
    for (int i = 0; i < segments; i++) {
        int base = i * 2;
        indices.push_back(base);
        indices.push_back(base + 1);
        indices.push_back(base + 2);

        indices.push_back(base + 1);
        indices.push_back(base + 3);
        indices.push_back(base + 2);
    }

    // 윗면 중심점
    int topCenterIndex = vertices.size() / 8;
    vertices.push_back(0.0f); vertices.push_back(height); vertices.push_back(0.0f);
    vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
    vertices.push_back(0.5f); vertices.push_back(0.5f);

    // 아랫면 중심점
    int bottomCenterIndex = vertices.size() / 8;
    vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.0f);
    vertices.push_back(0.0f); vertices.push_back(-1.0f); vertices.push_back(0.0f);
    vertices.push_back(0.5f); vertices.push_back(0.5f);

    // 윗면 인덱스
    for (int i = 0; i < segments; i++) {
        int base = i * 2 + 1; // 위쪽 원 둘레 정점
        indices.push_back(topCenterIndex);
        indices.push_back(base);
        indices.push_back(base + 2);
    }

    // 아랫면 인덱스
    for (int i = 0; i < segments; i++) {
        int base = i * 2; // 아래쪽 원 둘레 정점
        indices.push_back(bottomCenterIndex);
        indices.push_back(base + 2);
        indices.push_back(base);
    }

    mesh.count = (GLsizei)indices.size();
    mesh.useIndices = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    setMeshAttributes();

    return mesh;
}
// 원뿔 메쉬
Mesh createConeMesh() {
    Mesh mesh;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float radius = 0.5f;
    float height = 1.0f;
    int segments = 64;

    // 꼭짓점 (tip)
    vertices.push_back(0.0f); vertices.push_back(height); vertices.push_back(0.0f);
    vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
    vertices.push_back(0.5f); vertices.push_back(1.0f);

    // 밑면 원 둘레
    for (int i = 0; i <= segments; i++) {
        float theta = (float)i / segments * 2.0f * M_PI;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        vertices.push_back(x); vertices.push_back(0.0f); vertices.push_back(z);
        vertices.push_back(0.0f); vertices.push_back(-1.0f); vertices.push_back(0.0f);
        vertices.push_back((float)i / segments); vertices.push_back(0.0f);
    }

    // 밑면 중심점
    int bottomCenterIndex = vertices.size() / 8;
    vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.0f);
    vertices.push_back(0.0f); vertices.push_back(-1.0f); vertices.push_back(0.0f);
    vertices.push_back(0.5f); vertices.push_back(0.5f);

    // 옆면 삼각형 인덱스
    for (int i = 1; i <= segments; i++) {
        indices.push_back(0);       // 꼭짓점
        indices.push_back(i);       // 현재 원 둘레 점
        indices.push_back(i + 1);   // 다음 원 둘레 점
    }

    // 밑면 삼각형 인덱스
    for (int i = 1; i <= segments; i++) {
        indices.push_back(bottomCenterIndex);
        indices.push_back(i + 1);
        indices.push_back(i);
    }

    mesh.count = (GLsizei)indices.size();
    mesh.useIndices = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    setMeshAttributes();

    return mesh;
}
// 고리 메쉬
Mesh createRingMesh() {
    Mesh mesh;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float innerRadius = 0.8f;
    float outerRadius = 1.2f;
    int segments = 128;

    for (int i = 0; i <= segments; i++) {
        float theta = (float)i / segments * 2.0f * M_PI;
        float cosT = cos(theta);
        float sinT = sin(theta);

        // 외부 원
        vertices.push_back(outerRadius * cosT);
        vertices.push_back(0.0f);
        vertices.push_back(outerRadius * sinT);
        vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
        vertices.push_back((float)i / segments); vertices.push_back(1.0f);

        // 내부 원
        vertices.push_back(innerRadius * cosT);
        vertices.push_back(0.0f);
        vertices.push_back(innerRadius * sinT);
        vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
        vertices.push_back((float)i / segments); vertices.push_back(0.0f);
    }

    for (int i = 0; i < segments; i++) {
        int base = i * 2;
        indices.push_back(base);
        indices.push_back(base + 1);
        indices.push_back(base + 2);

        indices.push_back(base + 1);
        indices.push_back(base + 3);
        indices.push_back(base + 2);
    }

    mesh.count = (GLsizei)indices.size();
    mesh.useIndices = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    setMeshAttributes();

    return mesh;
}
// 반구 메쉬
Mesh createAntennaMesh() {
    Mesh mesh;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float maxRadius = 1.0f;
    float depth = 0.3f;
    int sectors = 64;
    int rings = 32;

    for (int r = 0; r <= rings; ++r) {
        float rFactor = (float)r / rings;
        float currentRadius = rFactor * maxRadius;
        float yPos = depth * (rFactor * rFactor);

        for (int s = 0; s <= sectors; ++s) {
            float sFactor = (float)s / sectors;
            float theta = sFactor * 2.0f * M_PI;

            float xPos = currentRadius * std::cos(theta);
            float zPos = currentRadius * std::sin(theta);

            float nx = -2.0f * (depth / maxRadius) * rFactor * std::cos(theta);
            float ny = 1.0f;
            float nz = -2.0f * (depth / maxRadius) * rFactor * std::sin(theta);

            float length = std::sqrt(nx * nx + ny * ny + nz * nz);
            nx /= length; ny /= length; nz /= length;

            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);

            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);

            float u = 0.5f + 0.5f * rFactor * std::cos(theta);
            float v = 0.5f + 0.5f * rFactor * std::sin(theta);
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    for (int r = 0; r < rings; ++r) {
        for (int s = 0; s < sectors; ++s) {
            unsigned int first = r * (sectors + 1) + s;
            unsigned int second = first + sectors + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    mesh.count = (GLsizei)indices.size();
    mesh.useIndices = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    setMeshAttributes();

    return mesh;
}




