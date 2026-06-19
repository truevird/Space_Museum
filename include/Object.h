#ifndef OBJECTS_H
#define OBJECTS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "Shader.h"

// 1. 전시관 구조체
struct Stage {
    Mesh* sphereMesh;
    unsigned int wallTex;

    Stage(Mesh& spMesh, unsigned int wTex);
    void draw(Shader& shader, float time, glm::mat4 parentModel = glm::mat4(1.0f));
};

struct Planet {
    Mesh* sphereMesh;
    unsigned int planetTex;

    Planet(Mesh& sMesh, unsigned int pTex);
    void draw(Shader& shader, float time, glm::mat4 parentModel = glm::mat4(1.0f));
};

struct SmallExhibit {
    Mesh* cubeMesh;
    unsigned int innerTex;  // 안쪽 텍스처
    unsigned int outerTex;  // 바깥쪽 텍스처

    SmallExhibit(Mesh& cMesh, unsigned int iTex, unsigned int oTex);
    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};

struct GlassWall {
    Mesh* cubeMesh;
    glm::vec3 color;
    float alpha;

    GlassWall(Mesh& cMesh, const glm::vec3& colorIn, float alphaIn);
    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};

// 2.지구 달 구조체
struct EarthMoonSystem {
    Mesh* sphereMesh;
    unsigned int earthTex;
    unsigned int moonTex;

    EarthMoonSystem(Mesh& mesh, unsigned int eTex, unsigned int mTex);
    void draw(Shader& shader, float time, glm::mat4 parentModel);
};

// 3. 태양계 구조체
struct SolarSystem {
    Mesh* sphereMesh;
    Mesh* ringMesh;
    Mesh* springMesh;
    EarthMoonSystem* earthMoon;
    unsigned int solarTex;
    unsigned int mercuryTex;
    unsigned int venusTex;
    unsigned int marsTex;
    unsigned int jupiterTex;
    unsigned int saturnTex;
    unsigned int uranusTex;
    unsigned int neptuneTex;
    unsigned int ringTex;

    SolarSystem(Mesh& mesh, Mesh& rMesh, Mesh& spMesh, EarthMoonSystem& emSystem, unsigned int sTex, unsigned int meTex, unsigned int vTex, unsigned int maTex, unsigned int jTex, unsigned int saTex, unsigned int uTex, unsigned int nTex, unsigned int rTex);
    void draw(Shader& shader, float time, glm::mat4 parentModel);
};

// 4. 인공위성 구조체
struct satellite {
    Mesh* sphereMesh;
    Mesh* antennaMesh;
    Mesh* cubeMesh;
    Mesh* coneMesh;
    unsigned int bodyTex;
    unsigned int solarTex;
    unsigned int antennaTex;

    satellite(Mesh& spMesh, Mesh& anMesh, Mesh& cuMesh, Mesh& coMesh, unsigned int sbTex, unsigned int slTex, unsigned int anTex);
    void draw(Shader& shader, float time, glm::mat4 parentModel = glm::mat4(1.0f));
};

// 원기둥 형태 인공위성
struct CylinderSatellite {
    Mesh* cylinderMesh;
    Mesh* panelMesh; // 패널은 큐브 메쉬를 재사용
    Mesh* antennaMesh; // 기존 안테나 메쉬 재사용
    Mesh* coneMesh; // 기존 콘 메쉬 재사용
    Mesh* sphereMesh; // 기존 스피어 메쉬 재사용
    Mesh* springMesh;

    unsigned int bodyTex;
    unsigned int panelTex;
    unsigned int accentTex;

    CylinderSatellite(Mesh& cyMesh, Mesh& paMesh, Mesh& anMesh, Mesh& coMesh, Mesh& spMesh, Mesh& srMesh,unsigned int bTex, unsigned int pTex, unsigned int aTex);
    void draw(Shader& shader, float time, glm::mat4 parentModel = glm::mat4(1.0f));
};
// 5.화성탐사로봇
struct MarsRover {
    Mesh* cubeMesh;
    Mesh* cylinderMesh;
    Mesh* sphereMesh;
    Mesh* coneMesh;

    unsigned int bodyTex;
    unsigned int wheelTex;
    unsigned int darkTex;

    MarsRover(
        Mesh& cuMesh,
        Mesh& cyMesh,
        Mesh& spMesh,
        Mesh& coMesh,
        unsigned int bTex,
        unsigned int wTex,
        unsigned int dTex
    );

    void draw(
        Shader& shader,
        float time,
        glm::mat4 parentModel = glm::mat4(1.0f)
    );
};

// 우주왕복선
struct SpaceShuttle { 
    Mesh* cubeMesh;
    Mesh* cylinderMesh;
    Mesh* coneMesh;
	Mesh* sphereMesh;

    unsigned int bodyTex;
    unsigned int wingTex;
    unsigned int darkTex;
    unsigned int sunTex;

    SpaceShuttle(
        Mesh& cuMesh,
        Mesh& cyMesh,
        Mesh& coMesh,
		Mesh& spMesh,
        unsigned int bTex,
        unsigned int wTex,
        unsigned int dTex,
		unsigned int sTex
    );

    void draw(
        Shader& shader, float time,
        glm::mat4 parentModel = glm::mat4(1.0f)
    );
};
struct Info {
    Mesh* floorMesh;
    unsigned int infoTex;

    Info(Mesh& fMesh, unsigned int ifTex);
    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};

struct Barrier {
    Mesh* cylinderMesh;
    Mesh* sphereMesh;
    unsigned int baseTex;

    Barrier(Mesh& cyMesh, Mesh& spMesh, unsigned int baTex);

    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};

struct Stand {
    Mesh* cubeMesh;
    Info* infoMesh;
    unsigned int baseTex;

    Stand(Mesh& cMesh,Info& ifMesh, unsigned int bTex);

    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};

#endif