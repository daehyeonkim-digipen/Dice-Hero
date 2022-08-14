/*
File name: 1_1_ingame_screen.h
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "monster.h"
#include "scene_manager.h"
#include "tile.h"
#include "game_header.h"
#include "ingameShop.h"
#include "quest_info.h"
#include "UI.h"
#include "IngameObjectManager.h"

struct ingameInformation
{
    unsigned long long gold{};
    long double exp{};
    int  matl{};
    bool  boss{false};
    std::map<Material*, int> playerMatrial{};
    void reset()
    {
        gold = 0;
        exp  = 0;
        matl = 0;
        boss = false;
        playerMatrial.clear();
    }
};


inline ingameInformation inInform{};


class IngameScene : public Scene,public IngameObjectManager
{
protected:
    RightSideUIButton  exitButton{"Back",  WINDOW_HEIGHT * 0.45};


    int    caseNumber = 0;

    IngameShop magicTower{{100, 100}, 3, 1, 27, ingameGold, playerMagics};
    Peddler    peddler{{32, 32}, 3, 2, 1, ingameGold, playerMagics,nowTurn};

    vector<IngameMagic*> playerMagics{}; //인게임 마법 구상중, 머법을 누르면 플레이어에게 이펙트 적용, 상속 할지도
                                         //모르니 일단 포인터로 만듬

    Gold    gold{WINDOW_WIDTH * -0.47, -WINDOW_HEIGHT * 0.2, 60, 60};
    Profile player{to_string(ingameLevel), WINDOW_WIDTH * -0.35, -WINDOW_HEIGHT * 0.4,
                   WINDOW_WIDTH / 7,
                   WINDOW_HEIGHT / 18,
                   ingameExp,
                   ingameExpGoal, {120, 120, 255} };
    
    virtual void ingame_goal_update() = 0;
    void         level_up_update();
    virtual void ingame_boss_set() {}
    void         ingame_magic_update();
    void         ingame_magic_draw();
    void         ingame_effect_update();
    void         draw_background() const;
    virtual void goal_UI_draw() = 0;
    void magic_gene();
    void ingame_material_draw() const ;


public:
    IngameScene() = default;
    void tile_setup();
    void status_setup();
    void setup() override;
    void update() override;
    void player_turn_setup();
    void draw() override;
    void turn_setup();
    void ui_draw();
};



class IngameGoldQuest : public IngameScene
{
    unsigned long long goalGold{};

    /*void spawn_objects(int) override{}*/
    void ingame_goal_update() override
    {
        if (ingameGold >= nowQuest->get_gold_goal()/*goalGold*/)
        {
            selected.clear();
            inInform.gold = ingameGold;
            inInform.exp  = ingameLevel - status.level;
            SceneChangeInput::toCompleteScene();
        }
    }

    void goal_UI_draw() override
    {
        push_settings();
        set_font_size(40);
        set_fill_color(250, 210, 30);
        no_outline();
        draw_text("Goal " + to_string(ingameGold) + "/" + to_string(nowQuest->get_gold_goal()), WINDOW_WIDTH * -0.48,
                  -WINDOW_HEIGHT * 0.1);
        pop_settings();
    }

public:
    IngameGoldQuest() = default;
    IngameGoldQuest(long long goal) : IngameScene(), goalGold(goal) {}


};


class IngameBossQuest : public IngameScene
{
    string boss{};
    bool   bossOn{false};
    int    bossLoca{18};

    //void spawn_objects(int i) override
    //{
    //    const auto counter = random(100);
    //    if (counter < 3)
    //    {
    //        tiles[i].spawnGoldBox(5 * difficulty);
    //    }
    //    else if (counter < 15)
    //    {
    //        tiles[i].spawnBox(5 * difficulty);
    //    }
    //    else if (counter < 28)
    //    {
    //        tiles[i].spawnEnemy(commonMonster.get("Slime"), difficulty);
    //    }
    //    else if (counter < 38)
    //    {
    //        tiles[i].spawnEnemy(commonMonster.get("Mimic"), difficulty, 0.05, 0.2);
    //    }
    //    else if (counter < 43)
    //    {
    //        tiles[i].spawnEnemy(commonMonster.get("Rabbit"), difficulty, 0.03, 0.15);
    //    }
    //}
    void ingame_goal_update() override
    {
        if (bossOn == true)
        {
            //보스 죽었는지 확인
            if (tiles[18].getEnemy() == nullptr)
            {
                selected.clear();
                inInform.gold = ingameGold;
                inInform.exp  = ingameLevel - status.level;
                inInform.boss = true;
                SceneChangeInput::toCompleteScene();
            }
        }
    }
    void   ingame_boss_set() override
    {
        if (bossOn == false && nowTurn >= 0)
        {
            tiles[bossLoca].setMonsterOn(true);
            tiles[bossLoca].spawn_boss(nowQuest->get_boss_goal());
            dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_target(myCharacters);
            dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_tile(tiles);
            dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_turn(nowTurn);
            dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_whoseTurn(whosTurn);
            switch(now_chapter)
            {
            case forest:
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&mandragora);
                break;
            case desert:
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&genieLamp);
                break;
            case skypia:
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&titanAlloy);
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&titanEngine);
                break;
            case abyss:
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&cephalopodInk);
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&treasureofWreck);
                break;
            case hellgate:
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&hellOre);
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&diamond);
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&dragonFire);
                break;
            case hell:
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&hellfire);
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&devilClaw);
                dynamic_cast<Boss*>(tiles[bossLoca].getEnemy())->give_mat(&devilkingWish);
                break;

            }
            bossOn = true;
        }
    }

    void goal_UI_draw() override
    {
        push_settings();
        set_font_size(40);
        set_fill_color(0);
        no_outline();
        draw_text("Boss: " + nowQuest->get_boss_goal()->get_name(), WINDOW_WIDTH * -0.48,
                  WINDOW_HEIGHT * -0.1);
        pop_settings();
    }

public:
    IngameBossQuest() = default;
    IngameBossQuest( string& bossName) : IngameScene(), boss{bossName} {}
};


class IngameMatlQuest : public IngameScene
{
    string material{};
    int    *numOfMat{nullptr};//특정 몬스터 보상으로 주게 만든다
    int    goalNum{1};
    Material* goalMaterial{};

    //void enemy_reward_percentage(Enemy* ) override
    //{
    //    //몬스터 확인 후 재료 지급
    //}
    /*void spawn_objects(int ) override
    {
        
    }*/
    void ingame_goal_update() override
    {
        if (*numOfMat >=  goalNum)
        {
            selected.clear();
            inInform.gold = ingameGold;
            inInform.exp  = ingameLevel - status.level;
            inInform.matl = *numOfMat;
            SceneChangeInput::toCompleteScene();
        }
    }

    void goal_UI_draw() override
    {
        push_settings();
        set_font_size(40);
        set_fill_color(200);
        no_outline();
        draw_text(nowQuest->get_material_goal()->getName(), WINDOW_WIDTH * -0.48, WINDOW_HEIGHT * -0.1);
        pop_settings();
    }


public:
    IngameMatlQuest(): material(nowQuest->get_material_goal()->getName()), goalNum(1)
    {
        goalMaterial = nowQuest->get_material_goal();
        numOfMat = &inInform.playerMatrial[goalMaterial];
    }
};


/*
 *몬스터 세팅
 *                      name        now                           exp                 money
 *tiles[i].spawnEnemy("Slime",   8 * difficulty, length,     5 * difficulty,     static_cast<int>(2 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Mimic",   10 * difficulty, length,    6 * difficulty,     static_cast<int>(6 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Rabbit",  20 * difficulty, length,    12 * difficulty,    static_cast<int>(3 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Orc",     15 * difficulty, length,    10 * difficulty,    static_cast<int>(2 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Bandit",  12 * difficulty, length,    8 * difficulty,     static_cast<int>(4 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Wolf",    12 * difficulty, length,    9 * difficulty,     static_cast<int>(2 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Golem",   20 * difficulty, length,    11 * difficulty,    static_cast<int>(5 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Merman",  10 * difficulty, length,    7 * difficulty,     static_cast<int>(6 * pow(difficulty, 2)));
 *tiles[i].spawnEnemy("Skeleton",5 * difficulty, length,     5 * difficulty,     static_cast<int>(2 * pow(difficulty, 2)));
 */



class IngameTutorial : public IngameGoldQuest
{
    Image half_black{};
    bool tutorialStop{false};
    bool warrior{false};
    bool thief{ false };
    bool mage{ false };
    bool archer{ false };
    enum class Tutorial
    {
        NONE = -5,
        UI_NONE,
        BEHAVIOR_NONE,
        INGAME_SHOP_NONE,
        MAGIC_NONE,
        UI,
        BEHAVIOR_WARRIOR,
        BEHAVIOR_MAGE,
        BEHAVIOR_THIEF,
        BEHAVIOR_ARCHER,
        INGAME_SHOP,
        MAGIC,


    };
    Tutorial tuNum{Tutorial::NONE};
    vector<vector<string>> tutorialText{
        {"This is character status\nPlease move your mouse \non the character name circle","Then right bottom will\nshow you the character's information\n","Attack Damage Formula:\nCharacter's AD * Dice Number * 0.5\n","Receive Damage Formula:\n(Monster's Remaining HP - Character's DF)\n*\n(1 - Damage Reduction)", "Here is player status, stage goal", "Dice, Token\nRoll the Dice First\nAnd drag the token onto the Dice" },
        {"Warrior has high HP and DF\nRage increases when warrior is attacked\nIf rage is over the rage cost,\nWarrior can get one more turn"},
        {"Mage has MP and mana token\nCan get MP by using the mana token\nIf MP is over the mana cose,\nMage can get a Magic"},
        {"Thief can moves tiles one by one\nCan attack on the move."},
        {"Archer has high Ad and Attack Range"},
        {"Here is Magic Tower\nMage's MP can be filled by mana cost\nYou can buy the magics","Here is Peddler\nHe moves to random tiles\nat the end of the turn\nYou can buy the magics"},
        {"Here is Magic List\nYou can use this at Mage's turn"}
    };
    int tutoTextNum{0};
    void UI_none();
    void UI_tuto();
    void base_be();
    void be_thief();
    void ingame_shop();
    void draw_tuto(double x,double y,double w,double h);
    void behavior_tuto_st(Tutorial tt);
    void recopy_half_black() { half_black = Image{ "assets/half_black.png" }; }
    void show_tuto( Vec2 pos = {}, double wid = 1, double hei = 1);
    void show_tuto(int col, int row, int wid = 1, int hei = 1);
public:
    using IngameGoldQuest::IngameGoldQuest;
    void setup() override;
    void update() override;
    void draw() override;

};