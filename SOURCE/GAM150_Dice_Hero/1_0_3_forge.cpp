/*
File name: 1_0_3_forge.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_0_3_forge.h"
#include "game_header.h"
#include "UI.h"

template <typename T>
void GameForgeScene::draw_forge_item(T input, int number)
{
    positionY = WINDOW_HEIGHT * 0.25 - WINDOW_HEIGHT * 0.05 * number;
   
    switch (input->getClass())
    {
        case Warrior_C: 
             draw_image(
                EquipmentImage["sword" + to_string(input->getTheme() + 1) + "." + to_string(input->getValue() + 1)],
                positionX, positionY + gap);
            break;
        case Mage_C:
            draw_image(
                EquipmentImage["wand" + to_string(input->getTheme() + 1) + "." + to_string(input->getValue() + 1)],
                positionX, positionY + gap);
            break;
        case Thief_C:
            draw_image(
                EquipmentImage["knuckle" + to_string(input->getTheme() + 1) + "." + to_string(input->getValue() + 1)],
                positionX, positionY + gap);
            break;
        case Archer_C:
            draw_image(
                EquipmentImage["bow" + to_string(input->getTheme() + 1) + "." + to_string(input->getValue() + 1)],
                positionX, positionY + gap);
            break;
        case Public_Item: 
                    draw_image(
                EquipmentImage["armor" + to_string(input->getTheme() + 1) + "." + to_string(input->getValue() + 1)],
                positionX, positionY + gap);
            break;
    }

    push_settings();
    set_font_size(LISTFONTSIZE);
    no_outline();
    draw_text(input->getName(), positionX + WINDOW_WIDTH * 0.02, positionY);
    draw_text(std::move(input->getExplanation()), positionX + WINDOW_WIDTH * 0.185, positionY); //-WINDOW_WIDTH * 0.15,
    draw_text(to_string(input->getPrice()), positionX + WINDOW_WIDTH * 0.38, positionY); //WINDOW_WIDTH * 0.0
    draw_text(essence1.getStatus(static_cast<int>(input->getValue())) + " Essence", positionX + WINDOW_WIDTH * 0.52, positionY); //WINDOW_WIDTH * 0.17
    push_settings();
    set_fill_color(255, 255, 255, 160);
    if (MouseIsPressed == true && phase == shop &&
        Helpers::Collision::objToMouse({ positionX + WINDOW_WIDTH * 0.67, positionY + gap }, 40, 40) == true)
    {
        set_fill_color(255, 120, 120, 160);
    }
    else if (wasMousePressed == true && MouseIsPressed == false && phase == shop &&
            Helpers::Collision::objToMouse({ positionX + WINDOW_WIDTH * 0.67, positionY + gap }, 40, 40) == true)
    {
         chosenItem = input;
         for (auto iter = status.inventoryEssence.begin(); iter != status.inventoryEssence.end(); iter++)
         {
             if (iter->first->theme == chosenItem->theme &&
                 iter->first->value == chosenItem->value && iter->second > 0 &&
                 status.money >= chosenItem->getPrice())
             {
                 neededEssence = iter->first;
                 phase = buy;

             }
         }
         if (neededEssence == nullptr)
         {
             phase = cannot;
         }
    }
    if (phase == buy) 
    {
        push_settings();
        draw_image(guide, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT + gap);
        set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4],
                       chapterColor[now_chapter][5]);
        set_font_size(TOPSIZE);
        no_outline();
        draw_text("Are you sure you want to buy it? \n", -385, 110);
        set_font_size(DIALOGUESIZE);
        draw_text("Item: " + chosenItem->getName(), -270, 0);
        draw_text("Cost: " + to_string(chosenItem->getPrice()) + " gold, " +
                      essence1.getStatus(static_cast<int>(chosenItem->getValue())) + " Essence", -270, -100);
        //draw_text("Price: " + to_string(chosenItem->getPrice()) + " gold" , -250, -100);
        //draw_text("Essence: " + essence1.getStatus(static_cast<int>(chosenItem->getValue())), -250, -200);
        pop_settings();
        forgeBuyButton.draw_button();
        forgeCancelButton.draw_button();
        if (forgeBuyButton.get_button_status() == true)
        {
            status.money -= chosenItem->getPrice();
            status.inventoryEssence[neededEssence]--;
            status.inventoryEquipment[chosenItem]++;
            neededEssence = nullptr;
            chosenItem = nullptr;
            phase = shop;
            if (forgeTutorial == true)//tutorial
            {
                forgeTutorial = false;//tutorial
                equipmentTutorial = true;//tutorial
            }
        }
        else if (forgeCancelButton.get_button_status() == true)
        {
            neededEssence = nullptr;
            chosenItem = nullptr;
            phase = shop;
        }
    }
    if (phase == cannot)
    {
        push_settings();
        draw_image(guide, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4],
                       chapterColor[now_chapter][5]);
        set_font_size(DIALOGUESIZE);
        no_outline();
        draw_text("Not enough cost!\n", -150, 0);
        pop_settings();
        forgeOKButton.draw_button();
        if (forgeOKButton.get_button_status() == true)
        {
            chosenItem = nullptr;
            phase = shop;
        }
    }
    pop_settings();
    draw_rectangle(positionX + WINDOW_WIDTH * 0.67, positionY + gap, 40);
}

void GameForgeScene::setup()
{
    //선택 안 된 무기 상점에 넣기 (map)
    for (auto itr= weaponData.begin(); itr != weaponData.end(); ++itr)
    {
        if (itr->second.getTheme() == now_chapter - 1)
        {
            forgeItem.push_back(&(itr->second));
        }
    }
    for (auto itr = armorData.begin(); itr != armorData.end(); ++itr)
    {
        if (itr->second.getTheme() == now_chapter - 1)
        {
            forgeItem.push_back(&(itr->second));
        }
    }
}

void GameForgeScene::update()
{
    if (forgeBackButton.get_button_status() == true && phase == forgePhase::shop)
    {
        SceneChangeInput::toGameMain();
    }
    if (valueCommon.get_button_status() == true && phase == forgePhase::shop)
    {
        nowValue = Item::Common;
    }
    if (valueRare.get_button_status() == true && phase == forgePhase::shop)
    {
        nowValue = Item::Rare;
    }
    if (valueUnique.get_button_status() == true && phase == forgePhase::shop)
    {
        nowValue = Item::Unique;
    }
    if (valueEpic.get_button_status() == true && phase == forgePhase::shop)
    {
        nowValue = Item::Epic;
    }
}

void GameForgeScene::draw()
{
    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    forgeBackButton.draw_button();
    valueCommon.draw_button();
    valueRare.draw_button();
    valueUnique.draw_button();
    valueEpic.draw_button();
    //현재 돈 추가 + 플레이어가 상점에서 필요한 정보 표시
    push_settings();
    set_outline_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    draw_image(UIImage["forge-" + to_string(now_chapter) + "." + to_string(static_cast<int>(nowValue)+1)], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    set_font_size(HEADFONTSIZE);
    no_outline();
    draw_text("Name", -WINDOW_WIDTH * 0.33, WINDOW_HEIGHT * 0.3);
    draw_text("Capability", -WINDOW_WIDTH * 0.165, WINDOW_HEIGHT * 0.3);
    draw_text("Price: Gold   +  ", WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.3);
    draw_text("Essence", WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.3);
    draw_text("Buy", WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3);
    draw_image(gold, -WINDOW_WIDTH * 0.3, -WINDOW_HEIGHT * 0.32, 90, 90);
    draw_text(":  " + to_string(status.money), -WINDOW_WIDTH * 0.27, -WINDOW_HEIGHT * 0.35);

    //무기로 변경
    ////판매 가능한 목록 그리기
    for (unsigned int i = 0, l = 0; i < forgeItem.size(); i++)
    {
        if(forgeItem[i]->getValue() == nowValue)
        {
            draw_forge_item(forgeItem[i], l);
            l++;
        }
        //범위 내에 클릭했을 때 구입 가능한 상태로 (check 상태 바꾸기)
    }
    pop_settings();
}
