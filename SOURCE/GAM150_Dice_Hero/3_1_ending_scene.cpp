/*
File name: 3_1_ending_scene.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "3_1_ending_scene.h"
#define TEXT_INTERVAL_MAX 30
#define CREDIT_X_POS WINDOW_WIDTH*-0.45
void EndingScene::setup()
{
    arts.PlayBGM(&arts.Ending_BGM);
    data.open("dataFile/credit_text.txt");
    getline(data, line);
    texts.emplace_back(creditText{ line });
}
EndingScene::~EndingScene()
{
    data.close();
}

void EndingScene::update()
{
    if (MouseIsPressed)
    {
        speed = 10;
    } else
    {
        speed = 5;
    }

    if (data.is_open() == true
        && data.eof() == false
        && textInterval >= TEXT_INTERVAL_MAX)
    {
        getline(data, line);
        texts.emplace_back(creditText{ line });
        texts.remove_if([](creditText& t)->bool {return t.ypos > WINDOW_HEIGHT / 2;});
        textInterval = 0;
    }
    if ((data.eof() == true && (int)texts.size() == 0) || endingBackButton.get_button_status() == true)
    {
        SceneChangeInput::toGameMain();
    }
    for (auto& t : texts)
    {
        t.ypos += speed;
    }
    textInterval += speed / 5;
}

void EndingScene::draw()
{
 //하셈
    push_settings();
    clear_background(0);
    set_fill_color(255);

    for (auto& t : texts)
    {

        draw_text(t.text, CREDIT_X_POS, t.ypos);
    }
    pop_settings();
    endingBackButton.draw_button();
}