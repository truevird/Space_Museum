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

// ==========================================
// SmallExhibit 구현 (작은 전시관 - 사방에 문 구멍)
// ==========================================
SmallExhibit::SmallExhibit(Mesh& cMesh, unsigned int iTex, unsigned int oTex)
    : cubeMesh(&cMesh), innerTex(iTex), outerTex(oTex) {
}

void SmallExhibit::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;
    
    // ===== 바깥쪽 벽 (wall 텍스처) =====
    glBindTexture(GL_TEXTURE_2D, outerTex);
    glCullFace(GL_FRONT);  // 안쪽 면만 제거, 바깥쪽만 보임
    
    // 천장
    model = parentModel;
    model = glm::scale(model, glm::vec3(5.0f, 0.5f, 4.5f));
    model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();


    // 왼쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 1.5f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, -0.75f, -1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, -0.75f, 1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 1.5f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, -0.75f, -1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, -0.75f, 1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 2.0f));
    model = glm::scale(model, glm::vec3(4.0f, 1.5f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.25f, -0.75f, 2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.25f, -0.75f, 2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
    model = glm::scale(model, glm::vec3(4.0f, 1.5f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.25f, -0.75f, -2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.25f, -0.75f, -2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // ===== 안쪽 벽 (spaceTex) - 약간 작은 크기 =====
    glBindTexture(GL_TEXTURE_2D, innerTex);
    glCullFace(GL_BACK);  // 바깥쪽 면만 제거, 안쪽만 보임

    // 천장
    model = parentModel;
    model = glm::scale(model, glm::vec3(4.9f, 0.49f, 4.4f));  // 약간 작게
    model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    //바닥
    model = parentModel;
    model = glm::scale(model, glm::vec3(4.9f, 0.49f, 4.4f));  // 약간 작게
    model = glm::translate(model, glm::vec3(0.0f, -2.9f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 왼쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, 0.49f, 0.0f));
    model = glm::scale(model, glm::vec3(0.49f, 1.49f, 4.4f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, -0.74f, -1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, -0.74f, 1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, 0.49f, 0.0f));
    model = glm::scale(model, glm::vec3(0.49f, 1.49f, 4.4f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, -0.74f, -1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, -0.74f, 1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.49f, 1.99f));
    model = glm::scale(model, glm::vec3(4.0f, 1.49f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.24f, -0.74f, 1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.24f, -0.74f, 1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.49f, -1.99f));
    model = glm::scale(model, glm::vec3(4.0f, 1.49f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.24f, -0.74f, -1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.24f, -0.74f, -1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glCullFace(GL_BACK);  // 기본값 복구
}

EarthExhibit::EarthExhibit(Mesh& cMesh, unsigned int iTex, unsigned int fTex, unsigned int oTex)
    : cubeMesh(&cMesh), innerTex(iTex), outerTex(oTex), floorTex(fTex) {
}

void EarthExhibit::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;
    
    // ===== 바깥쪽 벽 (wall 텍스처) =====
    glBindTexture(GL_TEXTURE_2D, outerTex);
    glCullFace(GL_FRONT);  // 안쪽 면만 제거, 바깥쪽만 보임
    
    // 천장
    model = parentModel;
    model = glm::scale(model, glm::vec3(5.0f, 0.5f, 4.5f));
    model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();


    // 왼쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 1.5f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, -0.75f, -1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, -0.75f, 1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 1.5f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, -0.75f, -1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, -0.75f, 1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 2.0f));
    model = glm::scale(model, glm::vec3(4.0f, 1.5f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.25f, -0.75f, 2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.25f, -0.75f, 2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
    model = glm::scale(model, glm::vec3(4.0f, 1.5f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.25f, -0.75f, -2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.25f, -0.75f, -2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // ===== 안쪽 벽 (spaceTex) - 약간 작은 크기 =====
    glBindTexture(GL_TEXTURE_2D, innerTex);
    glCullFace(GL_BACK);  // 바깥쪽 면만 제거, 안쪽만 보임

    // 천장
    model = parentModel;
    model = glm::scale(model, glm::vec3(4.9f, 0.49f, 4.4f));  // 약간 작게
    model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glBindTexture(GL_TEXTURE_2D, floorTex);
    //바닥
    model = parentModel;
    model = glm::scale(model, glm::vec3(4.9f, 0.49f, 4.4f));  // 약간 작게
    model = glm::translate(model, glm::vec3(0.0f, -2.9f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glBindTexture(GL_TEXTURE_2D, innerTex);
    // 왼쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, 0.49f, 0.0f));
    model = glm::scale(model, glm::vec3(0.49f, 1.49f, 4.4f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, -0.74f, -1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, -0.74f, 1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, 0.49f, 0.0f));
    model = glm::scale(model, glm::vec3(0.49f, 1.49f, 4.4f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, -0.74f, -1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, -0.74f, 1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.49f, 1.99f));
    model = glm::scale(model, glm::vec3(4.0f, 1.49f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.24f, -0.74f, 1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.24f, -0.74f, 1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.49f, -1.99f));
    model = glm::scale(model, glm::vec3(4.0f, 1.49f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.24f, -0.74f, -1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.24f, -0.74f, -1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glCullFace(GL_BACK);  // 기본값 복구
}

MarsExhibit::MarsExhibit(Mesh& cMesh, unsigned int iTex, unsigned int fTex, unsigned int oTex)
    : cubeMesh(&cMesh), innerTex(iTex), outerTex(oTex), floorTex(fTex) {
}

void MarsExhibit::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;
    
    // ===== 바깥쪽 벽 (wall 텍스처) =====
    glBindTexture(GL_TEXTURE_2D, outerTex);
    glCullFace(GL_FRONT);  // 안쪽 면만 제거, 바깥쪽만 보임
    
    // 천장
    model = parentModel;
    model = glm::scale(model, glm::vec3(5.0f, 0.5f, 4.5f));
    model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();


    // 왼쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 1.5f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, -0.75f, -1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, -0.75f, 1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 1.5f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, -0.75f, -1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, -0.75f, 1.5f));
    model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 2.0f));
    model = glm::scale(model, glm::vec3(4.0f, 1.5f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.25f, -0.75f, 2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.25f, -0.75f, 2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
    model = glm::scale(model, glm::vec3(4.0f, 1.5f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.25f, -0.75f, -2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.25f, -0.75f, -2.0f));
    model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // ===== 안쪽 벽 (spaceTex) - 약간 작은 크기 =====
    glBindTexture(GL_TEXTURE_2D, innerTex);
    glCullFace(GL_BACK);  // 바깥쪽 면만 제거, 안쪽만 보임

    // 천장
    model = parentModel;
    model = glm::scale(model, glm::vec3(4.9f, 0.49f, 4.4f));  // 약간 작게
    model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glBindTexture(GL_TEXTURE_2D, floorTex);
    //바닥
    model = parentModel;
    model = glm::scale(model, glm::vec3(4.9f, 0.49f, 4.4f));  // 약간 작게
    model = glm::translate(model, glm::vec3(0.0f, -2.9f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glBindTexture(GL_TEXTURE_2D, innerTex);
    // 왼쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, 0.49f, 0.0f));
    model = glm::scale(model, glm::vec3(0.49f, 1.49f, 4.4f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, -0.74f, -1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.24f, -0.74f, 1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, 0.49f, 0.0f));
    model = glm::scale(model, glm::vec3(0.49f, 1.49f, 4.4f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, -0.74f, -1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.24f, -0.74f, 1.49f));
    model = glm::scale(model, glm::vec3(0.49f, 0.99f, 1.50f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.49f, 1.99f));
    model = glm::scale(model, glm::vec3(4.0f, 1.49f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.24f, -0.74f, 1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.24f, -0.74f, 1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.49f, -1.99f));
    model = glm::scale(model, glm::vec3(4.0f, 1.49f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-1.24f, -0.74f, -1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.24f, -0.74f, -1.99f));
    model = glm::scale(model, glm::vec3(1.55f, 0.99f, 0.49f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glCullFace(GL_BACK);  // 기본값 복구
}

// ==========================================
// 화성탐사로봇 구현
// ==========================================

MarsRover::MarsRover(
    Mesh& cuMesh, Mesh& cyMesh, Mesh& spMesh, unsigned int bTex, unsigned int wTex, unsigned int dTex
) : cubeMesh(&cuMesh), cylinderMesh(&cyMesh), sphereMesh(&spMesh), bodyTex(bTex), wheelTex(wTex), darkTex(dTex) {
}

void MarsRover::draw(Shader& shader, float time, glm::mat4 parentModel) {
    glm::mat4 model;

    // 로버 전체 기준 위치
    glm::mat4 roverBase = parentModel;
    roverBase = glm::translate(roverBase, glm::vec3(0.0f, 0.15f, 0.0f));

    // 1. 본체

    glBindTexture(GL_TEXTURE_2D, bodyTex);
    model = roverBase;
    model = glm::translate(model, glm::vec3(0.0f, 0.35f, 0.0f));
    model = glm::scale(model, glm::vec3(1.8f, 0.25f, 1.2f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glBindTexture(GL_TEXTURE_2D, darkTex);
    model = roverBase;
    model = glm::translate(model, glm::vec3(0.1f, 0.48f, 0.0f));
    model = glm::scale(model, glm::vec3(1.5f, 0.04f, 1.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = roverBase;
    model = glm::translate(model, glm::vec3(0.95f, 0.28f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.8f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 2. 카메라 마스트

    glBindTexture(GL_TEXTURE_2D, darkTex);
    model = roverBase;
    model = glm::translate(model, glm::vec3(0.6f, 0.5f, -0.4f));
    model = glm::scale(model, glm::vec3(0.06f, 0.6f, 0.06f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    float scanAngle = sin(time * 1.5f) * glm::radians(60.0f);
    glm::mat4 headBase = roverBase;
    headBase = glm::translate(headBase, glm::vec3(0.6f, 1.1f, -0.4f));
    headBase = glm::rotate(headBase, scanAngle, glm::vec3(0, 1, 0));

    glBindTexture(GL_TEXTURE_2D, bodyTex);
    model = headBase;
    model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
    model = glm::scale(model, glm::vec3(0.35f, 0.18f, 0.45f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glBindTexture(GL_TEXTURE_2D, darkTex);
    model = headBase;
    model = glm::translate(model, glm::vec3(0.175f, 0.1f, -0.1f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(0.08f, 0.05f, 0.08f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    model = headBase;
    model = glm::translate(model, glm::vec3(0.175f, 0.1f, 0.1f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    // 3. 로봇 팔 및 드릴

    float armBreathe = sin(time * 2.0f) * glm::radians(5.0f);
    glm::mat4 armBase = roverBase;
    armBase = glm::translate(armBase, glm::vec3(0.9f, 0.35f, 0.0f));
    armBase = glm::rotate(armBase, armBreathe, glm::vec3(0, 0, 1));

    glBindTexture(GL_TEXTURE_2D, bodyTex);
    glm::mat4 arm1 = armBase;
    arm1 = glm::rotate(arm1, glm::radians(20.0f), glm::vec3(0, 0, 1));
    model = arm1;
    model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.6f, 0.06f, 0.06f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glm::mat4 arm2 = arm1;
    arm2 = glm::translate(arm2, glm::vec3(0.6f, 0.0f, 0.0f));
    arm2 = glm::rotate(arm2, glm::radians(-70.0f), glm::vec3(0, 0, 1));
    model = arm2;
    model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.05f, 0.05f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    glm::mat4 drill = arm2;
    drill = glm::translate(drill, glm::vec3(0.5f, 0.0f, 0.0f));
    model = drill;
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(0.0f, -0.15f, 0.0f));
    model = glm::rotate(model, time * 10.0f, glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    // 4. 서스펜션 및 바퀴

    float wheelX[] = { 0.8f, 0.0f, -0.8f };
    float wheelZ[] = { 0.75f, -0.75f };

    for (int j = 0; j < 2; j++) {
        float z = wheelZ[j];

        // 측면 메인 프레임
        glBindTexture(GL_TEXTURE_2D, darkTex);
        model = roverBase;
        model = glm::translate(model, glm::vec3(0.0f, 0.35f, z * 0.7f));
        model = glm::scale(model, glm::vec3(1.7f, 0.08f, 0.08f));
        shader.setMat4("model", model);
        cubeMesh->draw();

        for (int i = 0; i < 3; i++) {
            float x = wheelX[i];

            // 수직 프레임
            glBindTexture(GL_TEXTURE_2D, darkTex);
            model = roverBase;
            model = glm::translate(model, glm::vec3(x, 0.175f, z * 0.7f));
            model = glm::scale(model, glm::vec3(0.05f, 0.35f, 0.05f));
            shader.setMat4("model", model);
            cubeMesh->draw();

            // 타이어
            glm::mat4 wheelBase = roverBase;
            wheelBase = glm::translate(wheelBase, glm::vec3(x, 0.0f, z - 0.15f));
            wheelBase = glm::rotate(wheelBase, time * 1.5f, glm::vec3(0, 0, 1));
            wheelBase = glm::rotate(wheelBase, glm::radians(90.0f), glm::vec3(1, 0, 0));

            glBindTexture(GL_TEXTURE_2D, wheelTex);
            model = wheelBase;
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            shader.setMat4("model", model);
            cylinderMesh->draw();
        }
    }
}
