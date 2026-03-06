/* licensed under GPL v3.0 see https://github.com/ZDev22/ZEngine/blob/main/LICENSE for current license

#define FPS_CAP 60.f // set the framerate, dont define for no FPS cap
*/

/* ZENGINE */
#define ZENGINE_IMPLEMENTATION
#define ZENGINE_DEPS_DEFINED
#define ZENGINE_DISABLE_AUDIO
#define ZENGINE_DISABLE_VSYNC
#define ZENGINE_MAX_SPRITES 1000000
#define ZENGINE_MAX_TEXTURES 1
#include "zengine.hpp"

/* STD */
#include <thread>

#define SPRITES 1000 /* SPRITES * SPRITES = sprites on screen*/
   
/* vars for calculating fps and deltaTime */
int fps = 0;
float appTimer = 0.f;
float appWait = 0.f;
std::chrono::high_resolution_clock::time_point fpsTime;
std::chrono::high_resolution_clock::time_point fpsLastTime;

int main() {
    /* init engine */
    windowdata = RGFW_createWindow("zdevchallenge", 0, 0, 1920, 1080, (u64)0);
    ZEngineInit();

    /* init sprites */
    float x = -1.f;
    float y = -1.f;
    for (unsigned int i = 0 ; i < SPRITES; i++) {
        for (unsigned int j = 0; j < SPRITES; j++) {
            createSprite(squareModel, 0, x, y, .1f, .1f, 0.f);
            x += .02f;
        }
        x = -1.f;
        y += .02f;
    }

    while (true) {
        fpsTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(fpsTime - fpsLastTime).count();
        appTimer += deltaTime;
        fpsLastTime = fpsTime;

        if (appTimer > 1.f) {
            RGFW_window_setName(windowdata, ("fps: " + std::to_string(fps)).c_str());
            appTimer = 0.f;
            fps = 0;
        }
        fps++;

        /* poll window events */
        RGFW_event event;
        while (RGFW_window_checkEvent(windowdata, &event)) {
            if (event.type == RGFW_windowResized) framebufferResized = true;
            else if (event.type == RGFW_quit) {
                RGFW_window_close(windowdata);
                ZEngineDeinit();
                return 0;
            }
        }

        if (RGFW_isKeyDown(RGFW_w)) camera.position[1] += 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_s)) camera.position[1] -= 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_d)) camera.position[0] -= 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_a)) camera.position[0] += 1.f * deltaTime;

        ZEngineRender();
    }
}
