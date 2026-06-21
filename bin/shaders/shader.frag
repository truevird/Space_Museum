#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in vec4 FragPosLightSpace;

uniform sampler2D ourTexture;
uniform sampler2D shadowMap; 

#define NUM_LIGHTS 5
uniform vec3 lightPos[NUM_LIGHTS];
uniform vec3 lightColor[NUM_LIGHTS];

uniform bool useLighting;
uniform bool useColor;
uniform vec3 overrideColor;
uniform float alpha;

// 그림자 값 계산 함수
float ShadowCalculation(vec4 fragPosLightSpace, vec3 norm, vec3 lightDir) {
    // 원근 분할
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // [-1, 1] 범위를 [0, 1] 범위로 변환
    projCoords = projCoords * 0.5 + 0.5;
    
    if(projCoords.z > 1.0) return 0.0; // 조명 가시범위 밖은 그림자 제외

    float currentDepth = projCoords.z;
    
    // 가변 바이어스 계산(그림자Acne 방지)
    float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
    
    // PCF 부드러운 그림자 경계 처리
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    return shadow;
}

void main() {
    vec3 texColor = texture(ourTexture, TexCoord).rgb;
    vec3 baseColor = useColor ? overrideColor : texColor;
    
    if (!useLighting) {
        FragColor = vec4(baseColor, alpha);
        return; 
    } 

    vec3 norm = normalize(Normal);
    vec3 totalAmbient = vec3(0.0);      
    vec3 totalDiffuse = vec3(0.0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
        if (FragPos.x > 20.0) {
            if (i == 4) {
                float ambientStrength = 0.2; 
                totalAmbient += ambientStrength * lightColor[i];

                vec3 lightDir = normalize(lightPos[i] - FragPos);
                float diff = max(dot(norm, lightDir), 0.0);
                
                if (length(lightPos[i] - FragPos) < 3.0) {
                    //태양 본체
                    totalDiffuse += 1.0 * lightColor[i] * 0.4; 
                } 
                else {
                    //주변 행성
                    // 행성 앞면은 기존 밝기 배율유지
                    float diff = max(dot(norm, lightDir), 0.0);
                    totalDiffuse += diff * lightColor[i] * 1.0; 
                }
            }
            continue; 
        }

        if (i == 4) continue;

        float ambientStrength = 0.03;
        totalAmbient += ambientStrength * lightColor[i];

        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        
        if(i == 0) {
            float shadow = ShadowCalculation(FragPosLightSpace, norm, lightDir);
            totalDiffuse += (1.0 - shadow) * diff * lightColor[i] * 0.3;
        } else {
            totalDiffuse += diff * lightColor[i] * 0.3;
        }
    }
    vec3 result = (totalAmbient + totalDiffuse) * baseColor;
    FragColor = vec4(result, 1.0);
}