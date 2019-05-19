# Coelum
> Game engine in pure C.

## Story
> This game engine was originally a pong game, the engine was later separated
> from the game, and the game was separated from the engine.  
> The pong game can be found here: [https://github.com/sebbekarlsson/cpong](https://github.com/sebbekarlsson/cpong)

## Requirements (Debian)
> Install these:

    apt-get install libglfw3-dev

    pip install --upgrade git+https://github.com/dav1dde/glad.git#egg=glad

    glad --generator=c --extensions=GL_EXT_framebuffer_multisample,GL_EXT_texture_filter_anisotropic --out-path=GL
