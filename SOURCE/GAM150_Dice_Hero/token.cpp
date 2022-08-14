/*
File name: token.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "token.h"

#include "Arts.h"
Token::Token() {}
Token::Token(double x, double y, double sz, EffectType t) :stPoint{ x,y }, position{ x, y }, size{ sz }, type{ t } {}
void Token::Draw() const
{
    push_settings();
    draw_ellipse(position.x, position.y, size*2, size*2);
    set_fill_color(0);
    switch (type)
    {
        case EffectType::attack: 
            draw_image(objectImage["Attack Token"], position.x, position.y, size * 2, size * 2);
            //draw_text("Attack", position.x - size *2/3 , position.y - size / 4);
        break;

        case EffectType::move: 
            draw_image(objectImage["Move Token"], position.x, position.y, size * 2, size * 2);
            //draw_text("Move", position.x - size *2/3, position.y - size / 4);
        break;
        case EffectType::mana: 
            draw_image(objectImage["Mana Token"], position.x, position.y, size * 2, size * 2);
            //draw_text("Mana", position.x - size *2/3, position.y - size / 4);
        break;
        case EffectType::BACK_MOVE:
            push_settings();
            set_tint_color(100);
            draw_image(objectImage["Move Token"], position.x, position.y, size * 2, size * 2);
            pop_settings();
        break;
        default:
            break;
    }
    pop_settings();
}


void Token::Update()
{
    const auto x{static_cast<double>(get_mouse_x())};
    const auto y{static_cast<double>(get_mouse_y())};
    if (tokenDrop == true)
    {
        tokenDrop = false;
    }
    if (tokenArea(x, y) == true && MouseIsPressed == true && anotherTokenChooose == false && tokenPressed == false)
    {
        arts.PlaySound(sounds::token1);
        tokenPressed = true;
    }
    if (tokenArea(x, y) == false && MouseIsPressed == true)
    {
        anotherTokenChooose = true;
    }
    if (tokenPressed ==  true)
    {
        position.x = {x};
        position.y = {y};
    }
    if (tokenPressed == true && MouseIsPressed == false)
    {
        arts.PlaySound(sounds::token2);
        tokenPressed = false;
        tokenDrop    = true;
    }
    if (anotherTokenChooose == true && MouseIsPressed == false)
    {
        anotherTokenChooose = false;
    }
    if (anotherTokenChooose == true)
    {
        avoidAnotherToken();
    }
    if(MouseIsPressed == false && (anotherTokenChooose == true 
            || avoiding == true))
    {
        anotherTokenChooose = false;
        avoiding = false;
    }
    restrict_area();
}
void Token::restrict_area()
{
    if(Helpers::Distance::objToObj(stPoint,position) >= WINDOW_HEIGHT/3)
    {
        init();
    }
}
void Token::init()
{
    position = stPoint;
    tokenPressed = false;
    anotherTokenChooose = false;
    tokenDrop = false;
    avoiding = false;
}



bool Token::tokenArea(double x, double y) const
{
    const auto xytoPosition{getdistfromxy(x,y)};
    if (size >xytoPosition)
    {
        return true;
    }
    return false;
}
bool      Token::getTokenDrop() const { return tokenDrop; }
EffectType Token::getTokenType() const { return type; }
void      Token::avoidAnotherToken()
{
    if (getdistfromxy(get_mouse_x(), get_mouse_y()) <= 2 * size)
    {
        avoid(get_mouse_x(), get_mouse_y());
    }
}
double Token::getdistfromxy(double x, double y) const
{
    x -= position.x;
    y -= position.y;
    const auto xytoPosition{sqrt(x * x + y * y)};
    return xytoPosition;
}
void Token::avoid(double x, double y)
{
    constexpr auto MULT{100};
    x -= position.x;
    y -= position.y;
    const auto dist{-getdistfromxy(x, y)};
    x /= dist;
    y /= dist;
    position.x += x * MULT;
    position.y += y * MULT;
}

