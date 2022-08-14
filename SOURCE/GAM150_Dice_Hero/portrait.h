/*
File name: portrait.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "Ingame_image.h"// for portrait image
#include "EffectStar.h"

#define PORT_WID 150
#define PORT_HEI 150
#define PORT_POS_X 125

class Portrait
{
    
    double x{};
    double y{};
    double width{};
    double height{};
    string name{};
    highLightingEffect::RectHighLight rectHighLight{};
    unsigned int                      col{0xff};
    int                      colSpeed{0x00001000};

public:
    Portrait(double x, double y, double wid, double hei) : x{x}, y{y}, width{wid}, height{hei} {}
    void naming(string &s) { name = s; }
    void naming(const string& s) { name = s; }
    string get_name()const { return name; }
    void draw()
    {
        push_settings();
        set_rectangle_mode(RectMode::Center);
        set_font_size(14);
        if (Helpers::Collision::objToMouse({x, y}, width, height))
        {
            set_fill_color(200);
            set_tint_color(200);
        }
        else
        {
            set_fill_color(255);
        }
        set_outline_width(10);
        draw_rectangle(x, y, width, height);
        if(enemyImage[name].empty() != true)
        {
                    draw_image(enemyImage[name][0], x, y, width, height);

        }
        set_fill_color(0);
        set_font_size(35);
        draw_text(name, x-width/2, y+height/2);
        pop_settings();
        rectHighLight.operator()({x, y}, width/2, height/2,col);
        if (col > 0xEEEEEEff)
        {
            colSpeed = -0x00001000;
        }
        else if (col>0x000000ff)
        {
            colSpeed = 011111000;
        }
        col -= colSpeed;
    }
    bool area() const
    { return Helpers::Collision::objToMouse({x, y}, width, height);
    }

};