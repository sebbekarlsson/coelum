# Coelum
> Game engine in pure C.

## How it works
> The engine is built upon `5` different parts:

### [You (Zeus)](/)
> You are the god.

### [The Parser (Hermes)](./hermes)
> The parser is used for multiple things, for example the built in hermes
> language that you can use to define behavior of actors.

### [The Core (Coelum)](./coelum)
> The foundation, game loop, input management, drivers, etc...

### [The GUI (Apollon)](./apollon)
> The graphical user interface, use it to design actors, levels, etc...
> This one actually uses the [The Core](./src) to power it self.

### [The Launcher (Leto)](./leto)
> The launcher is used to run your games.

## Installing The Parser (Hermes)
> To install Hermes, just run this:

    cd hermes
    make && sudo make install

## Installing The Core (Coelum)
> To install the core, just run this:

    cd coelum
    make && sudo make install

## Installing The GUI (Apollon)
> To get Apollon up and running, just run this:

    cd apollon
    make && ./apollon.out

## Using The Core
> Here is the minimal required code to get a game up and running using only
> the core:
```C
#include <coelum/main.h>
#include <coelum/scene.h>
#include <coelum/theatre.h>
#include <coelum/constants.h>
#include <coelum/scene.h>


extern theatre_T* THEATRE;

void scene_main_tick(state_T* self)
{
    scene_tick((scene_T*) self);
}

void scene_main_draw(state_T* self)
{
    scene_draw((scene_T*) self);
}

typedef struct SCENE_MAIN_STRUCT {
    scene_T base;
} scene_main_T;

scene_main_T* init_scene_main()
{
    scene_main_T* s_main = calloc(1, sizeof(struct SCENE_MAIN_STRUCT));
    scene_T* s = (scene_T*) s_main;

    scene_constructor(s, scene_main_tick, scene_main_draw);

    s->bg_r = 48.0f;
    s->bg_g = 48.0f;
    s->bg_b = 48.0f;

    return s_main;
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
gcc main.c -lcoelum -lglfw -lm -ldl -lpthread -lopenal
```

## Story
> This game engine was originally a pong game, the engine was later separated
> from the game, and the game was separated from the engine.  
> The pong game can be found here: [https://github.com/sebbekarlsson/cpong](https://github.com/sebbekarlsson/cpong)

## Requirements (Debian)
> Install these:

    apt-get install libglfw3-dev

    pip install --upgrade git+https://github.com/dav1dde/glad.git#egg=glad

    glad --generator=c --extensions=GL_EXT_framebuffer_multisample,GL_EXT_texture_filter_anisotropic --out-path=GL
