/*
File name: MagicEffect.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "MagicEffect.h"
#include "Arts.h"
FireballEffect::FireballEffect(double _x, double _y, double _TargetX, double _TargetY, Tile& _tile, int _turn,
                               const function<void(Tile&, int, int)>& _skill, int _dmg)
    : x(_x), y(_y), TargetX(_TargetX), TargetY(_TargetY), tile(_tile), turn(_turn), dmg(_dmg)
{
    angle = atan2(TargetY - y, TargetX - x);
    if ((TargetX - x) * (TargetX - x) + (TargetY - y) * (TargetY - y) <= 2500)
    {
        closed = true;
    }
    skill = _skill;
}

void FireballEffect::draw()
{
    push_settings();
    apply_translate(x, y);
    apply_rotate(angle);
    apply_scale(1, s);
    draw_image(MagicImage["Fireball"][static_cast<int>(anim)], 0, 0);
    pop_settings();
}

void FireballEffect::update()
{
    if (!s1)
    {
        arts.PlaySound(fb1);
        s1 = true;
    }

    if ((TargetX - x) * (TargetX - x) + (TargetY - y) * (TargetY - y) <= 900 || closed)
    {
        if (!s2)
        {
            arts.PlaySound(fb2);
            s2 = true;
        }
        anim -= 0.5;
        x = TargetX;
        y = TargetY;
        if (anim <= 1)
        {
            animationEnd = true;
            skill(tile, turn, dmg);
        }
    }
    else if (anim < MagicImage["Fireball"].size() - 1)
    {
        anim += 0.2;
        x += 30 * cos(angle);
        y += 30 * sin(angle);
    }
    else
    {
        x += 30 * cos(angle);
        y += 30 * sin(angle);
    }
    s *= -1;
}

BombEffect::BombEffect(double _TargetX, double _TargetY, int _tile, int _turn, int st, int end,
                       const function<void(int, int, int, int, int)>& _skill, int _dmg)
    : TargetX(_TargetX), TargetY(_TargetY), tile(_tile), turn(_turn), st(st), end(end), dmg(_dmg)
{
    skill = _skill;
}

void BombEffect::draw()
{
    push_settings();
    apply_translate(TargetX, TargetY);
    apply_scale(2, 2);
    if (timer >= 50)
    {
        draw_image(magicImage2["bombexp"], 0, 0, 512, 512, static_cast<int>(anim) % 8 * 512,
                   static_cast<int>(anim / 8) % 8 * 512);
    }
    pop_settings();
}

void BombEffect::update()
{
    if (!s1)
    {
        arts.PlaySound(bm);
        s1 = true;
    }

    if (timer >= 50)
    {
        if (!exp)
        {
            exp = true;
            skill(turn, tile, st, end, dmg);
        }
        anim += 1;
        if (anim == 64)
        {
            animationEnd = true;
        }
    }
    timer += 1;
}

TeleportEffect::TeleportEffect(double                          x, double y, double tx, double ty, int turn, int t2,
                               const function<void(int, int)>& tp)
    : x(x), y(y), TargetX(tx), TargetY(ty), turn(turn), arrive(t2)
{
    skill = tp;
}

void TeleportEffect::draw()
{
    push_settings();
    if (phase == 1)
    {
        apply_translate(x, y);
        apply_scale(0.5, 0.5);
        draw_image(magicImage2["teleport"], 11.5, 21, 256, 256, static_cast<int>(anim) % 8 * 256,
                   static_cast<int>(anim / 8) % 8 * 256);
    }
    else if (phase == 2)
    {
        apply_translate(TargetX, TargetY);
        apply_scale(0.5, 0.5);
        draw_image(magicImage2["teleport"], 11.5, 21, 256, 256, static_cast<int>(anim) % 8 * 256,
                   static_cast<int>(anim / 8) % 8 * 256);
    }
    pop_settings();
}

void TeleportEffect::update()
{
    if (!s1)
    {
        arts.PlaySound(tp1);
        arts.PlaySound(tp2);
        s1 = true;
    }
    if (phase == 1)
    {
        anim++;
        if (anim == 25)
        {
            phase = 2;
            skill(turn, arrive);
        }
    }
    else if (phase == 2)
    {
        anim--;
        if (anim == -1)
        {
            animationEnd = true;
        }
    }
}

ResurrectionEfect::ResurrectionEfect(double x, double y)
    : x(x), y(y)
{
}

void ResurrectionEfect::draw()
{
    apply_translate(x, y);
    draw_image(magicImage2["resurrection"], 0, 96, 192, 192, static_cast<int>(anim) % 8 * 192,
               static_cast<int>(anim / 8) % 8 * 192);
}

void ResurrectionEfect::update()
{
    if (!s1)
    {
        arts.PlaySound(rus);
        s1 = true;
    }
    if (phase == 1)
    {
        anim++;
        if (anim == 32)
        {
            phase = 2;
        }
    }
    else if (phase == 2)
    {
        anim--;
        if (anim == -1)
        {
            animationEnd = true;
        }
    }
}
