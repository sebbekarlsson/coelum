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

extern unsigned int SHADER_TEXTURED;

config_T* CONFIG;
window_state_T* WINDOW_STATE;
keyboard_state_T* KEYBOARD_STATE;
mouse_state_T* MOUSE_STATE;
theatre_T* THEATRE;

volatile unsigned int RUNNING;

const GLubyte* vendor;
const GLubyte* renderer;
const GLubyte* version;

void coelum_init()
{
    printf("Coelum is being initialized...\n");

    CONFIG = init_config();
    load_config_from_file_if_exists(CONFIG);

    WINDOW_STATE = setup_graphical_window(RES_WIDTH, RES_HEIGHT);

    THEATRE = init_theatre();
    register_shader_programs(THEATRE->shader_manager);
    register_textures(THEATRE->texture_manager);

    KEYBOARD_STATE = init_keyboard_state();
    glfwSetKeyCallback(WINDOW_STATE->window, key_callback);
    glfwSetCharCallback(WINDOW_STATE->window, character_callback);

    MOUSE_STATE = init_mouse_state();
    glfwSetCursorPosCallback(WINDOW_STATE->window, cursor_position_callback);

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
    window_state_free(WINDOW_STATE);

    printf("Freeing configuration object...\n");
    config_free(CONFIG);

    printf("Running glfwTerminate...\n");
    glfwTerminate();
}

int coelum_main(int argc, char* argv[])
{
    RUNNING = 1;

    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
    GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    // The texture we're going to render to
    GLuint renderedTexture;
    glGenTextures(1, &renderedTexture);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, RES_WIDTH, RES_HEIGHT, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    GLuint depthrenderbuffer;
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, RES_WIDTH, RES_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return 1;
    
    while(!glfwWindowShouldClose(WINDOW_STATE->window) && THEATRE->scene_manager->scenes->size > 0 && RUNNING)
    {
        if (THEATRE->scene_manager->scene_index == -1)
            scene_manager_next(THEATRE->scene_manager);

        scene_T* scene = scene_manager_get_current_scene(THEATRE->scene_manager);
        state_T* state = (state_T*) scene;

        MOUSE_STATE->dx = 0.0f;
        MOUSE_STATE->dy = 0.0f;

        glfwPollEvents();

        MOUSE_STATE->button_left = glfwGetMouseButton(WINDOW_STATE->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        MOUSE_STATE->button_right = glfwGetMouseButton(WINDOW_STATE->window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

        glfwSetInputMode(WINDOW_STATE->window, GLFW_CURSOR, MOUSE_STATE->input_mode);

        // Render to our framebuffer
        glUseProgram(SHADER_TEXTURED);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName); 

        glViewport(0, 0, RES_WIDTH, RES_HEIGHT);
        glClearColor(scene->bg_r / 255.0f, scene->bg_g / 255.0f, scene->bg_b / 255.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        theatre_tick(THEATRE);
        theatre_draw(THEATRE); 

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(
            0,
            0,
            RES_WIDTH,
            RES_HEIGHT,
            WINDOW_STATE->blit_start_x,
            WINDOW_STATE->blit_start_y,
            WINDOW_STATE->blit_start_x + WINDOW_STATE->blit_w,
            WINDOW_STATE->blit_start_y + WINDOW_STATE->blit_h, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST
        );
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glfwSwapBuffers(WINDOW_STATE->window);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // reset character
        KEYBOARD_STATE->character = 0;
    }

    coelum_terminate();

    return 0;
}
