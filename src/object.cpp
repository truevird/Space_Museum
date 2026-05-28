#include "Object.h"

// ==========================================
// Stage 구현
// ==========================================
Stage::Stage(Mesh& fMesh, Mesh& cMesh, unsigned int fTex, unsigned int wTex)
    : floorMesh(&fMesh), cubeMesh(&cMesh), floorTex(fTex), wallTex(wTex) {
}

void Stage::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;

    // 1. 바닥 (Floor)
    glBindTexture(GL_TEXTURE_2D, floorTex);
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    shader.setMat4("model", model);
    floorMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
    shader.setMat4("model", model);
    floorMesh->draw();

    // 2. 사방의 벽 (Walls)
    glBindTexture(GL_TEXTURE_2D, wallTex);

    // 왼쪽 벽
    model = parentModel;
    model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 20.0f, 20.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽
    model = parentModel;
    model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 20.0f, 20.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();
}

// ==========================================
// EarthMoonSystem 구현
// ==========================================
EarthMoonSystem::EarthMoonSystem(Mesh& mesh, unsigned int eTex, unsigned int mTex)
    : sphereMesh(&mesh), earthTex(eTex), moonTex(mTex) {
}

void EarthMoonSystem::draw(Shader& shader, float time, glm::mat4 parentModel) {
    // 1. 지구
    glBindTexture(GL_TEXTURE_2D, earthTex);
    glm::mat4 earthModel = parentModel;
    earthModel = glm::rotate(earthModel, time * 3.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // 공전 후 자전이 분리되지 않은 경우 순서 주의
    earthModel = glm::scale(earthModel, glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setMat4("model", earthModel);
    sphereMesh->draw();

    // 2. 달
    glBindTexture(GL_TEXTURE_2D, moonTex);
    glm::mat4 moonModel = parentModel;
    moonModel = glm::rotate(moonModel, time * 12.0f, glm::vec3(0.0f, 1.0f, 0.0f));  // 1. 지구 중심 공전
    moonModel = glm::translate(moonModel, glm::vec3(1.2f, 0.0f, 0.0f));           // 2. 궤도 반지름 거리
    moonModel = glm::rotate(moonModel, time * 12.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    moonModel = glm::scale(moonModel, glm::vec3(0.12f, 0.12f, 0.12f));               // 3. 크기
    shader.setMat4("model", moonModel);
    sphereMesh->draw();
}

// ==========================================
// SolarSystem 구현
// ==========================================
SolarSystem::SolarSystem(Mesh& mesh, EarthMoonSystem& emSystem, unsigned int sTex, unsigned int meTex, unsigned int vTex, unsigned int maTex, unsigned int jTex, unsigned int saTex, unsigned int uTex, unsigned int nTex)
    : sphereMesh(&mesh), earthMoon(&emSystem), solarTex(sTex), mercuryTex(meTex), venusTex(vTex), marsTex(maTex), jupiterTex(jTex), saturnTex(saTex), uranusTex(uTex), neptuneTex(nTex) {
}

void SolarSystem::draw(Shader& shader, float time, glm::mat4 parentModel) {
    // 1. 태양
    glBindTexture(GL_TEXTURE_2D, solarTex);
    glm::mat4 solarModel = parentModel;
    solarModel = glm::scale(solarModel, glm::vec3(2.5f, 2.5f, 2.5f));
    solarModel = glm::rotate(solarModel, time * 0.04f, glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("model", solarModel);
    sphereMesh->draw();

    // 2. 수성
    glBindTexture(GL_TEXTURE_2D, mercuryTex);
    glm::mat4 mercuryModel = parentModel;
    mercuryModel = glm::rotate(mercuryModel, time * 4.15f, glm::vec3(0.0f, 1.0f, 0.0f));  // 1. 공전
    mercuryModel = glm::translate(mercuryModel, glm::vec3(3.5f, 0.0f, 0.0f));             // 2. 거리
    mercuryModel = glm::rotate(mercuryModel, time * 0.017f, glm::vec3(0.0f, 1.0f, 0.0f)); // 3. 자전
    mercuryModel = glm::scale(mercuryModel, glm::vec3(0.25f, 0.25f, 0.25f));              // 4. 크기
    shader.setMat4("model", mercuryModel);
    sphereMesh->draw();

    // 3. 금성
    glBindTexture(GL_TEXTURE_2D, venusTex);
    glm::mat4 venusModel = parentModel;
    venusModel = glm::rotate(venusModel, time * 1.62f, glm::vec3(0.0f, 1.0f, 0.0f));
    venusModel = glm::translate(venusModel, glm::vec3(5.0f, 0.0f, 0.0f));
    venusModel = glm::rotate(venusModel, time * -0.004f, glm::vec3(0.0f, 1.0f, 0.0f)); // 역행 자전
    venusModel = glm::scale(venusModel, glm::vec3(0.45f, 0.45f, 0.45f));
    shader.setMat4("model", venusModel);
    sphereMesh->draw();

    // 4. 지구 달
    glm::mat4 earthModel = parentModel;
    earthModel = glm::rotate(earthModel, time * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // 태양 기준 공전
    earthModel = glm::translate(earthModel, glm::vec3(7.0f, 0.0f, 0.0f));           // 태양과의 거리
    earthMoon->draw(shader, time, earthModel);

    // 5. 화성
    glBindTexture(GL_TEXTURE_2D, marsTex);
    glm::mat4 marsModel = parentModel;
    marsModel = glm::rotate(marsModel, time * 0.53f, glm::vec3(0.0f, 1.0f, 0.0f));
    marsModel = glm::translate(marsModel, glm::vec3(9.0f, 0.0f, 0.0f));
    marsModel = glm::rotate(marsModel, time * 0.97f, glm::vec3(0.0f, 1.0f, 0.0f));
    marsModel = glm::scale(marsModel, glm::vec3(0.35f, 0.35f, 0.35f));
    shader.setMat4("model", marsModel);
    sphereMesh->draw();

    // 6. 목성
    glBindTexture(GL_TEXTURE_2D, jupiterTex);
    glm::mat4 jupiterModel = parentModel;
    jupiterModel = glm::rotate(jupiterModel, time * 0.084f + glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    jupiterModel = glm::translate(jupiterModel, glm::vec3(12.5f, 0.0f, 0.0f));
    jupiterModel = glm::rotate(jupiterModel, time * 2.4f, glm::vec3(0.0f, 1.0f, 0.0f));
    jupiterModel = glm::scale(jupiterModel, glm::vec3(1.2f, 1.2f, 1.2f));
    shader.setMat4("model", jupiterModel);
    sphereMesh->draw();

    // 7. 토성
    glBindTexture(GL_TEXTURE_2D, saturnTex);
    glm::mat4 saturnModel = parentModel;
    saturnModel = glm::rotate(saturnModel, time * 0.034f + glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    saturnModel = glm::translate(saturnModel, glm::vec3(16.0f, 0.0f, 0.0f));
    saturnModel = glm::rotate(saturnModel, time * 2.2f, glm::vec3(0.0f, 1.0f, 0.0f));
    saturnModel = glm::scale(saturnModel, glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setMat4("model", saturnModel);
    sphereMesh->draw();

    // 8. 천왕성
    glBindTexture(GL_TEXTURE_2D, uranusTex);
    glm::mat4 uranusModel = parentModel;
    uranusModel = glm::rotate(uranusModel, time * 0.012f + glm::radians(200.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    uranusModel = glm::translate(uranusModel, glm::vec3(19.0f, 0.0f, 0.0f));
    uranusModel = glm::rotate(uranusModel, time * -1.4f, glm::vec3(0.0f, 1.0f, 0.0f)); // 역행 자전
    uranusModel = glm::scale(uranusModel, glm::vec3(0.75f, 0.75f, 0.75f));
    shader.setMat4("model", uranusModel);
    sphereMesh->draw();

    // 9. 해왕성
    glBindTexture(GL_TEXTURE_2D, neptuneTex);
    glm::mat4 neptuneModel = parentModel;
    neptuneModel = glm::rotate(neptuneModel, time * 0.006f + glm::radians(290.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    neptuneModel = glm::translate(neptuneModel, glm::vec3(22.0f, 0.0f, 0.0f));
    neptuneModel = glm::rotate(neptuneModel, time * 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    neptuneModel = glm::scale(neptuneModel, glm::vec3(0.7f, 0.7f, 0.7f));
    shader.setMat4("model", neptuneModel);
    sphereMesh->draw();
}



// ==========================================
// satellite 구현
// ==========================================
satellite::satellite(Mesh&spMesh,  Mesh& anMesh, Mesh& cuMesh, Mesh& coMesh, unsigned int sbTex, unsigned int slTex, unsigned int anTex)
    : sphereMesh(&spMesh), antennaMesh(&anMesh), cubeMesh(&cuMesh), coneMesh(&coMesh), bodyTex(sbTex), solarTex(slTex), antennaTex(anTex) {
}

void satellite::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;

    // 1. 위성 본체 (Body)
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bodyTex);
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 2. 태양광 패널 (Solar Panels)
    glBindTexture(GL_TEXTURE_2D, solarTex);

    //패널을 반복문으로 생성
    float panelXPositions[] = { 1.5f, 2.6f, 3.7f, -1.5f, -2.6f, -3.7f };
    for (float xPos : panelXPositions) {
        model = parentModel;
        model = glm::translate(model, glm::vec3(xPos, 1.0f, -0.8f));
        model = glm::scale(model, glm::vec3(1.0f, 2.0f, 0.2f));
        shader.setMat4("model", model);
        cubeMesh->draw();
    }

    // 3. 안테나 및 콘 (Antenna & Cone)
    glBindTexture(GL_TEXTURE_2D, antennaTex);
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setMat4("model", model);
    antennaMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
    shader.setMat4("model", model);
    coneMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.3f));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setMat4("model", model);
    sphereMesh->draw();

}
