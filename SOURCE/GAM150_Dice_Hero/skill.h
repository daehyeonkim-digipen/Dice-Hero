/*
File name: skill.h
Project name: Dice Hero, minor - Jihyeon Song
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"

class Skill
{
protected:
    Image skillImage;
    bool   skill_on{false};
    Button skillButton;
    string description;
    string name;
    Vec2 pos1;
    Vec2 pos2;
    int cost{ 1 };
    int tier{ 1 };

public:
    Skill(Image image, string _name, string input, Vec2 _pos1, Vec2 _pos2, int _cost, int _tier) :
    skillImage(std::move(image)), name(std::move(_name)), description(std::move(input)), pos1(_pos1), pos2(_pos2), cost(_cost), tier(_tier)
    {
        skillButton = Button("Square", pos1.x, pos1.y,skillImage.GetWidth(),skillImage.GetHeight());
    }
    virtual ~Skill() = default;
    Button& get_button() {return skillButton;}
    void draw()
    {
        set_outline_width(7);
        push_settings();
        set_outline_color(100);
        draw_line(pos1.x, pos1.y, pos2.x, pos2.y);
        pop_settings();
        skillButton.draw_button();
        if(skill_on)
        {
            push_settings();
            set_outline_color(255, 255, 0);
            draw_line(pos1.x, pos1.y, pos2.x, pos2.y);
            pop_settings();
            draw_image(skillImage, pos1.x, pos1.y);
        }
    }
    bool&        get_skillon() { return skill_on; }
    int& get_cost() { return cost; }
    string get_name() { return name; }
    string get_description() { return description; }
    virtual int get_hp() { return 0; }
    virtual int get_df() { return 0; } 
    virtual int get_ad() { return 0; } 
    virtual int get_ra() { return 0; } 
    virtual int get_regen() { return 0; }
    virtual int get_mana_cost() { return 0; }
    virtual int get_rage() { return 0; }
    virtual bool get_drain() { return false; }
    virtual bool get_protection() { return false; }
    virtual bool get_unlimited() { return false; }
    virtual double get_dodge() { return 0; }
    virtual double get_poison() { return 0; }
    virtual bool get_lockpicking() { return false; }
    virtual bool get_backmove() { return false; }
    virtual double get_penetration() { return 0; }
    virtual bool get_attacktoken2() { return false; }
    int levelLimit() { return 5 * tier + tier - 1; }
};

class Basic : public Skill
{
private:
    int hp{ 0 };
    int df{ 0 };
    int ad{ 0 };
    int ra{ 0 };
public:
    Basic(Image image, string _name, string input, Vec2 _pos1, Vec2 _pos2, int _cost, int _tier, int _hp, int _df,
          int _ad, int _ra)
        : Skill(image, _name, input, _pos1, _pos2, _cost, _tier), hp(_hp), df(_df), ad(_ad), ra(_ra)
    {
    }
    int get_hp() override { return hp; }
    int get_df() override { return df; }
    int get_ad() override { return ad; }
    int get_ra() override { return ra; }
};

class WarriorSkill : public Basic
{
    int rage{ 0 };
    bool drain = false;
    bool protection = false;
public:
    WarriorSkill(Image image, string _name, string input, Vec2 _pos1, Vec2 _pos2, int _cost, int _tier, int _hp,
                 int _df, int _ad, int _ra, int _rage, bool _drain, bool _protection)
        : Basic(image, _name, input, _pos1, _pos2, _cost, _tier, _hp, _df, _ad, _ra), rage(_rage), drain(_drain),
          protection(_protection)
    {
    }
    int get_rage() override { return rage; }
    bool get_drain() override { return drain; }
    bool get_protection() override{ return protection; }
};

class MageSkill : public Basic
{
    int regen{ 0 };
    int mana_cost{ 0 };
    bool unlimited = false;
public:
    MageSkill(Image image, string _name, string input, Vec2 _pos1, Vec2 _pos2, int _cost, int _tier, int _hp, int _df,
              int _ad, int _ra, int _regen, int _manacost, bool _unlimited)
        : Basic(image, _name, input, _pos1, _pos2, _cost, _tier, _hp, _df, _ad, _ra), regen(_regen),
          mana_cost(_manacost),
          unlimited(_unlimited)
    {
    }
    int get_regen() override { return regen; }
    int get_mana_cost() override { return mana_cost; }
    bool get_unlimited() override { return unlimited; }
};

class ThiefSkill : public Basic
{
    double dodge{ 0 };
    double poison{0};
    bool lockpicking = false;
    bool backmove = false;
public:
    ThiefSkill(Image image, string _name, string input, Vec2 _pos1, Vec2 _pos2, int _cost, int _tier, int _hp, int _df,
               int _ad, int _ra, double _dodge, double _poision, bool _pickpocket, bool _backmove)
        : Basic(image, _name, input, _pos1, _pos2, _cost, _tier, _hp, _df, _ad, _ra), dodge(_dodge), poison(_poision),
          lockpicking(_pickpocket), backmove(_backmove)
    {
    }
    double get_dodge() override { return dodge; }
    double get_poison() override { return poison; }
    bool get_lockpicking() override { return lockpicking; }
    bool get_backmove() override { return backmove; }
};

class ArcherSkill : public Basic
{
    double penetration{ 0 };
    bool attacktoken2 = false;
public:
    ArcherSkill(Image image, string _name, string input, Vec2 _pos1, Vec2 _pos2, int _cost, int _tier, int _hp, int _df,
                int _ad, int _ra, double _penetration, bool _attacktoken2)
        : Basic(image, _name, input, _pos1, _pos2, _cost, _tier, _hp, _df, _ad, _ra), penetration(_penetration),
          attacktoken2(_attacktoken2)
    {
    }
    double get_penetration() override { return penetration; }
    bool get_attacktoken2() override { return attacktoken2; }

};

inline Basic        warriorSkill1(Image("assets/skill/w1.png"), "Physical Training(2pt)", "maxHP +5\nDF +2\nAD+2",
                                  {WINDOW_WIDTH * 0.138, WINDOW_HEIGHT * 0.17}, {WINDOW_WIDTH * 0.158, WINDOW_HEIGHT * -0.1},
                                  2, 1, 5, 2, 2, 0);
inline WarriorSkill warriorSkill2(Image("assets/skill/w2.png"), "Belligerent(20pt)", "AD +2\nRange +1\nRage Cost -1",
                                  {WINDOW_WIDTH * 0.158, WINDOW_HEIGHT * -0.1},
                                  {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2}, 20, 2, 0, 0, 2, 1, 1, false, false);
inline WarriorSkill warriorSkill3(Image("assets/skill/w3.png"), "Cannibalize(120pt)",
                                  "Drain\nAD +3\nRange +1\nRage Cost -1", {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2},
                                  {WINDOW_WIDTH * 0.326, WINDOW_HEIGHT * -0.1},
                                  120, 3, 0, 0, 3, 1, 1, true, false);
inline WarriorSkill warriorSkill4(Image("assets/skill/w4.png"), "Defender(5000pt)",
                                  "maxHP +15\nDF +4\nRange +1\nRage Cost -2\nProtection: \nWhen HP is more than half, "
                                  "\nwill be damaged by \nother characters instead",
                                  {WINDOW_WIDTH * 0.326, WINDOW_HEIGHT * -0.1},
                                  {WINDOW_WIDTH * 0.346, WINDOW_HEIGHT * 0.17},
                                  5000, 4, 15, 4, 0, 1, 2, true, true);
inline WarriorSkill warriorSkill5(Image("assets/skill/w5.png"), "Unstoppable Power(75000pt)", "DF +5\nAD +5\nRage Cost -2",
                                  {WINDOW_WIDTH * 0.346, WINDOW_HEIGHT * 0.17},
                                  {WINDOW_WIDTH * 0.346, WINDOW_HEIGHT * 0.17}, 75000, 5, 0, 5, 0, 1, 2, true, true);

inline MageSkill mageSkill1(Image("assets/skill/m1.png"), "Mana Flow(1pt)", "Mana Regen +1\nMana Cost -1",
                            {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * 0.2}, {WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.05}, 1,
                            1, 0, 0, 0, 0, 1, 1, false);
inline MageSkill mageSkill2(Image("assets/skill/m2.png"), "Mana Emission(150pt)",
                            "AD +2\nRange+2\nMana Regen +1\nMana Cost -2", {WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.05},
                            {WINDOW_WIDTH * 0.176, WINDOW_HEIGHT * -0.05},
                            150, 3, 0, 0, 2, 2, 1, 2, false);
inline MageSkill mageSkill3(Image("assets/skill/m3.png"), "Mana Reduction(4200pt)",
                            "maxHP +4\nDF +3\nMana Regen +1\nMana Cost -3\nPromotion: Can create high level magic",
                            {WINDOW_WIDTH * 0.176, WINDOW_HEIGHT * -0.05},
                            {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2},
                            4200, 4, 4, 3, 0, 0, 1, 3, false);
inline MageSkill mageSkill4(Image("assets/skill/m4.png"), "Mana Explosion(300000pt)",
                            "AD +3\nRange+3\nMana Cost -4\nUnlimited Magic: \nRemove useable magic limit per turn",
                            {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2}, {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2},
                            300000, 6, 0, 0, 3, 3, 0, 4, true);

inline ThiefSkill thiefSkill1(Image("assets/skill/t1.png"), "Quick Hand Movement(3pt)",
                              "maxHP +2\nDF +1\nAD +2\nRange +1\nDodge +10%\nLockpicking: Higher damage to the box",
                              {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * 0.2}, {WINDOW_WIDTH * 0.346, WINDOW_HEIGHT * 0.16},
                              3,
                              1, 2, 1, 2, 1, 0.1, 0, true, false);
inline ThiefSkill thiefSkill2(Image("assets/skill/t2.png"), "Alacrity Training(15pt)",
                              "maxHP +1\nDF +2\nAD +1\nRange +1\nDodge +10%",
                              {WINDOW_WIDTH * 0.346, WINDOW_HEIGHT * 0.16}, {WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0},
                              15, 2, 1, 2, 1, 1, 0.1, 0, true, false);
inline ThiefSkill thiefSkill3(Image("assets/skill/t3.png"), "Poisoning(225pt)",
                              "maxHP +2\nDF +1\nAD +2\nPoison Attack:\n2% damage of enemy's HP \nwhile 3 turn, 20% chance",
                              {WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0}, {WINDOW_WIDTH * 0.268, WINDOW_HEIGHT * -0.07}, 100, 3, 2, 1,
                              2, 0, 0, 0.2, true, false);
inline ThiefSkill thiefSkill4(Image("assets/skill/t4.png"), "Backstep(6300pt)", "Dodge +13%\nBack move token",
                              {WINDOW_WIDTH * 0.268, WINDOW_HEIGHT * -0.07},
                              {WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * -0.21},
                              6300, 4, 0, 0, 0, 0, 0.13, 0, true, true);
inline ThiefSkill thiefSkill5(Image("assets/skill/t5.png"), "Poisoning2(55000pt)",
                              "maxHP +1\nDF +1\nAD +3\nDodge +17%\nEnhanced Poison Attack:\n4% damage of enemy's HP while 3 turn, \n40% chance",
                              {WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * -0.21}, {WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * -0.21}, 55000, 5, 1,
                              1, 3, 0, 0.17, 0.2, true, true);

inline Basic archerSkill1(Image("assets/skill/a1.png"), "Focus(1pt)", "AD +2\nRange +2",
                          {WINDOW_WIDTH * 0.12, WINDOW_HEIGHT * 0}, {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * 0}, 1, 1, 0,
                          0, 2, 2);
inline Basic archerSkill2(Image("assets/skill/a2.png"), "Agility Training(30pt)", "maxHP +2\nDF +1\nAD +3\nRange +2",
                          {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * 0}, {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * 0.2}, 30,
                          2, 2, 1, 3, 2);
inline Basic archerSkill3(Image("assets/skill/a3.png"), "Focus2(250pt)", "AD +4\nRange +2", {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * 0.2}, {WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.1}, 250,
                          3, 0, 0, 4, 2);
inline Basic archerSkill4(Image("assets/skill/a4.png"), "Agility Training2(8000pt)", "maxHP +3\nDF +2\nAD +5\nRange +2",
                          {WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.1}, {WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * -0.1}, 8000,
                          4, 3, 2, 5, 2);
inline ArcherSkill archerSkill5(Image("assets/skill/a5.png"), "Penetration Shot(65000pt)",
                                "Range +24\nPenetration:\n2% damage of enemy's current HP",
                                {WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * -0.1},
                                {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2},
                                45000, 5, 0, 0, 0, 24, 0.02, false);
inline ArcherSkill archerSkill6(Image("assets/skill/a6.png"), "Towering(300000pt)",
                                "Consume 10% of HP, Use Two attack tokens\nEnhanced Penetration:\n5% damage of enemy's current HP",
                                {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2},
                                {WINDOW_WIDTH * 0.238, WINDOW_HEIGHT * -0.2}, 300000, 6, 0, 0, 0, 0, 0.03, true);