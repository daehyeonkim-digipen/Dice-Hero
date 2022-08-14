/*
File name: 1_0_6_stat.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_0_6_stat.h"

void GameStatScene::draw_status(Character* which)
{
    const double positionX = -WINDOW_WIDTH * 0.4;
    push_settings();
    
    no_outline();
    set_font_size(TOPSIZE);
    draw_text(which->get_class_name(), -WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.28);
    set_font_size(DIALOGUESIZE);
    draw_text(which->get_information(), positionX, WINDOW_HEIGHT * 0.2);
    draw_image(characterImage[which->get_class_name()], -WINDOW_WIDTH * 0.18, WINDOW_HEIGHT * 0.3, 70, 70);

    if (which->get_weapon() == nullptr)
    {
        draw_text("Weapon:\nEmpty", positionX , -WINDOW_HEIGHT * 0.1);
    }
    else
    {
        unequipWeapon.draw_button();
        draw_text("Weapon:\n" + which->get_weapon()->getName(), positionX , -WINDOW_HEIGHT * 0.1);
    }
    if (which->get_armor() == nullptr)
    {
        draw_text("Armor:\nEmpty", positionX , -WINDOW_HEIGHT * 0.23);
    }
    else
    {
        unequipArmor.draw_button();
        draw_text("Armor:\n" + which->get_armor()->getName(), positionX , -WINDOW_HEIGHT * 0.23);
    }
    pop_settings();
}

void GameStatScene::draw_information(Character* which)
{
    switch (nowPhase)
    {
        case equipment:
        {
            int          i         = 0;
            if (maxPage >= 1 && page != 1)
            {
                UpButton.draw_button();
            } 
            if (page <= maxPage)
            {
                DownButton.draw_button();
            }
            push_settings();
            set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4],
                           chapterColor[now_chapter][5]);
            set_font_size(HEADFONTSIZE);
            no_outline();
            draw_text("Page:  " + to_string(page), WINDOW_WIDTH * 0.25, -WINDOW_HEIGHT * 0.35);
            set_font_size(HEADFONTSIZE);
            draw_text("Equip", WINDOW_WIDTH * 0.33, WINDOW_HEIGHT * 0.310);
            pop_settings();
            for (auto iter = status.inventoryEquipment.begin(); iter != status.inventoryEquipment.end(); iter++)
            {
                if ((iter->first->getClass() == which->myClass || iter->first->getClass() == Public_Item) &&
                    iter->second > 0)
                {
                    const double positionX = WINDOW_WIDTH * 0.07;
                    const double positionY = WINDOW_HEIGHT * 0.265 - WINDOW_HEIGHT * 0.05 * i + WINDOW_HEIGHT * 0.55 * (page - 1);
                    if (i >= 11 * (page - 1) && i <= 11 * page - 1)
                    {
                    
                    push_settings();
                    set_font_size(LISTFONTSIZE);
                    set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4],
                                   chapterColor[now_chapter][5]);
                    no_outline();
                    draw_text(iter->first->getName(), positionX + WINDOW_WIDTH * 0.05, positionY);
                    pop_settings();
                    push_settings();
                    if(MouseIsPressed && Helpers::Collision::objToMouse({ positionX + WINDOW_WIDTH * 0.28, positionY + WINDOW_HEIGHT * 0.01 }, 40, 40))
                    {
                        set_fill_color(255, 120, 120, 160);
                    } else
                    {
                        set_fill_color(255, 255, 255, 160);
                    }
                    draw_rectangle(positionX + WINDOW_WIDTH * 0.28, positionY + gap, 40); //change to image
                    switch (iter->first->getClass())
                    {
                        case Warrior_C:
                            draw_image(EquipmentImage["sword" + to_string(iter->first->getTheme() + 1) + "." +
                                                      to_string(iter->first->getValue() + 1)],
                                       positionX + WINDOW_WIDTH * 0.03, positionY + gap);
                            break;
                        case Mage_C:
                            draw_image(EquipmentImage["wand" + to_string(iter->first->getTheme() + 1) + "." +
                                                      to_string(iter->first->getValue() + 1)],
                                       positionX + WINDOW_WIDTH * 0.03, positionY + gap);
                            break;
                        case Thief_C:
                            draw_image(EquipmentImage["knuckle" + to_string(iter->first->getTheme() + 1) + "." +
                                                      to_string(iter->first->getValue() + 1)],
                                       positionX + WINDOW_WIDTH * 0.03, positionY + gap);
                            break;
                        case Archer_C:
                            draw_image(EquipmentImage["bow" + to_string(iter->first->getTheme() + 1) + "." +
                                                      to_string(iter->first->getValue() + 1)],
                                       positionX + WINDOW_WIDTH * 0.03, positionY + gap);
                            break;
                        case Public_Item:
                            draw_image(EquipmentImage["armor" + to_string(iter->first->getTheme() + 1) + "." +
                                                      to_string(iter->first->getValue() + 1)],
                                       positionX + WINDOW_WIDTH * 0.03, positionY + gap);
                            break;
                    }

                    draw_rectangle(positionX + WINDOW_WIDTH * 0.8, positionY + gap, 40);
                    }
                    maxPage = i / 11; 
                    if (MouseIsPressed == false && wasMousePressed == true &&
                        Helpers::Collision::objToMouse({positionX + WINDOW_WIDTH * 0.28, positionY + gap }, 40, 40))
                    {
                        if (iter->first->get_type() == 2 && which->get_armor() == nullptr)
                        {
                            which->set_armor(dynamic_cast<Armor*>(iter->first));
                            --iter->second;
                        }
                        else if (iter->first->get_type() == 1 && which->get_weapon() == nullptr)
                        {
                            which->set_weapon(dynamic_cast<Weapon*>(iter->first));
                            --iter->second;
                        }
                    }
                    else if (wasMousePressed == true && Helpers::Collision::objToMouse({positionX, positionY+ gap }, 40, 40))
                    {
                        set_fill_color(255, 120, 120, 160);
                    }
                    pop_settings();
                    i++;
                }
            }
        }
        break;

        case skills:
            statBuyButton.draw_button();
            statUpButton.draw_button();
            push_settings();
            no_outline();
            set_font_size(DIALOGUESIZE);
            draw_image(gold, WINDOW_WIDTH * 0.1, -WINDOW_HEIGHT * 0.32, 80, 80);
            draw_text(":  " + to_string(status.money), WINDOW_WIDTH * 0.13, -WINDOW_HEIGHT * 0.35);
            set_font_size(DIALOGUESIZE);
            draw_text("+" + to_string(buyPoint) + " (" + to_string(buyPoint * 50) + " Gold)", WINDOW_WIDTH * 0.09,
                      WINDOW_HEIGHT * 0.30);
            draw_text(to_string(status.skillPoint) + "pt", WINDOW_WIDTH * 0.325, -WINDOW_HEIGHT * 0.35);
            switch (which->myClass)
            {
                case Warrior_C:
                    draw_image(EquipmentImage["armor6.3"], WINDOW_WIDTH * 0.24, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.3,
                               WINDOW_WIDTH * 0.28);
                    break;
                case Mage_C:
                    draw_image(EquipmentImage["wand3.4"], WINDOW_WIDTH * 0.24, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.3,
                               WINDOW_WIDTH * 0.28);
                    break;
                case Thief_C:
                    draw_image(EquipmentImage["knuckle1.2"], WINDOW_WIDTH * 0.24, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.3,
                               WINDOW_WIDTH * 0.28);
                    break;
                case Archer_C:
                    draw_image(EquipmentImage["bow2.3"], WINDOW_WIDTH * 0.24, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.3,
                               WINDOW_WIDTH * 0.28);
                    break;
            }
            set_fill_color(characterColor[which->myClass][0], characterColor[which->myClass][1],
                           characterColor[which->myClass][2], 200);
            draw_rectangle(WINDOW_WIDTH * 0.24, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.3, WINDOW_WIDTH * 0.28);
            pop_settings();

            for (auto s : which->skilltree->skills)
            {
                s->draw();
                if (s->get_button().mouse_on_check() == true)
                {
                    push_settings();
                    set_fill_color(0);
                    no_outline();
                    set_font_size(DIALOGUESIZE);
                    draw_text(s->get_name() + "\nLevel: " + to_string(s->levelLimit()), get_mouse_x() + 40, get_mouse_y());
                    set_font_size(LISTFONTSIZE);
                    draw_text("\n\n" + s->get_description(), get_mouse_x() + 40, get_mouse_y());
                    pop_settings();
                }
                if (s->get_button().get_button_status() == true && s->get_skillon() == false && status.level >= s->levelLimit())
                {
                    if (status.skillPoint >= s->get_cost())
                    {
                        status.skillPoint -= s->get_cost();
                        s->get_skillon() = true;
                        which->controlSkill();
                        arts.PlaySound(getskill);
                    }
                    else
                    {
                        events.push_event(EventLog{"Not enough point", get_mouse_x(), get_mouse_y()});
                    }
                }
            }
    }
}

void GameStatScene::update()
{
    if(statBuyButton.get_button_status())
    {
        if(status.money >= buyPoint * 50)
        {
            status.money -= buyPoint * 50;
            status.skillPoint += buyPoint;
        } else
        {
            events.push_event(EventLog{ "Not enough gold",get_mouse_x(),get_mouse_y()});
        }
    }
    if(statUpButton.get_button_status())
    {
        if(buyPoint != 100000)
        {
            buyPoint *= 10;
        }
        else
        {
            buyPoint = 1;
        }  
    }
    if (statBackButton.get_button_status() == true)
    {
        SceneChangeInput::toGameMain();
    }
    if (statWarrior.get_button_status() == true)
    {
        nowCharacter = Warrior_C;
    }
    if (statMage.get_button_status() == true)
    {
        nowCharacter = Mage_C;
    }
    if (statThief.get_button_status() == true)
    {
        nowCharacter = Thief_C;
    }
    if (statArcher.get_button_status() == true)
    {
        nowCharacter = Archer_C;
    }
    if (unequipWeapon.get_button_status() == true)
    {
        status.inventoryEquipment[myCharacter->get_weapon()]++;
        myCharacter->set_weapon(nullptr);
    }

    if (unequipArmor.get_button_status() == true)
    {
        status.inventoryEquipment[myCharacter->get_armor()]++;
        myCharacter->set_armor(nullptr);
    }
    if(equeipmentButton.get_button_status() == true)
    {
        nowPhase = equipment;
    }
    if(skillButton.get_button_status() == true)
    {
        nowPhase = skills;
    }

    // page system
    if (UpButton.get_button_status() == true)
    {
        page--;
    }
    else if (DownButton.get_button_status() == true)
    {
        page++;
    }
}

void GameStatScene::draw()
{
    statWarrior.draw_button();
    statMage.draw_button();
    statThief.draw_button();
    statArcher.draw_button();
    equeipmentButton.draw_button();
    skillButton.draw_button();

    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    draw_image(UIImage["stat-" + to_string(now_chapter) + "." + to_string((static_cast<int>(nowCharacter + 1) * 2 - static_cast<int>(nowPhase)))], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    statBackButton.draw_button();

    push_settings();
    set_outline_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    switch (nowCharacter)
    {
        case Warrior_C:
            myCharacter = myWarrior;
            draw_status(myCharacter);
            draw_information(myCharacter);
            break;
        case Mage_C:
            myCharacter = myMage;
            draw_status(myCharacter);
            draw_information(myCharacter);
            break;
        case Thief_C:
            myCharacter = myThief;
            draw_status(myCharacter);
            draw_information(myCharacter);
            break; 
        case Archer_C:
            myCharacter = myArcher;
            draw_status(myCharacter);
            draw_information(myCharacter);
            break; 
    }
    pop_settings();
}