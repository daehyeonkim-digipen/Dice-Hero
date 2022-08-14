/*
File name: AttackEffect.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

#include "Arts.h"
#include "Effect_base.h"
#include "Ingame_image.h"
class ThiefEffect : public Effect
{
    double x;
    double y;
    int anim = 0;
    int time = 0;
    static constexpr int attacktime = 2;
    bool s1 = false;
public:
    ThiefEffect(Vec2 input);

    void draw() override;

    void update() override;
};

class WarriorEffect : public Effect
{
    double x;
    double y;
    int anim = 0;
    bool s1 = false;
public:
    WarriorEffect(Vec2 input) : x(input.x), y(input.y) {}
    void draw() override;

    void update() override;
};

class MageEffect : public Effect
{
    double x;
    double y;
    double TargetX;
    double TargetY;
    double angle;
    int phase = 0;
    int anim = 0;
    int tile;
    int turn;
    int dice;
    bool s1 = false;
    bool closed = false;
    function<void(int, int, int, bool)> k;
public:
    MageEffect(Vec2 input, Vec2 Target, const function<void(int, int, int, bool)>& a, int tile, int turn, int dice);

    void draw() override;

    void update() override;
};

class ArcherEffect : public Effect
{
    double x;
    double y;
    double TargetX;
    double TargetY;
    double angle;
    int anim = 0;
    int tile;
    int turn;
    int dice;
    bool s1 = false;
    bool s2 = false;
    bool closed = false;
    bool b = false;
    function<void(int, int, int, bool)> k;
public:
    ArcherEffect(Vec2 input, Vec2 Target, const function<void(int, int, int, bool)>& a, int tile, int turn, int dice, bool b);

    void draw() override;

    void update() override;
};