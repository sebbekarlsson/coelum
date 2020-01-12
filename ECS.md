# Entity Component System
> Coelum has a built-in Entity Component System.
> Below is an example on how to use it:
```C
#include <coelum/actor.h>
#include <coelum/component.h>


void component_movement_tick(component_T* component, actor_T* actor)
{
    actor->dx += 0.1f;

    physics_tick_actor(actor);
}

component_T* init_component_movement()
{                                          // tick                   draw
    component_T* component = init_component(component_movement_tick, (void*)0);

    return component;
}

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

// adding a component to the actor
actor_add_component(a, init_component_movement());
```
> So to initialize a component, the method is as follows:
```C
init_component(tick_function, draw_function);
```
> The definition of the tick and draw methods
> looks like [this](src/include/component.h).
