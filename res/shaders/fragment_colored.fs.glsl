#version 330 core
out vec4 FragColor;
  
in vec4 ourColor;
in vec3 pos;
varying vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = ourColor;
    //gl_FragDepth = pos[2];
}
