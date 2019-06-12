#include "include/scene.h"
#include "include/constants.h"
#include "include/actor.h"
#include "include/draw_utils.h"
#include <string.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


extern unsigned int SHADER_DEFAULT;

/**
 * Creates a new scene.
 * (This function is abstract and should not be used)
 *
 * @return scene_T*
 */
scene_T* init_scene()
{
    return (scene_T*) calloc(1, sizeof(struct SCENE_STRUCT));
}

/**
 * Scene constructor, structs that inherit from scene should use this in their
 * initialization method.
 *
 * @param scene_T* s
 *
 * @return scene_T*
 */
scene_T* scene_constructor(scene_T* scene,  void (*tick)(scene_T* self), void (*draw)(scene_T* self), unsigned int dimensions)
{
    state_constructor((state_T*) scene, WINDOW_WIDTH, WINDOW_HEIGHT, dimensions);

    scene->tick = tick;
    scene->draw = draw;

    scene->bg_r = 255.0f;
    scene->bg_g = 255.0f;
    scene->bg_b = 255.0f; 
}

/**
 * Default scene tick method.
 *
 * @param scene_T* s
 */
void scene_tick(scene_T* scene)
{
}

/**
 * Default scene draw method.
 *
 * @param scene_T* scene
 */
void scene_draw(scene_T* scene)
{
}
