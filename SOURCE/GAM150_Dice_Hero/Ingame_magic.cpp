/*
File name: game_header.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Ingame_magic.h"

#define MAGIC_FONT_SIZE 20

IngameMagic::IngameMagic(string n, double wid, double hei, EffectInfo info,unsigned long long price)
    : name{n}, width{wid}, height{hei}, info{info},price(price)
{
    
}
IngameMagic::IngameMagic(IngameMagic& magic)
{
    name   = magic.get_name();
    info   = magic.get_effect();
    width  = magic.get_size().x;
    height = magic.get_size().y;
    price  = magic.get_price();
    image = magic.image;
}

void IngameMagic::set_pos(double posx, double posy)
{
    this->x = posx;
    this->y = posy;
}

void IngameMagic::draw() const
{
    push_settings();
    set_rectangle_mode(RectMode::Center);

    draw_image(image, x, y, width, height);
    if (area() == true)
    {
        set_fill_color(50, 50);
        no_outline();
        draw_rectangle(x, y, width, height);
    }
    set_fill_color(0);
    set_font_size(MAGIC_FONT_SIZE);
    draw_text(name, x-width/2, y+height/2);
    pop_settings();
}
void IngameMagic::draw_with_price() const
{
    draw();
    push_settings();
    set_fill_color(0);
    set_font_size(MAGIC_FONT_SIZE);
    draw_text("Price: \n"+to_string(price), x - width / 2, y - height / 2 - 20);
    pop_settings();
}

bool IngameMagic::area() const
{
    if (Helpers::Collision::objToMouse({x, y}, width, height) == true)
    {
        return true;
    }
    return false;
}
EffectInfo IngameMagic::get_effect() const
{ return info; }


