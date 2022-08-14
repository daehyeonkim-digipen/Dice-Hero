/*
File name: 2_setting_scene.cpp
Project name: Dice Hero
Author(s): Major - Taeju Kwon, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "2_setting_scene.h"
void SettingScene::update()
{
    if (settingBackButton.get_button_status() == true)
    {
        if(isGameLoaded == true)
        {
            SceneChangeInput::toGameMain();
        } else
        {
            SceneChangeInput::toPlay();
        }
    }
    if (cheatModeButton.get_button_status() == true)
    {
        isGodModeOn = true;
    }
}

void SettingScene::draw()
{
    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    push_settings();
    set_fill_color(255, 180);
    set_outline_width(5);
    draw_rectangle(0, 0, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    pop_settings();
    arts.barUpdate();
    settingBackButton.draw_button();

    if (now_chapter != 0)
    {
        cheatModeButton.draw_button();
    }
}