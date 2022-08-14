/*
File name: quest_info.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "item.h"
#include "material.h"
#include "monster.h"


class QuestInfo
{

protected:
    int code = 0;

public:
    QuestInfo(int number) : code(number) {}
    virtual ~QuestInfo() = default;
    int              getCode() const { return code; }
    virtual unsigned long long      get_gold_goal() { return 0; }
    virtual Material* get_material_goal()
    {
        return nullptr;
    }
    virtual Boss *    get_boss_goal()
    {
        Boss *nullBoss{};
        return nullBoss;
    }
    /*QuestType get_quest_type() const { return this->nowType; }*/
};

class GoldQuest : public QuestInfo
{
    unsigned long long goal = 0;
public:
    GoldQuest(int number, unsigned long long input) : QuestInfo(number), goal(input) { }
    unsigned long long get_gold_goal() override { return goal; }
};


class MaterialQuest : public QuestInfo
{
    Material* goal;
    int      numGoal{1};

public:
    MaterialQuest(int number, Material *input) : QuestInfo(number), goal(input) {}
    Material* get_material_goal() override { return goal; }
};

class BossQuest : public QuestInfo
{
    Boss* goal;
    string bossName{};
public:
    BossQuest(int number, Boss* input) : QuestInfo(number) , goal(input),bossName("???")
    {
        if (goal != nullptr)
        {
            bossName = goal->get_name();

        }
    }
    Boss* get_boss_goal() override

    { return goal;}
    string get_boss_name()const { return bossName; }
};

inline QuestInfo* nowQuest;