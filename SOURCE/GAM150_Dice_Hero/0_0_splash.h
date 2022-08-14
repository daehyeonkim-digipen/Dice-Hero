/*
File name: 0_0_splash.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
class Splash: public Scene
{
    Vec2 Pos{0, /*-WINDOW_HEIGHT / 5*/0};
    Image logo{ "assets/digipen.png" };
    int  timer = 0;
public:
    void update() override;
    void draw() override;
};