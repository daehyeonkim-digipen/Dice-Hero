/*
File name: 1_0_5_inventory.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
#include "game_header.h"
#include "UI.h"

class GameInventoryScene : public Scene
{
    Image guide{"assets/UI/guide/guide" + to_string(now_chapter) + ".png"};
    Button inventoryBackButton{"Back", WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.415, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button inventoryMaterialButton{"Material", -WINDOW_WIDTH * 0.325, WINDOW_HEIGHT * 0.395, WINDOW_WIDTH / 10,
                               WINDOW_HEIGHT / 15};
    Button inventoryEssenceButton{"Essence", -WINDOW_WIDTH * 0.195, WINDOW_HEIGHT * 0.395, WINDOW_WIDTH / 10,
                               WINDOW_HEIGHT / 15};
    Button inventoryEquipmentButton{"Equipment", -WINDOW_WIDTH * 0.065, WINDOW_HEIGHT * 0.395, WINDOW_WIDTH / 10,
                               WINDOW_HEIGHT / 15};
    Button okButton{"OK", -WINDOW_WIDTH * 0.1, -WINDOW_HEIGHT * 0.2, WINDOW_WIDTH / 14, WINDOW_HEIGHT / 11};
    Button cancelButton{"X", WINDOW_WIDTH * 0.1, -WINDOW_HEIGHT * 0.2, WINDOW_WIDTH / 14, WINDOW_HEIGHT / 11};
    Button UpButton{"Up", WINDOW_WIDTH * 0.38, WINDOW_HEIGHT * 0.3, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 16};
    Button DownButton{"Down", WINDOW_WIDTH * 0.38, -WINDOW_HEIGHT * 0.3, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 16};
    Button numUpButton{"Up", WINDOW_WIDTH * 0.2, 0, WINDOW_WIDTH / 23, WINDOW_HEIGHT / 20};
    Button numDownButton{"Down", WINDOW_WIDTH * 0.2, -50, WINDOW_WIDTH / 23, WINDOW_HEIGHT / 20};
    Image  gold{"assets/UI/gold.png"};

    Item* sellItem{};

    enum InventoryPhase
    {
        bag,
        sell
    };
    InventoryPhase phase = bag;
    int            page  = 1;
    int            maxPage = 0;
    int            sellnum = 1;
    int            sellmax = 0;
    enum WhichItem
    {
        material = 1,
        essence,
        equipment
    };
    WhichItem whichItemCase = material;
    template <typename T>
    void draw_item_list(T input, int number, int count);

public:
    void draw() override;
    void update() override;
    const double positionX = -WINDOW_WIDTH * 0.35;
    double positionY{};
};
