/*
File name: Effect.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "doodle/drawing.hpp"
#include <doodle/angle.hpp>
#include <doodle/input.hpp>
#include <list>
#include "Effect_base.h"


class clickEffect:public Effect
{
    double x{};
    double y{};
    const double leng{5};
    double animationNum{0};
    const double     animationSpeed{10};
    const double     animationEndNum{255};
    double angle{};
    const double     angleSpeed{0.06};

    void rotaRect(double stAngle) const
    {
        doodle::push_settings();
        doodle::apply_translate(x, y);
        doodle::set_outline_color(0, 255 - animationNum);
        doodle::set_fill_color(animationNum+160, 120, angle * 255 / TWO_PI,
                               255 - animationNum);
        doodle::apply_rotate(stAngle + angle);
        doodle::apply_translate(animationNum / 15, animationNum / 15);
        doodle::draw_rectangle(0, 0, leng, leng);
        doodle::pop_settings();
    }

public:
    clickEffect(int x, int y) : x{static_cast<double>(x)}, y{static_cast<double>(y)} {}
    clickEffect(double x, double y) : x{x}, y{y} {}

    void draw() override
    {
        rotaRect(0);
        rotaRect(doodle::PI / 2);
        rotaRect(doodle::PI);
        rotaRect(doodle::PI * 1.5);
        angle += angleSpeed;
        animationNum += animationSpeed;
        if (animationNum > animationEndNum)
        {
            animationEnd = true;
        }
    }
};