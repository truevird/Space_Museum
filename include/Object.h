#ifndef OBJECTS_H
#define OBJECTS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "Shader.h"

// 1. 전시관 구조체
struct Stage {
    Mesh* floorMesh;
    Mesh* cubeMesh;
    unsigned int floorTex;
    unsigned int wallTex;

    Stage(Mesh& fMesh, Mesh& cMesh, unsigned int fTex, unsigned int wTex);
    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};

struct SmallExhibit {
    Mesh* cubeMesh;
    unsigned int innerTex;  // 안쪽 텍스처
    unsigned int outerTex;  // 바깥쪽 텍스처

    SmallExhibit(Mesh& cMesh, unsigned int iTex, unsigned int oTex);
    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};
struct EarthExhibit {
    Mesh* cubeMesh;
    unsigned int innerTex;  // 안쪽 텍스처
    unsigned int outerTex;
    unsigned int floorTex;  // 바깥쪽 텍스처

    EarthExhibit(Mesh& cMesh, unsigned int iTex, unsigned int fTex, unsigned int oTex);
    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};
struct MarsExhibit {
    Mesh* cubeMesh;
    unsigned int innerTex;  // 안쪽 텍스처
    unsigned int outerTex;
    unsigned int floorTex;  // 바깥쪽 텍스처

    MarsExhibit(Mesh& cMesh, unsigned int iTex, unsigned int fTex, unsigned int oTex);
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
    EarthMoonSystem* earthMoon;
    unsigned int solarTex;
    unsigned int mercuryTex;
    unsigned int venusTex;
    unsigned int marsTex;
    unsigned int jupiterTex;
    unsigned int saturnTex;
    unsigned int uranusTex;
    unsigned int neptuneTex;

    SolarSystem(Mesh& mesh, Mesh& rMesh, EarthMoonSystem& emSystem, unsigned int sTex, unsigned int meTex, unsigned int vTex, unsigned int maTex, unsigned int jTex, unsigned int saTex, unsigned int uTex, unsigned int nTex);
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
    void draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f));
};

// 5.화성탐사로봇
struct MarsRover {
    Mesh* cubeMesh;
    Mesh* cylinderMesh;
    Mesh* sphereMesh;

    unsigned int bodyTex;
    unsigned int wheelTex;
    unsigned int darkTex;

    MarsRover(
        Mesh& cuMesh,
        Mesh& cyMesh,
        Mesh& spMesh,
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

//우주왕복선
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
        Shader& shader,
        glm::mat4 parentModel = glm::mat4(1.0f)
    );
};

#endif