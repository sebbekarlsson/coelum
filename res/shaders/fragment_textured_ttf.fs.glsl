#version 330 core
out vec4 FragColor;
  
in vec4 ourColor;
varying vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(ourTexture, TexCoord).r);
    gl_FragColor = vec4(vec3(1, 1, 1), 1.0) * sampled;

}
