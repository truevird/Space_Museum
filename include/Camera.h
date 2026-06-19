#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) : Front(glm::vec3(-0.5f, -0.3f, -1.0f)), MovementSpeed(8.0f), MouseSensitivity(0.08f), Zoom(45.0f) {
        Position = position;
        Up = glm::vec3(0.0f, 1.0f, 0.0f);
        Yaw = -120.0f;
        Pitch = -15.0f;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }
    
    // 강제 이동 함수
    void ProcessKeyboard(int direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == 0) Position += Front * velocity; // W
        if (direction == 1) Position -= Front * velocity; // S
        if (direction == 2) Position -= glm::normalize(glm::cross(Front, Up)) * velocity; // A
        if (direction == 3) Position += glm::normalize(glm::cross(Front, Up)) * velocity; // D
        if (direction == 4) Position += Up * velocity; // SPACE
        if (direction == 5) Position -= Up * velocity; // LCTRL
    }

    // 이동할 위치를 미리 계산만 해서 반환하는 함수
    glm::vec3 GetNextPosition(int direction, float deltaTime) const {
        float velocity = MovementSpeed * deltaTime;
        glm::vec3 nextPos = Position;
        
        if (direction == 0) nextPos += Front * velocity; // W
        if (direction == 1) nextPos -= Front * velocity; // S
        if (direction == 2) nextPos -= glm::normalize(glm::cross(Front, Up)) * velocity; // A
        if (direction == 3) nextPos += glm::normalize(glm::cross(Front, Up)) * velocity; // D
        if (direction == 4) nextPos += Up * velocity; // SPACE
        if (direction == 5) nextPos -= Up * velocity; // LCTRL
        
        return nextPos;
    }

    // 시점 전환
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch) {
            if (Pitch > 89.0f) Pitch = 89.0f;
            if (Pitch < -89.0f) Pitch = -89.0f;
        }
        updateCameraVectors();
    }
    
    // 확대 축소
    void ProcessMouseScroll(float yoffset) {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f) Zoom = 1.0f;
        if (Zoom > 45.0f) Zoom = 45.0f;
    }

private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
    }
};
#endif