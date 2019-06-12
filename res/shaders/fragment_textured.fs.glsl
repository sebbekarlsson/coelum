#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
varying vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    //FragColor = texture2D(ourTexture, TexCoord);

    FragColor = texture2D(ourTexture, TexCoord) * vec4(ourColor, 1);

}
