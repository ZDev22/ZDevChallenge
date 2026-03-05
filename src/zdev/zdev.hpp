#pragma once

#define SPRITES 500

#include "zengine.hpp"
#include "deps/RGFW.h"

struct Game {
    Game(Camera& camera) : camera(camera) {
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
    }
    void tick() {
        if (RGFW_isKeyDown(RGFW_w)) camera.position[1] += 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_s)) camera.position[1] -= 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_d)) camera.position[0] -= 1.f * deltaTime;
        if (RGFW_isKeyDown(RGFW_a)) camera.position[0] += 1.f * deltaTime;
    }

private:
    Camera& camera;
};
