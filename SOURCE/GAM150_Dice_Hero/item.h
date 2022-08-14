/*
File name: Item.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"

enum CharacterClass
{
    Warrior_C,
    Mage_C,
    Thief_C,
    Archer_C,
    Public_Item
};

class Item // item.h
{
protected:
    string itemExplanation = {}; 
    string itemName = {};
    int price = 0;
    string themename[6]    = {"Forest", "Desert", "Skypia","Abyss", "Underground", "Hell"};
    int type = 0;
public:
    enum Value
    {
        Common=0,
        Rare,
        Unique,
        Epic
    };
    enum Theme
    {
        forest = 0,
        desert,
        skypia,
        abyss,
        hellgate,
        hell
    };
    CharacterClass which{};
    Value  value = Common;
    Theme theme = forest;

    Item(int input_price, Value input_value, Theme input_theme)
        : price(input_price), value(input_value), theme(input_theme){}
    virtual ~Item(){}
    virtual string getExplanation() { return itemExplanation; }
    string getName()const { return itemName; }
    int&    getPrice() { return price; }
    CharacterClass getClass() { return which; }
    Value          getValue() { return value; }
    Theme          getTheme() { return theme; }
    virtual int    get_type() { return type; }
};

//inline map<string, Image> itemImage;
inline map<string, Image> EssenceImage{};
inline map<string, Image> EquipmentImage{};
inline map<string, Image> MaterialImage{};
namespace ItemImage
{
    inline void equipmentImageSet1()
    {
        EquipmentImage["bow1.1"] = Image{ "assets/weapon/bow-1.1.png" };
        EquipmentImage["bow1.2"] = Image{ "assets/weapon/bow-2.1.png" };
        EquipmentImage["bow1.3"] = Image{ "assets/weapon/bow-3.1.png" };
        EquipmentImage["bow1.4"] = Image{ "assets/weapon/bow-4.1.png" };
        EquipmentImage["bow2.1"] = Image{ "assets/weapon/bow-1.2.png" };
        EquipmentImage["bow2.2"] = Image{ "assets/weapon/bow-2.2.png" };
        EquipmentImage["bow2.3"] = Image{ "assets/weapon/bow-3.2.png" };
        EquipmentImage["bow2.4"] = Image{ "assets/weapon/bow-4.2.png" };
        EquipmentImage["bow3.1"] = Image{ "assets/weapon/bow-1.3.png" };
        EquipmentImage["bow3.2"] = Image{ "assets/weapon/bow-2.3.png" };
        EquipmentImage["bow3.3"] = Image{ "assets/weapon/bow-3.3.png" };
        EquipmentImage["bow3.4"] = Image{ "assets/weapon/bow-4.3.png" };
        EquipmentImage["bow4.1"] = Image{ "assets/weapon/bow-1.4.png" };
        EquipmentImage["bow4.2"] = Image{ "assets/weapon/bow-2.4.png" };
        EquipmentImage["bow4.3"] = Image{ "assets/weapon/bow-3.4.png" };
        EquipmentImage["bow4.4"] = Image{ "assets/weapon/bow-4.4.png" };
        EquipmentImage["bow5.1"] = Image{ "assets/weapon/bow-1.5.png" };
        EquipmentImage["bow5.2"] = Image{ "assets/weapon/bow-2.5.png" };
        EquipmentImage["bow5.3"] = Image{ "assets/weapon/bow-3.5.png" };
        EquipmentImage["bow5.4"] = Image{ "assets/weapon/bow-4.5.png" };
        EquipmentImage["bow6.1"] = Image{ "assets/weapon/bow-1.6.png" };
        EquipmentImage["bow6.2"] = Image{ "assets/weapon/bow-2.6.png" };
        EquipmentImage["bow6.3"] = Image{ "assets/weapon/bow-3.6.png" };
        EquipmentImage["bow6.4"] = Image{ "assets/weapon/bow-4.6.png" };

        EquipmentImage["knuckle1.1"] = Image{ "assets/weapon/knuckle-1.1.png" };
        EquipmentImage["knuckle1.2"] = Image{ "assets/weapon/knuckle-2.1.png" };
        EquipmentImage["knuckle1.3"] = Image{ "assets/weapon/knuckle-3.1.png" };
        EquipmentImage["knuckle1.4"] = Image{ "assets/weapon/knuckle-4.1.png" };
        EquipmentImage["knuckle2.1"] = Image{ "assets/weapon/knuckle-1.2.png" };
        EquipmentImage["knuckle2.2"] = Image{ "assets/weapon/knuckle-2.2.png" };
        EquipmentImage["knuckle2.3"] = Image{ "assets/weapon/knuckle-3.2.png" };
        EquipmentImage["knuckle2.4"] = Image{ "assets/weapon/knuckle-4.2.png" };
        EquipmentImage["knuckle3.1"] = Image{ "assets/weapon/knuckle-1.3.png" };
        EquipmentImage["knuckle3.2"] = Image{ "assets/weapon/knuckle-2.3.png" };
        EquipmentImage["knuckle3.3"] = Image{ "assets/weapon/knuckle-3.3.png" };
        EquipmentImage["knuckle3.4"] = Image{ "assets/weapon/knuckle-4.3.png" };
        EquipmentImage["knuckle4.1"] = Image{ "assets/weapon/knuckle-1.4.png" };
        EquipmentImage["knuckle4.2"] = Image{ "assets/weapon/knuckle-2.4.png" };
        EquipmentImage["knuckle4.3"] = Image{ "assets/weapon/knuckle-3.4.png" };
        EquipmentImage["knuckle4.4"] = Image{ "assets/weapon/knuckle-4.4.png" };
        EquipmentImage["knuckle5.1"] = Image{ "assets/weapon/knuckle-1.5.png" };
        EquipmentImage["knuckle5.2"] = Image{ "assets/weapon/knuckle-2.5.png" };
        EquipmentImage["knuckle5.3"] = Image{ "assets/weapon/knuckle-3.5.png" };
        EquipmentImage["knuckle5.4"] = Image{ "assets/weapon/knuckle-4.5.png" };
        EquipmentImage["knuckle6.1"] = Image{ "assets/weapon/knuckle-1.6.png" };
        EquipmentImage["knuckle6.2"] = Image{ "assets/weapon/knuckle-2.6.png" };
        EquipmentImage["knuckle6.3"] = Image{ "assets/weapon/knuckle-3.6.png" };
        EquipmentImage["knuckle6.4"] = Image{ "assets/weapon/knuckle-4.6.png" };

        // armor list
        EquipmentImage["armor1.1"] = Image{ "assets/weapon/armor-1.1.png" };
        EquipmentImage["armor1.2"] = Image{ "assets/weapon/armor-2.1.png" };
        EquipmentImage["armor1.3"] = Image{ "assets/weapon/armor-3.1.png" };
        EquipmentImage["armor1.4"] = Image{ "assets/weapon/armor-4.1.png" };
        EquipmentImage["armor2.1"] = Image{ "assets/weapon/armor-1.2.png" };
        EquipmentImage["armor2.2"] = Image{ "assets/weapon/armor-2.2.png" };
        EquipmentImage["armor2.3"] = Image{ "assets/weapon/armor-3.2.png" };
        EquipmentImage["armor2.4"] = Image{ "assets/weapon/armor-4.2.png" };
        EquipmentImage["armor3.1"] = Image{"assets/weapon/armor-1.3.png"};
        EquipmentImage["armor3.2"] = Image{"assets/weapon/armor-2.3.png"};
        EquipmentImage["armor3.3"] = Image{"assets/weapon/armor-3.3.png"};
        EquipmentImage["armor3.4"] = Image{"assets/weapon/armor-4.3.png"};
        EquipmentImage["armor4.1"] = Image{"assets/weapon/armor-1.4.png"};
        EquipmentImage["armor4.2"] = Image{"assets/weapon/armor-2.4.png"};
        EquipmentImage["armor4.3"] = Image{"assets/weapon/armor-3.4.png"};
        EquipmentImage["armor4.4"] = Image{"assets/weapon/armor-4.4.png"};
        EquipmentImage["armor5.1"] = Image{"assets/weapon/armor-1.5.png"};
        EquipmentImage["armor5.2"] = Image{"assets/weapon/armor-2.5.png"};
        EquipmentImage["armor5.3"] = Image{"assets/weapon/armor-3.5.png"};
        EquipmentImage["armor5.4"] = Image{"assets/weapon/armor-4.5.png"};
        EquipmentImage["armor6.1"] = Image{"assets/weapon/armor-1.6.png"};
        EquipmentImage["armor6.2"] = Image{"assets/weapon/armor-2.6.png"};
        EquipmentImage["armor6.3"] = Image{"assets/weapon/armor-3.6.png"};
        EquipmentImage["armor6.4"] = Image{"assets/weapon/armor-4.6.png"};
        cout << "Equip 1 Load End" << endl;
    }

    inline void equipmentImageSet2()
    {
        EquipmentImage["sword1.1"] = Image{ "assets/weapon/sword-1.1.png" };
        EquipmentImage["sword1.2"] = Image{ "assets/weapon/sword-2.1.png" };
        EquipmentImage["sword1.3"] = Image{ "assets/weapon/sword-3.1.png" };
        EquipmentImage["sword1.4"] = Image{ "assets/weapon/sword-4.1.png" };
        EquipmentImage["sword2.1"] = Image{ "assets/weapon/sword-1.2.png" };
        EquipmentImage["sword2.2"] = Image{ "assets/weapon/sword-2.2.png" };
        EquipmentImage["sword2.3"] = Image{ "assets/weapon/sword-3.2.png" };
        EquipmentImage["sword2.4"] = Image{ "assets/weapon/sword-4.2.png" };
        EquipmentImage["sword3.1"] = Image{ "assets/weapon/sword-1.3.png" };
        EquipmentImage["sword3.2"] = Image{ "assets/weapon/sword-2.3.png" };
        EquipmentImage["sword3.3"] = Image{ "assets/weapon/sword-3.3.png" };
        EquipmentImage["sword3.4"] = Image{ "assets/weapon/sword-4.3.png" };
        EquipmentImage["sword4.1"] = Image{ "assets/weapon/sword-1.4.png" };
        EquipmentImage["sword4.2"] = Image{ "assets/weapon/sword-2.4.png" };
        EquipmentImage["sword4.3"] = Image{ "assets/weapon/sword-3.4.png" };
        EquipmentImage["sword4.4"] = Image{ "assets/weapon/sword-4.4.png" };
        EquipmentImage["sword5.1"] = Image{ "assets/weapon/sword-1.5.png" };
        EquipmentImage["sword5.2"] = Image{ "assets/weapon/sword-2.5.png" };
        EquipmentImage["sword5.3"] = Image{ "assets/weapon/sword-3.5.png" };
        EquipmentImage["sword5.4"] = Image{ "assets/weapon/sword-4.5.png" };
        EquipmentImage["sword6.1"] = Image{ "assets/weapon/sword-1.6.png" };
        EquipmentImage["sword6.2"] = Image{ "assets/weapon/sword-2.6.png" };
        EquipmentImage["sword6.3"] = Image{ "assets/weapon/sword-3.6.png" };
        EquipmentImage["sword6.4"] = Image{ "assets/weapon/sword-4.6.png" };

        EquipmentImage["wand1.1"] = Image{ "assets/weapon/wand-1.1.png" };
        EquipmentImage["wand1.2"] = Image{ "assets/weapon/wand-2.1.png" };
        EquipmentImage["wand1.3"] = Image{ "assets/weapon/wand-3.1.png" };
        EquipmentImage["wand1.4"] = Image{ "assets/weapon/wand-4.1.png" };
        EquipmentImage["wand2.1"] = Image{ "assets/weapon/wand-1.2.png" };
        EquipmentImage["wand2.2"] = Image{ "assets/weapon/wand-2.2.png" };
        EquipmentImage["wand2.3"] = Image{ "assets/weapon/wand-3.2.png" };
        EquipmentImage["wand2.4"] = Image{ "assets/weapon/wand-4.2.png" };
        EquipmentImage["wand3.1"] = Image{ "assets/weapon/wand-1.3.png" };
        EquipmentImage["wand3.2"] = Image{ "assets/weapon/wand-2.3.png" };
        EquipmentImage["wand3.3"] = Image{ "assets/weapon/wand-3.3.png" };
        EquipmentImage["wand3.4"] = Image{ "assets/weapon/wand-4.3.png" };
        EquipmentImage["wand4.1"] = Image{ "assets/weapon/wand-1.4.png" };
        EquipmentImage["wand4.2"] = Image{ "assets/weapon/wand-2.4.png" };
        EquipmentImage["wand4.3"] = Image{ "assets/weapon/wand-3.4.png" };
        EquipmentImage["wand4.4"] = Image{ "assets/weapon/wand-4.4.png" };
        EquipmentImage["wand5.1"] = Image{ "assets/weapon/wand-1.5.png" };
        EquipmentImage["wand5.2"] = Image{ "assets/weapon/wand-2.5.png" };
        EquipmentImage["wand5.3"] = Image{ "assets/weapon/wand-3.5.png" };
        EquipmentImage["wand5.4"] = Image{ "assets/weapon/wand-4.5.png" };
        EquipmentImage["wand6.1"] = Image{ "assets/weapon/wand-1.6.png" };
        EquipmentImage["wand6.2"] = Image{ "assets/weapon/wand-2.6.png" };
        EquipmentImage["wand6.3"] = Image{ "assets/weapon/wand-3.6.png" };
        EquipmentImage["wand6.4"] = Image{ "assets/weapon/wand-4.6.png" };


        cout << "Equip 2 Load End" << endl;


    }
    inline void imageSet() //name-chapter.level
    {
        //essence list
        EssenceImage["essence1.1"] = Image{"assets/essence/essence-1.1.png"};
        EssenceImage["essence1.2"] = Image{"assets/essence/essence-1.2.png"};
        EssenceImage["essence1.3"] = Image{"assets/essence/essence-1.3.png"};
        EssenceImage["essence1.4"] = Image{"assets/essence/essence-1.4.png"};

        EssenceImage["essence2.1"] = Image{"assets/essence/essence-2.1.png"};
        EssenceImage["essence2.2"] = Image{"assets/essence/essence-2.2.png"};
        EssenceImage["essence2.3"] = Image{"assets/essence/essence-2.3.png"};
        EssenceImage["essence2.4"] = Image{"assets/essence/essence-2.4.png"};

        EssenceImage["essence3.1"] = Image{"assets/essence/essence-3.1.png"};
        EssenceImage["essence3.2"] = Image{"assets/essence/essence-3.2.png"};
        EssenceImage["essence3.3"] = Image{"assets/essence/essence-3.3.png"};
        EssenceImage["essence3.4"] = Image{"assets/essence/essence-3.4.png"};

        EssenceImage["essence4.1"] = Image{"assets/essence/essence-4.1.png"};
        EssenceImage["essence4.2"] = Image{"assets/essence/essence-4.2.png"};
        EssenceImage["essence4.3"] = Image{"assets/essence/essence-4.3.png"};
        EssenceImage["essence4.4"] = Image{"assets/essence/essence-4.4.png"};

        EssenceImage["essence5.1"] = Image{"assets/essence/essence-5.1.png"};
        EssenceImage["essence5.2"] = Image{"assets/essence/essence-5.2.png"};
        EssenceImage["essence5.3"] = Image{"assets/essence/essence-5.3.png"};
        EssenceImage["essence5.4"] = Image{"assets/essence/essence-5.4.png"};

        EssenceImage["essence6.1"] = Image{"assets/essence/essence-6.1.png"};
        EssenceImage["essence6.2"] = Image{"assets/essence/essence-6.2.png"};
        EssenceImage["essence6.3"] = Image{"assets/essence/essence-6.3.png"};
        EssenceImage["essence6.4"] = Image{"assets/essence/essence-6.4.png"};


        //weapon list (chapter2까지 수정 완료)
        //EquipmentImage["bow1.1"] = Image{"assets/weapon/bow-1.1.png"};
        //EquipmentImage["bow1.2"] = Image{"assets/weapon/bow-2.1.png"};
        //EquipmentImage["bow1.3"] = Image{"assets/weapon/bow-3.1.png"};
        //EquipmentImage["bow1.4"] = Image{"assets/weapon/bow-4.1.png"}; 
        //EquipmentImage["bow2.1"] = Image{"assets/weapon/bow-1.2.png"};
        //EquipmentImage["bow2.2"] = Image{"assets/weapon/bow-2.2.png"};
        //EquipmentImage["bow2.3"] = Image{"assets/weapon/bow-3.2.png"};
        //EquipmentImage["bow2.4"] = Image{"assets/weapon/bow-4.2.png"}; 
        //EquipmentImage["bow3.1"] = Image{"assets/weapon/bow-1.png"};
        //EquipmentImage["bow3.2"] = Image{"assets/weapon/bow-2.3.png"};
        //EquipmentImage["bow3.3"] = Image{"assets/weapon/bow-3.3.png"};
        //EquipmentImage["bow3.4"] = Image{"assets/weapon/bow-3.3.png"};
        //EquipmentImage["bow4.1"] = Image{"assets/weapon/bow-1.png"};
        //EquipmentImage["bow4.2"] = Image{"assets/weapon/bow-2.4.png"};
        //EquipmentImage["bow4.3"] = Image{"assets/weapon/bow-3.4.png"};
        //EquipmentImage["bow4.4"] = Image{"assets/weapon/bow-3.4.png"}; 
        //EquipmentImage["bow5.1"] = Image{"assets/weapon/bow-1.png"};
        //EquipmentImage["bow5.2"] = Image{"assets/weapon/bow-2.5.png"};
        //EquipmentImage["bow5.3"] = Image{"assets/weapon/bow-3.5.png"};
        //EquipmentImage["bow5.4"] = Image{"assets/weapon/bow-3.5.png"}; 
        //EquipmentImage["bow6.1"] = Image{"assets/weapon/bow-1.png"};
        //EquipmentImage["bow6.2"] = Image{"assets/weapon/bow-2.6.png"};
        //EquipmentImage["bow6.3"] = Image{"assets/weapon/bow-3.6.png"};
        //EquipmentImage["bow6.4"] = Image{"assets/weapon/bow-3.6.png"}; 

        //EquipmentImage["knuckle1.1"] = Image{"assets/weapon/knuckle-1.1.png"};
        //EquipmentImage["knuckle1.2"] = Image{"assets/weapon/knuckle-2.1.png"};
        //EquipmentImage["knuckle1.3"] = Image{"assets/weapon/knuckle-3.1.png"};
        //EquipmentImage["knuckle1.4"] = Image{"assets/weapon/knuckle-4.1.png"}; 
        //EquipmentImage["knuckle2.1"] = Image{"assets/weapon/knuckle-1.2.png"};
        //EquipmentImage["knuckle2.2"] = Image{"assets/weapon/knuckle-2.2.png"};
        //EquipmentImage["knuckle2.3"] = Image{"assets/weapon/knuckle-3.2.png"};
        //EquipmentImage["knuckle2.4"] = Image{"assets/weapon/knuckle-4.2.png"}; 
        //EquipmentImage["knuckle3.1"] = Image{"assets/weapon/knuckle-1.1.png"};
        //EquipmentImage["knuckle3.2"] = Image{"assets/weapon/knuckle-2.3.png"};
        //EquipmentImage["knuckle3.3"] = Image{"assets/weapon/knuckle-2.3.png"};
        //EquipmentImage["knuckle3.4"] = Image{"assets/weapon/knuckle-2.3.png"}; 
        //EquipmentImage["knuckle4.1"] = Image{"assets/weapon/knuckle-1.1.png"};
        //EquipmentImage["knuckle4.2"] = Image{"assets/weapon/knuckle-2.4.png"};
        //EquipmentImage["knuckle4.3"] = Image{"assets/weapon/knuckle-2.4.png"};
        //EquipmentImage["knuckle4.4"] = Image{"assets/weapon/knuckle-2.4.png"}; 
        //EquipmentImage["knuckle5.1"] = Image{"assets/weapon/knuckle-1.1.png"};
        //EquipmentImage["knuckle5.2"] = Image{"assets/weapon/knuckle-2.5.png"};
        //EquipmentImage["knuckle5.3"] = Image{"assets/weapon/knuckle-2.5.png"};
        //EquipmentImage["knuckle5.4"] = Image{"assets/weapon/knuckle-2.5.png"}; 
        //EquipmentImage["knuckle6.1"] = Image{"assets/weapon/knuckle-1.1.png"};
        //EquipmentImage["knuckle6.2"] = Image{"assets/weapon/knuckle-2.6.png"};
        //EquipmentImage["knuckle6.3"] = Image{"assets/weapon/knuckle-2.6.png"};
        //EquipmentImage["knuckle6.4"] = Image{"assets/weapon/knuckle-2.6.png"}; 

        //EquipmentImage["sword1.1"] = Image{"assets/weapon/sword-1.1.png"};
        //EquipmentImage["sword1.2"] = Image{"assets/weapon/sword-2.1.png"};
        //EquipmentImage["sword1.3"] = Image{"assets/weapon/sword-3.1.png"};
        //EquipmentImage["sword1.4"] = Image{"assets/weapon/sword-4.1.png"}; 
        //EquipmentImage["sword2.1"] = Image{"assets/weapon/sword-1.2.png"};
        //EquipmentImage["sword2.2"] = Image{"assets/weapon/sword-2.2.png"};
        //EquipmentImage["sword2.3"] = Image{"assets/weapon/sword-3.2.png"};
        //EquipmentImage["sword2.4"] = Image{"assets/weapon/sword-4.2.png"}; 
        //EquipmentImage["sword3.1"] = Image{"assets/weapon/sword-1.3.png"};
        //EquipmentImage["sword3.2"] = Image{"assets/weapon/sword-2.3.png"};
        //EquipmentImage["sword3.3"] = Image{"assets/weapon/sword-2.3.png"};
        //EquipmentImage["sword3.4"] = Image{"assets/weapon/sword-2.3.png"}; 
        //EquipmentImage["sword4.1"] = Image{"assets/weapon/sword-1.4.png"};
        //EquipmentImage["sword4.2"] = Image{"assets/weapon/sword-2.4.png"};
        //EquipmentImage["sword4.3"] = Image{"assets/weapon/sword-2.4.png"};
        //EquipmentImage["sword4.4"] = Image{"assets/weapon/sword-2.4.png"}; 
        //EquipmentImage["sword5.1"] = Image{"assets/weapon/sword-1.5.png"};
        //EquipmentImage["sword5.2"] = Image{"assets/weapon/sword-2.5.png"};
        //EquipmentImage["sword5.3"] = Image{"assets/weapon/sword-2.5.png"};
        //EquipmentImage["sword5.4"] = Image{"assets/weapon/sword-2.5.png"}; 
        //EquipmentImage["sword6.1"] = Image{"assets/weapon/sword-1.6.png"};
        //EquipmentImage["sword6.2"] = Image{"assets/weapon/sword-2.6.png"};
        //EquipmentImage["sword6.3"] = Image{"assets/weapon/sword-3.6.png"};
        //EquipmentImage["sword6.4"] = Image{"assets/weapon/sword-2.6.png"}; 

        //EquipmentImage["wand1.1"] = Image{"assets/weapon/wand-1.1.png"};
        //EquipmentImage["wand1.2"] = Image{"assets/weapon/wand-2.1.png"};
        //EquipmentImage["wand1.3"] = Image{"assets/weapon/wand-3.1.png"};
        //EquipmentImage["wand1.4"] = Image{"assets/weapon/wand-4.1.png"}; 
        //EquipmentImage["wand2.1"] = Image{"assets/weapon/wand-1.2.png"};
        //EquipmentImage["wand2.2"] = Image{"assets/weapon/wand-2.2.png"};
        //EquipmentImage["wand2.3"] = Image{"assets/weapon/wand-3.2.png"};
        //EquipmentImage["wand2.4"] = Image{"assets/weapon/wand-4.2.png"}; 
        //EquipmentImage["wand3.1"] = Image{"assets/weapon/wand-1.png"};
        //EquipmentImage["wand3.2"] = Image{"assets/weapon/wand-2.3.png"};
        //EquipmentImage["wand3.3"] = Image{"assets/weapon/wand-2.3.png"};
        //EquipmentImage["wand3.4"] = Image{"assets/weapon/wand-2.3.png"}; 
        //EquipmentImage["wand4.1"] = Image{"assets/weapon/wand-1.png"};
        //EquipmentImage["wand4.2"] = Image{"assets/weapon/wand-2.4.png"};
        //EquipmentImage["wand4.3"] = Image{"assets/weapon/wand-2.4.png"};
        //EquipmentImage["wand4.4"] = Image{"assets/weapon/wand-2.4.png"}; 
        //EquipmentImage["wand5.1"] = Image{"assets/weapon/wand-1.png"};
        //EquipmentImage["wand5.2"] = Image{"assets/weapon/wand-2.5.png"};
        //EquipmentImage["wand5.3"] = Image{"assets/weapon/wand-2.5.png"};
        //EquipmentImage["wand5.4"] = Image{"assets/weapon/wand-2.5.png"}; 
        //EquipmentImage["wand6.1"] = Image{"assets/weapon/wand-1.png"};
        //EquipmentImage["wand6.2"] = Image{"assets/weapon/wand-2.6.png"};
        //EquipmentImage["wand6.3"] = Image{"assets/weapon/wand-2.6.png"};
        //EquipmentImage["wand6.4"] = Image{"assets/weapon/wand-2.6.png"};


        //// armor list
        //EquipmentImage["armor1.1"] = Image{"assets/weapon/armor-1.1.png"};
        //EquipmentImage["armor1.2"] = Image{"assets/weapon/armor-2.1.png"};
        //EquipmentImage["armor1.3"] = Image{"assets/weapon/armor-3.1.png"};
        //EquipmentImage["armor1.4"] = Image{"assets/weapon/armor-4.1.png"};
        //EquipmentImage["armor2.1"] = Image{"assets/weapon/armor-1.2.png"};
        //EquipmentImage["armor2.2"] = Image{"assets/weapon/armor-2.2.png"};
        //EquipmentImage["armor2.3"] = Image{"assets/weapon/armor-3.2.png"};
        //EquipmentImage["armor2.4"] = Image{"assets/weapon/armor-4.2.png"};


        //material list
        MaterialImage["Stone"] = Image{"assets/materials/chapter1/stone.png"};
        MaterialImage["Firewood"] = Image{"assets/materials/chapter1/firewood.png"};
        MaterialImage["Marble"] = Image{"assets/materials/chapter1/marble.png"};
        MaterialImage["Fairy Wing"] = Image{"assets/materials/chapter1/fairyWing.png"};
        MaterialImage["Sapling"] = Image{"assets/materials/chapter1/sapling.png"};
        MaterialImage["Wolf Skin"] = Image{"assets/materials/chapter1/wolfSkin.png"};
        MaterialImage["Mandragora"] = Image{"assets/materials/chapter1/mandragora.png"};

        MaterialImage["Cactus Thorn"]      = Image{"assets/materials/chapter2/cactusThorn.png"};
        MaterialImage["Scorpion Claw"]   = Image{"assets/materials/chapter2/scorpionClaw.png"};
        MaterialImage["Mummy Bandage"]     = Image{"assets/materials/chapter2/mummyBandage.png"};
        MaterialImage["Scorpion Sting"]  = Image{"assets/materials/chapter2/scorpionSting.png"};
        MaterialImage["Oasis Water"]    = Image{"assets/materials/chapter2/oasisWater.png"};
        MaterialImage["Cactus Flower"]   = Image{"assets/materials/chapter2/cactusFlower.png"};
        MaterialImage["Genie Lamp"] = Image{"assets/materials/chapter2/genieLamp.png"};

        MaterialImage["Lubricant"]      = Image{"assets/materials/chapter3/lubricant.png"};
        MaterialImage["Battery"]   = Image{"assets/materials/chapter3/battery.png"};
        MaterialImage["Robot Screw"]     = Image{"assets/materials/chapter3/robotScrew.png"};
        MaterialImage["Titan Alloy"]  = Image{"assets/materials/chapter3/titanAlloy.png"};
        MaterialImage["AutoGun Barrel"]    = Image{"assets/materials/chapter3/autoGunBarrel.png"};
        MaterialImage["Algorithm CPU"]   = Image{"assets/materials/chapter3/algorithmCPU.png"};
        MaterialImage["Titan Engine"] = Image{"assets/materials/chapter3/titanEngine.png"};

        MaterialImage["Fragment of Wreck"]      = Image{"assets/materials/chapter4/fragmentofWreck.png"};
        MaterialImage["Hydra Teeth"]   = Image{"assets/materials/chapter4/hydraTeeth.png"};
        MaterialImage["Fragment of Soul"]     = Image{"assets/materials/chapter4/fragmentofSoul.png"};
        MaterialImage["Cephalopod Ink"]  = Image{"assets/materials/chapter4/krakenInk.png"};
        MaterialImage["Pearl"]    = Image{"assets/materials/chapter4/pearl.png"};
        MaterialImage["Esca"]   = Image{"assets/materials/chapter4/esca.png"};
        MaterialImage["Treasure of Wreck"] = Image{"assets/materials/chapter4/treasureofWreck.png"};

        MaterialImage["Hell Ore"]      = Image{"assets/materials/chapter5/hellOre.png"};
        MaterialImage["Imp Skull"]   = Image{"assets/materials/chapter5/impSkull.png"};
        MaterialImage["Soul"]     = Image{"assets/materials/chapter5/soul.png"};
        MaterialImage["Mimic Ring"]  = Image{"assets/materials/chapter5/mimicRing.png"};
        MaterialImage["Mimic Map"]    = Image{"assets/materials/chapter5/mimicMap.png"};
        MaterialImage["Diamond"]   = Image{"assets/materials/chapter5/diamond.png"};
        MaterialImage["Dragon Fire"] = Image{"assets/materials/chapter5/dragonFire.png"};

        MaterialImage["Sulfur"]      = Image{"assets/materials/chapter6/sulfur.png"};
        MaterialImage["Hellfire"]   = Image{"assets/materials/chapter6/hellfire.png"};
        MaterialImage["Sinner Blood"]     = Image{"assets/materials/chapter6/sinnerBlood.png"};
        MaterialImage["Efreet Lamp"]  = Image{"assets/materials/chapter6/efreetLamp.png"};
        MaterialImage["Devil Claw"]    = Image{"assets/materials/chapter6/devilNail.png"};
        MaterialImage["Basilisk Eye"]   = Image{"assets/materials/chapter6/basiliskEye.png"};
        MaterialImage["Devilking Wish"] = Image{"assets/materials/chapter6/devilkingWish.png"};

        cout << "Item Load End" << endl;

    }
    inline void imageClear()
    {
        MaterialImage.clear();
        EquipmentImage.clear();
        EssenceImage.clear();
    }

}