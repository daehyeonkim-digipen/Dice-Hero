/*
File name: 0_0_splash.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "0_0_splash.h"

#include "Ingame_image.h"

void Splash::update()
{
    timer++;
    if (timer > 60)
    {
        SceneChangeInput::toPlay();
    }
}

void Splash::draw()
{
    clear_background(0);
    draw_image(magicImage2["bombexp"], 0, 0, 1, 1);
    draw_image(magicImage2["teleport"], 0, 0, 1, 1);
    draw_image(logo, Pos.x, Pos.y/*, Width * 0.9, Height * 0.9*/);
    clear_background(0, timer*5);

}
