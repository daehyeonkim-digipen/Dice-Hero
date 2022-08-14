/*
File name: 3_credit_scene.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "3_credit_scene.h"

void CreditScene::update()
{
    if (creditBackButton.get_button_status() == true)
    {
        SceneChangeInput::toPlay();
    }
}

void CreditScene::draw()
{
    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    creditBackButton.draw_button();
    push_settings();
    set_fill_color(255, 180);
    set_outline_width(5);
    draw_rectangle(0, 0, WINDOW_WIDTH * 0.75, WINDOW_HEIGHT * 0.75);
    set_fill_color(0);
    set_font_size(DIALOGUESIZE);
    no_outline();
    draw_text("President: Claude Comair\nInstructor: KiKyeong Lim, David Ly\nTeaching Assistant: Jina Hyun, Haewon Shon\nProducer: Daehyeon Kim\nTechnical Director: Junsu Jang\nLead Designer: Taeju Kwon\nTest Manager: Jihyeon Song\n\nBGM: Scott Buckly\nhttps://www.scottbuckley.com.au/library/\nFemale Dying Sound: AmeAngleofSin(Freesound)\nhttps://freesound.org/people/AmeAngelofSin/sounds/345049/\nSkill Icon: Horror Pen(OpenGameArt)\nhttps://opengameart.org/content/random-rpg-icons-part-1", -WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.27);
    pop_settings();
}