/*
File name: 1_0_2_quest.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song, Taeju Kwon
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_0_2_quest.h"


void GameQuestScene::player_scene()
{
    const auto imageWidth  = WINDOW_WIDTH / 1.5;
    const auto imageHeight = WINDOW_HEIGHT / 1.5;
    phase                  = 1;
    draw_image(signboard, 0, 0, imageWidth, imageHeight);
    push_settings();
    set_outline_width(8);
    // change line color per chapter
    set_outline_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
    draw_line(-imageWidth / 8, imageHeight / 2.7, -imageWidth / 8, -imageHeight / 2.7);
    pop_settings();
    warriorButton.draw_button();
    mageButton.draw_button();
    thiefButton.draw_button();
    archerButton.draw_button();
    if (selected.size() == 4)
    {
        startButton.draw_button();
    }
    else
    {
        applyButton.draw_button();
    }
    cancelButton.draw_button();
    if (!selected.empty())
    {
        for (auto j = 0; j < selected.size(); j++)
        {
            push_settings();
            set_font_size(HEADFONTSIZE);
            no_outline();
            set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
            draw_text( to_string(j + 1) + ".  " + selected[j]->get_class_name(), WINDOW_WIDTH * 0.13, WINDOW_HEIGHT * 0.18 - WINDOW_HEIGHT * 0.09 * j);

            pop_settings();
        }
    }
    /*switch (nowQuest->get_quest_type())
    {
        case QuestType::gold:
            draw_image(goldSign, -imageWidth / 4, imageHeight / 5, imageWidth / 10, imageHeight / 8);
            draw_text("Goal:" + nowQuest->get_gold_goal(), -imageWidth / 5, imageHeight * 0 );
            break;
        case QuestType::material:
            draw_image(materialSign, -imageWidth / 4, imageHeight / 5, imageWidth / 10, imageHeight / 8);
            draw_text("Goal:" + nowQuest->get_material_goal().name, -imageWidth / 5, imageHeight * 0);
            break;
        case QuestType::boss:
            draw_image(bossSign, -imageWidth / 4, imageHeight / 5, imageWidth / 10, imageHeight / 8);
            draw_text("Goal:" + nowQuest->get_boss_goal().get_boss_name(), -imageWidth / 5, imageHeight * 0);
            break;
    }*/

    //change text color per chapter
    if (dynamic_cast<GoldQuest*>(nowQuest))
    {
        push_settings();
        draw_image(goldSign, -imageWidth * 0.3, imageHeight * 0.25, imageWidth / 3, imageHeight / 4);
        draw_image(gold, -imageWidth * 0.3, imageHeight * 0.03, imageWidth / 6.5, imageHeight / 4);
        set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
        no_outline();
        set_font_size(HEADFONTSIZE);
        draw_text("Goal:\n" + to_string(nowQuest->get_gold_goal()), -imageWidth * 0.37, -imageHeight * 0.3);
        pop_settings();
    }
    else if (dynamic_cast<MaterialQuest*>(nowQuest))
    {
        push_settings();
        draw_image(materialSign, -imageWidth * 0.3, imageHeight * 0.25, imageWidth / 3, imageHeight / 4);
        draw_image(MaterialImage[nowQuest->get_material_goal()->getName()], -imageWidth * 0.3, imageHeight * 0.03, imageWidth / 6.5, imageHeight / 4);
        set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
        no_outline();
        set_font_size(HEADFONTSIZE);
        draw_text("Goal:\n" + nowQuest->get_material_goal()->getName(), -imageWidth * 0.4, -imageHeight * 0.3);
        pop_settings();
    }
    else if (dynamic_cast<BossQuest*>(nowQuest))
    {
        push_settings();
        draw_image(bossSign, -imageWidth * 0.3, imageHeight * 0.25, imageWidth / 3, imageHeight / 4);
        draw_image(enemyImage[nowQuest->get_boss_goal()->get_name()][0], -imageWidth * 0.3, imageHeight * 0.03, imageWidth / 6.5, imageHeight / 4);
        set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4], chapterColor[now_chapter][5]);
        no_outline();
        set_font_size(HEADFONTSIZE);
        draw_text("Goal:\n" + nowQuest->get_boss_goal()->get_name(), -imageWidth * 0.4, -imageHeight * 0.3);
        pop_settings();
    }

    if ( status.openStage == 1)//tutorial
    {
        if (selected.size() == 4)
        {
            startButton.click_me();
        }
        else
        {
            if(choose == true)
            {
                applyButton.click_me();
            }
            else
            {
                for (auto& s:selected)
                {
                    if(s == myWarrior)
                    {
                        warriorButton.can_high_lighting() = false;
                    }
                    if (s == myMage)
                    {
                        mageButton.can_high_lighting() = false;
                    }
                    if (s == myArcher)
                    {
                        archerButton.can_high_lighting() = false;
                    }
                    if (s == myThief)
                    {
                        thiefButton.can_high_lighting() = false;
                    }
                }
                warriorButton.click_me();
                mageButton.click_me();
                archerButton.click_me();
                thiefButton.click_me();
            }
        }
    }
}

void GameQuestScene::draw()
{
    draw_image(questBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (phase == 0)
    {
        questBackButton.draw_button();
        for (auto& list : questButtons)
        {
            push_settings();
            set_outline_width(5);
            if (list.get_button_working() == false)
            {
                set_fill_color(120);
            }
            else
            {
                set_fill_color(255);
            }
            draw_ellipse(list.Pos.x, list.Pos.y, list.buttonWidth, list.buttonHeight);
            if(list.name != "Gold")
            {
                if(enemyImage.find(list.name) != enemyImage.end())
                {
                    draw_image(enemyImage[list.name][0], list.Pos.x, list.Pos.y, list.buttonWidth, list.buttonHeight);
                } else
                {
                    draw_image(MaterialImage[list.name], list.Pos.x, list.Pos.y, list.buttonWidth, list.buttonHeight);
                }
            }
            pop_settings();
            list.draw_button();  
        }
        if (status.openStage == 1)//tutorial
        {
            questButtons[0].click_me();
        }
    }
    if (phase == 1)
    {
        player_scene();
    }
    
    
}
void GameQuestScene::update()
{

    if (Helpers::Keyboard::Rl_key(KeyboardButtons::A) == true)//cheat
    {
        ++status.openStage;
    }

    if (phase == 0)
    {
        if(questBackButton.get_button_status() == true)
        {
            SceneChangeInput::toGameMain();
        }
        for (auto& list : questButtons)
        {
            choose_quest_update(list);
        }
    }
    if (phase == 1)
    {
        if (warriorButton.get_button_status() == true)
        {
            which = 0;
            choose = true;
        }
        if (mageButton.get_button_status() == true)
        {
            which = 1;
            choose = true;
        }
        if (thiefButton.get_button_status() == true)
        {
            which = 2;
            choose = true;
        }
        if (archerButton.get_button_status() == true)
        {
            which = 3;
            choose = true;
        }
        if (applyButton.get_button_status() == true)
        {
            choose = false;
            vector<Character*>::iterator selecetItr;
            switch (which)
            {
                case 0:
                    selecetItr = find(selected.begin(), selected.end(), myWarrior);
                    if (selecetItr == selected.end())
                    {
                        selected.push_back(myWarrior);
                    }
                    break;
                case 1:
                    selecetItr = find(selected.begin(), selected.end(), myMage);
                    if (selecetItr == selected.end())
                    {
                        selected.push_back(myMage);
                    }
                    break;
                case 2:
                    selecetItr = find(selected.begin(), selected.end(), myThief);
                    if (selecetItr == selected.end())
                    {
                        selected.push_back(myThief);
                    }
                    break;
                case 3:
                    selecetItr = find(selected.begin(), selected.end(), myArcher);
                    if (selecetItr == selected.end())
                    {
                        selected.push_back(myArcher);
                    }
                    break;
                default: break;
            }
        }
        if (startButton.get_button_status())
        {
            SceneChangeInput::toIngame();
        }
        if (cancelButton.get_button_status() == true)
        {
            phase = 0;
            choose = false;
            selected.clear();
            delete nowQuest;
            nowQuest  = nullptr;
        }
    }
}

void GameQuestScene::choose_quest_update(Button& whatQuest)
{
    if (whatQuest.get_button_status() == true)
    {
        phase = 1;
        cancelButton.set_button_position({WINDOW_WIDTH * 0.28, WINDOW_HEIGHT * 0.25});
        if (whatQuest.get_button_code() == 10 || whatQuest.get_button_code() == 20 || whatQuest.get_button_code() == 24 || whatQuest.get_button_code() == 32 || whatQuest.get_button_code() == 37 || whatQuest.get_button_code() == 42)
        {
            switch (now_chapter)
            {
            case 1: nowQuest = new BossQuest(whatQuest.get_button_code(), new Ent(500, 96, 96, 200, 500, "Ent")); break;
            case 2: nowQuest = new BossQuest(whatQuest.get_button_code(), new Genie(8000, 96, 96, 1500, 2000, "Genie")); break;
            case 3: nowQuest = new BossQuest(whatQuest.get_button_code(), new Titan(180000, 96, 96, 12000, 16000, "Titan")); break;
            case 4: nowQuest = new BossQuest(whatQuest.get_button_code(), new KraKen(1500000, 192, 96, 200000, 300000, "KraKen")); break;
            case 5: nowQuest = new BossQuest(whatQuest.get_button_code(), new BlackDragon(100000000, 180, 160, 18000000, 20000000, "Black Dragon")); break;
            case 6: nowQuest = new BossQuest(whatQuest.get_button_code(), new DevilKing(4000000000, 120, 120, 800000000, 800000000, "DevilKing")); break;

            default: break;
            }
        }
        else if (whatQuest.get_button_name() != "Gold")
        {
            for(auto iter = materials[now_chapter - 1]->begin(); iter != materials[now_chapter - 1]->end(); iter++)
            {
                if((*iter)->getName() == whatQuest.get_button_name())
                {
                    nowQuest =
                        new MaterialQuest(whatQuest.get_button_code(), *iter);
                }
            }
        }
        else
        {
            long double goal = 1;
            int time = 1;
            for(int i = 0; i < now_chapter; i++)
            {
                for(int j = 0; j < chapterNumber[i]; j++)
                {
                    goal *= chapterRoot[i];
                    time++;
                    if(time > whatQuest.get_button_code())
                    {
                        break;
                    }
                }
                if (time > whatQuest.get_button_code())
                {
                    break;
                }
            }
             nowQuest = new GoldQuest(whatQuest.get_button_code(), static_cast<unsigned long long>(goal * 5 * (3)));
        }
    }
}

void GameQuestScene::setup()
{
    setup_helper(now_chapter);

    for (int i = 0; i < questButtons.size(); i++)
    {
        if (questButtons[i].get_button_code() <= status.openStage)
        {
            questButtons[i].set_button_working(true);
        }
    }
}

void GameQuestScene::setup_helper(int input)
{
    switch (input)
    {
        case 1:
            questButtons.assign(10, Button());
            questButtons[0] =
                Button{ "Gold", -WINDOW_WIDTH * 0.485, WINDOW_HEIGHT * 0.01, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 1, false };
            questButtons[1] =
                Button{ "Gold", -WINDOW_WIDTH * 0.40, WINDOW_HEIGHT * 0.11, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 2, false };
            questButtons[2] =
                Button{ "Gold", -WINDOW_WIDTH * 0.28, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 3, false };
            questButtons[3] = 
                Button{ "Sapling", -WINDOW_WIDTH * 0.185, -WINDOW_HEIGHT * 0.145, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07,  4, false };
            questButtons[4] = Button{
                "Gold", -WINDOW_WIDTH * 0.07, -WINDOW_HEIGHT * 0.150, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 5, false };
            questButtons[5] = Button{
                "Gold", WINDOW_WIDTH * 0.025, -WINDOW_HEIGHT * 0.005, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 6, false };
            questButtons[6] =
                Button{ "Gold", WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.06, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 7, false };
            questButtons[7] =
                Button{ "Wolf Skin", WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07, 8, false };
            questButtons[8] = Button{
                "Gold", WINDOW_WIDTH * 0.35, -WINDOW_HEIGHT * 0.11, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 9, false };
            questButtons[9] =
                Button{ "Ent", WINDOW_WIDTH * 0.47, -WINDOW_HEIGHT * 0.07, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.08, 10, false };
            break;
        case 2:
            questButtons.assign(10, Button());
            questButtons[0] =
                Button{ "Gold", -WINDOW_WIDTH * 0.43, -WINDOW_HEIGHT * 0.38, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 11, false };
            questButtons[1] =
                Button{ "Gold", -WINDOW_WIDTH * 0.28, -WINDOW_HEIGHT * 0.4, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 12, false };
            questButtons[2] =
                Button{ "Gold", -WINDOW_WIDTH * 0.15, -WINDOW_HEIGHT * 0.42, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 13, false };
            questButtons[3] = 
                Button{ "Scorpion Sting", WINDOW_WIDTH * 0.0, -WINDOW_HEIGHT * 0.43, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07,  14, false };
            questButtons[4] = 
                Button{ "Gold", WINDOW_WIDTH * 0.14, -WINDOW_HEIGHT * 0.44, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 15, false };
            questButtons[5] =
                Button{ "Gold", WINDOW_WIDTH * 0.28, -WINDOW_HEIGHT * 0.42, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 16, false };
            questButtons[6] =
                Button{ "Gold", WINDOW_WIDTH * 0.18, -WINDOW_HEIGHT * 0.38, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 17, false };
            questButtons[7] =
                Button{ "Cactus Flower", WINDOW_WIDTH * 0.01, -WINDOW_HEIGHT * 0.35, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07, 18, false };
            questButtons[8] = 
                Button{ "Gold", -WINDOW_WIDTH * 0.156, -WINDOW_HEIGHT * 0.325, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 19, false };
            questButtons[9] =
                Button{ "Genie", -WINDOW_WIDTH * 0.03, -WINDOW_HEIGHT * 0.26, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.08, 20, false };
            break;
        case 3:
            questButtons.assign(4, Button());
            questButtons[0] =
                Button{ "Gold", WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.1, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 21, false };
            questButtons[1] =
                Button{ "Gold", WINDOW_WIDTH * 0.07, WINDOW_HEIGHT * 0, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 22, false };
            questButtons[2] =
                Button{ "AutoGun Barrel", -WINDOW_WIDTH * 0.05, -WINDOW_HEIGHT * 0.07, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 23, false };
            questButtons[3] = Button{
                "Titan", -WINDOW_WIDTH * 0.08, WINDOW_HEIGHT * 0.06, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07, 24,
                false};
            break;
        case 4:
            questButtons.assign(8, Button());
            questButtons[0] = Button{
                "Gold", WINDOW_WIDTH * 0.45, WINDOW_HEIGHT * 0.37, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 25,
                false};
            questButtons[1] = Button{
                "Gold", WINDOW_WIDTH * 0.32, WINDOW_HEIGHT * 0.35, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 26,
                false};
            questButtons[2] = Button{
                "Pearl", WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.25, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07, 27,
                false};
            questButtons[3] = Button{
                "Gold", WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.05, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 28,
                false};
            questButtons[4] = Button{
                "Gold", -WINDOW_WIDTH * 0.02, WINDOW_HEIGHT * 0.02, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 29,
                false};
            questButtons[5] = Button{
                "Esca", -WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.03, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07, 30,
                false};
            questButtons[6] = Button{
                "Gold", -WINDOW_WIDTH * 0.30, WINDOW_HEIGHT * 0.04, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 31,
                false};
            questButtons[7] = Button{
                "KraKen", -WINDOW_WIDTH * 0.42, WINDOW_HEIGHT * 0.05, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.08, 32,
                false};
            break;
        case 5:
            questButtons.assign(5, Button());
            questButtons[0] =
                Button{"Gold", -WINDOW_WIDTH * 0.135, WINDOW_HEIGHT * 0.08, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 33, false};
            questButtons[1] = Button{
                "Mimic Ring", -WINDOW_WIDTH * 0.12, -WINDOW_HEIGHT * 0.17, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 34, false};
            questButtons[2] = Button{
                "Mimic Map", WINDOW_WIDTH * 0.14, -WINDOW_HEIGHT * 0.07, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 35,
                false};
            questButtons[3] = Button{ "Diamond", WINDOW_WIDTH * 0.2, -WINDOW_HEIGHT * 0.33, WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.07, 36, false};
            questButtons[4] = Button{ "Black Dragon", -WINDOW_WIDTH *0.1, -WINDOW_HEIGHT * 0.42, WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.05, 37, false };
            break;
        case 6:
            questButtons.assign(5, Button());
            questButtons[0] =

                Button{ "Gold", WINDOW_WIDTH * 0.27, -WINDOW_HEIGHT * 0.45, WINDOW_WIDTH * 0.045, WINDOW_HEIGHT * 0.07, 38, false };
            questButtons[1] =
                Button{ "Efreet Lamp", -WINDOW_WIDTH * 0.23, -WINDOW_HEIGHT * 0.27, WINDOW_WIDTH * 0.04, WINDOW_HEIGHT * 0.06, 39, false };
            questButtons[2] =
                Button{ "Devil Claw", -WINDOW_WIDTH * 0.14, -WINDOW_HEIGHT * 0.1, WINDOW_WIDTH * 0.035, WINDOW_HEIGHT * 0.055, 40, false };
            questButtons[3] = Button{ "Basilisk Eye",          WINDOW_WIDTH * 0.06, WINDOW_HEIGHT * 0.03,
                                     WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.045,  41, false };
            questButtons[4] = Button{
                "DevilKing", -WINDOW_WIDTH * 0.09, WINDOW_HEIGHT * 0.08, WINDOW_WIDTH * 0.06, WINDOW_HEIGHT * 0.09, 42, false };
            break;
    }
}