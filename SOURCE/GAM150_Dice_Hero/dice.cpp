/*
File name: dice.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "dice.h"

#include "Arts.h"

Dice::Dice(double x, double y, double sz) : square{x, y,0,sz} {}

void Dice::draw()
{
    push_settings();
    set_rectangle_mode(RectMode::Center);
    //set_fill_color(255, 255, 0);
    //draw_rectangle(this->position.x, this->position.y, size, size);
    square.draw();
    set_fill_color(0);
    set_font_size(DICENUMBER);
    no_outline();
    if (isRolled == true)
    {
        if (animationEnd == false)
        {
            square.rolling(TWO_PI/60);
            --count;
            if (count <= 0)
            {
                animationEnd = true;
            }
        }
        else
        {
            draw_text(to_string(number), square.get_Vector().x - square.get_size() /3.5 ,
                      square.get_Vector().y - square.get_size() * 0.54);
            //draw_text(to_string(number), position.x - size / 5, position.y - size / 2);
        }
    }
    pop_settings();
}



bool Dice::is_released() const { return dicePressed == true && MouseIsPressed == false; }

void Dice::update()
{

    if (dice_area() == true)
    {
        if(MouseIsPressed == true){dicePressed = true;}
        if(isRolled == false && is_released() == true)
        {
            roll();
            dicePressed = false;
            isRolled = true;
        }
        if (is_released() == true) { dicePressed = false; }
    }
    else
    {
        dicePressed = false;
    }
}
void Dice::set_max_num(int num) { maxNumber = num; }
void Dice::roll() {
    arts.PlaySound(sounds::dice);
    this->number = doodle::random(0, maxNumber) + 1; }

bool Dice::dice_area() const
{
    return Helpers::Collision::objToMouse({square.get_Vector().x, square.get_Vector().y}, square.get_size(), square.get_size());
}
Vec2 Dice::get_pos() const { return {square.get_Vector().x, square.get_Vector().y}; }
bool Dice::get_animation_end() const { return animationEnd; }
void Dice::do_roll()
{
    isRolled = true;
    roll();
}
