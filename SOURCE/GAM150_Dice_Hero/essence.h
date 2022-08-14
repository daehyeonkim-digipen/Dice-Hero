/*
File name: Essence.h
Project name: Dice Hero
Author(s): Major - Jihyeon Song, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "doodle/doodle.hpp"
#include "Ingame_image.h"
#include "item.h"

using namespace std;

class Essence : public Item
{
protected:
    int point = 0;
    vector<string> status = {"Small", "Medium", "Large", "Huge"};

public:
    string getStatus(int i) { return status[i]; }
    Essence(int input_price, Value input_value, Theme input_theme, int input_point, string input_name, string input_explanation)
        : Item(input_price, input_value, input_theme), point(input_point)
    {
        itemName = status[value] + " " + input_name + " of " + themename[theme];
        itemExplanation = input_explanation;
    }
};

inline Essence essence1{5, Item::Value::Common, Item::Theme::forest, 10, "Essence", "Under 64 Points"};
inline Essence essence2{25, Item::Value::Rare, Item::Theme::forest, 10, "Essence", "64~120 Points"};
inline Essence essence3{150, Item::Value::Epic, Item::Theme::forest, 10, "Essence", "120~720 Points"};
inline Essence essence4{500, Item::Value::Unique, Item::Theme::forest, 10, "Essence", "Over 720 Points"};

inline Essence essence5{35, Item::Value::Common, Item::Theme::desert, 10, "Essence", "Under 64 Points" };
inline Essence essence6{ 160, Item::Value::Rare, Item::Theme::desert, 10, "Essence", "64~120 Points" };
inline Essence essence7{ 900, Item::Value::Epic, Item::Theme::desert, 10, "Essence", "120~720 Points" };
inline Essence essence8{ 3000, Item::Value::Unique, Item::Theme::desert, 10, "Essence", "Over 720 Points" };

inline Essence essence9{135, Item::Value::Common, Item::Theme::skypia, 10, "Essence", "Under 64 Points"};
inline Essence essence10{1600, Item::Value::Rare, Item::Theme::skypia, 10, "Essence", "64~120 Points"};
inline Essence essence11{3300, Item::Value::Epic, Item::Theme::skypia, 10, "Essence", "120~720 Points"};
inline Essence essence12{12800, Item::Value::Unique, Item::Theme::skypia, 10, "Essence", "Over 720 Points"};

inline Essence essence13{5000, Item::Value::Common, Item::Theme::abyss, 10, "Essence", "Under 64 Points"};
inline Essence essence14{35000, Item::Value::Rare, Item::Theme::abyss, 10, "Essence", "64~120 Points"};
inline Essence essence15{150000, Item::Value::Epic, Item::Theme::abyss, 10, "Essence", "120~720 Points"};
inline Essence essence16{430000, Item::Value::Unique, Item::Theme::abyss, 10, "Essence", "Over 720 Point"};

inline Essence essence17{110000, Item::Value::Common, Item::Theme::hellgate, 10, "Essence", "Under 64 Points"};
inline Essence essence18{960000, Item::Value::Rare, Item::Theme::hellgate, 10, "Essence", "64~120 Points"};
inline Essence essence19{3600000, Item::Value::Epic, Item::Theme::hellgate, 10, "Essence", "120~720 Points"};
inline Essence essence20{15000000, Item::Value::Unique, Item::Theme::hellgate, 10, "Essence", "Over 720 Point"};

inline Essence essence21{10000000, Item::Value::Common, Item::Theme::hell, 10, "Essence", "Under 64 Points"};
inline Essence essence22{53000000, Item::Value::Rare, Item::Theme::hell, 10, "Essence", "64~120 Points"};
inline Essence essence23{160000000, Item::Value::Epic, Item::Theme::hell, 10, "Essence", "120~720 Points"};
inline Essence essence24{2000000000, Item::Value::Unique, Item::Theme::hell, 10, "Essence", "Over 720 Point"};

inline vector<Essence*> essences;

inline void sortEssence()
{
    essences.push_back(&essence1);
    essences.push_back(&essence2);
    essences.push_back(&essence3);
    essences.push_back(&essence4);

    essences.push_back(&essence5);
    essences.push_back(&essence6);
    essences.push_back(&essence7);
    essences.push_back(&essence8);

    essences.push_back(&essence9);
    essences.push_back(&essence10);
    essences.push_back(&essence11);
    essences.push_back(&essence12);

    essences.push_back(&essence13);
    essences.push_back(&essence14);
    essences.push_back(&essence15);
    essences.push_back(&essence16);

    essences.push_back(&essence17);
    essences.push_back(&essence18);
    essences.push_back(&essence19);
    essences.push_back(&essence20);

    essences.push_back(&essence21);
    essences.push_back(&essence22);
    essences.push_back(&essence23);
    essences.push_back(&essence24);
}
inline void  drawEssence(){}