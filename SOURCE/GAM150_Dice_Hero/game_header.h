/*
File name: game_header.h
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"
#include "item.h"
#include "token.h"
#include "dice.h"
#include "quest_info.h"
#include "equipment.h"
#include "essence.h"
#include "material.h"
#include "scene_manager.h"
#include "skills.h"


struct PlayerStatus
{
    int    level{1};
    unsigned long long    money{0};
    long double    exp{0};
    long double    expGoal{10};
    bool clear = false;
    int    openStage{1};
    int skillPoint{ 0 };
    map<Material*, int> inventoryMaterial;
    map<Essence*, int> inventoryEssence;
    map<Item*, int> inventoryEquipment;

    void   set_exp_goal();
};

inline PlayerStatus status;

class Character //game_header.h
{
protected:
    bool isDead = false;
    Vec2          position{0, 0};
    int           location{0};
    double        maxHP{};
    double        hp{0};
    double        ad{0};
    double        df{0};
    double        diceFactor{0.5};
    int           attackRange{1};
    Weapon*       myWeapon = nullptr;
    Armor*         myArmor  = nullptr;
    vector<Dice>  dices{};  
    vector<Token> tokens{};
    bool          isMove{false};
    string      className;
    EffectInfo tEffect{};
    int         usedDiceNum{};
    vector<int>   doubleCheck{};
    bool          Isdouble{false};
    bool          isProvideDouble{false};
    bool          skillOn{false};
    bool IsStun{false};
    int           skillPoint{0};
    void doubleUpdate();
    string base_information() const
    {
        return className
        +"\nHP: "
        + Helpers::floatData::to_one_point_string(hp)
        + "\nAD: "
        + Helpers::floatData::to_one_point_string(ad)
        + "\nDF: "
        + Helpers::floatData::to_one_point_string(df) + " (" + Helpers::floatData::to_one_point_string((1 - pow(0.996, df)) * 100) + "% Damage Reduction)"
        + "\nAR: "
        + to_string(attackRange);
    }
    virtual void extra_turn_setup() {}
    void                 MaintenanceStatus();
    bool check_dices_rolled();
    bool least_check_dices_rolled();
    bool check_pick_over_one_token();
    void make_one_token_pick();
    virtual void new_game_extra_set() {}

public:
    bool& getisdead() { return isDead; }
    bool& is_stun() { return IsStun; }
    bool turn_end()const {
        return usedDiceNum >= 2 /*num of dice*/ || hp <= 0 || IsStun == true;
    }
    void new_game_set()
    {
        location = 0;
        hp       = maxHP;
        isDead = false;
        IsStun = false;
        skillOn = false;
        isMove = false;
        new_game_extra_set();
    }
    CharacterClass myClass;
    Character(CharacterClass, string, double, double, double, int);
    virtual ~Character() = default;
    Weapon*        get_weapon() { return myWeapon; }
    Armor*         get_armor() { return myArmor; }
    void           set_weapon(Weapon* input);
    void           set_armor(Armor* input);
    bool           get_is_move()const { return isMove; }
    vector<Dice> & get_dice() { return dices; }
    string         get_class_name() const;
    bool           dice_in_token(Token t, const Dice& d);
    void           set_location(int);
    void           set_position(Vec2);
    Vec2           get_position() const;
    int            get_location() const;
    bool           is_mouse_clicked_token(int i);
    int            get_token_size()const { return static_cast<int>(tokens.size()); }
    virtual void   update(){}
    virtual void   draw(){}
    virtual void   turn_setup();

    void         set_skill_on(const bool on) { skillOn = on; }
    double       get_dice_factor() { return diceFactor; }
    void         set_dice_factor(double input) { diceFactor = input; } 
    double       get_ad() const { return ad; }
    void         set_ad(const double input) { ad = input; }
    double       get_df() const { return df; }
    void         set_df(const double input) { df = input; }
    double       get_hp() const { return hp; }
    void         set_hp(const double input) { hp = input; }
    void heal_hp(double heal) { hp += heal; }
    double       get_max_hp() const { return maxHP; }
    void         set_max_hp(const double m) { maxHP = m; }
    int          get_attack_range() const { return attackRange; }
    void         set_attack_range(const int input) { attackRange = input; }
    void         dt_draw();
    void         dt_update();
    EffectInfo  get_effect() const { return tEffect; }
    void         use_effect_howMuch() { tEffect.howMuch -= 1; }
    void         set_effect(EffectInfo e) { tEffect = e; }
    void         initial_effect() { tEffect = {}; } 
    void         use_dice() { ++usedDiceNum; }
    void         initial_used_dice_num() { usedDiceNum = 0; }
    int          get_used_dice_num() const { return usedDiceNum; }
    virtual void         give_damage(double damage);
    virtual void give_extra_resource(int) {}
    bool         get_is_double() { return Isdouble; }
    void         initial_is_double()
    {
        Isdouble = false;
        doubleCheck.clear();
    }
    void set_provide_double(bool b) { isProvideDouble = b; }
    bool get_provide_double() { return isProvideDouble; }
    virtual string get_information() { return base_information(); }
    virtual void           My_turn() = 0;
    EffectType get_token_type(int i)const{return tokens[i].getTokenType();}
    SkillTree* skilltree;
    virtual void controlSkill(){}
};

class Warrior : public Character
{
    int maxRage{8};
    int nowRage{ 0 };
    bool drain = false;
    bool protection = false;
    void new_game_extra_set() override { nowRage = 0; }
public:
    Warrior(CharacterClass inputClass, string whatName, double inputAD, double inputDF, double inputHP, int inputAR)
        : Character(inputClass, whatName, inputAD, inputDF, inputHP, inputAR) {
        skilltree = &WarriorTree;
    }
    void     update() override;
    void     draw() override;
    void My_turn() override;
    void     give_damage(double damage) override;
    bool   check_rage()const { return nowRage >= maxRage; }
    void use_rage() { nowRage -= maxRage; }
    void controlSkill() override;
    bool get_protection()const  { return protection; }
    bool get_drain()const { return drain; }
    string get_information() override {
        return base_information() + 
        "\nRage: "
        + to_string(nowRage);
    }

};

class Mage : public Character
{
    int mp{0};
    int mana_regen{ 0 };
    int mana_cost{ 15 };
    bool unlimited = false;
    void new_game_extra_set() override { mp = 0; }
public:
    Mage(CharacterClass inputClass, string whatName, double inputAD, double inputDF, double inputHP, int inputAR)
        : Character(inputClass, whatName, inputAD, inputDF, inputHP, inputAR)
    {
        skilltree = &MageTree;
    }
    void update() override;
    void draw() override;
    void   My_turn() override;
    void extra_turn_setup() override;
    void give_extra_resource(int) override;
    int& get_mama_regen() { return mana_regen; }
    void do_mana_regen() { mp += mana_regen; }
    int& get_cost() { return mana_cost; }
    int  get_mp() const { return mp; }
    void set_mp(int m) { mp = m; }
    void use_mana() { mp -= mana_cost; }
    string get_information() override { return base_information() + "\nMP: " + to_string(mp); }
    void controlSkill() override;
    bool& get_unlimited() { return unlimited; }
    int magicLevel{1};
};

class Thief : public Character
{
    Button move{"Thief", WINDOW_WIDTH * -0.025, WINDOW_HEIGHT * -0.025, 100,50};
    bool   passiveMove{false};
    int    moveNum{};
    double dodge{ 0 };
    double poison{ 0 };
    bool pickpocket = false;
    bool backmove = false;
public:
    Thief(CharacterClass inputClass, string whatName, double inputAD, double inputDF, double inputHP, int inputAR)
        : Character(inputClass, whatName, inputAD, inputDF, inputHP, inputAR)
    {
        skilltree = &ThiefTree;
    }
    void extra_turn_setup() override;
    void update() override;
    void draw() override;
    void My_turn() override;
    void set_moveNum(int num) { moveNum = num; }
    bool   get_passive_move() const { return passiveMove; }
    void   set_passive_move(bool TF) { passiveMove = TF; }
    void give_damage(double damage) override;
    int  get_moveNum()const { return moveNum; }
    bool get_pickpocket()const { return pickpocket; }
    double get_poison() const{ return poison; }
    Button get_move_button() { return move; }
    void controlSkill() override;
};

class Archer : public Character
{
    double penetraion{ 0 };
    bool doubleattack{false };
public:
    Archer(CharacterClass inputClass, string whatName, double inputAD, double inputDF, double inputHP, int inputAR)
        : Character(inputClass, whatName, inputAD, inputDF, inputHP, inputAR)
    {
        skilltree = &ArcherTree;
    };
    void extra_turn_setup() override;
    void update() override;
    void draw() override;
    void My_turn() override;
    double get_penetraion()const { return penetraion; }
    void controlSkill() override;
};

inline Character* myWarrior = new Warrior(Warrior_C, "Warrior", 2, 2, 15, 1);
inline Character* myMage    = new Mage(Mage_C, "Mage", 3, 1, 8, 3);
inline Character* myThief   = new Thief(Thief_C,"Thief", 3, 0, 7, 1);
inline Character* myArcher  = new Archer(Archer_C, "Archer", 4, 1, 10, 4);

inline vector<Character*> selected;

inline map<string, Image> UIImage{};

namespace mainUIImage
{
    inline void imageSet()
    {
        for (int i = start; i <= hell; i++)
        {
            chapterBackgrounds.push_back(Image{ "assets/MainScene/Chapter" + to_string(i) + "_Background.png" });
        }
        for (int i = start; i <= hell; i++)
        {
            questBackgrounds.push_back(Image{ "assets/QuestScene/Chapter" + to_string(i) + "_Background.png" });
        }
        std::thread t2([&]() {
        for(int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <= 6; j++)
            {
                UIImage["chamber-" + to_string(i) + "." + to_string(j)] = Image{ "assets/UI/chamber/chamber-" + to_string(i) + "." + to_string(j) + ".png" };
            }
        }});

        std::thread t3([&](){for (int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <= 4; j++)
            {
                UIImage["forge-" + to_string(i) + "." + to_string(j)] = Image{ "assets/UI/forge/forge-" + to_string(i) + "." + to_string(j) + ".png"};
            }
        }
        for (int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <=3; j++)
            {
                UIImage["inventory-" + to_string(i) + "." + to_string(j)] = Image{ "assets/UI/inventory/inventory-" + to_string(i) + "." + to_string(j) + ".png"};
            }
        }});
        
        std::thread t1([&](){for (int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <= 8; j++)
            {
                UIImage["stat-" + to_string(i) + "." + to_string(j)] = Image{ "assets/UI/stat/stat-" + to_string(i) + "." + to_string(j) + ".png"};
            }
        }});


        t1.join();
        t2.join();
        t3.join();
    }
    inline void imageClear()
    {
        UIImage.clear();
        chapterBackgrounds.clear();
    }
}