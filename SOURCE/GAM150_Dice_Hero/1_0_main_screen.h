/*
File name: 1_0_main_screen.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
#include "game_header.h"
#include "UI.h"


class GameMainScene : public Scene
{
    enum phase
    {
        main,
        chapter
    };

    Button questButton{"Quest", 0, -WINDOW_HEIGHT * 0.40, WINDOW_WIDTH / 6.5, WINDOW_HEIGHT / 9};

    Button menuButton{"Menu", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button inventoryButton{"Inventory", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.37, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button chamberButton{"Chamber", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.29, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button statsceneButton{"Stat", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.21, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button ingameSettingButton{"Setting", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.13, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button quitButton{"Quit", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.05, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};

    Button forgeButton{"Forge", WINDOW_WIDTH * 0.4, -WINDOW_HEIGHT * 0.40, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button chapterButton{"Chapter", -WINDOW_WIDTH * 0.4, -WINDOW_HEIGHT * 0.40, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};

    Gold    gold{WINDOW_WIDTH * -0.396, WINDOW_HEIGHT * 0.3, 90, 90};
    Profile profile{ to_string(status.level) , WINDOW_WIDTH * -0.3, WINDOW_HEIGHT * 0.4, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 20, status.exp, status.expGoal, {120, 120, 255}};
    int phase = main;
    bool menuOn = false;
    
    Button chapter_1Button{"1chapter", 0, WINDOW_HEIGHT * 0.25, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11,true};
    Button chapter_2Button{"2chapter", 0, WINDOW_HEIGHT * 0.15, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11, false};
    Button chapter_3Button{"3chapter", 0, WINDOW_HEIGHT * 0.05, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11, false };
    Button chapter_4Button{"4chapter", 0, -WINDOW_HEIGHT * 0.05, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11, false };
    Button chapter_5Button{"5chapter", 0, -WINDOW_HEIGHT * 0.15, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11, false };
    Button chapter_6Button{"6chapter", 0, -WINDOW_HEIGHT * 0.25, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11, false };

public:
    GameMainScene();
    void status_update();
    void setup() override;
    void draw() override;
    void update() override;
};

