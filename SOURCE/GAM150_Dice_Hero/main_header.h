/*
File name: main_header.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "0_0_splash.h"
#include "0_1_play_scene.h"
#include "2_setting_scene.h"
#include "3_credit_scene.h"
#include "1_0_main_screen.h"
#include "1_0_2_quest.h"
#include "1_0_3_forge.h"
#include "1_0_4_chamber.h"
#include "1_0_5_inventory.h"
#include "1_1_ingame_screen.h"
#include "1_2_endgame_screen.h"
#include "scene_manager.h"
#include "Effect.h"
#include "1_0_6_stat.h"
#include "3_1_ending_scene.h"
#include "GameDataManager.h"

inline Scene* nowScene = nullptr;

inline void sceneChanger()//main_header.h
{
    if (isNumberChanged == true)
    {
        delete nowScene;
        events.clear();
        switch (currentNumber)
        {
            case SceneNumber::splash: nowScene = new Splash(); break;
            case SceneNumber::play_scene: nowScene = new PlayScene(); break;
            case SceneNumber::game_scene_main: 
                PlayerData::Instance().saveData();
                nowScene = new GameMainScene(); break;
            case SceneNumber::game_scene_quest: nowScene = new GameQuestScene(); break;
            case SceneNumber::game_scene_ingame:
                if(nowQuest->getCode() == 1 && status.openStage == 1)
                {
                    nowScene = new IngameTutorial();
                }
                else if(dynamic_cast<GoldQuest*>(nowQuest))
                {
                    nowScene = new IngameGoldQuest();
                }
                else if (dynamic_cast<MaterialQuest*>(nowQuest))
                {
                    nowScene = new IngameMatlQuest();
                }
                else if (dynamic_cast<BossQuest*>(nowQuest))
                {
                    nowScene = new IngameBossQuest();
                }
            break;
            case SceneNumber::setting_scene: nowScene = new SettingScene(); break;
            case SceneNumber::credit_scene: nowScene = new CreditScene(); break;
            case SceneNumber::ending_scene: nowScene = new EndingScene(); break;
            case SceneNumber::game_complete_scene:
                nowScene = new ClearScene(inInform.gold, inInform.exp,inInform.matl,inInform.boss);
            break;
            case SceneNumber::game_fail_scene:
                nowScene = new FailScene(inInform.gold,inInform.exp);
                break;//fail 갈 때 보상 수정
            case SceneNumber::game_scene_forge: nowScene = new GameForgeScene(); break;
            case SceneNumber::game_scene_chamber: nowScene = new GameChamberScene(); break;
            case SceneNumber::game_scene_inventory: nowScene = new GameInventoryScene(); break;
            case SceneNumber::game_stat_scene: nowScene = new GameStatScene(); break;
        }
        isNumberChanged = false;
    }
}

namespace data
{
    inline void readData()
    {
        commonMonster.set_data();
        setWeaponData();
        setArmorData();
        cout << "End Read Data" << endl;
    }
}
