/*
File name: 1_0_5_inventory.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_0_5_inventory.h"

template <typename T>
void GameInventoryScene::draw_item_list(T input, int number, int count)
{
    positionY = WINDOW_HEIGHT * 0.25 - WINDOW_HEIGHT * 0.05 * number + WINDOW_HEIGHT * 0.55 * (page - 1);
    //add page system: 11, 22, 33, 44...
    if (number >= 11 * (page - 1) && number <= 11 * page - 1)
    {
        //essence image
        if (whichItemCase == essence)
        {
            string name = "essence" + to_string(input->getTheme() + 1) + "." + to_string(input->getValue() + 1);
            draw_image(EssenceImage[name], positionX, positionY + gap);
        }
        //equipment image
        else if (whichItemCase == equipment)
        {
            switch (input->getClass())
            {
                case Warrior_C:
                    draw_image(EquipmentImage["sword" + to_string(input->getTheme() + 1) + "." +
                                              to_string(input->getValue() + 1)],
                               positionX, positionY + gap);
                    break;
                case Mage_C:
                    draw_image(EquipmentImage["wand" + to_string(input->getTheme() + 1) + "." +
                                              to_string(input->getValue() + 1)],
                               positionX, positionY + gap);
                    break;
                case Thief_C:
                    draw_image(EquipmentImage["knuckle" + to_string(input->getTheme() + 1) + "." +
                                              to_string(input->getValue() + 1)],
                               positionX, positionY + gap);
                    break;
                case Archer_C:
                    draw_image(EquipmentImage["bow" + to_string(input->getTheme() + 1) + "." +
                                              to_string(input->getValue() + 1)],
                               positionX, positionY + gap);
                    break;
                case Public_Item:
                    draw_image(EquipmentImage["armor" + to_string(input->getTheme() + 1) + "." +
                                              to_string(input->getValue() + 1)],
                               positionX, positionY + gap);
                    break;
            }
        }
        //material image
        else if (whichItemCase == material)
        {
            push_settings();
            set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
            draw_rectangle(positionX, positionY + gap, 40, 40);
            pop_settings();
            draw_image(MaterialImage[input->getName()], positionX, positionY + gap);
        }

        push_settings();
        set_font_size(LISTFONTSIZE);
        no_outline();
        draw_text(input->getName(), positionX + WINDOW_WIDTH * 0.02, positionY);
        draw_text(to_string(input->getPrice()), positionX + WINDOW_WIDTH * 0.25, positionY);
        draw_text(to_string(count), positionX + WINDOW_WIDTH * 0.35, positionY);
        draw_text(input->getExplanation(), positionX + WINDOW_WIDTH * 0.5, positionY);
        if (MouseIsPressed == true && phase != sell &&
            Helpers::Collision::objToMouse({ positionX + WINDOW_WIDTH * 0.67, positionY + gap }, 40, 40) == true)
        {
            set_fill_color(255, 120, 120, 160);
        } else
        {
            set_fill_color(255, 255, 255, 160);
        }
        pop_settings();
        draw_rectangle(positionX + WINDOW_WIDTH * 0.67, positionY + WINDOW_HEIGHT * 0.005, 40);
    }

    //selling system
    push_settings();
    if (wasMousePressed == true && MouseIsPressed == false && phase != sell &&
             Helpers::Collision::objToMouse({positionX + WINDOW_WIDTH * 0.67, positionY + gap }, 40, 40) == true)
        {
            phase = sell;
            sellItem = input;
            sellmax  = count;
        }
    if (phase == sell) //selling page
        {
            push_settings();
            draw_image(guide, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            no_outline();
            set_font_size(TOPSIZE);
            set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
            draw_text("Are you sure you want to sell it? \n", -390, 110);
            set_font_size(DIALOGUESIZE);
            //������ �ȸ����� ����
            draw_text("Set amount of it: " + to_string(sellnum), -270, -50);
            draw_text("You will lose: " + sellItem->getName(), -270, 0);
            draw_text("You can get: " + to_string(static_cast<unsigned long long>(sellItem->getPrice()) * sellnum) + " gold", -270, -100);
            pop_settings();
            okButton.draw_button();
            cancelButton.draw_button();
            numUpButton.draw_button();
            numDownButton.draw_button();
        }
    if (okButton.get_button_status() == true)
        {
            switch (whichItemCase) 
            {
                case material: status.inventoryMaterial[dynamic_cast<Material*>(sellItem)] -= sellnum; break;
                case essence: status.inventoryEssence[dynamic_cast<Essence*>(sellItem)] -= sellnum; break;
                case equipment: status.inventoryEquipment[sellItem] -= sellnum; break;
            }
            status.money += static_cast<unsigned long long>(sellItem->getPrice()) * sellnum;
    		phase = bag;
            sellnum = 1;
        }
    else if (cancelButton.get_button_status() == true) 
        {
            phase = bag;
            sellnum = 1;
        }

    pop_settings();

}

void GameInventoryScene::update()
{
    if (inventoryBackButton.get_button_status() == true && phase != sell)
    {
        SceneChangeInput::toGameMain();
    }
    if (inventoryMaterialButton.get_button_status() == true && phase != sell)
    {
        whichItemCase = material;
        page          = 1;
    }
    if (inventoryEssenceButton.get_button_status() == true && phase != sell)
    {
        whichItemCase = essence;
        page          = 1;
    }
    if (inventoryEquipmentButton.get_button_status() == true && phase != sell)
    {
        whichItemCase = equipment;
        page          = 1;
    }

    //page system
    if (UpButton.get_button_status() == true && phase != sell)
    {
        page--;
    }
    else if (DownButton.get_button_status() == true && phase != sell)
    {
        page++;
    } 

    // set item num
    if (numUpButton.get_button_status() == true && sellnum < sellmax)
    {
        sellnum++;
    }
    else if (numDownButton.get_button_status() == true && sellnum >= 2)
    {
        sellnum--;
    }
}

void GameInventoryScene::draw()
{
    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    inventoryBackButton.draw_button();
    inventoryMaterialButton.draw_button();
    inventoryEssenceButton.draw_button();
    inventoryEquipmentButton.draw_button();

    draw_image(UIImage["inventory-" + to_string(now_chapter) + "." + to_string(static_cast<int>(whichItemCase))], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    push_settings();
    set_outline_width(3);
    set_outline_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    set_font_size(HEADFONTSIZE);
    no_outline();
    draw_text("Name", -WINDOW_WIDTH * 0.33, WINDOW_HEIGHT * 0.3);
    draw_text("Price", -WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.3);
    draw_text("Amount", WINDOW_WIDTH * 0.0, WINDOW_HEIGHT * 0.3);
    draw_text("Sell", WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3);
    draw_image(gold, -WINDOW_WIDTH * 0.3, -WINDOW_HEIGHT * 0.32, 90, 90);
    draw_text(":  " + to_string(status.money), -WINDOW_WIDTH * 0.27, -WINDOW_HEIGHT * 0.35);
    draw_text("Page:  " + to_string(page), WINDOW_WIDTH * 0.2, -WINDOW_HEIGHT * 0.35);

    if (maxPage >= 1 && page != 1) 
    {
       UpButton.draw_button(); 
    }
    if (page <= maxPage) 
    {
       DownButton.draw_button();  
    }

    switch (whichItemCase)
    {
        case material:
            {
                int i = 0;
                for (auto iter = status.inventoryMaterial.begin(); iter != status.inventoryMaterial.end(); iter++)
                {
                    if (iter->second != 0)
                    {
                        draw_item_list(iter->first, i, iter->second);
                        i++;
                    }
                }
                maxPage = i/ 11; 
            }
            break;
        case essence:
            {
                draw_text("Capability", WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.3);
                int i = 0;
                for (auto iter = status.inventoryEssence.begin(); iter != status.inventoryEssence.end(); iter++)
                {
                    if (iter->second != 0)
                    {
                        draw_item_list(iter->first, i, iter->second);
                        i++;
                    }
                }
                maxPage = i / 11;
            }
            break;

        case equipment:
            {
                draw_text("Capability", WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.3);
                int i = 0;
                for (auto iter = status.inventoryEquipment.begin(); iter != status.inventoryEquipment.end(); iter++)
                {
                    if (iter->second != 0)
                    {
                        draw_item_list(iter->first, i, iter->second);
                        i++;
                    }
                }
                maxPage = i / 11;
            } 
            break;
                
    }
    pop_settings();
}


