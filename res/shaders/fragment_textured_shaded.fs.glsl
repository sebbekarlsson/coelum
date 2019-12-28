#version 330 core
out vec4 FragColor;
  
in vec4 ourColor;
in vec3 normal;
in float textureShiftX;
in float textureShiftY;

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
    float brightnessMod = 0.0f;

    for (int i = 0; i < number_of_lights; i+=3)
    {
        vec3 lightpos = vec3(light_positions[i], light_positions[i + 1], light_positions[i + 2]);
        vec3 lightVector = vec3(normalize(normal) - lightpos);

        float dist = distance(world_pos, lightpos);
        float angle = acos(dot(normalize(lightVector), normalize(normal)));
        float darkness = min((smoothstep(0.0, PI / 2.0, angle) * MAX_DARKNESS) + (dist * 0.01), MAX_DARKNESS);

        brightnessMod += 1.0 - darkness;
    }

    vec4 shade = vec4(brightnessMod, brightnessMod, brightnessMod, SHADE_OPACITY);

    int width = atlas_width;

    if (width == 0)
        width += 1;

    int height = atlas_height;

    if (height == 0)
        height += 1;

    int x = int(textureShiftX);
    int y = int(textureShiftY);

    float scalarX = 1.0 / width;
    float scalarY = 1.0 / height;

    FragColor = vec4(1.0) * texture2D(ourTexture, vec2((TexCoord.x + x) * scalarX,  (TexCoord.y * scalarY) + y * scalarY)) * (ourColor + shade);

    //FragColor = texture2D(ourTexture, vec2(TexCoord.x - 16, TexCoord.y)) * (ourColor + shade);
}
