/*
File name: 0_1_play_scene.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "0_1_play_scene.h"
#include "GameDataManager.h"
void PlayScene::setup()
{
    now_chapter = start;
    if (arts.nowPlayBGM != &arts.Play_BGM)
    {
        arts.PlayBGM(&arts.Play_BGM);   
    }
    isGameLoaded = false;
}


void PlayScene::update()
{
    if (amount < 6)
    {
        timer++;
        if (timer >= 15)
        {
            timer = 0;
            amount++;
            show = !show;
        }
    }
    else
    {
        show = true;
    }
    if (PlayerData::Instance().event_on() == false)
    {
        if (startGameButton.get_button_status() == true)
        {
            //SceneChangeInput::toGameMain();
            PlayerData::Instance().event_on() = true;
        }
        if (settingButton.get_button_status() == true)
        {
            SceneChangeInput::toSetting();
        }
        if (creditButton.get_button_status() == true)
        {
            SceneChangeInput::toCredit();
        }
        if (quitButton.get_button_status() == true)
        {
            close_window();
        }
    }
    else
    {
        PlayerData::Instance().update_load_window();
    }
    if (MouseIsPressed == false && wasMousePressed == true)
    {
        which = pressed;
    }

}

void PlayScene::draw()
{

    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (show_slowly <= 0)
    {

        if (show && which == unpressed)
        {
            push_settings();
            set_fill_color(0);
            /*set_font_size(sqrt(WINDOW_WIDTH * WINDOW_HEIGHT) / 16);*/
            set_font_size(DICENUMBER);
            no_outline();
            draw_text("Press mouse left button to start", textPos.x, textPos.y);
            pop_settings();
        }
        if (which == pressed)
        {
            if (now_chapter == start)
            {
                startGameButton.draw_button();
                settingButton.draw_button();
                creditButton.draw_button();
                quitButton.draw_button();
            }
            startGameButton.set_button_working(true);
            settingButton.set_button_working(true);
            creditButton.set_button_working(true);
            quitButton.set_button_working(true);
        }
        if (PlayerData::Instance().event_on() == true)
        {
            PlayerData::Instance().draw_data_manage_window("Load");
        }
    }
    else
    {
        clear_background(0, show_slowly * 9);
        --show_slowly;
    }
}