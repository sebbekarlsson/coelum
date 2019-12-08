#include <stdio.h>
#include "include/main.h"
#include "include/constants.h"
#include "include/config.h"
#include "include/window.h"
#include "include/input.h"
#include "include/theatre.h"
#include "include/shader_registry.h"
#include "include/texture_manager.h"
#include "include/texture_registry.h"
#include "include/sound.h"


extern volatile unsigned int window_width;
extern volatile unsigned int window_height;

config_T* CONFIG;
keyboard_state_T* KEYBOARD_STATE;
mouse_state_T* MOUSE_STATE;
theatre_T* THEATRE;

GLFWwindow* window = (void*) 0;
volatile unsigned int RUNNING;

const GLubyte* vendor;
const GLubyte* renderer;
const GLubyte* version;

void coelum_init()
{
    printf("Coelum is being initialized...\n");

    CONFIG = init_config();
    load_config_from_file_if_exists(CONFIG);

    window = setup_graphical_window(RES_WIDTH, RES_HEIGHT);

    THEATRE = init_theatre();
    register_shader_programs(THEATRE->shader_manager);
    register_textures(THEATRE->texture_manager);

    KEYBOARD_STATE = init_keyboard_state();
    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, character_callback);

    MOUSE_STATE = init_mouse_state();
    glfwSetCursorPosCallback(window, cursor_position_callback);

    vendor = glGetString(GL_VENDOR);
    renderer = glGetString(GL_RENDERER);
    version = glGetString(GL_VERSION);

    printf("Vendor: %s\n", vendor);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL Version: %s\n", version);

    printf("Coelum was initialized.\n");
}

void coelum_terminate()
{
    RUNNING = 0;

    printf("Coelum is being terminated, deallocating memory...\n");

    printf("Freeing KEYBOARD_STATE...\n");
    keyboard_state_free(KEYBOARD_STATE);

    printf("Freeing MOUSE_STATE...\n");
    mouse_state_free(MOUSE_STATE);

    printf("Freeing THEATRE...\n");
    theatre_free(THEATRE);

    printf("Destroying window...\n");
    glfwDestroyWindow(window);

    printf("Freeing configuration object...\n");
    config_free(CONFIG);

    printf("Running glfwTerminate...\n");
    glfwTerminate();
}

int coelum_main(int argc, char* argv[])
{
    RUNNING = 1;

    GLuint renderBuffer;
    GLuint frameBuffer;
    GLuint depthRenderBuffer;

    // https://community.khronos.org/t/render-to-renderbuffer-with-depth-test/63793/3

    glGenRenderbuffers( 1, &renderBuffer );
    glBindRenderbuffer( GL_RENDERBUFFER, renderBuffer );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_RGB32F, RES_WIDTH, RES_HEIGHT );
    // TODO: check for errors here

    glGenRenderbuffers( 1, &depthRenderBuffer );
    glBindRenderbuffer( GL_RENDERBUFFER, depthRenderBuffer );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, RES_WIDTH, RES_HEIGHT );
    // TODO: check for errors here

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );

    while(!glfwWindowShouldClose(window) && THEATRE->scene_manager->scenes->size > 0 && RUNNING)
    {
        if (THEATRE->scene_manager->scene_index == -1)
            scene_manager_next(THEATRE->scene_manager);

        scene_T* scene = scene_manager_get_current_scene(THEATRE->scene_manager);
        state_T* state = (state_T*) scene;

        MOUSE_STATE->dx = 0.0f;
        MOUSE_STATE->dy = 0.0f;

        glfwPollEvents();

        MOUSE_STATE->button_left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        MOUSE_STATE->button_right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

        glfwSetInputMode(window, GLFW_CURSOR, MOUSE_STATE->input_mode);

        glViewport(0, 0, 640, 480);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glClearColor(scene->bg_r / 255.0f, scene->bg_g / 255.0f, scene->bg_b / 255.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        theatre_tick(THEATRE);
        theatre_draw(THEATRE);

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(
        0, 0, RES_WIDTH, RES_HEIGHT,
        0, 0, window_width, window_height,
        GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);

        glfwSwapBuffers(window);

        // reset character
        KEYBOARD_STATE->character = 0;
    }

    coelum_terminate();

    return 0;
}
