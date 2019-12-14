#include <coelum/main.h>
#include <coelum/scene.h>
#include <coelum/theatre.h>
#include <coelum/constants.h>
#include <coelum/scene.h>
#include <coelum/actor.h>


extern theatre_T* THEATRE;

#ifndef GL_RGBA
#define GL_RGBA 0x1908
#endif

scene_T* init_scene_main()
{
    // creating a scene                          tick        draw     (2 dimensions)
    scene_T* s = scene_constructor(init_scene(), (void*) 0, (void*) 0, 2);
    s->bg_r = 154;
    s->bg_g = 55;
    s->bg_g = 200;

    // creating an actor
    actor_T* a = actor_constructor(
        init_actor(),
        (640 / 2) - 32,
        (480 / 2) - 32,
        0.0f,
        (void*) 0, // tick method
        (void*) 0, // draw method
        "cherry"
    );
    a->width = 64;
    a->height = 64;
    a->sprite = init_sprite_from_file("cherry.png", GL_RGBA, 1.0f, a->width, a->height); 
   
    // adding the actor to the scene 
    dynamic_list_append(((state_T*)s)->actors, a);

    return s;
} 

int main(int argc, char* argv[])
{
    coelum_init();

    scene_manager_register_scene(THEATRE->scene_manager, (scene_T*) init_scene_main());

    return coelum_main(argc, argv);
}
