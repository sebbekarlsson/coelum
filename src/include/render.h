#ifndef PONG_RENDER_H
#define PONG_RENDER_H
void render_2D_mesh(float width, float height, float r, float g, float b, unsigned int VBO, unsigned int EBO);

void render_2D_positioned_2D_mesh(float x, float y, float width, float height, float r, float g, float b, unsigned int VAO);
#endif
