/*
File name: 1_0_4_chamber.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song, Taeju Kwon
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_0_4_chamber.h"
#include "EffectStar.h"

highLightingEffect::CircleHighLight ch{};
template <typename T>
void GameChamberScene::draw_item_list(T input, int number, int count)
{
    const double positionX = -WINDOW_WIDTH * 0.37;
    const double positionY = +WINDOW_HEIGHT * 0.23 - WINDOW_HEIGHT * 0.07 * number;

    push_settings();
    set_fill_color(chapterColor[nowTheme + 1][3], chapterColor[nowTheme + 1][4], chapterColor[nowTheme + 1][5]);
    draw_rectangle(positionX, positionY + WINDOW_HEIGHT * 0.01, 40, 40);
    pop_settings();
    draw_image(MaterialImage[input->getName()], positionX, positionY + WINDOW_HEIGHT * 0.01);

    push_settings();
    no_outline();
    set_font_size(LISTFONTSIZE);
    set_outline_color(chapterColor[nowTheme + 1][3], chapterColor[nowTheme + 1][4], chapterColor[nowTheme + 1][5]);
    set_fill_color(chapterColor[nowTheme + 1][3], chapterColor[nowTheme + 1][4], chapterColor[nowTheme + 1][5]);
    draw_text(input->getName(), positionX + WINDOW_WIDTH * 0.02, positionY);
    draw_text(to_string(input->getExtractPoint()), positionX + WINDOW_WIDTH * 0.15, positionY); //-WINDOW_WIDTH * 0.22
    draw_text(to_string(count), positionX + WINDOW_WIDTH * 0.22, positionY); //-WINDOW_WIDTH * 0.15
    if (MouseIsPressed == false && wasMousePressed == true && whichMaterial.size() < 2 &&
        Helpers::Collision::objToMouse({ positionX + WINDOW_WIDTH * 0.35, positionY }, 40, 40))
    {
        set_fill_color(255, 120, 120, 160);
        --status.inventoryMaterial[input];
        whichMaterial.push_back(input);
    }
    else
    {
        set_fill_color(255, 255, 255, 160);
    }

    draw_rectangle(positionX + WINDOW_WIDTH * 0.35, positionY + WINDOW_HEIGHT * 0.005, 40);// check box
    if(chamberTutorial == true && whichMaterial.size() != 2)//tutorial
    {
        ch.operator()({ positionX + WINDOW_WIDTH * 0.35, positionY + WINDOW_HEIGHT * 0.005 }, 20);
    }
    pop_settings();
}


void GameChamberScene::update()
{
    if (whichMaterial.size() >= 1 && phase == before)
    {
        if (whichMaterial.size() == 2)
        {
            extractButton.set_button_working(true);
        }
        resetButton.set_button_working(true);
    } else
    {
        extractButton.set_button_working(false);
        resetButton.set_button_working(false);
    }
    if (chamberBackButton.get_button_status() == true)
    {
        SceneChangeInput::toGameMain();
    }
    if (chapter1Button.get_button_status() == true)
    {
        nowTheme = Item::Theme::forest;
    }
    if (chapter2Button.get_button_status() == true)
    {
        nowTheme = Item::Theme::desert;
    }
    if (chapter3Button.get_button_status() == true)
    {
        nowTheme = Item::Theme::skypia;
    }
    if (chapter4Button.get_button_status() == true)
    {
        nowTheme = Item::Theme::abyss;
    }
    if (chapter5Button.get_button_status() == true)
    {
        nowTheme = Item::Theme::hellgate;
    }
    if (chapter6Button.get_button_status() == true)
    {
        nowTheme = Item::Theme::hell;
    }

    if (resetButton.get_button_status() == true)
    {
        for (auto w : whichMaterial)
        {
            status.inventoryMaterial[w]++;
        }
        whichMaterial.clear();
    }
    if (okButton.get_button_status() == true)
    {
        dices[0].reset();
        dices[1].reset();
        getItemName = {};
        point       = 0;
        whichMaterial.clear();
        phase = before;
    }
    if (extractButton.get_button_status() == true && dices[0].get_is_rolled() == false)
    {
        phase = during;
        for (auto& d : dices)
        {
            d.do_roll();
        }
        chamberTutorial = false;
        forgeTutorial = true;
    }
    if (dices[0].get_animation_end() == true)
    {
        if (phase == during)
        {
            do_extract();
            phase = check;
        }
    }
}

void GameChamberScene::getList(Item::Theme input)
{
    int i = 0;
    for (auto iter = status.inventoryMaterial.begin(); iter != status.inventoryMaterial.end(); iter++)
    {
        if (iter->first->theme == input)
        {
            if (iter->second != 0)
            {
              
                draw_item_list(iter->first, i, iter->second);
                i++;
            }
        }
    }
}


void GameChamberScene::draw()
{
    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    chamberBackButton.draw_button();
    chapter1Button.draw_button();
    chapter2Button.draw_button();
    chapter3Button.draw_button();
    chapter4Button.draw_button();
    chapter5Button.draw_button();
    chapter6Button.draw_button();
    extractButton.draw_button();
    resetButton.draw_button();
    draw_image(UIImage["chamber-" + to_string(now_chapter) + "." + to_string(static_cast<int>(nowTheme)+1)], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    push_settings();
    set_outline_color(chapterColor[nowTheme + 1][3], chapterColor[nowTheme + 1][4], chapterColor[nowTheme + 1][5]);
    set_fill_color(chapterColor[nowTheme + 1][3], chapterColor[nowTheme + 1][4], chapterColor[nowTheme + 1][5]);
    set_font_size(HEADFONTSIZE);
    no_outline();
    draw_text("Name", -WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.28);
    draw_text("Point", -WINDOW_WIDTH * 0.22, WINDOW_HEIGHT * 0.28);
    draw_text("Amount", -WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.28);
    draw_text("Pick", -WINDOW_WIDTH * 0.033, WINDOW_HEIGHT * 0.28);
    getList(nowTheme);
    pop_settings();
    push_settings();
    set_outline_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    if (whichMaterial.empty() == false)
    {
        for (int i = 0; i < whichMaterial.size(); i++)
        {
            set_font_size(DIALOGUESIZE);
            no_outline();
            draw_text(whichMaterial[i]->getName() + "\n : " + to_string(whichMaterial[i]->getExtractPoint()) + " pt", WINDOW_WIDTH * 0.115 + i * WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.25);
        }
    }
    
    if (whichMaterial.size() == 2)
    {
        for (auto& d : dices)
        {
            d.draw();
        }
    }
    if (phase == check)
    {
        set_font_size(DIALOGUESIZE);
        draw_text("You got points: " + to_string(point) + "\n\nYou got essence: \n" + getItemName, WINDOW_WIDTH * 0.15, -WINDOW_HEIGHT * 0.05);
        okButton.draw_button();
    }
    pop_settings();

    if (chamberTutorial == true && whichMaterial.size() == 2)//tutorial
    {
        extractButton.click_me(0x000000ff);
    }
}

void GameChamberScene::do_extract()
{
    point = (whichMaterial[0]->getExtractPoint() + whichMaterial[1]->getExtractPoint()) * dices[0].get_num() *
            dices[1].get_num();
    getEssence(point, whichMaterial[0]->theme);
}

void GameChamberScene::getEssence(int input_point, Item::Theme theme)
{
    if (input_point >= 720)
    {
        for (auto E : essences)
        {
            if(E->theme == theme && E->value == Item::Epic)
            {
                status.inventoryEssence[E]++;
                getItemName = E->getName();
            }
        }
        if(forgeTutorial == true && status.money == 0)//tutorial
        {
            status.money += 5000;
        }
    }
    else if (input_point >= 120)
    {
        for (auto E : essences)
        {
            if (E->theme == theme && E->value == Item::Unique)
            {
                status.inventoryEssence[E]++;
                getItemName = E->getName();
            }
        }
        if (forgeTutorial == true && status.money == 0)//tutorial
        {
            status.money += 2000;
        }
    }
    else if (input_point >= 64)
    {
        for (auto E : essences)
        {
            if (E->theme == theme && E->value == Item::Rare)
            {
                status.inventoryEssence[E]++;
                getItemName = E->getName();
            }
        }
        if (forgeTutorial == true && status.money == 0)//tutorial
        {
            status.money += 500;
        }
    } else
    {
        for (auto E : essences)
        {
            if (E->theme == theme && E->value == Item::Common)
            {
                status.inventoryEssence[E]++;
                getItemName = E->getName();
            }
        }
        if (forgeTutorial == true && status.money == 0)//tutorial
        {
            status.money += 100;
        }
    }
}