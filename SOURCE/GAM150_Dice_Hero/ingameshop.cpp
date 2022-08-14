/*
File name: ingameshop.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "IngameSceneHelper.h"
#include "ingameShop.h"
#include "quest_info.h"



IngameShop::IngameShop(Vec2 size, int hasNum, int level, int location, unsigned long long& money, vector<IngameMagic*>& playerMagics)

    : size(size), hasMagicNum(hasNum), magicLevel(level), locationNum(location), playerMoney(&money),
      playerMagics(playerMagics)
{
    setup();
}

IngameShop::~IngameShop()
{
    for (auto& s : shopMagics)
    {
        delete s;
    }
}


void IngameShop::draw(string&& name)
{
    // draw shop
    //draw_rectangle(position.x, position.y, size.x, size.y);//보드에 그려지는 그림
    draw_image(objectImage[name], position.x, position.y);
    if (IsOpen == true && isEnter == true)
    {
        events.clear();
        draw_rectangle(BOARD_CENTER.x, BOARD_CENTER.y, shopWindowSize.x, shopWindowSize.y);
        for (auto& m : shopMagics)
        {
            m->draw_with_price();
            if (m->area() == true)
            {
                Helpers::Information::ingameInforation(m->get_info());
            }
        }
        exitButton.draw_button();
        if (selectedMagic.is_empty() == false)
        {
            selectedMagic.draw();
            // text selected
            //text price
            buyButton.draw_button();
        }
        /*draw magics, draw buttons*/
    }
    if(isEnter == false && IsOpen == true)
    {
        enterButton.draw_button();
    }
}


void IngameShop::update()
{
    if (charLoca == locationNum)
    {
        IsOpen = true;
    }
    else
    {
        IsOpen = false;
    }

    if (IsOpen == false)
    {
        isEnter = false;
    }
    /*update when magic clicked set selected magic, check money, compute money, check button and exit or give
     * magic*/
    if (IsOpen == true && enterButton.get_button_status() == true)
    {
        isEnter = true;
        selectedMagic = {};
    }
    if (exitButton.get_button_status() == true)
    {
        isEnter = false;
    }

    if (buyButton.get_button_status() == true)
    {

        if (selectedMagic.is_empty() == false && playerMagics.size() < PlayerMagicMax
            && *playerMoney >= selectedMagic.get_price())
        {
            playerMagics.push_back(new IngameMagic{ selectedMagic });
            *playerMoney -= selectedMagic.get_price();
            buyButton.set_button_working(false);
        }
        else
        {
            if (playerMagics.size() >= PlayerMagicMax)
            {
                events.push_event(EventLog{ "Not enough space!!", WINDOW_WIDTH * 0., -WINDOW_HEIGHT * 0.,RGB{},40,7 });

            }
            if(*playerMoney < selectedMagic.get_price())
            {
                events.push_event(EventLog{ "\nNot enough money!!", WINDOW_WIDTH * 0., -WINDOW_HEIGHT * 0.,RGB{},40,7 });
            }
        }

    }
    else
    {
        buyButton.set_button_working(true);
    }

    for (auto& m : shopMagics)
    {
        if (m->area() == true && MouseIsPressed == true)
        {
            selectedMagic = *m;
            selectedMagic.set_pos(BOARD_CENTER.x, BOARD_CENTER.y - shopWindowSize.y * 1 / 5);
        }
    }

    move_location();
}


void IngameShop::setup()
{
    newMagicSet();
    set_location(locationNum);
}

void IngameShop::newMagicSet()
{
    double magicOffPosX{180};
    Vec2   magicStDrawPos{BOARD_CENTER};
    shopMagics.clear();
    for (int i = 0; i < hasMagicNum; ++i)
    {
        long double goal = 1;
        int time = 1;
        for (int k = 0; k < now_chapter; k++)
        {
            for (int j = 0; j < chapterNumber[k]; j++)
            {
                goal *= chapterRoot[k];
                time++;
                if (time > nowQuest->getCode())
                {
                    break;
                }
            }
            if (time > nowQuest->getCode())
            {
                break;
            }
        }
        AboutMagic::give_magic(shopMagics, static_cast<unsigned long long>(goal/5),magicLevel);
        magicStDrawPos.x = magicStDrawPos.x + magicOffPosX * i;
        shopMagics[i]->set_pos(magicStDrawPos.x, magicStDrawPos.y);
        magicOffPosX *= -1;
    }
}

void Peddler::move_location()
{
    if (*turn % MOVE_NUM == 1 && previousLocation == get_loca())
    {
        int willLoca{random(BOARD_START,BOARD_END)};
        if (willLoca == OBJECT_NUM || willLoca == BOSS_NUM || willLoca == MAGIC_TOWER_NUM || willLoca == BOARD_START)
        {
            ++willLoca;
        }
        set_location(willLoca);
    }
    else if (*turn % MOVE_NUM == 2)
    {
        previousLocation = get_loca();
    }
}
