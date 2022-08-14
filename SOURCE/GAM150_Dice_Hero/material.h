/*
File name: Material.h
Project name: Dice Hero
Author(s): Major - Jihyeon Song, minor - Daehyeon Kim, Taeju Kwon
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "item.h"

class Material : public Item
{
    int extractPoint = 0;

public:
    Material(int input_price, Value input_value, Theme input_theme ,string input_name, int input_point)
        : Item(input_price, input_value, input_theme), extractPoint(input_point)
    {
        itemName = input_name;
    }
    int getExtractPoint() { return extractPoint; }
    void draw(double x,double y)const {
        draw_image(MaterialImage[getName()], x, y);
        
    }
    void draw_info(double x, double y)const
    {
        if (Helpers::Collision::objToMouse({ x,y }, MaterialImage[getName()].GetWidth(), MaterialImage[getName()].GetHeight())
            == true)
        {
            push_settings();
            set_font_size(LISTFONTSIZE);
            switch (value)
            {
            case Value::Common:
                set_fill_color(0);break;
            case Value::Epic:
                set_fill_color(50, 50, 255);break;

            case Value::Rare:
                set_fill_color(255, 50, 50);break;

            case Value::Unique:
                set_fill_color(255, 50, 255);break;
            }
            draw_text(getName(), get_mouse_x(), get_mouse_y());
            pop_settings();
        }
    }
};

// chapter1
inline Material stone{3, Item::Value::Common, Item::Theme::forest,"Stone", 1};
inline Material firewood{3, Item::Value::Common, Item::Theme::forest, "Firewood", 1};
inline Material marble{3, Item::Value::Common, Item::Theme::forest, "Marble", 1};
inline Material fairyWing{16, Item::Value::Rare, Item::Theme::forest, "Fairy Wing", 3};
inline Material sapling{ 16, Item::Value::Rare, Item::Theme::forest, "Sapling", 4 };
inline Material wolfSkin{80, Item::Value::Epic, Item::Theme::forest, "Wolf Skin", 12};
inline Material mandragora{200, Item::Value::Unique, Item::Theme::forest, "Mandragora", 35};
// chapter2
inline Material cactusThorn{18, Item::Value::Common, Item::Theme::desert, "Cactus Thorn", 1};
inline Material scorpionClaw{18, Item::Value::Common, Item::Theme::desert, "Scorpion Claw", 1};
inline Material mummyBandage{18, Item::Value::Common, Item::Theme::desert, "Mummy Bandage", 1};
inline Material scorpionSting{70, Item::Value::Rare, Item::Theme::desert, "Scorpion Sting", 3};
inline Material oasisWater{75, Item::Value::Rare, Item::Theme::desert, "Oasis Water", 4};
inline Material cactusFlower{300, Item::Value::Epic, Item::Theme::desert, "Cactus Flower", 12};
inline Material genieLamp{1000, Item::Value::Unique, Item::Theme::desert, "Genie Lamp", 35};
// chapter3
inline Material lubricant{150, Item::Value::Common, Item::Theme::skypia, "Lubricant", 1};
inline Material battery{150, Item::Value::Common, Item::Theme::skypia, "Battery", 1};
inline Material robotScrew{150, Item::Value::Common, Item::Theme::skypia, "Robot Screw", 1};
inline Material titanAlloy{800, Item::Value::Rare, Item::Theme::skypia, "Titan Alloy", 3};
inline Material autoGunBarrel{850, Item::Value::Rare, Item::Theme::skypia, "AutoGun Barrel", 4};
inline Material algorithmCPU{1500, Item::Value::Epic, Item::Theme::skypia, "Algorithm CPU", 12};
inline Material titanEngine{5000, Item::Value::Unique, Item::Theme::skypia, "Titan Engine", 35};
//chapter4
inline Material fragmentofWreck{2000, Item::Value::Common, Item::Theme::abyss, "Fragment of Wreck", 1};
inline Material hydraTeeth{3000, Item::Value::Common, Item::Theme::abyss, "Hydra Teeth", 1};
inline Material fragmentofSoul{4500, Item::Value::Common, Item::Theme::abyss, "Fragment of Soul", 1};
inline Material cephalopodInk{15000, Item::Value::Rare, Item::Theme::abyss, "Cephalopod Ink", 3};
inline Material pearl{15000, Item::Value::Rare, Item::Theme::abyss, "Pearl", 4};
inline Material esca{65000, Item::Value::Epic, Item::Theme::abyss, "Esca", 12};
inline Material treasureofWreck{170000, Item::Value::Unique, Item::Theme::abyss, "Treasure of Wreck", 35};
//chapter5
inline Material hellOre{50000, Item::Value::Common, Item::Theme::hellgate, "Hell Ore", 1};
inline Material impSkull{60000, Item::Value::Common, Item::Theme::hellgate, "Imp Skull", 1};
inline Material soul{90000, Item::Value::Common, Item::Theme::hellgate, "Soul", 1};
inline Material mimicRing{280000, Item::Value::Rare, Item::Theme::hellgate, "Mimic Ring", 3};
inline Material mimicMap{450000, Item::Value::Rare, Item::Theme::hellgate, "Mimic Map", 4};
inline Material diamond{1500000, Item::Value::Epic, Item::Theme::hellgate, "Diamond", 12};
inline Material dragonFire{6000000, Item::Value::Unique, Item::Theme::hellgate, "Dragon Fire", 35};
//chapter6
inline Material sulfur{2500000, Item::Value::Common, Item::Theme::hell, "Sulfur", 1};
inline Material hellfire{3500000, Item::Value::Common, Item::Theme::hell, "Hellfire", 1};
inline Material sinnerBlood{5000000, Item::Value::Common, Item::Theme::hell, "Sinner Blood", 1};
inline Material efreetLamp{15000000, Item::Value::Rare, Item::Theme::hell, "Efreet Lamp", 3};
inline Material devilClaw{25000000, Item::Value::Rare, Item::Theme::hell, "Devil Claw", 4};
inline Material basiliskEye{72000000, Item::Value::Epic, Item::Theme::hell, "Basilisk Eye", 12};
inline Material devilkingWish{1000000000, Item::Value::Unique, Item::Theme::hell, "Devilking Wish", 35};

inline vector<Material*> chapter1 = {&stone, &firewood, &marble,
                                    &fairyWing, &sapling, &wolfSkin, &mandragora};
inline vector<Material*> chapter2 = {&cactusThorn, &scorpionClaw, &mummyBandage,
                                    &scorpionSting, &oasisWater, &cactusFlower, &genieLamp};
inline vector<Material*> chapter3 = {&lubricant, &battery, &robotScrew,
                                    &titanAlloy, &autoGunBarrel, &algorithmCPU, &titanEngine};
inline vector<Material*>          chapter4 = {&fragmentofWreck, &hydraTeeth, &fragmentofSoul, &cephalopodInk,
                                     &pearl,           &esca,       &treasureofWreck};
inline vector<Material*>          chapter5 = {&hellOre, &impSkull, &soul, &mimicRing, &mimicMap, &diamond, &dragonFire};
inline vector<Material*>          chapter6 = {&sulfur,    &hellfire,    &sinnerBlood,  &efreetLamp,
                                     &devilClaw, &basiliskEye, &devilkingWish};
inline vector<vector<Material*>*> materials{ &chapter1, &chapter2, &chapter3, &chapter4, &chapter5, &chapter6 };