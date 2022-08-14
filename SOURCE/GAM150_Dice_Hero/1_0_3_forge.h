/*
File name: 1_0_3_forge.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Taeju Kwon
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "game_header.h"
#include "scene_manager.h"
#include "UI.h"

class GameForgeScene : public Scene
{
    Image guide{"assets/UI/guide/guide" + to_string(now_chapter) + ".png"};
    Button forgeBackButton{"Back", WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.415, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button forgeBuyButton{"Buy", -WINDOW_WIDTH * 0.1, -WINDOW_HEIGHT * 0.195, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 9.5 };
    Button forgeOKButton{ "OK", 0, -WINDOW_HEIGHT * 0.2, WINDOW_WIDTH / 13, WINDOW_HEIGHT / 11 };
    Button forgeCancelButton{ "X",WINDOW_WIDTH * 0.1, -WINDOW_HEIGHT * 0.2, WINDOW_WIDTH / 14, WINDOW_HEIGHT / 11 };
    Button valueCommon{ "Common", -WINDOW_WIDTH * 0.325, WINDOW_HEIGHT * 0.395, WINDOW_WIDTH / 10,
                               WINDOW_HEIGHT / 15 };
    Button valueRare{ "Rare", -WINDOW_WIDTH * 0.195, WINDOW_HEIGHT * 0.395, WINDOW_WIDTH / 10,
                           WINDOW_HEIGHT / 15 };
    Button valueUnique{ "Unique", -WINDOW_WIDTH * 0.065, WINDOW_HEIGHT * 0.395, WINDOW_WIDTH / 10,
                               WINDOW_HEIGHT / 15 };
    Button valueEpic{ "Epic", WINDOW_WIDTH * 0.075, WINDOW_HEIGHT * 0.395, WINDOW_WIDTH / 10,
                           WINDOW_HEIGHT / 15 };
    Image  gold{"assets/UI/gold.png"};

    //장비로 변경
    enum forgePhase
    {
        shop,
        buy,
        cannot
    };
    forgePhase phase = shop;
    vector<Item*> forgeItem;
    Essence* neededEssence = nullptr;
    Item* chosenItem = nullptr;
    Item::Value nowValue = Item::Common;
public:
    void setup() override;
    void update() override;
    void draw() override;

    template <typename T>
    void draw_forge_item(T input, int);
    
protected:
    double positionX = -WINDOW_WIDTH * 0.35;
    double positionY{};
    const int mouseX = get_mouse_x();
    const int mouseY = get_mouse_y();
};
