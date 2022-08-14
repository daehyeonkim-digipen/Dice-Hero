/*
File name: scene_manager.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "scene_manager.h"

#include <utility>

Button::Button(string buttonName, double x, double y, double width, double height)
    : Pos{x, y}, name{move(buttonName)}, buttonWidth{width}, buttonHeight{height} {}

Button::Button(string buttonName, double x, double y, double width, double height, bool w)
    : Pos{x, y}, name{move(buttonName)}, buttonWidth{width}, buttonHeight{height}, working(w)
{}
Button::Button(string buttonName, double x, double y, double width, double height, int code, bool w)
    : Pos{x, y}, name{move(buttonName)}, buttonWidth{width}, buttonHeight{height}, buttonCode{code}, working(w)
{}

bool Button::mouse_on_check() const { return Helpers::Collision::objToMouse(Pos, buttonWidth, buttonHeight); }

void Button::draw_button() 
{
    if (mouse_on_check() == true && wasMousePressed == true && working == true && MouseIsPressed == false)
    {
        isButtonPressed = true;
        if(buttonCode == 0 || name == "Gold")
        {
            draw_image(buttonImage[name + to_string(now_chapter) + ".1"], Pos.x, Pos.y, buttonWidth, buttonHeight);
        }
    }
    else if (mouse_on_check() == true && working == true && MouseIsPressed == true)
    {
        if (buttonCode == 0 || name == "Gold") {
            draw_image(buttonImage[name + to_string(now_chapter) + ".2"], Pos.x, Pos.y, buttonWidth, buttonHeight);
        }
    }
    else
    {
        isButtonPressed = false;
        if (buttonCode == 0 || name == "Gold") {
            draw_image(buttonImage[name + to_string(now_chapter) + ".1"], Pos.x, Pos.y, buttonWidth, buttonHeight);
        }
    }
    if (name != "OK" && name != "X" && name != "Up" && name != "Down" && name != "1chapter" && name != "2chapter" && name != "3chapter" && name != "4chapter" && name != "5chapter" && name != "6chapter" && buttonCode == 0)
    {
        draw_image(buttonImage["outline" + to_string(now_chapter)], Pos.x, Pos.y, buttonWidth, buttonHeight);
    }
}

bool Button::get_button_status()
{
    if (isButtonPressed == true)
    {
        const auto returnCode = isButtonPressed;
        isButtonPressed       = false;
        return returnCode;
    }
    return isButtonPressed;
}

void Button::set_button_position(const Vec2 input) { this->Pos = input; }

int Button::get_button_code() const
{
    return buttonCode;
}

string Button::get_button_name() const
{ return name; }

void Button::set_button_working(bool w)
{ working = w; }

bool Button::get_button_working()
{ return working; }
