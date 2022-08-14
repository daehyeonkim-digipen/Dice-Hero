/*
File name: IngameShop.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "Ingame_magic.h"
#include "scene_manager.h"

class IngameShop
{
    Vec2                 position{};
    Vec2                 size{};
    Vec2                 shopWindowSize{500,500};
    vector<IngameMagic*> shopMagics{};
    IngameMagic          selectedMagic{};
    vector<IngameMagic*> &playerMagics;
    Button enterButton{"Trade",
        BOARD_CENTER.x, BOARD_CENTER.y - shopWindowSize.y * 3 / 5,
        100, 70 };
    Button buyButton{"Apply",
        BOARD_CENTER.x, BOARD_CENTER.y - shopWindowSize.y * 2/5,
        100, 70};
    Button exitButton{"X",
        BOARD_CENTER.x + shopWindowSize.x * 2 / 5, BOARD_CENTER.y + shopWindowSize.y * 2/5,
        70, 70};

    int                  hasMagicNum{3};
    int                  magicLevel{1};
    int                  locationNum{};
    bool                 IsOpen{false};
    bool                 isEnter{false};

    unsigned long long*playerMoney{};
    int charLoca{};

public:

        IngameShop() = default;
        IngameShop(Vec2 size, int hasNum, int level, int location, unsigned long long& money, vector<IngameMagic*>& playerMagics);
        virtual ~IngameShop();
    void draw(string&& name);
        void update(/*money ref, character location*/);
        void setup();
        void newMagicSet();
        bool get_is_entered() const { return IsOpen == true && isEnter == true; }
        void check_charLoca(int charicLocation) { charLoca = charicLocation; }
        void set_location(int loca) { locationNum = loca; }
        virtual void move_location(){};
        int  get_loca() { return locationNum; }
        void set_position(Vec2 pos) { position = pos; }
        Vec2 get_pos() const{ return position; }
};


class Peddler:public IngameShop
{
    int *turn{};
    int  previousLocation{};
    static constexpr int MOVE_NUM{3};
    static constexpr int MAGIC_TOWER_NUM{27};
    static constexpr int BOSS_NUM{18};
    static constexpr int OBJECT_NUM{9};
    static constexpr int BOARD_START{0};
    static constexpr int BOARD_END{35};

public:
    Peddler() = default;
    Peddler(Vec2 size, int hasNum, int level, int location, unsigned long long& money, vector<IngameMagic*>& playerMagics,int &turn):IngameShop(size,hasNum,level,location,money,playerMagics),turn(&turn),previousLocation(location) {}
    void move_location() override;
};