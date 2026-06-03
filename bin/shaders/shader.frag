#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;
#define NUM_LIGHTS 5
uniform vec3 lightPos[NUM_LIGHTS];
uniform vec3 lightColor[NUM_LIGHTS];

uniform bool useLighting;

void main()
{
    
    vec3 texColor = texture(ourTexture, TexCoord).rgb;
    
    if (!useLighting) 
        {
            FragColor = vec4(texColor, 1.0);
            return; // 여기서 함수를 종료하여 아래 조명 연산을 수행하지 않습니다.
        } 

    vec3 norm = normalize(Normal);
    
    // 최종 색상을 누적할 변수
    vec3 totalAmbient = vec3(0.0);      
    vec3 totalDiffuse = vec3(0.0);

    // 각 광원에 대해 반복문 수행
    for(int i = 0; i < NUM_LIGHTS; i++)
    {
        // 1. Ambient
        float ambientStrength = 0.03; 
        totalAmbient += ambientStrength * lightColor[i];

        // 2. Diffuse
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        totalDiffuse += diff * lightColor[i] * 0.3;
    }

    vec3 result = (totalAmbient + totalDiffuse) * texColor;
    FragColor = vec4(result, 1.0);
}