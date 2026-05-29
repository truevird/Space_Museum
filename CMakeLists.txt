cmake_minimum_required(VERSION 3.10)
project(Space_Museum)

set(CMAKE_CXX_STANDARD 17)

# 바이너리 출력 디렉토리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 1. 헤더 파일(.h) 검색 경로 추가 (내 프로젝트 헤더 + 외부 라이브러리 헤더)
include_directories(include)
include_directories(libs/glad/include)
include_directories(libs/glfw/include)
include_directories(libs/glm)
include_directories(libs/stb_image)

# 2. 컴파일할 소스 파일 목록을 SOURCE에 저장
set(SOURCES
    src/main.cpp
    src/Mesh.cpp
    src/object.cpp
    src/stb_image.cpp
    libs/glad/src/glad.c
)

add_executable(Space_Museum ${SOURCES})#생성할 실행파일 이름 + 컴파일할 소스 파일 목록 -> 생성

# ---------------------------------------------------------------------
#GLFW 라이브러리 파일 경로 지정(vs2022)
set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/libs/glfw/lib-vc2022")

# 해당 폴더 안의 정적 라이브러리 파일(glfw3.lib)의 절대 경로 지정
set(GLFW_LIBRARY "${GLFW_LIB_DIR}/glfw3.lib") 
# ---------------------------------------------------------------------

# 4. 라이브러리 링크
# 운영체제 기본 OpenGL 라이브러리 찾기
find_package(OpenGL REQUIRED)

# 내가 폴더에 넣은 glfw3와 OS의 OpenGL을 내 프로젝트에 연결
target_link_libraries(Space_Museum PRIVATE ${GLFW_LIBRARY} OpenGL::GL)

# 5. 에셋 복사 (bin 폴더 안의 shaders와 textures를 bin/Debug 폴더로 복사)
file(COPY ${CMAKE_SOURCE_DIR}/bin/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/bin/textures DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
