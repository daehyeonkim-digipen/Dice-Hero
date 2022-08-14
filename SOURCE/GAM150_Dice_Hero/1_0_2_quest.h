/*
File name: 1_0_2_quest.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
#include "game_header.h"

class GameQuestScene : public Scene
{
    int which = 0;
    int phase = 0;
    bool choose{false}; //tutorial

    //change image per chapter
    Image          signboard{"assets/UI/quest/signboard" + to_string(now_chapter ) + ".png"};
    Image          goldSign{"assets/UI/quest/gold_sign" + to_string(now_chapter ) + ".png"};
    Image          materialSign{"assets/UI/quest/material_sign" + to_string(now_chapter ) + ".png"};
    Image          bossSign{"assets/UI/quest/boss_sign" + to_string(now_chapter ) + ".png"};
    Image          gold{"assets/UI/gold.png"};
    vector<Button> questButtons;
    Button warriorButton{"Warrior", -WINDOW_WIDTH * 0, WINDOW_HEIGHT * 0.19, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 10};
    Button mageButton{"Mage", -WINDOW_WIDTH * 0, WINDOW_HEIGHT * 0.065, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 10};
    Button thiefButton{"Thief", -WINDOW_WIDTH * 0, -WINDOW_HEIGHT * 0.06, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 10};
    Button archerButton{"Archer", -WINDOW_WIDTH * 0, -WINDOW_HEIGHT * 0.185, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 10};
    Button applyButton{"Apply", WINDOW_WIDTH * 0.2, -WINDOW_HEIGHT * 0.185, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 10};
    Button startButton{"Start", WINDOW_WIDTH * 0.2, -WINDOW_HEIGHT * 0.185, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 10};
    Button questBackButton{"Back", WINDOW_WIDTH * 0.4, -WINDOW_HEIGHT * 0.45, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
public :
    ~GameQuestScene() override { questButtons.clear(); }
    GameQuestScene() = default;
    void player_scene();
    void choose_quest_update(Button& whatQuest);
    void setup() override;
    void setup_helper(int);
    void draw() override;
    void update() override;
};