/*
File name: MagicEffect.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

#include "Effect_base.h"
#include "Ingame_image.h"
#include "tile.h"

class FireballEffect : public Effect
{
    int dmg;
    double x;
    double y;
    double TargetX;
    double TargetY;
    double angle;
    Tile& tile;
    int turn;
    double anim = 0;
    bool s1 = false;
    bool s2 = false;
    bool closed = false;
    bool hit = false;
    function<void(Tile&, int, int)> skill;
    int s = 1;
public:
    FireballEffect(double _x, double _y, double _TargetX, double _TargetY, Tile& _tile, int _turn,
                   const function<void(Tile&, int, int)>& _skill, int _dmg);

    void draw() override;

    void update() override;
};


class BombEffect : public Effect
{
    int dmg;
    double TargetX;
    double TargetY;
    int x = 0;
    int y = 0;
    int tile;
    int turn;
    int timer = 0;
    int st;
    int end;
    int anim = 0;
    bool exp = false;
    bool s1 = false;
    function<void(int, int, int, int, int)> skill;
public:
    BombEffect(double _TargetX, double _TargetY, int _tile, int _turn, int st, int end,
               const function<void(int, int, int, int, int)>& _skill, int _dmg);

    void draw() override;

    void update() override;
};

class TeleportEffect : public Effect
{
    double x;
    double y;
    double TargetX;
    double TargetY;
    int turn;
    int arrive;
    int anim = 0;
    int phase = 1;
    bool s1 = false;
    function<void(int, int)> skill;
public:
    TeleportEffect(double x, double y, double tx, double ty, int turn, int t2, const function<void(int, int)>& tp);

    void draw() override;

    void update() override;
};

class ResurrectionEfect : public Effect
{
    double x, y;
    int anim = 0;
    int phase = 1;
    bool s1 = false;
public:
    ResurrectionEfect(double x, double y);

    void draw() override;

    void update() override;
};