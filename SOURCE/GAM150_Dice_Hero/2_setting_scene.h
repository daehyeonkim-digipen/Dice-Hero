/*
File name: 2_setting_scene.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"

class SettingScene : public Scene
{
    Button settingBackButton{"Back", -WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button cheatModeButton{"Cheat", WINDOW_WIDTH * 0.35, -WINDOW_HEIGHT * 0.45, WINDOW_WIDTH / 7, WINDOW_HEIGHT / 9};

public:
    void update() override;
    void draw() override;
};