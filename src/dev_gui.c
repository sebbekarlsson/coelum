#include "include/dev_gui.h"
#include "include/render.h"
#include "include/scene_manager.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


extern scene_manager* SCENE_MANAGER;
extern unsigned int SHADER_COLORED;


void dev_gui_tick()
{
}

void dev_gui_draw()
{
    // scene* s = scene_manager_get_current_scene(SCENE_MANAGER);
    // render_2D_positioned_2D_mesh(0.0f, 480 / 2, 640.0f, 24.0f, 255.0f, 0.0f, 0.0f, s->VAO, s->pv);
}
