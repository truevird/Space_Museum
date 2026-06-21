#include "Object.h"

// ==========================================
// Stage 구현
// ==========================================
Stage::Stage(Mesh& spMesh, unsigned int wTex)
    : sphereMesh(&spMesh), wallTex(wTex) {
}
void Stage::draw(Shader& shader, float time, glm::mat4 parentModel) {
    glm::mat4 model;

    glBindTexture(GL_TEXTURE_2D, wallTex);

    // 돔
    model = parentModel; 
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
    model = glm::rotate(model, time * 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("model", model);
    sphereMesh->draw();

}

//단일 행성
Planet::Planet(Mesh& sMesh, unsigned int pTex)
    :  sphereMesh(&sMesh), planetTex(pTex) {
}

void Planet::draw(Shader& shader, float time, glm::mat4 parentModel) {
    glm::mat4 model;

    glBindTexture(GL_TEXTURE_2D, planetTex);

    model = parentModel;
    model = glm::rotate(model, time * 0.04f, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
    shader.setMat4("model", model);
    sphereMesh->draw();

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
    earthModel = glm::rotate(earthModel, time * 3.0f, glm::vec3(0.0f, 1.0f, 0.0f));    // 공전 후 자전이 분리되지 않은 경우 순서 주의
    earthModel = glm::scale(earthModel, glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setMat4("model", earthModel);
    sphereMesh->draw();

    // 2. 달
    glBindTexture(GL_TEXTURE_2D, moonTex);
    glm::mat4 moonModel = parentModel;
    moonModel = glm::rotate(moonModel, time * 12.0f, glm::vec3(0.0f, 1.0f, 0.0f));     // 1. 지구 중심 공전
    moonModel = glm::translate(moonModel, glm::vec3(1.2f, 0.0f, 0.0f));                 // 2. 궤도 반지름 거리
    moonModel = glm::rotate(moonModel, time * 12.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    moonModel = glm::scale(moonModel, glm::vec3(0.12f, 0.12f, 0.12f));                  // 3. 크기
    shader.setMat4("model", moonModel);
    sphereMesh->draw();
}

// ==========================================
// SolarSystem 구현
// ==========================================
SolarSystem::SolarSystem(Mesh& mesh, Mesh& rMesh, Mesh& srMesh, EarthMoonSystem& emSystem, unsigned int sTex, unsigned int meTex, unsigned int vTex, unsigned int maTex, unsigned int jTex, unsigned int saTex, unsigned int uTex, unsigned int nTex, unsigned int rTex)
    : sphereMesh(&mesh), ringMesh(&rMesh), springMesh(&srMesh), earthMoon(&emSystem), solarTex(sTex), mercuryTex(meTex), venusTex(vTex), marsTex(maTex), jupiterTex(jTex), saturnTex(saTex), uranusTex(uTex), neptuneTex(nTex), ringTex(rTex) {
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

    // 공전
    saturnModel = glm::rotate(saturnModel, time * 0.034f + glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    saturnModel = glm::translate(saturnModel, glm::vec3(16.0f, 0.0f, 0.0f));

    // 토성계 전체 자전축 기울기
    saturnModel = glm::rotate(saturnModel, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.5f));

    // 자전
    saturnModel = glm::rotate(saturnModel, time * 2.2f, glm::vec3(0.0f, 1.0f, 0.0f));

    // 토성 구체 그리기
    glm::mat4 planetModel = glm::scale(saturnModel, glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setMat4("model", planetModel);
    sphereMesh->draw();

    // 토성 고리 그리기
    glm::mat4 ringModel = glm::scale(saturnModel, glm::vec3(1.6f, 1.6f, 1.6f));
    shader.setMat4("model", ringModel);

    // 컬링 해제
    glDisable(GL_CULL_FACE);
    ringMesh->draw();

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

    glBindTexture(GL_TEXTURE_2D, ringTex);
    glm::mat4 springModel = parentModel;
    springModel = glm::translate(springModel, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel = glm::scale(springModel, glm::vec3(3.5f, 3.5f, 3.5f));
    shader.setMat4("model", springModel);
    springMesh->draw();

    glm::mat4 springModel1 = parentModel;
    springModel1 = glm::translate(springModel1, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel1 = glm::scale(springModel1, glm::vec3(5.0f, 5.0f, 5.0f));
    shader.setMat4("model", springModel1);
    springMesh->draw();


    glm::mat4 springModel2 = parentModel;
    springModel2 = glm::translate(springModel2, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel2 = glm::scale(springModel2, glm::vec3(7.0f, 7.0f, 7.0f));
    shader.setMat4("model", springModel2);
    springMesh->draw();


    glm::mat4 springModel3 = parentModel;
    springModel3 = glm::translate(springModel3, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel3 = glm::scale(springModel3, glm::vec3(9.0f, 9.0f, 9.0f));
    shader.setMat4("model", springModel3);
    springMesh->draw();


    glm::mat4 springModel4 = parentModel;
    springModel4 = glm::translate(springModel4, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel4 = glm::scale(springModel4, glm::vec3(12.5f, 12.5f, 12.5f));
    shader.setMat4("model", springModel4);
    springMesh->draw();

    glm::mat4 springModel5 = parentModel;
    springModel5 = glm::translate(springModel5, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel5 = glm::scale(springModel5, glm::vec3(16.0f, 16.0f, 16.0f));
    shader.setMat4("model", springModel5);
    springMesh->draw();

    glm::mat4 springModel6 = parentModel;
    springModel6 = glm::translate(springModel6, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel6 = glm::scale(springModel6, glm::vec3(19.0f, 19.0f, 19.0f));
    shader.setMat4("model", springModel6);
    springMesh->draw();

    glm::mat4 springModel7 = parentModel;
    springModel7 = glm::translate(springModel7, glm::vec3(0.0f, 0.0f, 0.0f));
    springModel7 = glm::scale(springModel7, glm::vec3(22.0f, 22.0f, 22.0f));
    shader.setMat4("model", springModel7);
    springMesh->draw();



}



// ==========================================
// satellite 구현 (큐브위성)
// ==========================================
satellite::satellite(Mesh&spMesh,  Mesh& anMesh, Mesh& cuMesh, Mesh& coMesh, unsigned int sbTex, unsigned int slTex, unsigned int anTex)
    : sphereMesh(&spMesh), antennaMesh(&anMesh), cubeMesh(&cuMesh), coneMesh(&coMesh), bodyTex(sbTex), solarTex(slTex), antennaTex(anTex) {
}

void satellite::draw(Shader& shader,float time, glm::mat4 parentModel) {
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
// CylinderSatellite 구현 (원기둥 위성)
// ==========================================
CylinderSatellite::CylinderSatellite(Mesh& cyMesh, Mesh& paMesh, Mesh& anMesh, Mesh& coMesh, Mesh& spMesh, Mesh& srMesh, unsigned int bTex, unsigned int pTex, unsigned int aTex)
    : cylinderMesh(&cyMesh), panelMesh(&paMesh), antennaMesh(&anMesh), coneMesh(&coMesh), sphereMesh(&spMesh), springMesh(&srMesh), bodyTex(bTex), panelTex(pTex), accentTex(aTex) {
}

void CylinderSatellite::draw(Shader& shader,float time, glm::mat4 parentModel) {
    glm::mat4 model;

    // 본체 (원기둥)
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, accentTex);
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.8f, 1.0f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.1f, 1.0f, 1.1f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    //큐브
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.6f, 1.0f, 0.5f));
    model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.3f));
    shader.setMat4("model", model);
    panelMesh->draw();
    //큐브
    model = parentModel;
    model = glm::translate(model, glm::vec3(-0.6f, 1.0f, 0.5f));
    model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.3f));
    shader.setMat4("model", model);
    panelMesh->draw();

    //큐브
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.6f, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 0.25f, 0.2f));
    shader.setMat4("model", model);
    panelMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(1.0f, 1.0f, 0.5f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.1f, 1.0f, 0.1f));
    shader.setMat4("model", model);
    cylinderMesh->draw();


    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.5f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.1f, 1.0f, 0.1f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    glBindTexture(GL_TEXTURE_2D, bodyTex);
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.05f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.05f, 1.0f, 1.05f));
    shader.setMat4("model", model);
    cylinderMesh->draw();


    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.05f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.9f, 1.8f, 0.9f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -0.2f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.9f, 1.8f, 0.9f));
    shader.setMat4("model", model);
    cylinderMesh->draw();



    // 태양광 패널 (좌우)
    glBindTexture(GL_TEXTURE_2D, panelTex);
    for (float side : { -1.0f, 1.0f }) {
        model = parentModel;
        model = glm::translate(model, glm::vec3(side * 1.7f, 1.0f, 0.5f));
        model = glm::scale(model, glm::vec3(1.6f, 0.12f, 0.6f));
        shader.setMat4("model", model);
        panelMesh->draw();
    }

    // 안테나
    glBindTexture(GL_TEXTURE_2D, accentTex);
    model = parentModel;
    
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 2.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    
    shader.setMat4("model", model);
    antennaMesh->draw();
    
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 2.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
    shader.setMat4("model", model);
    coneMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 2.3f));
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

//
GlassWall::GlassWall(Mesh& cMesh, const glm::vec3& colorIn, float alphaIn)
    : cubeMesh(&cMesh), color(colorIn), alpha(alphaIn) {}

void GlassWall::draw(Shader& shader, glm::mat4 parentModel) {
    shader.setBool("useColor", true);
    shader.setVec3("overrideColor", color.x, color.y, color.z);
    shader.setFloat("alpha", alpha);
    shader.setBool("useLighting", false);

    glm::mat4 model = parentModel;
    shader.setMat4("model", model);
    cubeMesh->draw();

    shader.setBool("useColor", false);
    shader.setFloat("alpha", 1.0f);
}

void SmallExhibit::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;
     
    // ===== 바깥쪽 벽 (wall 텍스처) =====
    glBindTexture(GL_TEXTURE_2D, outerTex);
    
    // 천장
    model = parentModel;
    model = glm::scale(model, glm::vec3(5.0f, 0.5f, 4.5f));
    model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();
     
    //바닥
    model = parentModel;
    model = glm::scale(model, glm::vec3(5.0f, 0.49f, 4.5f));  // 약간 작게
    model = glm::translate(model, glm::vec3(0.0f, -2.9f, 0.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 왼쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.4f, 0.9f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.7f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 오른쪽 벽 (상단 + 하단)
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.4f, 0.9f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.7f, 4.5f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 앞쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.9f, 2.15f));
    model = glm::scale(model, glm::vec3(4.0f, 0.7f, 0.2f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    // 뒤쪽 벽 (상단 + 하단 양쪽)
    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.9f, -2.15f));
    model = glm::scale(model, glm::vec3(4.0f, 0.7f, 0.2f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    //4개의 기둥
    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f, 0.055f, 2.0f));
    model = glm::scale(model, glm::vec3(0.51f, 3.4f, 0.51f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, 0.055f, -2.0f));
    model = glm::scale(model, glm::vec3(0.51f, 3.4f, 0.51f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(-2.25f, 0.055f, 2.0f));
    model = glm::scale(model, glm::vec3(0.51f, 3.4f, 0.51f)); 
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(2.25f,  0.055f, -2.0f));
    model = glm::scale(model, glm::vec3(0.51f, 3.4f, 0.51f));
    shader.setMat4("model", model);
    cubeMesh->draw();

} 

//우주왕복선 모델링 클래스 구현
SpaceShuttle::SpaceShuttle(
    Mesh& cuMesh,
    Mesh& cyMesh,
    Mesh& coMesh,
    Mesh& spMesh,
    unsigned int bTex,
    unsigned int wTex,
    unsigned int dTex,
	unsigned int sTex
)
    : cubeMesh(&cuMesh),
    cylinderMesh(&cyMesh),
    coneMesh(&coMesh),
    sphereMesh(&spMesh),
    bodyTex(bTex),
    wingTex(wTex),
    darkTex(dTex),
    sunTex(sTex)
{
}

void SpaceShuttle::draw(
    Shader& shader,float time,
    glm::mat4 parentModel
)
{
    glm::mat4 model;

    //--------------------------------------------------
    // 메인 동체
    //--------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, bodyTex);

    model = parentModel;
    model = glm::translate(
        model,
        glm::vec3(.0f, 0.0f, -2.5f));
    model = glm::rotate(
        model,
        glm::radians(90.0f),
        glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model,
        glm::vec3(0.9f, 5.0f, 0.9f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    //--------------------------------------------------
    // 메인 동체2
    //--------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, bodyTex);

    model = parentModel;
    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.5f, -2.5f));
    model = glm::rotate(
        model,
        glm::radians(90.0f),
        glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model,
        glm::vec3(0.9f, 3.8f, 0.9f));
    shader.setMat4("model", model);
    cylinderMesh->draw();



    //--------------------------------------------------
    // 기수
    //--------------------------------------------------

    model = parentModel;
    model = glm::translate(model,
        glm::vec3(0.0f, 0.0f, 2.5f));
    model = glm::rotate(model,
        glm::radians(90.0f),
        glm::vec3(1, 0, 0));
    model = glm::scale(model,
        glm::vec3(0.9f, 0.8f, 0.9f));

    shader.setMat4("model", model);
    coneMesh->draw();

    //--------------------------------------------------
    // 꼬리 엔진부
    //--------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, bodyTex);

    float engineX[3] =
    {
        -0.35f,
         0.0f,
         0.35f
    };

    for (int i = 0;i < 3;i++)
    {
        model = parentModel;

        model = glm::translate(
            model,
            glm::vec3(
                engineX[i],
                0.0f,
                -2.9f
            ));

        model = glm::rotate(
            model,
            glm::radians(90.0f),
            glm::vec3(1, 0, 0));

        model = glm::scale(
            model,
            glm::vec3(
                0.6f,
                0.6f,
                0.6f));

        shader.setMat4("model", model);
        cylinderMesh->draw();
    }

    glBindTexture(GL_TEXTURE_2D, sunTex);

    float fire[3] =
    {
        -0.35f,
         0.0f,
         0.35f
    };

    for (int i = 0;i < 3;i++)
    {
        model = parentModel;

        model = glm::translate(
            model,
            glm::vec3(
                fire[i],
                0.0f,
                -4.9f
            ));

        model = glm::rotate(
            model,
            glm::radians(90.0f),
            glm::vec3(1, 0, 0));

        model = glm::scale(
            model,
            glm::vec3(
                0.2f,
                1.4f,
                0.2f));
        int d = 1;
        if(i==1)d=-1;

        model = glm::rotate(model, time * 40.0f, glm::vec3(0, d, d));

        shader.setMat4("model", model);
        sphereMesh->draw();
    }



    //--------------------------------------------------
    // 주 날개
    //--------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, wingTex);

    model = parentModel;
    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            0.0f,
            -1.0f));

    model = glm::rotate(
        model,
        glm::radians(45.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(
            2.2f,
            0.08f,
            2.2f));


    shader.setMat4("model", model);
    cubeMesh->draw();


    //--------------------------------------------------
    // 수직 꼬리날개
    //--------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, bodyTex);

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            0.9f,
            -1.8f));

    model = glm::rotate(
        model,
        glm::radians(45.0f),
        glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(
            0.15f,
            1.0f,
            1.0f));

    shader.setMat4("model", model);
    cubeMesh->draw();

    //--------------------------------------------------
    // 조종석
    //--------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, darkTex);

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            0.35f,
            1.5f));



    model = glm::scale(
        model,
        glm::vec3(
            0.35f,
            0.35f,
            0.35f));

    shader.setMat4("model", model);
    sphereMesh->draw();

    //--------------------------------------------------
    // OMS 포드
    //--------------------------------------------------

    for (float x : {-0.55f, 0.55f})
    {
        model = parentModel;

        model = glm::translate(
            model,
            glm::vec3(
                x,
                0.35f,
                -2.3f));

        model = glm::rotate(
            model,
            glm::radians(90.0f),
            glm::vec3(1, 0, 0));

        model = glm::scale(
            model,
            glm::vec3(
                0.18f,
                0.18f,
                0.8f));

        shader.setMat4("model", model);
        cylinderMesh->draw();
    }
}


// ==========================================
// 화성탐사로봇 구현
// ==========================================

MarsRover::MarsRover(
    Mesh& cuMesh, Mesh& cyMesh, Mesh& spMesh, Mesh& coMesh, unsigned int bTex, unsigned int wTex, unsigned int dTex
) : cubeMesh(&cuMesh), cylinderMesh(&cyMesh), sphereMesh(&spMesh), coneMesh(&coMesh), bodyTex(bTex), wheelTex(wTex), darkTex(dTex) {
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

    glBindTexture(GL_TEXTURE_2D, wheelTex);
    glm::mat4 drill = arm2;
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    model = glm::rotate(model, time * 10.0f, glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(1.5f, 0.2f, 1.5f));
    shader.setMat4("model", model);
    coneMesh->draw();

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

//단일 전시안내판
Info::Info(Mesh& fMesh, unsigned int iTex)
   :  floorMesh(&fMesh), infoTex(iTex) {
}

void Info::draw(Shader& shader, glm::mat4 parentModel) {
   glm::mat4 model;

   glBindTexture(GL_TEXTURE_2D, infoTex);

   model = parentModel;
   
   model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
   model = glm::scale(model, glm::vec3(0.24f, 0.15f, 1.0f));
   model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
   shader.setMat4("model", model);
   floorMesh->draw();

}

// =========================================================================
// 차단봉 구현 
// =========================================================================
Barrier::Barrier(Mesh& cyMesh, Mesh& spMesh, unsigned int baTex)
    : cylinderMesh(&cyMesh), sphereMesh(&spMesh), baseTex(baTex) {
}

void Barrier::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;
    glBindTexture(GL_TEXTURE_2D, baseTex);

    model = parentModel;
    
    model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.2f, 0.10f, 1.2f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 5.0f, 0.2f));
    shader.setMat4("model", model);
    cylinderMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    shader.setMat4("model", model);
    sphereMesh->draw();
}
Stand ::Stand(Mesh& cMesh,Info& ifMesh, unsigned int bTex)
    : cubeMesh(&cMesh), infoMesh(&ifMesh), baseTex(bTex) {
}
void Stand::draw(Shader& shader, glm::mat4 parentModel) {
    glm::mat4 model;
    glBindTexture(GL_TEXTURE_2D, baseTex);

    model = parentModel;
    
    model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.0f, 0.3f, 2.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, -3.8f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 4.0f, 1.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, -1.5f, 1.0f));
    model = glm::scale(model, glm::vec3(3.0f, 0.5f, 2.0f));
    shader.setMat4("model", model);
    cubeMesh->draw();

    model = parentModel;
    model = glm::translate(model, glm::vec3(0.0f, -1.6f, 0.3f));
    model = glm::scale(model, glm::vec3(0.55f, 0.55f, 0.55f));
    model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    shader.setMat4("model", model);
    infoMesh->draw(shader, model);

}