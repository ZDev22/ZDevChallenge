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

/* APPS */
#include "zdev.hpp"

/* STD */
#include <thread>

#ifndef ZENGINE_DISABLE_VSYNC
    #define FPS_CAP 60.f
#endif
   
/* vars for calculating fps and deltaTime */
int fps = 0;
float appTimer = 0.f;
float appWait = 0.f;
std::chrono::high_resolution_clock::time_point fpsTime;
std::chrono::high_resolution_clock::time_point fpsLastTime;

void render();
int main() {
    #ifdef FPS_CAP
        deltaTime = 1.f / FPS_CAP;
    #endif

    /* init engine */
    windowdata = RGFW_createWindow("zdevchallenge", 0, 0, 1920, 1080, (u64)0);
    ZEngineInit();
    Game game{camera};

    while (true) {
        /* calculate fps */
        #ifdef FPS_CAP
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(((1.f / FPS_CAP) * 1000) - appWait)));
            fpsTime = std::chrono::high_resolution_clock::now();
            appTimer += 1.f / FPS_CAP;
        #else
            fpsTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<float>(fpsTime - fpsLastTime).count();
            appTimer += deltaTime;
            fpsLastTime = fpsTime;
        #endif
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

        game.tick();

        #ifdef FPS_CAP
            fpsLastTime = std::chrono::high_resolution_clock::now();
            appWait = std::chrono::duration<float>(fpsLastTime - fpsTime).count();
        #endif

        ZEngineRender();
    }
}
