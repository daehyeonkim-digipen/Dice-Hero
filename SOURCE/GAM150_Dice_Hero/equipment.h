/*
File name: Equipment.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "item.h"
#include "game_header.h"

class Armor : public Item
{
protected:
    double df{0};
    double hp{0};
    string status[4] = {"Shabby", "Standard", "Sturdy", "Shining"};
public:
    Armor() :Item(0, Item::Value::Common, Item::Theme::forest) {}
    Armor(int input_price, Value input_value, Theme input_theme, string input_name)
        : Item(input_price, input_value, input_theme)
    {
        itemName = status[value] + " " + input_name + " of " + themename[theme];
        which = Public_Item;
        type = 2;
        switch (theme)
        {
        case forest:
            switch (value)
            {
            case Common:
                hp = 3;
                df = 5;
                break;
            case Rare:
                hp = 10;
                df = 10;                break;
            case Unique:
                hp = 30;
                df = 15;                break;
            case Epic:
                hp = 150;
                df = 50;                break;
            }
            break;
        case desert:
            switch (value)
            {
            case Common:
                hp = 15;
                df = 10;                break;
            case Rare:
                hp = 45;
                df = 20;                break;
            case Unique:
                hp = 120;
                df = 30;                break;
            case Epic:
                hp = 500;
                df = 60;                break;
            }
            break;
        case skypia:
            switch (value)
            {
            case Common:
                hp = 90;
                df = 15;                break;
            case Rare:
                hp = 300;
                df = 30;                break;
            case Unique:
                hp = 850;
                df = 45;                break;
            case Epic:
                hp = 4000;
                df = 70;                break;
            }
            break;
        case abyss:
            switch (value)
            {
            case Common:
                hp = 700;
                df = 20;                break;
            case Rare:
                hp = 2000;
                df = 35;                break;
            case Unique:
                hp = 6000;
                df = 50;                break;
            case Epic:
                hp = 25000;
                df = 80;                break;
            }
            break;
        case hellgate:
            switch (value)
            {
            case Common:
                hp = 5000;
                df = 25;                break;
            case Rare:
                hp = 16000;
                df = 45;                break;
            case Unique:
                hp = 50000;
                df = 65;                break;
            case Epic:
                hp = 160000;
                df = 90;                break;
            }
            break;
        case hell:
            switch (value)
            {
            case Common:
                hp = 100000;
                df = 40;                break;
            case Rare:
                hp = 350000;
                df = 60;                break;
            case Unique:
                hp = 1000000;
                df = 80;                break;
            case Epic:
                hp = 3500000;
                df = 100;
            }
            break;
        }
        itemExplanation = "maxHP*" + Helpers::floatData::to_one_point_string(hp) + ", DF*" + Helpers::floatData::to_one_point_string(df);
    }
    double get_df() { return df; }
    double get_hp() { return hp; }
};

class Weapon : public Item
{
protected:
    double ad{0};
    string status[4] = {"Shabby", "Standard", "Sturdy", "Shining"};

public:
    Weapon():Item(0,Item::Value::Common,Item::Theme::forest){}
    Weapon(int input_price, Value input_value, Theme input_theme, string input_name)
        : Item(input_price, input_value, input_theme)
    {
        itemName        = status[value] + " " + input_name + " of " + themename[theme];

        if (input_name[0] == 'S')
        {
            which = Warrior_C;
        }
        else if (input_name[0] == 'W')
        {
            which = Mage_C;
        }
        else if (input_name[0] == 'K')
        {
            which = Thief_C;
        }
        else if (input_name[0] == 'B')
        {
            which = Archer_C;
        }
        type = 1;
        switch(theme)
        {
        case forest:
            switch(value)
            {
            case Common:
                ad = 1.5;
                break;
            case Rare:
                ad = 5;
                break;
            case Unique:
                ad = 15;
                break;
            case Epic:
                ad = 70;
                break;
            }
            break;
        case desert:
            switch (value)
            {
            case Common:
                ad = 12;
                break;
            case Rare:
                ad = 35;
                break;
            case Unique:
                ad = 90;
                break;
            case Epic:
                ad = 600;
                break;
            }
            break;
        case skypia:
            switch (value)
            {
            case Common:
                ad = 80;
                break;
            case Rare:
                ad = 320;
                break;
            case Unique:
                ad = 875;
                break;
            case Epic:
                ad = 12800;
                break;
            }
            break;
        case abyss:
            switch (value)
            {
            case Common:
                ad = 600;
                break;
            case Rare:
                ad = 2400;
                break;
            case Unique:
                ad = 7500;
                break;
            case Epic:
                ad = 116200;
                break;
            }
            break;
        case hellgate:
            switch (value)
            {
            case Common:
                ad = 6000;
                break;
            case Rare:
                ad = 20000;
                break;
            case Unique:
                ad = 50000;
                break;
            case Epic:
                ad = 1500000;
                break;
            }
            break;
        case hell:
            switch (value)
            {
            case Common:
                ad = 100000;
                break;
            case Rare:
                ad = 300000;
                break;
            case Unique:
                ad = 1000000;
                break;
            case Epic:
                ad = 10000000;
                break;
            }
            break;
        }
        itemExplanation = "AD*" + Helpers::floatData::to_one_point_string(ad);
    }
    double get_ad() { return ad; }
};

inline unordered_map<string, Weapon> weaponData{
    //{"test",{10,Item::Value::Common,Item::Theme::forest,10,"Test weapon","For test"}},
};
inline unordered_map<string, Armor> armorData{};
namespace data
{
    inline void setWeaponData()
    {
        for(int i = 0; i < 6; i++) // theme
        {
            for(int j = 0; j < 4; j++) // name
            {
                for(int k = 0; k < 4; k++) // value
                {
                    string name{};
                    switch(j)
                    {
                    case 0:
                        name = "Sword";
                        break;
                    case 1:
                        name = "Wand";
                        break;
                    case 2:
                        name = "Knuckle";
                        break;
                    case 3:
                        name = "Bow";
                        break;
                    }
                    int p = 40 * static_cast<int>(pow(9+i,i)) * static_cast<int>(pow(3, k));
                    weaponData[name + to_string(i) + to_string(k)] = Weapon(p, static_cast<Item::Value>(k), static_cast<Item::Theme>(i), name);
                }
            }
        }
    }

    inline void setArmorData()
    {
        for (int i = 0; i < 6; i++) // theme
        {
            for (int k = 0; k < 4; k++) // value
            {
                string name{"Armor"};
                int p = 30 * static_cast<int>(pow(9+i, i)) * static_cast<int>(pow(3, k));
                armorData[name + to_string(i) + to_string(k)] = Armor(p, static_cast<Item::Value>(k), static_cast<Item::Theme>(i), name);
            }
        }
    }
}
    

