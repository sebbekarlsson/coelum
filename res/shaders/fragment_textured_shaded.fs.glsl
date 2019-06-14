#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec3 normal;

varying vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec3 lightpos;

#define PI 3.1415926535897932384626433832795

void main()
{
    vec3 lightVector = vec3(normal-lightpos);
    float angle = acos(dot(normalize(lightVector),normalize(normal)));
    float brightnessMod = 1.0 - (smoothstep(0.0, PI / 2.0, angle) * 1.6f);


    vec4 shade = vec4(brightnessMod, brightnessMod, brightnessMod, 0.03);

    FragColor = texture2D(ourTexture, TexCoord) * (vec4(ourColor, 1) + shade);
}
