/*
File name: 3_credit_scene.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
class CreditScene : public Scene
{
    Button creditBackButton{"Back", -WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};

public:
    void update() override;
    void draw() override;
};