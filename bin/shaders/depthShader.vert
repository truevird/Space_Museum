#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main() {
    // 조명 공간 행렬을 기준으로 위치 계산
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}