#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec3 normal;
varying vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec3 nn = normalize(normal);

    vec4 shade = vec4(nn[0], nn[0], nn[0], 0.03);

    FragColor = texture2D(ourTexture, TexCoord) * (vec4(ourColor, 1) + shade);
}
