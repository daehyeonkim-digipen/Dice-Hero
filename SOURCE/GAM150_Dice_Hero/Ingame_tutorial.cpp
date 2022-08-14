/*
File name: ingame_tutorial.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_1_ingame_screen.h"
#include "IngameSceneHelper.h"

void IngameTutorial::setup()
{
    IngameGoldQuest::setup();
    half_black = Image{ "assets/half_black.png" };
}

void IngameTutorial::show_tuto( Vec2 pos, double wid , double hei )
{
    int col{ static_cast<int>((pos.x + (double)WINDOW_WIDTH/2 )/ (double)WINDOW_WIDTH* half_black.GetWidth())   };
    int row{ static_cast<int>(( (double)WINDOW_HEIGHT/2 - pos.y) / (double)WINDOW_HEIGHT*half_black.GetHeight()) };

    show_tuto(col,row, static_cast<int>((double)wid / (double)WINDOW_WIDTH * half_black.GetWidth()),
        static_cast<int>(hei/(double)WINDOW_HEIGHT * half_black.GetHeight()));
}
void IngameTutorial::show_tuto(int col, int row, int wid, int hei)
{
    recopy_half_black();
    for (int i = 0;i < wid;++i)
    {
        for (int j = 0;j < hei;++j)
        {
            if(col + i>=half_black.GetWidth()||row+j >=half_black.GetHeight())
            {
                break;
            }
            half_black.operator()(col + i, row + j) = Color{ 0,0 };
        }
    }
    tutorialStop = true;
}


void IngameTutorial::behavior_tuto_st(Tutorial tt)
{
    tuNum = tt;
    recopy_half_black();
    tutorialStop = true;
}
void IngameTutorial::UI_none()
{

    if (nowTurn == 2)
    {
        tutoTextNum = -1;
        tuNum = Tutorial::INGAME_SHOP;
        show_tuto(Vec2{ magicTower.get_pos().x - objectImage["Magic tower"].GetWidth() /2,
            magicTower.get_pos().y + objectImage["Magic tower"].GetHeight() / 2 }, 
            objectImage["Magic tower"].GetWidth(), objectImage["Magic tower"].GetHeight());// magic tower
        doodle::MouseButton = doodle::MouseButtons::None;

    }
    else if (warrior == false && dynamic_cast<Warrior*>(myCharacters[whosTurn]) != nullptr)
    {
        behavior_tuto_st(Tutorial::BEHAVIOR_WARRIOR);
        warrior = true;
    }
    else if (mage == false && dynamic_cast<Mage*>(myCharacters[whosTurn]) != nullptr)
    {
        behavior_tuto_st(Tutorial::BEHAVIOR_MAGE);
        mage = true;
    }
    else if (thief == false&& dynamic_cast<Thief*>(myCharacters[whosTurn]) != nullptr)
    {
        behavior_tuto_st(Tutorial::BEHAVIOR_THIEF);
        thief = true;
    }
    else if (archer == false && dynamic_cast<Archer*>(myCharacters[whosTurn]) != nullptr)
    {
        behavior_tuto_st(Tutorial::BEHAVIOR_ARCHER);
        archer = true;
    }
}

void IngameTutorial::update()
{
    if (tutorialStop == false)
    {
        IngameGoldQuest::update();
        switch (tuNum)
        {
        case Tutorial::NONE:
            tuNum = Tutorial::UI;
            show_tuto(0,0,20,14);
            break;
        case Tutorial::UI_NONE:
            UI_none();
            break;
        case Tutorial::INGAME_SHOP_NONE:
            if(playerMagics.size()>0)
            {
                tuNum = Tutorial::MAGIC;
                show_tuto(38, 0, 22, 12);
                doodle::MouseButton = doodle::MouseButtons::None;
            }
            break;
        default:break;
        }
    }
}
void IngameTutorial::draw()
{
    IngameGoldQuest::draw();
    if (tutorialStop == true)
    {
        events.clear();
        draw_image(half_black,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
        switch (tuNum)
        {
        case Tutorial::UI:
            UI_tuto();
            break;
        case Tutorial::BEHAVIOR_WARRIOR: 
            base_be();
            break;
        case Tutorial::BEHAVIOR_MAGE:
            base_be();
            break;
        case Tutorial::BEHAVIOR_THIEF:
            be_thief();
            break;
        case Tutorial::BEHAVIOR_ARCHER:
            base_be();
            break;
        case Tutorial::INGAME_SHOP:
            ingame_shop();
            break;
        case Tutorial::MAGIC:
            draw_tuto(0, WINDOW_HEIGHT * -0.3, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3);
            if (MouseIsPressed == true)
            {
                tutoTextNum = 0;
                tutorialStop = false;
                tuNum = Tutorial::MAGIC_NONE;
            }
            break;

        default:tutorialStop = false; break;
        }
        
    }
}

void IngameTutorial::UI_tuto()
{
    Profile profile{ myCharacters[0]->get_class_name(), -WINDOW_WIDTH * 0.4,
                                             WINDOW_HEIGHT * (0.43 - 0), WINDOW_WIDTH / 13, WINDOW_HEIGHT / 32,
                                             myCharacters[0]->get_hp(),
                                         myCharacters[0]->get_max_hp(),{120, 120, 255} };
    draw_tuto(0, WINDOW_HEIGHT * -0.3, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3);
    switch (tutoTextNum)
    {
    case 0:
        profile.high_lighting();
        profile.draw();
        dynamic_cast<Profile*>(&profile)->drawing(myCharacters[0]->get_class_name(), 2);
        if (profile.area() == true)
        {
            show_tuto(38, 19, 22, 12);
            ++tutoTextNum;
            doodle::MouseButton = doodle::MouseButtons::None;
        }
        break;
    case 1:
    case 2:
    case 3:
        Helpers::Information::ingameInforation(myCharacters[0]->get_information());
        if (Helpers::MouseButton::Rl_Button(MouseButtons::Left) == true)
        {
            if (tutoTextNum == 3)
            {
                show_tuto(0, 15, 20, 14);

            }
            ++tutoTextNum;
        }
        break;
    case 4:
        if (Helpers::MouseButton::Rl_Button(MouseButtons::Left) == true)
        {
            show_tuto(22, 8, 16, 14);
            ++tutoTextNum;
        }
        break;
    case 5:
        if (Helpers::MouseButton::Rl_Button(MouseButtons::Left) == true)
        {
            tutoTextNum = 0;
            tutorialStop = false;
            tuNum = Tutorial::UI_NONE;
        }
        break;


    default:
        break;
    }
    
}
void IngameTutorial::base_be()
{
    draw_tuto(0, WINDOW_HEIGHT * 0.3, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3);
    if (MouseIsPressed == true)
    {
        tutoTextNum = 0;
        tutorialStop = false;
        tuNum = Tutorial::UI_NONE;
    }
}


void IngameTutorial::be_thief()
{
    base_be();
}




void IngameTutorial::ingame_shop()
{
    if(tutoTextNum == 0)
    {
        draw_tuto(0, WINDOW_HEIGHT * 0.3, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3);
    }
    else if(tutoTextNum == 1)
    {
        draw_tuto(0, 0, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3);
    }
    if(tutoTextNum == -1 && Helpers::MouseButton::Rl_Button(MouseButtons::Left) == true)
    {
        ++tutoTextNum;
    }
    if (tutoTextNum == 0 && Helpers::MouseButton::Rl_Button(MouseButtons::Left) == true)
    {
        ++tutoTextNum ;
        show_tuto(Vec2{ tiles[peddler.get_loca()].getTilePos().x - objectImage["Peddler"].GetWidth() / 2,
            tiles[peddler.get_loca()].getTilePos().y + objectImage["Peddler"].GetHeight() / 2 },
            objectImage["Peddler"].GetWidth()*2, objectImage["Peddler"].GetHeight()*2 );
    }
    if (tutoTextNum == 1 && Helpers::MouseButton::Rl_Button(MouseButtons::Left) == true)
    {
        tutoTextNum=0;
        tutorialStop = false;
        tuNum = Tutorial::INGAME_SHOP_NONE;
    }
}



void IngameTutorial::draw_tuto(double x, double y, double w, double h)
{
    const double newY = y - WINDOW_HEIGHT * +0.02;
    push_settings();
    draw_image(objectImage["UI_board_Large_stone"],
        x, y, w * 1.1, h * 1.1);

    draw_image(objectImage["UI_board_Large_parchment"],
        x, y, w, h);
    draw_image(objectImage["Exclamation_Gray"],x,y+h*1.1/2);

    set_fill_color(0);
    set_font_size(LISTFONTSIZE);
    draw_text(tutorialText[static_cast<int>(tuNum)][tutoTextNum], x- w / 2 + w / 20, newY+h/2 - h/6);
    pop_settings();
}
