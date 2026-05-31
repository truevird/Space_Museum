#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Object.h"
#include <iostream>

// 설정
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 전역 변수 (콜백용)
Camera camera(glm::vec3(5.0f, 4.0f, 8.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

// 콜백 함수
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
        firstMouse = true;
        return;
    }
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(0, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(1, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(2, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(3, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.ProcessKeyboard(4, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera.ProcessKeyboard(5, deltaTime);
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Jupiter 3D Showcase", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // 셰이더 빌드 
    Shader shaderProgram("shaders/shader.vert", "shaders/shader.frag");

    // 메쉬 로드
    Mesh floorMesh = createFloorMesh();
    Mesh cubeMesh = createCubeMesh();
    Mesh sphereMesh = createSphereMesh();
    Mesh cylinderMesh = createCylinderMesh();
    Mesh coneMesh = createConeMesh();
    Mesh ringMesh = createRingMesh();
    Mesh antennaMesh = createAntennaMesh();

    // 텍스처 로드 
    unsigned int floorTex = loadTexture("textures/floor.jpg");
    unsigned int sunTex = loadTexture("textures/sun.jpg", true);
    unsigned int mercuryTex = loadTexture("textures/mercury.jpg", true);
    unsigned int venusTex = loadTexture("textures/venus.jpg", true);
    unsigned int marsTex = loadTexture("textures/mars.jpg", true);
    unsigned int jupiterTex = loadTexture("textures/jupiter.jpg", true);
    unsigned int saturnTex = loadTexture("textures/saturn.jpg", true);
    unsigned int uranusTex = loadTexture("textures/uranus.jpg", true);
    unsigned int neptuneTex = loadTexture("textures/neptune.jpg", true);
    unsigned int earthTex = loadTexture("textures/earth.jpg", false,true);
    unsigned int moonTex = loadTexture("textures/moon.jpg");
    unsigned int wallTex = loadTexture("textures/wall.jpg");
    unsigned int spaceTex = loadTexture("textures/space.jpg");
    unsigned int sattTex = loadTexture("textures/satellitebody.jpg");
    unsigned int solarTex = loadTexture("textures/solarpanel.jpg");

    //구조체 생성
    EarthMoonSystem earthSystem(sphereMesh, earthTex, moonTex);
    SolarSystem solarSystem(sphereMesh, earthSystem, sunTex, mercuryTex, venusTex, marsTex, jupiterTex, saturnTex, uranusTex, neptuneTex);
    Stage myStage(floorMesh, cubeMesh, floorTex, wallTex);
    SmallExhibit smStage(cubeMesh, spaceTex, wallTex);
    EarthExhibit earthStage(cubeMesh, spaceTex, earthTex,  wallTex);
    MarsExhibit marsStage(cubeMesh, spaceTex, marsTex, wallTex);
    satellite satelliteMesh(sphereMesh, antennaMesh, cubeMesh, coneMesh, sattTex, solarTex, wallTex);//안테나 텍스쳐 추가 필요
    MarsRover rover(cubeMesh, cylinderMesh, sphereMesh, sattTex, wallTex, spaceTex);
<<<<<<< HEAD
    SpaceShuttle shuttle(cubeMesh,cylinderMesh,coneMesh,sphereMesh,wallTex,wallTex,spaceTex,sunTex); //우주왕복선
=======
>>>>>>> 9e60268eab5e6d0f639e5bacc77a8efac23852ed
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
        shaderProgram.setVec3("lightPos", 2.0f, 1.0f, 3.0f);
        shaderProgram.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shaderProgram.setMat4("projection", projection);
        shaderProgram.setMat4("view", view);

        glm::mat4 model;
        //전시장
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(3.0f, 1.8f, 3.0f));
        myStage.draw(shaderProgram, model);

        //작은 전시장
        //태양 전시관
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(15.0f, 1.8f, -15.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        smStage.draw(shaderProgram, model);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(15.0f, 1.8f, 15.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        smStage.draw(shaderProgram, model);

        //인공위성 전시관
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-15.0f, 1.8f, -15.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        earthStage.draw(shaderProgram, model);
        //화성 바닥
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-15.0f, 1.8f, 15.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        marsStage.draw(shaderProgram, model);


       //태양계
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(15.0f, 1.0f, -15.0f));
        model = glm::rotate(model, (float)glfwGetTime() * 0.2f, glm::vec3(0.0f, 1.0f, 0.0f)); // 공전도 메인에서 제어 가능
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        solarSystem.draw(shaderProgram, (float)glfwGetTime(), model);

<<<<<<< HEAD
		//우주왕복선
        glm::mat4 shuttleModel(1.0f);

        shuttleModel =
            glm::translate(
                shuttleModel,
                glm::vec3(14.0f, 1.0f, 14.0f));

        shuttleModel =
            glm::scale(
                shuttleModel,
                glm::vec3(0.8f));

        shuttle.draw(shaderProgram, shuttleModel);

=======
>>>>>>> 9e60268eab5e6d0f639e5bacc77a8efac23852ed
       /*
       // 목성
       glBindTexture(GL_TEXTURE_2D, jupiterTex);
       model = glm::mat4(1.0f);
       model = glm::rotate(model, (float)glfwGetTime() * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
       shaderProgram.setMat4("model", model);
       sphereMesh.draw();
       */

        /*glBindTexture(GL_TEXTURE_2D, wallTex);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 10.0f, 0.0f));
        shaderProgram.setMat4("model", model);
        cylinderMesh.draw();

        glBindTexture(GL_TEXTURE_2D, wallTex);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
        shaderProgram.setMat4("model", model);
        coneMesh.draw();

        glBindTexture(GL_TEXTURE_2D, wallTex);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, 5.0f));
        shaderProgram.setMat4("model", model);
        ringMesh.draw();
        */
        //인공위성
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-15.0f, 0.5f, -15.0f));
        satelliteMesh.draw(shaderProgram, model);

        // 화성 탐사 로봇
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-15.0f, -1.7f, 15.0f));
        model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(0, 1, 0));
        model = glm::scale(model, glm::vec3(0.95f));
        rover.draw(shaderProgram, (float)glfwGetTime(), model);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}