#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec3 normal;

varying vec2 TexCoord;

uniform sampler2D ourTexture;

uniform int number_of_lights;

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

    FragColor = texture2D(ourTexture, TexCoord) * (vec4(ourColor, 1) + shade);
}
