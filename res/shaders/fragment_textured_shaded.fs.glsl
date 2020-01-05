#version 330 core
out vec4 FragColor;
  
in vec4 ourColor;
in vec3 normal;
in vec3 fragPos;
flat in int textureShiftX;
flat in int textureShiftY;

varying vec2 TexCoord;

uniform sampler2D ourTexture;

uniform int number_of_lights;

uniform int atlas_width;
uniform int atlas_height;

uniform vec3 light_positions;
uniform vec3 world_pos;

#define PI 3.1415926535897932384626433832795
#define MAX_DARKNESS 1.6f
#define SHADE_OPACITY 0.003f

void main()
{
    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightColor = vec3(1, 1, 1);
    vec3 lightPos = vec3(-128, -128, -10);
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor; 

    vec3 result = (ambient + diffuse) * objectColor;

    int width = atlas_width;

    if (width == 0)
        width += 1;

    int height = atlas_height;

    if (height == 0)
        height += 1;

    int x = textureShiftX;
    int y = textureShiftY;

    float scalarX = 1.0 / width;
    float scalarY = 1.0 / height;

    FragColor = (texture2D(ourTexture, vec2((TexCoord.x + x) * scalarX,  (TexCoord.y * scalarY) + y * scalarY)) * (ourColor)) * vec4(result, 1.0f);

    //FragColor = texture2D(ourTexture, vec2(TexCoord.x - 16, TexCoord.y)) * (ourColor + shade);
}
