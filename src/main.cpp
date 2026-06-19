#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Object.h"
#include <iostream>
#include <vector>
// 설정
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;

//충돌 판정 구조체
struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

// 모든 충돌 박스를 담을 리스트
std::vector<AABB> colliders;

bool checkCollision(glm::vec3 pos, const AABB& box) {
    float margin = 1.0f; // 카메라의 몸체 두께(반경) 여백
    return (pos.x >= box.min.x - margin && pos.x <= box.max.x + margin) &&
           (pos.y >= box.min.y - margin && pos.y <= box.max.y + margin) &&
           (pos.z >= box.min.z - margin && pos.z <= box.max.z + margin);
}

// 전역 변수(콜백)
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        firstMouse = true;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// 개별 키에 대한 이동 시도 함수
void tryMoveCamera(GLFWwindow* window, int key, int direction) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
        // 1. 가고자 하는 완전한 다음 예상 위치 계산
        glm::vec3 nextPos = camera.GetNextPosition(direction, deltaTime);
        
        // 2. 전체 3축 이동에 대해 충돌 검사
        bool isCollidingFull = false;
        for (const auto& box : colliders) {
            if (checkCollision(nextPos, box)) {
                isCollidingFull = true;
                break;
            }
        }
        
        // 3. 충돌이 전혀 없다면 한 번에 깔끔하게 이동 후 종료
        if (!isCollidingFull) {
            camera.Position = nextPos;
            return;
        }

        // 4. [모든 경우의 수 대응 완전 슬라이딩]
        // 부딪혔다면 X, Y, Z축 이동 성분을 각각 쪼개서 독립적으로 갈 수 있는지 검사합니다.
        
        // 현재 위치와 다음 위치 사이의 축별 순수 이동량 계산
        float moveX = nextPos.x - camera.Position.x;
        float moveY = nextPos.y - camera.Position.y;
        float moveZ = nextPos.z - camera.Position.z;

        // 4-1. X축 단독 이동 검사 (현재 위치에서 X만 이동해봄)
        if (moveX != 0.0f) {
            glm::vec3 testX = glm::vec3(camera.Position.x + moveX, camera.Position.y, camera.Position.z);
            bool collideX = false;
            for (const auto& box : colliders) {
                if (checkCollision(testX, box)) {
                    collideX = true;
                    break;
                }
            }
            // X축 방향으로 벽이 없다면 X축 이동 승인!
            if (!collideX) {
                camera.Position.x = testX.x;
            }
        }

        // 4-2. Y축 단독 이동 검사 (현재 위치에서 Y만 이동해봄)
        if (moveY != 0.0f) {
            glm::vec3 testY = glm::vec3(camera.Position.x, camera.Position.y + moveY, camera.Position.z);
            bool collideY = false;
            for (const auto& box : colliders) {
                if (checkCollision(testY, box)) {
                    collideY = true;
                    break;
                }
            }
            // Y축 방향(바닥/천장)으로 벽이 없다면 Y축 이동 승인!
            if (!collideY) {
                camera.Position.y = testY.y;
            }
        }

        // 4-3. Z축 단독 이동 검사 (현재 위치에서 Z만 이동해봄)
        if (moveZ != 0.0f) {
            glm::vec3 testZ = glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z + moveZ);
            bool collideZ = false;
            for (const auto& box : colliders) {
                if (checkCollision(testZ, box)) {
                    collideZ = true;
                    break;
                }
            }
            // Z축 방향으로 벽이 없다면 Z축 이동 승인!
            if (!collideZ) {
                camera.Position.z = testZ.z;
            }
        }
    }
}

// 이동
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        
    tryMoveCamera(window, GLFW_KEY_W, 0);
    tryMoveCamera(window, GLFW_KEY_S, 1);
    tryMoveCamera(window, GLFW_KEY_A, 2);
    tryMoveCamera(window, GLFW_KEY_D, 3);
    tryMoveCamera(window, GLFW_KEY_SPACE, 4);
    tryMoveCamera(window, GLFW_KEY_LEFT_CONTROL, 5);
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SpaceMuseum", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 셰이더 빌드 
    Shader shaderProgram("shaders/shader.vert", "shaders/shader.frag");
    Shader depthShader("shaders/depthShader.vert", "shaders/depthShader.frag"); //깊이 셰이더

    // 메쉬 로드
    Mesh floorMesh = createFloorMesh();
    Mesh cubeMesh = createCubeMesh();
    Mesh sphereMesh = createSphereMesh();
    Mesh stsphereMesh = createStSphereMesh();
    Mesh cylinderMesh = createCylinderMesh();
    Mesh coneMesh = createConeMesh();
    Mesh ringMesh = createRingMesh();
    Mesh antennaMesh = createAntennaMesh();
    Mesh springMesh = createSpRingMesh();

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
    unsigned int spaceTex = loadTexture("textures/space3.jpg");
    unsigned int sattTex = loadTexture("textures/satellitebody.jpg");
    unsigned int solarTex = loadTexture("textures/solarpanel.jpg");
    unsigned int earthfloorTex = loadTexture("textures/earthfloor.jpg");
    unsigned int solarsystempicTex = loadTexture("textures/SolarSystemPicture.jpg",true,true);
    unsigned int solarsysteminfoTex = loadTexture("textures/SolarSystemInfo.jpg",true,false);
    unsigned int satellitepicTex = loadTexture("textures/SatellitePicture.jpg",true,true);
    unsigned int satelliteinfoTex = loadTexture("textures/SatelliteInfo.jpg",true,false);
    unsigned int marsroverpicTex = loadTexture("textures/MarsRoverPicture.jpg",true,true);
    unsigned int marsroverinfoTex = loadTexture("textures/MarsRoverInfo.jpg",true,false);
    unsigned int spaceshuttlepicTex = loadTexture("textures/SpaceShuttlePicture.jpg",true,true);
    unsigned int spaceshuttleinfoTex = loadTexture("textures/SpaceShuttleInfo.jpg",true,false);

    // 구조체 생성
    EarthMoonSystem earthSystem(sphereMesh, earthTex, moonTex);
    SolarSystem solarSystem(sphereMesh, ringMesh, springMesh, earthSystem, sunTex, mercuryTex, venusTex, marsTex, jupiterTex, saturnTex, uranusTex, neptuneTex, wallTex);
    Stage myStage(stsphereMesh, spaceTex);
    Planet earth(sphereMesh, earthTex);
    Planet solar(sphereMesh, sunTex);
    Planet mars(sphereMesh, marsTex);
    SmallExhibit smStage(cubeMesh, spaceTex, wallTex);
    satellite satelliteMesh(sphereMesh, antennaMesh, cubeMesh, coneMesh, sattTex, solarTex, wallTex);
    CylinderSatellite cylSatellite(cylinderMesh, cubeMesh, antennaMesh, coneMesh, sphereMesh, springMesh, spaceTex, solarTex, wallTex);
    MarsRover rover(cubeMesh, cylinderMesh, sphereMesh, coneMesh, sattTex, wallTex, spaceTex);
    SpaceShuttle shuttle(cubeMesh,cylinderMesh,coneMesh,sphereMesh,wallTex,wallTex,spaceTex,sunTex); 
    GlassWall glassWall(cubeMesh, glm::vec3(1.0f, 1.0f, 1.0f), 0.15f);
    Info solarpic(floorMesh,solarsystempicTex);
    Info solarinfo(floorMesh,solarsysteminfoTex);
    Info satellitepic(floorMesh,satellitepicTex);
    Info satelliteinfo(floorMesh,satelliteinfoTex);
    Info marsroverpic(floorMesh,marsroverpicTex);
    Info marsroverinfo(floorMesh,marsroverinfoTex);
    Info spaceshuttlepic(floorMesh,spaceshuttlepicTex);
    Info spaceshuttleinfo(floorMesh,spaceshuttleinfoTex);
    Barrier museumBarrier(cylinderMesh, sphereMesh, wallTex);
    Stand solarStand(cubeMesh, solarinfo, wallTex);
    Stand satelliteStand(cubeMesh, satelliteinfo, wallTex);
    Stand marsroverStand(cubeMesh, marsroverinfo, wallTex);
    Stand spaceshuttleStand(cubeMesh, spaceshuttleinfo, wallTex);

    // 전시장 벽면 충돌설정
    colliders.push_back({ glm::vec3(-9.5f, -5.0f, -9.5f), glm::vec3(9.5f, 5.0f, -8.5f) });
    colliders.push_back({ glm::vec3(-10.5f, -5.0f, -10.0f), glm::vec3(-9.5f, 5.0f, 10.0f) });
    colliders.push_back({ glm::vec3(-10.0f, -5.0f, 8.5f), glm::vec3(10.0f, 5.0f, 9.5f) });
    colliders.push_back({ glm::vec3(9.0f, -5.0f, -10.0f), glm::vec3(10.5f, 5.0f, 9.5f) });
    colliders.push_back({ glm::vec3(-10.0f, 5.0f, -10.0f), glm::vec3(10.0f, 6.0f, 10.0f) });
    colliders.push_back({ glm::vec3(-10.0f, -5.0f, -10.0f), glm::vec3(10.0f, -4.0f, 10.0f) });
    
    // -------------------------------------------------------------
    // 그림자 맵 FBO (프레임버퍼 오브젝트) 및 텍스처 설정
    // -------------------------------------------------------------
    const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048; // 해상도가 높을수록 그림자가 선명해집니다.
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE); // 색상 버퍼는 사용하지 않음
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    shaderProgram.use();
    shaderProgram.setBool("ourTexture", 0); // 일반 오브젝트용 텍스처 샘플러는 0번 슬롯
    shaderProgram.setBool("shadowMap", 1);  // 그림자용 텍스처 샘플러는 1번 슬롯 

    // -------------------------------------------------------------
    // 중복 코드를 방지하기 위한 씬 렌더링 람다 함수 정의
    // -------------------------------------------------------------
    auto renderScene = [&](Shader& currentShader) {
        glm::mat4 model;
        // 전시장
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(3.0f, 1.8f, 3.0f));
        myStage.draw(currentShader, (float)glfwGetTime(), model);
        
        // 작은 전시장 / 태양 전시관
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
        smStage.draw(currentShader, model);

        //태양계
        glm::vec3 sunPos = glm::vec3(40.0f, -8.0f, 0.0f); // 태양계 중심 (태양 위치)
        currentShader.setVec3("lightPos[4]", 40.0f, -8.0f, 0.0f); 
        currentShader.setVec3("lightColor[4]", 1.5f, 1.5f, 1.5f); // 태양빛 세기
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(40.0f, -8.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
        model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        solarSystem.draw(currentShader, (float)glfwGetTime(), model);

        // 우주왕복선
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-25.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f));
        model = glm::rotate(model, glm::radians(50.0f), glm::vec3(-0.75f, 0.75f, -1.0f));
        shuttle.draw(currentShader, (float)glfwGetTime(), model);

        //지구
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -35.0f, -30.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        earth.draw(currentShader, (float)glfwGetTime(), model); 
        
        //태양
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(15.0f, 10.0f, -50.0f)); 
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        solar.draw(currentShader, (float)glfwGetTime(), model);

        // 인공위성
        glm::mat4 satModel = glm::mat4(1.0f);
        satModel = glm::translate(satModel, glm::vec3(5.0f, 0.0f, -30.0f));
        satModel = glm::rotate(satModel, glm::radians(50.0f), glm::vec3(0.75f, -0.75f, 1.0f));
        satModel = glm::scale(satModel, glm::vec3(1.0f, 1.0f, 1.0f));
        satelliteMesh.draw(currentShader, 0, satModel);

        for (int i = 0; i < 20; i++) {
            glm::mat4 satModel2 = glm::mat4(1.0f);
            float randFactor = sin(i * 45.123f); 
            float randFactor2 = cos(i * 78.456f);
            glm::vec3 earthCenter = glm::vec3(0.0f, -35.0f, -30.0f);
            satModel2 = glm::translate(satModel2, earthCenter);
            float speed = (float)glfwGetTime() * (0.2f + randFactor * 0.1f); 
            glm::vec3 rotAxis = glm::normalize(glm::vec3(randFactor, 1.0f - abs(randFactor), randFactor2));
            satModel2 = glm::rotate(satModel2, speed, rotAxis);
            float radius = 30.0f + randFactor * 1.5f; 
            satModel2 = glm::translate(satModel2, glm::vec3(radius, 0.0f, 0.0f)); 
            satModel2 = glm::rotate(satModel2, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            satModel2 = glm::scale(satModel2, glm::vec3(0.2f, 0.2f, 0.2f));
            satelliteMesh.draw(currentShader, (float)glfwGetTime(), satModel2);
        }

        // 옆에 추가한 원기둥 위성
        glm::mat4 cylModel = glm::mat4(1.0f);
        cylModel = glm::translate(cylModel, glm::vec3(9.0f, 0.0f, -25.0f));
        cylModel = glm::rotate(cylModel, glm::radians(50.0f), glm::vec3(0.75f, -0.75f, 1.0f));
        cylModel = glm::scale(cylModel, glm::vec3(1.5f, 1.5f, 1.5f));
        cylSatellite.draw(currentShader, 0, cylModel);

        for (int i = 0; i < 20; i++) {
            glm::mat4 satModel3 = glm::mat4(1.0f);
            float randFactor = sin(i * 33.123f); 
            float randFactor2 = cos(i * 58.456f);
            glm::vec3 earthCenter = glm::vec3(0.0f, -35.0f, -30.0f);
            satModel3 = glm::translate(satModel3, earthCenter);
            float speed = (float)glfwGetTime() * (0.2f + randFactor * 0.1f); 
            glm::vec3 rotAxis = glm::normalize(glm::vec3(randFactor, 1.0f - abs(randFactor), randFactor2));
            satModel3 = glm::rotate(satModel3, speed, rotAxis);
            float radius = 30.0f + randFactor * 1.5f; 
            satModel3 = glm::translate(satModel3, glm::vec3(radius, 0.0f, 0.0f)); 
            satModel3 = glm::rotate(satModel3, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            satModel3 = glm::scale(satModel3, glm::vec3(0.2f, 0.2f, 0.2f));
            cylSatellite.draw(currentShader, (float)glfwGetTime(), satModel3);
        }

        //화성
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -35.0f, 30.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        mars.draw(currentShader, 0, model);

        // 화성 탐사 로봇
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -8.0f, 23.0f));
        model = glm::rotate(model, glm::radians(35.0f), glm::vec3(-0.2, 1, -0.1));
        model = glm::scale(model, glm::vec3(2.0f));
        rover.draw(currentShader, (float)glfwGetTime(), model);

        currentShader.setBool("useLighting", false);

        //태양계전시 사진
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(11.49f, 4.5f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        solarpic.draw(currentShader, model);

        //인공위성전시 사진
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 4.5f, -10.2f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        satellitepic.draw(currentShader, model);

        //화성탐사로봇전시 사진
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 4.5f, 10.2f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        marsroverpic.draw(currentShader, model);

        //우주왕복선전시 사진
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-11.49f, 4.5f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        spaceshuttlepic.draw(currentShader, model);


        // 유리벽 (투명)
        currentShader.setBool("useLighting", false);
        glm::mat4 glassModel = glm::mat4(1.0f);
        glassModel = glm::translate(glassModel, glm::vec3(0.0f, 0.0f, -10.8f));
        glassModel = glm::scale(glassModel, glm::vec3(20.0f, 15.0f, 0.15f));
        glassWall.draw(currentShader, glassModel);

        glassModel = glm::mat4(1.0f);
        glassModel = glm::translate(glassModel, glm::vec3(0.0f, 0.0f, 10.8f));
        glassModel = glm::scale(glassModel, glm::vec3(20.0f, 15.0f, 0.15f));
        glassWall.draw(currentShader, glassModel);

        glassModel = glm::mat4(1.0f);
        glassModel = glm::translate(glassModel, glm::vec3(-12.0f, 0.0f, 0.0f));
        glassModel = glm::scale(glassModel, glm::vec3(0.15f, 15.0f, 20.0f));
        glassWall.draw(currentShader, glassModel);

        glassModel = glm::mat4(1.0f);
        glassModel = glm::translate(glassModel, glm::vec3(12.0f, 0.0f, 0.0f));
        glassModel = glm::scale(glassModel, glm::vec3(0.15f, 15.0f, 20.0f));
        glassWall.draw(currentShader, glassModel);

        // //차단봉
        // model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        // museumBarrier.draw(currentShader, model);

        // 전시대
        model = glm::mat4(1.0f);
        
        model = glm::translate(model, glm::vec3(8.0f, -0.8f, 5.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        solarStand.draw(currentShader, model);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(6.0f, -0.8f, -7.0f));
        satelliteStand.draw(currentShader, model);

        model = glm::mat4(1.0f);
        
        model = glm::translate(model, glm::vec3(-6.0f, -0.8f, 7.0f));
        model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        marsroverStand.draw(currentShader, model);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-8.0f, -0.8f, -5.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        spaceshuttleStand.draw(currentShader, model);
        

        
    };

    // -------------------------------------------------------------
    // 메인 루프 시작
    // -------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        // -----------------------------------------------------------------
        // PASS 1: 조명 시점에서의 깊이 정보(Depth Map) 생성
        // -----------------------------------------------------------------
        // lightPos[0] (0.0f, 6.0f, 0.0f)을 기준으로 박물관 내부를 위에서 내려다보는 직교 변환 설정
        glm::mat4 lightProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 1.0f, 50.0f);
        glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 25.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        depthShader.use();
        depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        
        // 씬 오브젝트들을 depthShader를 사용하여 그리기
        renderScene(depthShader);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // -----------------------------------------------------------------
        // PASS 2: 원래 카메라 시점에서의 최종 화면 렌더링 (그림자 반영)
        // -----------------------------------------------------------------
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
        shaderProgram.setVec3("lightPos[0]", 0.0f, 6.0f, 0.0f); // 전시장
        shaderProgram.setVec3("lightColor[0]", 1.0f, 1.0f, 1.0f);

        shaderProgram.setVec3("lightPos[1]", 15.0f, 10.0f, -50.0f); // 태양
        shaderProgram.setVec3("lightColor[1]", 1.0f, 1.0f, 1.0f);

        shaderProgram.setVec3("lightPos[2]", 0.0f, -8.0f, 23.0f); // 화성탐사선
        shaderProgram.setVec3("lightColor[2]", 1.0f, 1.0f, 1.0f);

        shaderProgram.setVec3("lightPos[3]", -15.0f, -3.0f, 0.0f); // 우주왕복선
        shaderProgram.setVec3("lightColor[3]", 1.0f, 1.0f, 1.0f);

        shaderProgram.setVec3("lightPos[4]", 40.0f, -8.0f, 0.0f); // 태양계
        shaderProgram.setVec3("lightColor[4]", 1.0f, 1.0f, 1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shaderProgram.setMat4("projection", projection);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("lightSpaceMatrix", lightSpaceMatrix); // 행렬 정보 전송
        shaderProgram.setBool("useLighting", true);

        // 그림자 깊이 맵 텍스처를 1번 유닛(GL_TEXTURE1)에 바인딩
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glActiveTexture(GL_TEXTURE0);
        // 메인 셰이더를 사용하여 전체 씬 그리기
        renderScene(shaderProgram);

        glBindTexture(GL_TEXTURE_2D, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}