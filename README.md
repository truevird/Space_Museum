# 우주 박물관(Space_Museum)

OpenGL(3D)을 이용해 구현한 인터랙티브 가상 우주 박물관 프로젝트입니다. 태양계 공전/자전 시뮬레이션부터 정교한 우주 장비 메쉬 렌더링 및 애니메이션이 포함되어 있습니다.

## 주요 기능 및 전시관 안내

### 1. 메인 중앙 광장(Main Stage)
- 전체 박물관의 뼈대를 이루는 대리석 바닥 및 사방 벽면 배치
- 다중 광원(Multi-Lighting) 처리를 통한 입체적인 조명 효과

### 2. 태양계 시뮬레이션 전시관(Solar System)
- 태양을 중심으로 수성, 금성, 지구(달), 화성, 목성, 토성, 천왕성, 해왕성 구현
- **토성(Saturn) 고리 메쉬 특수 렌더링** 및 자전축 기울기 연산 반영
- 각 행성별 실제 고유 자전/공전 속도 비율 애니메이션 구현

### 3. 우주 장비 및 탐사선 전시관
- **인공위성 (Satellite):** 본체, 반복 루프 기반 태양광 패널, 안테나 및 콘 메쉬 조합
- **화성 탐사 로봇 (Mars Rover):** 실시간 지형 스캔 마스트 애니메이션 및 드릴 회전 연산 기믹
- **우주왕복선 (Space Shuttle):** 메인 동체, 주 날개 및 꼬리날개, OMS 포드 및 조종석 구체 결합 렌더링

---

## 개발 환경 및 개발 스택
- **Language:** C++
- **Graphics API:** OpenGL 3.3 (Core Profile)
- **Window Management:** GLFW
- **OpenGL Extension Loader:** GLAD
- **Mathematics:** GLM (OpenGL Mathematics)
- **Image Loading:** stb_image

---

## 조작 방법
- **카메라 이동:** `W`, `A`, `S`, `D` (앞, 왼쪽, 뒤, 오른쪽)
- **수직 이동:** `SPACE` (상승), `LEFT_CONTROL` (하강)
- **시선 전환:** `마우스 왼쪽 버튼 클릭 상태`로 드래그 (Free 카메라 뷰)
- **줌 인/아웃:** 마우스 `스크롤 휠`
- **프로그램 종료:** `ESC`

---

## License
본 프로젝트는 **MIT License** 하에 자유롭게 배포 및 수정이 가능합니다. 상세 내용은 `LICENSE` 파일을 참조하세요.