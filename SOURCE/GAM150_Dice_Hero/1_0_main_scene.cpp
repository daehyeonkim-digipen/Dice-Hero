/*
File name: 1_0_main_scene.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_0_main_screen.h"
#include "GameDataManager.h"
GameMainScene::GameMainScene()
{
    myWarrior->set_hp(myWarrior->get_max_hp());
    myMage->set_hp(myMage->get_max_hp());
    myThief->set_hp(myThief->get_max_hp());
    myArcher->set_hp(myArcher->get_max_hp());
}

void GameMainScene::status_update() {
    if(status.exp >= status.expGoal)
    {
        status.exp -= status.expGoal;
        status.level++;
        profile.set_now(status.exp);
        status.set_exp_goal();
        profile.set_max(status.expGoal);
    }
    gold.set_money(status.money);
}

void GameMainScene::setup()
{
    isGameLoaded = true;
    switch (now_chapter)
    {
        case forest: 
            if (arts.nowPlayBGM != &arts.Forest_BGM)
            {
                arts.PlayBGM(&arts.Forest_BGM); 
            }
            break;
        case desert:
            if (arts.nowPlayBGM != &arts.Desert_BGM)
            {
                arts.PlayBGM(&arts.Desert_BGM);
            }
            break;
        case skypia:
            if (arts.nowPlayBGM != &arts.Skypia_BGM)
            {
                arts.PlayBGM(&arts.Skypia_BGM);
            }
            break;
        case abyss:
            if (arts.nowPlayBGM != &arts.Abyss_BGM)
            {
                arts.PlayBGM(&arts.Abyss_BGM);
            }
            break;
        case hellgate:
            if (arts.nowPlayBGM != &arts.HellGate_BGM)
            {
                arts.PlayBGM(&arts.HellGate_BGM);
            }
            break;
        case hell:
            if (arts.nowPlayBGM != &arts.Hell_BGM)
            {
                arts.PlayBGM(&arts.Hell_BGM);
            }
            break;
    }
    if (isGodModeOn == true)
    {
        status.money = 10000000000;

        //equipment
        for (auto it = weaponData.begin(); it != weaponData.end(); ++it)
        {
            status.inventoryEquipment[&(it->second)]++;
        }
        for (auto it = armorData.begin(); it != armorData.end(); ++it)
        {
            status.inventoryEquipment[&(it->second)]++;
        }
        //essence
        for (const auto E : essences)
        {
            status.inventoryEssence[E]++;
        }
        //material
        for (const auto M : chapter1)
        {
            status.inventoryMaterial[M]++;
        }
        for (const auto M : chapter2)
        {
            status.inventoryMaterial[M]++;
        }
        for (const auto M : chapter3)
        {
            status.inventoryMaterial[M]++;
        }
        for (const auto M : chapter4)
        {
            status.inventoryMaterial[M]++;
        }
        for (const auto M : chapter5)
        {
            status.inventoryMaterial[M]++;
        }
        for (const auto M : chapter6)
        {
            status.inventoryMaterial[M]++;
        }
        status.level = 50;
        profile.set_now(status.exp);
        status.set_exp_goal();
        profile.set_max(status.expGoal);
        status.openStage = 42;
        isGodModeOn = false;
    }
    if(forgeTutorial == true)//tutorial
    {
        chamberTutorial = false;
    }
}

void GameMainScene::update() 
{
    if(Helpers::Keyboard::Rl_key(KeyboardButtons::C) == true)
    {
        SceneChangeInput::toEnding();
    }
    if (phase != main)
    {
        questButton.set_button_working(false);
        menuButton.set_button_working(false);
        ingameSettingButton.set_button_working(false);
        forgeButton.set_button_working(false);
        chapterButton.set_button_working(false);
        statsceneButton.set_button_working(false);
        inventoryButton.set_button_working(false);
        chamberButton.set_button_working(false);
        quitButton.set_button_working(false);

    } else
    {
        questButton.set_button_working(true);
        menuButton.set_button_working(true);
        ingameSettingButton.set_button_working(true);
        forgeButton.set_button_working(true);
        chapterButton.set_button_working(true);
        statsceneButton.set_button_working(true);
        inventoryButton.set_button_working(true);
        chamberButton.set_button_working(true);
        quitButton.set_button_working(true);
    }
    if (statsceneButton.get_button_status() == true)
    {
        SceneChangeInput::toGameStat();
        if (equipmentTutorial == true)
        {
            equipmentTutorial = false;//tutorial

        }
    }
    if (questButton.get_button_status() == true )
    {
        SceneChangeInput::toGameQuest();
    }
    if (ingameSettingButton.get_button_status() == true)
    {
        SceneChangeInput::toSetting();
    }
    if (forgeButton.get_button_status() == true)
    {
        SceneChangeInput::toGameForge();
    }
    if (chamberButton.get_button_status() == true)
    {
        SceneChangeInput::toGameChamber();
    }
    if (inventoryButton.get_button_status() == true)
    {
        SceneChangeInput::toGameInventory();
    }
    if (quitButton.get_button_status() == true)
    {
        SceneChangeInput::toPlay();
        PlayerData::Instance().saveData();
        status.level = 1;
        status.money = 0;
        status.exp = 0;
        status.expGoal = 0;
        status.clear = 0;
        status.openStage = 1;
        status.skillPoint = 0;
        status.inventoryMaterial.clear();
        status.inventoryEquipment.clear();
        status.inventoryEssence.clear();
        myWarrior->set_weapon(nullptr);
        myWarrior->set_armor(nullptr);
        myMage->set_weapon(nullptr);
        myMage->set_armor(nullptr);
        myThief->set_weapon(nullptr);
        myThief->set_armor(nullptr);
        myArcher->set_weapon(nullptr);
        myArcher->set_armor(nullptr);
    }

    if (chapterButton.get_button_status() == true)
    {
        cancelButton.set_button_position({WINDOW_WIDTH / 10, WINDOW_HEIGHT / 5});
        phase = chapter;
    }
    if (chapter_1Button.get_button_status() == true)
    {
        phase       = main;
        now_chapter = forest;
        setup();
    }
    if (chapter_2Button.get_button_status() == true)
    {
        phase   = main;
        now_chapter = desert;
        setup();
    }
    if (chapter_3Button.get_button_status() == true)
    {
        phase   = main;
        now_chapter = skypia;
        setup();
    }
    if (chapter_4Button.get_button_status() == true)
    {
        phase       = main;
        now_chapter = abyss;
        setup();
    }
    if (chapter_5Button.get_button_status() == true)
    {
        phase       = main;
        now_chapter = hellgate;
        setup();
    }
    if (chapter_6Button.get_button_status() == true)
    {
        phase       = main;
        now_chapter = hell;
        setup();
    }
    if (cancelButton.get_button_status() == true)
    {
        phase = main;
    }
    if (menuButton.get_button_status() == true)
    {
        if(menuOn == true)
        {
            menuOn = false;
        } else
        {
            menuOn = true;
        }
    }
    if(status.openStage > 10)
    {
        chapter_2Button.set_button_working(true);
    }
    if (status.openStage > 20)
    {
        chapter_3Button.set_button_working(true);
    }
    if (status.openStage > 24)
    {
        chapter_4Button.set_button_working(true);
    }
    if (status.openStage > 32)
    {
        chapter_5Button.set_button_working(true);
    }
    if (status.openStage > 37)
    {
        chapter_6Button.set_button_working(true);
    }
    status_update();
#ifdef _DEBUG
    //To main
    if(Helpers::Keyboard::Rl_key(KeyboardButtons::M) == true)
    {
        SceneChangeInput::toPlay();
    }
    if(Helpers::Keyboard::Rl_key(KeyboardButtons::S) == true)
    {
        PlayerData::Instance().saveData();
    }
#endif

}

void GameMainScene::draw()
{
    draw_image(chapterBackgrounds[now_chapter], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    push_settings();
    set_fill_color(chapterColor[now_chapter][0], chapterColor[now_chapter][1], chapterColor[now_chapter][2], 150);
    set_outline_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4],
                      chapterColor[now_chapter][5], 150);
    if (menuOn == true)
    {
        menuButton.draw_button();
        chamberButton.draw_button();
        inventoryButton.draw_button();
        statsceneButton.draw_button();
        ingameSettingButton.draw_button();
        quitButton.draw_button(); //메뉴 열 떄만 나오게
    }
    else if(menuOn == false)
    {
        menuButton.draw_button();
    }

    forgeButton.draw_button();
    chapterButton.draw_button();
    questButton.draw_button();
    if (status.openStage == 1)//tutorial
    {
        questButton.click_me(0x000000ff);
    }
    else if (status.openStage == 2 && chamberTutorial == true)//tutorial
    {
        if (menuOn == true)
        {
            chamberButton.click_me(0x000000ff);
        }
        else if (menuOn == false)
        {
            menuButton.click_me(0x000000ff);
        }
    }
    else if (forgeTutorial == true)//tutorial
    {
        forgeButton.click_me(0x000000ff);
    }
    else if(equipmentTutorial == true)//tutorial
    {
        if (menuOn == true)
        {
            statsceneButton.click_me(0x000000ff);
        }
        else if (menuOn == false)
        {
            menuButton.click_me(0x000000ff);
        }
    }

    if (phase == chapter)
    {
        draw_rectangle(0, 0, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 1.5);
        chapter_1Button.draw_button();
        chapter_2Button.draw_button();
        if(chapter_2Button.get_button_working() == false)
        {
            draw_image(buttonImage["closed2"], 0, WINDOW_HEIGHT * 0.15, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11);
        }
        chapter_3Button.draw_button();
        if (chapter_3Button.get_button_working() == false)
        {
            draw_image(buttonImage["closed3"], 0, WINDOW_HEIGHT * 0.05, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11);
        }
        chapter_4Button.draw_button();
        if (chapter_4Button.get_button_working() == false)
        {
            draw_image(buttonImage["closed4"], 0, -WINDOW_HEIGHT * 0.05, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11);
        }
        chapter_5Button.draw_button();
        if (chapter_5Button.get_button_working() == false)
        {
            draw_image(buttonImage["closed5"], 0, -WINDOW_HEIGHT * 0.15, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11);
        }
        chapter_6Button.draw_button();
        if (chapter_6Button.get_button_working() == false)
        {
            draw_image(buttonImage["closed6"], 0, -WINDOW_HEIGHT * 0.25, WINDOW_WIDTH / 8, WINDOW_HEIGHT / 11);
        }
        cancelButton.draw_button();
    }
    pop_settings();
    profile.draw();
    gold.draw();
}
