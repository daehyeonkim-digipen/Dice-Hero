/*
File name: GameDataManager.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "GameDataManager.h"
#include "game_header.h"
#include <fstream>


void PlayerData::clear_data(int i)
{
    ofstream data{ slot[i] };
    data << "level: " << 1 << endl;
    data << "money: " << 0 << endl;
    data << "exp: " << 0 << endl;
    data << "expGoal: " << 10 << endl;
    data << "openStage: " << 1 << endl;
    data << "skillPoint: " << 0 << endl;
    for (auto it = status.inventoryMaterial.begin();it != status.inventoryMaterial.end();++it)
    {
        data << "Matrial: " << it->first->getName() << " " << 0 << endl;
    }
    for (auto it = status.inventoryEssence.begin();it != status.inventoryEssence.end();++it)
    {
        data << "Essence: " << it->first->getName() << "\n" << 0 << endl;
    }
    for (auto it = status.inventoryEquipment.begin();it != status.inventoryEquipment.end();++it)
    {
        data << "Equipment: " << it->first->getName() << "\n" << 0 << endl;
    }
    data << "WarriorTree" << endl;
    for ([[maybe_unused]] auto& s : WarriorTree.skills)
    {
        data << 0 << endl;
    }
    data << "MageTree" << endl;
    for ([[maybe_unused]] auto& s : MageTree.skills)
    {
        data << 0 << endl;
    }
    data << "ThiefTree" << endl;
    for ([[maybe_unused]]auto& s : ThiefTree.skills)
    {
        data << 0 << endl;
    }
    data << "ArcherTree" << endl;
    for ([[maybe_unused]] auto& s : ArcherTree.skills)
    {
        data << 0 << endl;
    }
    data << "WarriorArmor: " << "None" << endl;
    data << "WarriorWeapon: " << "None" << endl;
    data << "MageArmor: " << "None" << endl;
    data << "MageWeapon: " << "None" << endl;
    data << "ThiefArmor: " << "None" << endl;
    data << "ThiefWeapon: " << "None" << endl;
    data << "ArcherArmor: " << "None" << endl;
    data << "ArcherWeapon: " << "None" << endl;
    data << "SoundScale: " << arts.getEffectSound() << endl;
    data << "BGMScale: " << arts.nowPlayBGM->getVolume() << endl;
    data.close();
    cout << "Clear: " + slot[i] << endl;
}

void PlayerData::saveData()
{
    ofstream data{ slot[choosen] };
    data << "level: "<<status.level<< endl;
    data << "money: " << status.money << endl;
    data << "exp: " << status.exp << endl;
    data << "expGoal: " << status.expGoal << endl;
    data << "clear: " << status.clear << endl;
    data << "openStage: " << status.openStage << endl;
    data << "skillPoint: " << status.skillPoint << endl;
    for (auto it = status.inventoryMaterial.begin();it != status.inventoryMaterial.end();++it)
    {
        data << "Matrial: " << it->first->getName() << " " << it->second << endl;
    }
    for (auto it = status.inventoryEssence.begin();it != status.inventoryEssence.end();++it)
    {
        data << "Essence: " << it->first->getName() << "\n" << it->second << endl;
    }
    for (auto it = status.inventoryEquipment.begin();it != status.inventoryEquipment.end();++it)
    {
        data << "Equipment: " << it->first->getName() << "\n" << it->second << endl;
    }
    data << "WarriorTree" << endl;
    for(auto &s:WarriorTree.skills)
    {
        data << s->get_skillon() << endl;
    }
    data << "MageTree" << endl;
    for (auto& s : MageTree.skills)
    {
        data << s->get_skillon() << endl;
    }
    data << "ThiefTree" << endl;
    for (auto& s : ThiefTree.skills)
    {
        data << s->get_skillon() << endl;
    }
    data << "ArcherTree" << endl;
    for (auto& s : ArcherTree.skills)
    {
        data << s->get_skillon() << endl;
    } 
    data << "WarriorArmor: "<< (myWarrior->get_armor() == nullptr ? "None": myWarrior->get_armor()->getName()) << endl;
    data << "WarriorWeapon: " << (myWarrior->get_weapon() == nullptr ? "None" : myWarrior->get_weapon()->getName()) << endl;
    data << "MageArmor: " << (myMage->get_armor() == nullptr ? "None" : myMage->get_armor()->getName()) << endl;
    data << "MageWeapon: " << (myMage->get_weapon() == nullptr ? "None" : myMage->get_weapon()->getName()) << endl;
    data << "ThiefArmor: " << (myThief->get_armor() == nullptr ? "None" : myThief->get_armor()->getName()) << endl;
    data << "ThiefWeapon: " << (myThief->get_weapon() == nullptr ? "None" : myThief->get_weapon()->getName()) << endl;
    data << "ArcherArmor: " << (myArcher->get_armor() == nullptr ? "None" : myArcher->get_armor()->getName()) << endl;
    data << "ArcherWeapon: " << (myArcher->get_weapon() == nullptr ? "None" : myArcher->get_weapon()->getName()) << endl;
    data << "SoundScale: " << arts.getEffectSound() << endl;
    data << "BGMScale: " << arts.nowPlayBGM->getVolume() << endl;
    data.close();
    cout << "Save: " + slot[choosen] << endl;
}
void PlayerData::loadData()
{
    ifstream data{ slot[choosen] };
    string text{};
    while (data >> text)
    {
        if (text == "level:")
        {
            data >> status.level;
        }
        else if (text == "money:")
        {
            data >> status.money;
        }
        else if (text == "exp:")
        {
            data >> status.exp;
        }
        else if (text == "expGoal:")
        {
            data >> status.expGoal;
        }
        else if (text == "openStage:")
        {
            data >> status.openStage;
        }
        else if (text == "clear:")
        {
            data >> status.clear;
        }
        else if (text == "skillPoint:")
        {
            data >> status.skillPoint;
        }
        else if (text == "Matrial:")
        {
            bool find{false};
            data >> text;
            for (auto& m : materials)
            {
                for (auto& chap : *m)
                {
                    if (text == chap->getName())
                    {
                        data >> status.inventoryMaterial[chap];
                        find = true;
                        break;
                    }
                }
                if(find == true)
                {
                    break;
                }
            }
        }
        else if (text == "Essence:")
        {
            getline(data, text);
            for (auto& e : essences)
            {
                if (text == " " + e->getName())
                {
                    data >> status.inventoryEssence[e];
                    break;
                }
            }
        }
        else if (text == "Equipment:")
        {
            bool find{false};
            getline(data, text);
            for (auto it = weaponData.begin();it!= weaponData.end();++it )
            {
                if (text == " " + it->second.getName())
                {
                    data >> status.inventoryEquipment[&(it->second)];
                    find = true;
                    break;
                }
            }
            for (auto it = armorData.begin();it != armorData.end();++it)
            {
                if (find == true)
                {
                    break;
                }
                if (text == " " + it->second.getName())
                {
                    data >> status.inventoryEquipment[&(it->second)];
                    break;
                } 
            }
        }
        else if(text == "WarriorTree")
        {
            for (auto& s : WarriorTree.skills)
            {
                data >> s->get_skillon();
            }
        }
        else if (text == "MageTree")
        {
            for (auto& s : MageTree.skills)
            {
                data >> s->get_skillon();
            }
        }
        else if (text == "ThiefTree")
        {
            for (auto& s : ThiefTree.skills)
            {
                data >> s->get_skillon();
            }
        }
        else if (text == "ArcherTree")
        {
            for (auto& s : ArcherTree.skills)
            {
                data >> s->get_skillon();
            }
        }
        else if (text == "WarriorWeapon:")
        {
        getline(data, text);
            if (text != " None") {
                for (auto it = weaponData.begin();it != weaponData.end();++it)
                {
                    if (text == " "+it->second.getName())
                    {
                        myWarrior->set_weapon(&(it->second));
                        break;
                    }
                }
            }
        }
        else if(text == "WarriorArmor:")
        {
        getline(data, text);
            if (text != " None") {
                for (auto it = armorData.begin();it != armorData.end();++it)
                {
                    if (text == " " + it->second.getName())
                    {
                        myWarrior->set_armor(&(it->second));
                        break;
                    }
                }
            }
        }
        else if (text == "MageArmor:")
        {
        getline(data, text);
        if (text != " None") {
            for (auto it = armorData.begin();it != armorData.end();++it)
            {
                if (text == " " + it->second.getName())
                {
                    myMage->set_armor(&(it->second));
                    break;
                }
            }
        }
        }
        else if (text == "MageWeapon:")
        {
        getline(data, text);
        if (text != " None") {
            for (auto it = weaponData.begin();it != weaponData.end();++it)
            {
                if (text == " " + it->second.getName())
                {
                    myMage->set_weapon(&(it->second));
                    break;
                }
            }
        }
        }
        else if (text == "ThiefArmor:")
        {
        getline(data, text);
        if (text != " None") {
            for (auto it = armorData.begin();it != armorData.end();++it)
            {
                if (text == " " + it->second.getName())
                {
                    myThief->set_armor(&(it->second));
                    break;
                }
            }
        }
        }
        else if (text == "ThiefWeapon:")
        {
        getline(data, text);
        if (text != " None") {
            for (auto it = weaponData.begin();it != weaponData.end();++it)
            {
                if (text == " " + it->second.getName())
                {
                    myThief->set_weapon(&(it->second));
                    break;
                }
            }
        }
        }
        else if (text == "ArcherArmor:")
        {
        getline(data, text);
            if (text != " None") {
            for (auto it = armorData.begin();it != armorData.end();++it)
            {
                if (text == " " + it->second.getName())
                {
                    myArcher->set_armor(&(it->second));
                    break;
                }
            }
        }
        }
        else if (text == "ArcherWeapon:")
        {
        getline(data, text);
            if (text != " None") {
            for (auto it = weaponData.begin();it != weaponData.end();++it)
            {
                if (text == " " + it->second.getName())
                {
                    myArcher->set_weapon(&(it->second));
                    break;
                }
            }
        }
        }
        else if (text == "SoundScale:")
        {
            data >> arts.getEffectSound();
        }
        else if (text == "BGMScale:")
        {
            data >> arts.getBGMSound();
        }
    
    }
    myWarrior->controlSkill();
    myMage->controlSkill();
    myThief->controlSkill();
    myArcher->controlSkill();
    data.close();
}

int PlayerData::read_level_data(int i)
{
    ifstream data{ slot[i] };
    int dataScore{ 0 };
    string text{};
    while (data >> text)
    {
        if (text == "level:")
        {
            data >> dataScore;
            break;
        }
    }
    data.close();
    return dataScore;
}
long long PlayerData::read_money_data(int i)
{
    ifstream data{ slot[i] };
    long long dataScore{ 0 };
    string text{};
    while (data >> text)
    {
        if (text == "money:")
        {
            data >> dataScore;
            break;
        }
    }
    data.close();
    return dataScore;
}
int PlayerData::read_clearStage_data(int i)
{
    ifstream data{ slot[i] };
    int dataScore{ 0 };
    string text{};
    while (data >> text)
    {
        if (text == "openStage:")
        {
            data >> dataScore;
            break;
        }
    }
    data.close();
    return dataScore;
}


void PlayerData::draw_simple_data(int i, double x, double y)
{
    static constexpr double windowStrinInterval{ 20 };
    static constexpr double stringHeight{ 25 };
    push_settings();
    set_outline_width(5);
    set_fill_color(chapterColor[0][3], chapterColor[0][4], chapterColor[0][5]);
    draw_rectangle(x, y, simple_data_w, simple_data_h);
    set_font_size(50);
    set_fill_color(255);
    no_outline();
    if (read_level_data(i) + read_money_data(i) + read_clearStage_data(i) <= 2)
    {
        draw_text("Empty", x - simple_data_w / 2 + windowStrinInterval, y- stringHeight);
    }
    else
    {
        draw_text("Level: " + to_string(read_level_data(i)), x - simple_data_w / 2 + windowStrinInterval, y + simple_data_interval- stringHeight);
        draw_text("Gold: " + to_string(read_money_data(i)), x - simple_data_w / 2 + windowStrinInterval, y- stringHeight);
        draw_text("Open Stage: " + to_string(read_clearStage_data(i)), x - simple_data_w / 2 + windowStrinInterval, y - simple_data_interval- stringHeight);
    }
    XButton.set_button_position({x+simple_data_w/2-25,y+simple_data_h/2-25});
    XButton.draw_button();
    if(XButton.get_button_status() == true)
    {
        clear_data(i);
    }
    pop_settings();
}


void PlayerData::draw_data_manage_window( std::string name, double x, double y)
{
    static constexpr double windowNameHeight{120};
    static constexpr double windowNameWidth{ 100 };
    push_settings();
    draw_image(backgroundObjImage["data_manage_window"],x, y, WWidth, WHeight);
    set_fill_color(0);
    set_font_size(TOPSIZE);
    no_outline();
    draw_text(name + "\nNow data: "+ slotName[choosen], x+ windowNameWidth - WWidth/2, y + WHeight/2 - windowNameHeight);
    
    for (int i = 0;i < slots.size();++i)
    {
        slots[i]->set_button_position({x + slotSTX + i * slotInterval, y+slotSTY});
        slots[i]->draw_button();
        draw_simple_data(i, x + slotSTX + i * slotInterval, y);
    }
    pop_settings();
}
void PlayerData::update_load_window(double x, double y)
{
    for (int i = 0;i < slots.size();++i)
    {
        if (slots[i]->get_button_status() == true)
        {
            choosen = { i };
            loadData();
            SceneChangeInput::toGameMain();
            eventOn = false;
            now_chapter = forest;
        }
    }
    if (Helpers::Collision::objToMouse({ x, y }, WWidth, WHeight) == false &&
        MouseIsPressed == true)
    {
        eventOn = false;
    }
}
void PlayerData::update_save_window(double x, double y)
{
    for (int i = 0;i < slots.size();++i)
    {
        if (slots[i]->get_button_status() == true)
        {
            choosen = { i };
            saveData();
        }
    }
    if (Helpers::Collision::objToMouse({ x, y }, WWidth, WHeight) == false &&
        MouseIsPressed ==true)
    {
        eventOn = false;
    }
}
