/*
File name: 0_1_play_scene.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
inline int show_slowly{ 30 };
class PlayScene: public Scene
{
    Button startGameButton{"StartGame",      WINDOW_WIDTH * 0,  -WINDOW_HEIGHT * 0.1, WINDOW_WIDTH / 7, WINDOW_HEIGHT / 11, false};
    Button settingButton{"Setting", WINDOW_WIDTH * 0, -WINDOW_HEIGHT * 0.18, WINDOW_WIDTH / 7, WINDOW_HEIGHT / 11, false};
    Button creditButton{"Credit", WINDOW_WIDTH * 0, -WINDOW_HEIGHT * 0.26, WINDOW_WIDTH / 7, WINDOW_HEIGHT / 11, false};
    Button quitButton{"Quit", WINDOW_WIDTH * 0, -WINDOW_HEIGHT * 0.34, WINDOW_WIDTH / 7, WINDOW_HEIGHT / 11, false};

    Vec2   textPos{-WINDOW_WIDTH * 0.285, WINDOW_HEIGHT* -0.4};
    enum phase
    {
        unpressed,
        pressed
    };
    phase which = unpressed;
    bool show = true;
    int timer = -60;
    int amount = 0;
    
public:
    void setup() override;
    void update() override;
    void draw() override;
};