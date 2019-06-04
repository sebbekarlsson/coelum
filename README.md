# Coelum
> Glorious Game Engine for divine intellects, written in pure C.
![screenshot](fps.png)

## The important parts
> There are `5` important parts that make up for this software, which is:  
> *Zeus (you)*,  
[Coelum (the core)](./coelum),  
[Apollon (the GUI)](https://github.com/sebbekarlsson/apollon),  
[Leto (the launcher)](./leto),  
[Hermes (the language)](https://github.com/sebbekarlsson/hermes)

## The Core (Coelum)
> The foundation, game loop, input management, drivers, etc...
### Installing Coelum
> To install the core, just run this:

    cd coelum
    make && sudo make install

## Using The Core
> Here is the minimal required code to get a game up and running using only
> the core:
```C
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
    a->texture = get_texture("cherry.png", GL_RGBA)->renderable_texture; 
   
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
```
> Paste the code into a `main.c` file, and compile it like this:
```bash
gcc main.c -lcoelum -lglfw -lm -ldl -lpthread -lopenal -laudio
```
> (Note, make sure you have a `cherry.png` file where you run the code).  
> Then run it:
```bash
./a.out
```
> You should now see something like this:
![screenshot](image.png)

## Story
> This game engine was originally a pong game, the engine was later separated
> from the game, and the game was separated from the engine.  
> The pong game can be found here: [https://github.com/sebbekarlsson/cpong](https://github.com/sebbekarlsson/cpong)

## Requirements (Debian)
> Install these:

    apt-get install libglfw3-dev libaudio-dev

    pip install --upgrade git+https://github.com/dav1dde/glad.git#egg=glad

    glad --generator=c --extensions=GL_EXT_framebuffer_multisample,GL_EXT_texture_filter_anisotropic --out-path=GL
