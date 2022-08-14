/*
File name: TextEvent.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include <string>
#include "doodle/drawing.hpp"
#include "Effect_base.h"
#include "RGB.h"

class EventLog: public Effect
{
    double x{};
    double y{};
    std::string eventLog{};
    double animation{255};
    const RGB color{};
    int           size{};
    double      animationSpeed{10};

    void animating()//virtual
    {
        y += animationSpeed/5;
    }

public:
    template<typename T>
    EventLog(std::string log,T posx, T posy,const RGB& col, int size,double speed = 10)
        : eventLog(log), color(col), size(size), y(static_cast<double>(posy)),animationSpeed(speed)
    {
        this->x = static_cast<double>(posx) - log.size() / 2 * size / 4;
    }
    template <typename T>
    EventLog(std::string log, T x, T y) : EventLog(log, x, y, RGB{}, 25) {}
    void texting() {
        
        doodle::push_settings();
        doodle::set_font_size(size);
        doodle::set_fill_color(color.R,color.G,color.B,animation);
        doodle::set_outline_color(0,animation);
        doodle::draw_text(eventLog, x, y);
        animating();
        animation-=animationSpeed;
        doodle::pop_settings();
    }
    void        draw() override { texting(); }
    void update() override
    {
        if (animation < 0)
        {
            animationEnd = true;
        }
    }
};