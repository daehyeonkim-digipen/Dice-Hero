/*
File name: 1_0_4_chamber.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "game_header.h"
#include "scene_manager.h"
class GameChamberScene : public Scene
{
    Button chamberBackButton{"Back", -WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.415, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button chapter1Button{ "1chapter", -WINDOW_WIDTH * 0.43, WINDOW_HEIGHT * 0.255, WINDOW_WIDTH / 50,
                     WINDOW_HEIGHT / 12 };
    Button chapter2Button{ "2chapter", -WINDOW_WIDTH * 0.43, WINDOW_HEIGHT * 0.153, WINDOW_WIDTH / 50,
                    WINDOW_HEIGHT / 12 };
    Button chapter3Button{ "3chapter", -WINDOW_WIDTH * 0.43, WINDOW_HEIGHT * 0.052, WINDOW_WIDTH / 50,
                     WINDOW_HEIGHT / 12 };
    Button chapter4Button{ "4chapter", -WINDOW_WIDTH * 0.43, -WINDOW_HEIGHT * 0.049, WINDOW_WIDTH / 50,
                    WINDOW_HEIGHT / 12 };
    Button chapter5Button{ "5chapter", -WINDOW_WIDTH * 0.43, -WINDOW_HEIGHT * 0.150, WINDOW_WIDTH / 50,
                     WINDOW_HEIGHT / 12 };
    Button chapter6Button{ "6chapter", -WINDOW_WIDTH * 0.43, -WINDOW_HEIGHT * 0.250, WINDOW_WIDTH / 50,
                    WINDOW_HEIGHT / 12 };

    Button extractButton{"Extract", WINDOW_WIDTH * 0.20, WINDOW_HEIGHT * 0.415, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 12, false};
    Button resetButton{"Reset", WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.415, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 12, false};
    Button okButton{"OK", WINDOW_WIDTH * 0.26, -WINDOW_HEIGHT * 0.3, WINDOW_WIDTH / 16, WINDOW_HEIGHT / 11};

    Item::Theme nowTheme = Item::Theme::forest;
    vector<Material*> whichMaterial;

    vector<Dice> dices{
        {WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.1,WINDOW_WIDTH / 15}, {WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.1, WINDOW_WIDTH / 15}
    };

    enum ChamberPhase
    {
        before,
        during,
        check
    };
    int imitation = 40;
    int point     = 0;
    string       getItemName{};
    ChamberPhase phase     = before;
    void do_extract();
    void getList(Item::Theme input);

    void getEssence(int input_point, Item::Theme theme);


    template <typename T>
    void draw_item_list(T input, int number, int count);

public:
    void draw() override;
    void update() override;


};

