/*
File name: IngameObjectManager.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once


#include "token.h"
#include "EffectStar.h"
#include <map>
#include <vector>

class Box;
class Enemy;
class Character;
class Tile;
class Material;

class IngameData
{
protected:
    int    ingameLevel   = 1;
    unsigned long long    ingameGold = 0;
    long double ingameExp = 0;
    long double ingameExpGoal = 10;


    int                      difficulty{ 1 };
    bool                     turnEnd = true;
    int                      nowTurn = 0;


    bool usedMagic{ false };


    EffectType effectAnimationType{};
    bool       effectAnimationSt{ false };
    double     animationNum{};

    int        whosTurn{ 0 };
    int        clickedTileNum{};
    int        effectTarget{};

    int characterRangeData{};
    virtual ~IngameData() = default;
};





class IngameObjectManager : public IngameData
{
protected:
    std::vector<Tile>       tiles;
    std::vector<Character*> myCharacters;
    int                     questTileCount = 36;

    enum PortraitTarget //
    {
        SOMETHING = -1,
        NOTHING = 0,
        BOX = 1,
        ENEMY,
    };
    class Cursor
    {
        Image cursorimg;
        double angle{};
    public:
        Cursor(string file);
        void draw();
    };
    Cursor cursor{ "assets/UI/cursor_red.png" };

    void do_effect();
    void attack_to_box();
    void attack_to_enemy();
    bool do_magic_teleport();
    bool do_magic_attack();
    bool do_magic_resur();
    bool do_magic_bomb(int, int);
    void do_magic();
    void get_gold(unsigned long long g);
    void get_exp(unsigned long long e);
    void level_up(int l = 1);



    void                     st_point_heal();
    void                     draw_possib_move_pos(EffectType t);
    void                     reward_update();
    virtual void             box_reward_percent(Box* b);
    virtual void             gold_box_reward_percent(Box* b);
    virtual void             enemy_reward_percentage(Enemy* e);
    void                     Thief_move();

    void                     update_target_of_effect();
    void                    tiles_set();
    void                    player_setup(unsigned int &deadNum);
    virtual void            spawn_objects(int i);
    void                    object_turn_setup();
    void                     count_down_gold_box();
    void count_PS_E();
    void                    show_portrait();
    void                     check_target_exist();


    void                     draw_range_col(int st = 0, int end = 0, unsigned int col = 0);
    void                     draw_attack_range();
    void                     ingame_effect_draw();
    void                     draw_effect_range(int st = 0, int end = 0);

public:

};
