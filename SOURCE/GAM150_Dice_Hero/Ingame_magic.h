/*
File name: Ingame_magic.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"
#include "token.h"

class IngameMagic
{
    string     name{};
    double     width{};
    double     height{};
    EffectInfo info{};
    double     x{};
    double     y{};
    unsigned long long        price{5};
    Image image{};
    Vec2                              get_size() const { return {width, height}; }
    string                            get_name() const { return name; }
    highLightingEffect::RectHighLight rectHighLight{};

public:
    IngameMagic() = default;
    IngameMagic(string n, double wid, double hei, EffectInfo info, unsigned long long price = 5);
    IngameMagic(IngameMagic& magic);
    virtual ~IngameMagic() = default;
    void setImage(string path){ image = Image{ path }; }
    void                     set_pos(double x, double y);
    void                     draw() const;
    void draw_with_price() const;
    bool                     area() const;
    [[nodiscard]] EffectInfo get_effect() const;
    string                   get_info()
    {
        return name + "\nDamage: " + to_string(info.howMuch) + "\nRange: " + to_string(info.extraRange);
    }
    [[nodiscard]] bool is_empty() const { return name.empty(); }
    void set_price(int val) { price = val; }
    [[nodiscard]] unsigned long long  get_price() const { return price; }
    void               click_me() { rectHighLight.operator()({x, y}, width, height); }
};


namespace AboutMagic
{
    inline void give_magic(vector<IngameMagic*> & Magics, unsigned long long diff = 1, int magicLevel = 1)
    {
        if(diff==0)
        {
            diff = 1;
        }
        const int percent{random(0, 100*magicLevel)};
        if (percent < 40)
        {
            Magics.push_back(
                new IngameMagic{"Fire ball", 50, 50, {random(6, 12), MAGIC_ATTACK, true, random(10, 15)},2 * diff});
            Magics[Magics.size() - 1]->setImage("assets/skill/Fire ball.png");
        }
        else if (percent < 70)
        {
            Magics.push_back(new IngameMagic{"Teleport", 50, 50, {0, MAGIC_TELEPORT, true, random(10, 20)},3 * diff });
            Magics[Magics.size() - 1]->setImage("assets/skill/Teleport.png");
        }
        else if (percent < 90)
        {
            Magics.push_back(
                new IngameMagic{"Bomb", 50, 50, {random(8, 15), MAGIC_BOMB, true, random(8, 12), -1, 1},4 * diff });
            Magics[Magics.size() - 1]->setImage("assets/skill/Bomb.png");

        }
        else if (percent < 100)
        {
            Magics.push_back(new IngameMagic{"Resurrection", 50, 50, {0, MAGIC_RESURRECTION, true, random(10, 15)}, 6 * diff });
            Magics[Magics.size() - 1]->setImage("assets/skill/Resurrection.png");

        }
        else if (percent < 120)
        {
            Magics.push_back(
                new IngameMagic{"High Level Bomb", 50, 50, {random(12, 20), MAGIC_BOMB, true, random(12, 14), -3, 3},16 * diff });
            Magics[Magics.size() - 1]->setImage("assets/skill/High Level Bomb.png");
        }
        else if (percent < 160)
        {
            Magics.push_back(
                new IngameMagic{"High Level Teleport", 50, 50, {0, MAGIC_TELEPORT, true, random(20, 25)},14 * diff });
            Magics[Magics.size() - 1]->setImage("assets/skill/High Level Teleport.png");

        }
        else if (percent >= 160)
        {
            Magics.push_back(
                new IngameMagic{ "Hellfire", 50, 50, {random(30, 40), MAGIC_ATTACK, true, 36},12 * diff });
            Magics[Magics.size() - 1]->setImage("assets/skill/Meteor.png");
        }
    }
}
