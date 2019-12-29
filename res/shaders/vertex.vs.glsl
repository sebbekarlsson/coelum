/*#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
*/
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in float atextureShiftX;
layout (location = 5) in float atextureShiftY;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 normal;
out vec3 pos;
flat out int textureShiftX;
flat out int textureShiftY;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    pos = aPos;
    ourColor = aColor;
    TexCoord = aTexCoord;
    normal = aNormal;
    textureShiftX = int(ceil(atextureShiftX));
    textureShiftY = int(ceil(atextureShiftY));
}
