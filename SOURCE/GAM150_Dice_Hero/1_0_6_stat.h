/*
File name: 1_0_6_stat.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "game_header.h"
#include "scene_manager.h"
#include "1_0_5_inventory.h"

class GameStatScene : public Scene
{
    Button statBackButton{"Back", WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.45, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button statEquipButton{"Equip ", WINDOW_WIDTH * 0.40, WINDOW_HEIGHT * -0.45, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11};
    Button statWarrior{"Warrior", -WINDOW_WIDTH * 0.368, WINDOW_HEIGHT * 0.385, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18};
    Button statMage{"Mage", -WINDOW_WIDTH * 0.28, WINDOW_HEIGHT * 0.385, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18};
    Button statThief{"Thief", -WINDOW_WIDTH * 0.192, WINDOW_HEIGHT * 0.385, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18};
    Button statArcher{"Archer", -WINDOW_WIDTH * 0.105, WINDOW_HEIGHT * 0.385, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18};
    Button unequipWeapon{"Unequip", -WINDOW_WIDTH * 0.23, -WINDOW_HEIGHT * 0.06, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 16};
    Button unequipArmor{"Unequip", -WINDOW_WIDTH * 0.23, -WINDOW_HEIGHT * 0.19, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 16};
    Button equeipmentButton{ "Equipment", WINDOW_WIDTH * 0.105, WINDOW_HEIGHT * 0.385, WINDOW_WIDTH / 16, WINDOW_HEIGHT / 24 };
    Button skillButton{ "Skill", WINDOW_WIDTH * 0.193, WINDOW_HEIGHT * 0.385, WINDOW_WIDTH / 16, WINDOW_HEIGHT / 24 };
    Button statBuyButton{"Buy", WINDOW_WIDTH * 0.37, WINDOW_HEIGHT * 0.325, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18};
    Button statUpButton{ "Up", WINDOW_WIDTH * 0.07, WINDOW_HEIGHT * 0.322, WINDOW_WIDTH / 50, WINDOW_HEIGHT / 28 };
    Button UpButton{"Up", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 16};
    Button DownButton{"Down", WINDOW_WIDTH * 0.4, -WINDOW_HEIGHT * 0.3, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 16};
    Image  gold{"assets/UI/gold.png"};

    CharacterClass nowCharacter = Warrior_C;
    Character*     myCharacter = myWarrior;
    void draw_status(Character* which);
    void draw_information(Character* which);
    int            page    = 1;
    int            maxPage = 0;
    enum phase
    {
        equipment = 1,
        skills = 0
    };
    phase nowPhase = equipment;
    int buyPoint = 1;
public:
    void update() override;
    void draw() override;

private:

};