/* licensed under GPL v3.0 see https://github.com/ZDev22/ZEngine/blob/main/LICENSE for current license */

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 199309L

#define SPRITES 500

/* ZENGINE */
#define ZENGINE_IMPLEMENTATION
#define ZENGINE_DEPS_DEFINED
#define ZENGINE_DISABLE_VSYNC
#define ZENGINE_MAX_FRAMES_IN_FLIGHT 1
#define ZENGINE_MAX_SPRITES SPRITES * SPRITES
#define ZENGINE_MATRIXMODE_MANUAL
#define ZENGINE_MAX_TEXTURES 2
#include "zengine.h"

/* RGFW */
#define RGFW_IMPLEMENTATION
#define RGFW_VULKAN
#define RGFW_EXPORT
#define RGFW_ASSERT(x) (void)(x)

/* STB_IMAGE */
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT

/* DEPENDENCIES */
#include "deps/RGFW.h"
#include "deps/stb_image.h"

#undef RGFW_IMPLEMENTATION
#undef STB_IMAGE_IMPLEMENTATION

#include <time.h>

unsigned int fps = 0;
float appTimer = 0.f;
clock_t fpsTime;
clock_t fpsLastTime;
struct timespec ts;

int main() {
    /* init engine */
    zwindow = RGFW_createWindow("loading", 0, 0, 1920, 1080, (u64)0);
    ZEngineInit();

    float y = -1.f;
    float x = -1.f;
    for (unsigned int i = 1; i < SPRITES * SPRITES + 1; i++) {
        createSprite(squareModel, 0, x, y, .05f, .05f, 0.f);
        setRotationMatrix(&sprites[spritesSize - 1]);
        x += .05f;
        if (i % SPRITES == SPRITES - 1) {
            y += .05f;
            x = -1.f;
        }
    }

    fpsLastTime = clock();
    while (1) {
        /* calculate fps */
        fpsTime = clock();
        deltaTime = (double)(fpsTime - fpsLastTime) / CLOCKS_PER_SEC;
        fpsLastTime = fpsTime;
        appTimer += deltaTime;

        if (appTimer > 1.f) {
            char name[64];
            snprintf(name, 64, "fps: %d", fps);
            RGFW_window_setName(zwindow, name);
            appTimer = 0.f;
            fps = 0;
        }
        fps++;

        /* poll window events */
        RGFW_event event;
        while (RGFW_window_checkEvent(zwindow, &event)) {
            if (event.type == RGFW_windowResized) {
                framebufferResized = 1;
                break;
            }
            else if (event.type == RGFW_quit) {
                RGFW_window_close(zwindow);
                zwindow = NULL;
                ZEngineDeinit();
                exit(0);
            }
        }

        if (RGFW_isKeyDown(RGFW_w)) camera.position[1] += 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_s)) camera.position[1] -= 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_d)) camera.position[0] -= 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_a)) camera.position[0] += 1.f * deltaTime;

        ZEngineRender();
    }
}

