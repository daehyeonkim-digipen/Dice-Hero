/*
File name: AttackEffect.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "AttackEffect.h"
#include "Arts.h"


ThiefEffect::ThiefEffect(Vec2 input)
    : x(input.x), y(input.y)
{
}

void ThiefEffect::draw()
{
    push_settings();
    apply_translate(x, y);
    if (time == 1)
    {
        apply_rotate(HALF_PI);
    }
    draw_image(ThiefAttackImage["Normal"][static_cast<int>(anim)], 0, 0);
    pop_settings();
}

void ThiefEffect::update()
{
    if (!s1)
    {
        arts.PlaySound(t1);
        s1 = true;
    }
    if (anim >= ThiefAttackImage["Normal"].size() - 1)
    {
        if (time != attacktime)
        {
            time++;
            anim = 0;
            arts.PlaySound(t2);
        }
        else
        {
            animationEnd = true;
        }
    }
    else
    {
        anim += 1;
    }
}

void WarriorEffect::draw()
{
    draw_image(WarriorAttackImage["Normal"][static_cast<int>(anim)], x, y);
}

void WarriorEffect::update()
{
    if (!s1)
    {
        arts.PlaySound(w);
        s1 = true;
    }
    if (anim >= WarriorAttackImage["Normal"].size() - 1)
    {
        animationEnd = true;
    }
    else
    {
        anim += 1;
    }
}

MageEffect::MageEffect(Vec2 input, Vec2 Target, const function<void(int, int, int, bool)>& a, int tile, int turn, int dice)
    : x(input.x), y(input.y), TargetX(Target.x), TargetY(Target.y), tile(tile), turn(turn), dice(dice)
{
    angle = atan2(TargetY - y, TargetX - x);
    if ((TargetX - x) * (TargetX - x) + (TargetY - y) * (TargetY - y) <= 2500)
    {
        closed = true;
    }
    k = a;
}

void MageEffect::draw()
{
    if (phase == 0)
    {
        push_settings();
        apply_translate(x, y);
        apply_rotate(angle);
        draw_image(MageAttackImage["Normal"][static_cast<int>(anim)], 0, 0);
        pop_settings();
    }
    else
    {
        draw_image(MageAttackImage["Hit"][static_cast<int>(anim)], x, y);
    }
}

void MageEffect::update()
{
    if (!s1)
    {
        arts.PlaySound(m1);
        s1 = true;
    }
    if (phase == 0)
    {
        x += 15 * cos(angle);
        y += 15 * sin(angle);
        if (anim != MageAttackImage["Normal"].size() - 1)
        {
            anim += 1;
        }
        else if ((TargetX - x) * (TargetX - x) + (TargetY - y) * (TargetY - y) < 2500 || closed)
        {
            phase = 1;
            anim  = 0;
            x     = TargetX;
            y     = TargetY;
            arts.PlaySound(m2);
        }
    }
    else if (phase == 1)
    {
        if (anim >= MageAttackImage["Hit"].size() - 1)
        {
            animationEnd = true;
            k(tile, turn, dice, false);
        }
        else
        {
            anim += 1;
        }
    }
}

ArcherEffect::ArcherEffect(Vec2 input, Vec2 Target, const function<void(int, int, int, bool)>& a, int tile, int turn,
                           int  dice, bool b)
    : x(input.x), y(input.y), TargetX(Target.x), TargetY(Target.y), tile(tile), turn(turn), dice(dice), b(b)
{
    angle = atan2(TargetY - y, TargetX - x);
    if ((TargetX - x) * (TargetX - x) + (TargetY - y) * (TargetY - y) <= 2500)
    {
        closed = true;
    }
    k = a;
}

void ArcherEffect::draw()
{
    push_settings();
    apply_translate(x, y);
    apply_rotate(angle - 3.14 / 4.);
    draw_image(ArcherAttackImage["Normal"][static_cast<int>(anim)], 0, 0);
    pop_settings();
}

void ArcherEffect::update()
{
    if (!s1)
    {
        arts.PlaySound(a1);
        s1 = true;
    }
    if (anim < ArcherAttackImage["Normal"].size() - 4)
    {
        anim += 1;
        x += 30 * cos(angle);
        y += 30 * sin(angle);
    }
    else if ((TargetX - x) * (TargetX - x) + (TargetY - y) * (TargetY - y) < 900 || closed)
    {
        if (!s2)
        {
            arts.PlaySound(a2);
            s2 = true;
        }
        anim += 1;
        x = TargetX;
        y = TargetY;
        if (anim == ArcherAttackImage["Normal"].size() - 1)
        {
            animationEnd = true;
            k(tile, turn, dice, b);
        }
    }
    else
    {
        x += 30 * cos(angle);
        y += 30 * sin(angle);
    }
}
