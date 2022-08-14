/*
File name: game_header.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "game_header.h"

#include "IngameSceneHelper.h"
#include "TextEvent.h"
#include <utility>
void PlayerStatus::set_exp_goal() { this->expGoal = static_cast<int>(10 * pow(1.08, level)); }
void Character::set_location(int input)
{
    if(hp > 0)
    {
            this->location = input;
    }
}
void Character::set_position(Vec2 input) { this->position = input; }
Vec2 Character::get_position() const { return position; }
int  Character::get_location() const { return location; }
bool Character::dice_in_token(Token t, const Dice& d)
{

    if (d.dice_area() == true && t.getTokenDrop() == true && d.get_is_rolled() == true)
    {
        return true;
    }
    return false;
}


Character::Character(CharacterClass inputClass, string whatName, double inputAD, double inputDF, double inputHP, int inputAR)
{
    myClass     = inputClass;
    className   = std::move(whatName);
    ad          = inputAD;
    df          = inputDF;
    hp          = inputHP;
    maxHP       = hp;
    attackRange = inputAR;
}

void Character::set_weapon(Weapon* input)
{
    if (myWeapon != nullptr)
    {
        ad /= myWeapon->get_ad();
    }
    myWeapon = input;
    if (myWeapon != nullptr)
    {
        ad *= myWeapon->get_ad();
    }
}

void Character::set_armor(Armor* input)
{
    if (myArmor != nullptr)
    {
        df /= myArmor->get_df();
        maxHP /= myArmor->get_hp();
        hp = maxHP;
    }
    myArmor = input;
    if (myArmor != nullptr)
    {
        df *= myArmor->get_df();
        maxHP *= myArmor->get_hp();
        hp = maxHP;
    }
}

void Character::give_damage(double damage)
{//warrior skill check
    if (hp > 0)
    {
        Warrior* wc{ dynamic_cast<Warrior*>(myWarrior) };
        if (wc != nullptr && wc->get_protection() == true && wc->get_hp() > wc->get_max_hp() / 2)//warrior skill defender
        {
            wc->give_damage((damage > this->get_df() ? damage - this->get_df() : 0) * pow(0.996, this->get_df()));
        }
        else
        {
            hp -= (damage > this->get_df() ? damage - this->get_df() : 0) * pow(0.996, this->get_df());
        }
    }
    
}

void Thief::give_damage(double damage)
{
    const double percent{ random(0.,1.) };// bug??
    if(dodge < percent)
    {
        Character::give_damage(damage);
    }
    else
    {
        events.push_event(EventLog{"Dodge!!",position.x,position.y});
    }
}


void Character::MaintenanceStatus()
{
    if (hp > maxHP)
    {
        hp = maxHP;
    }
    else if (hp < 0)
    {
        hp = 0;
    }
}
bool Character::is_mouse_clicked_token(int i)
{
    if (tokens[i].tokenArea(doodle::get_mouse_x(), doodle::get_mouse_y())==true && MouseIsPressed == true)
    {
        return true;
    }
    return false;
}


void Warrior::update()
{
    MaintenanceStatus();
}


void HighLightingMe(double posX,double posY)
{
    int timer = 0;
    timer++;
    push_settings();
    set_font_size(26);
    no_outline();
    //for (int timer = 0; timer >= 0; timer++)
    //{
        if (timer % 2 < 1)
        {
            set_fill_color(255, 255, 0);
        } 
        set_fill_color(0, 255, 255);

        draw_ellipse(posX, posY, 38, 42);

    pop_settings();
}
void Warrior::draw() {
    if(isDead)
    {
        draw_image(objectImage["blood"], position.x-5, position.y+10, 40, 40);
    }
    draw_image(characterImage["Warrior"], position.x - 15, position.y + 10, 40, 40);
    if (Helpers::Collision::objToMouse({ position.x - 5, position.y + 10 }, 40, 40))
    {
        Helpers::Information::ingameInforation(get_information());

    }
}
void Warrior::My_turn()
{
    HighLightingMe(position.x - 15, position.y + 10);
}
void Warrior::give_damage(double damage)
{
    if (hp > 0)
    {
        hp -= (damage > this->get_df() ? damage - this->get_df() : 0) * pow(0.996, this->get_df());
        nowRage += 1;
    }
}

void Warrior::controlSkill()
{
    Weapon& keepWeapon = *myWeapon;
    Armor& keepArmor = *myArmor;
    set_weapon(nullptr);
    set_armor(nullptr);
    ad = 2;
    df = 2;
    maxHP = 15;
    attackRange = 1;
    maxRage = 8;
    for(auto s : skilltree->skills)
    {
        if(s->get_skillon())
        {
            ad += s->get_ad();
            maxHP += s->get_hp();
            df += s->get_df();
            attackRange += s->get_ra();
            maxRage -= s->get_rage();
            drain = s->get_drain();
            protection = s->get_protection();
        }
    }
    set_weapon(&keepWeapon);
    set_armor(&keepArmor);
}


void Mage::update()
{
    MaintenanceStatus();
}
void Mage::draw() {
    if (isDead)
    {
        draw_image(objectImage["blood"],  position.x +15 , position.y+10, 40, 40);
    }
    draw_image(characterImage["Mage"], position.x + 5, position.y + 10, 40, 40);
    if (Helpers::Collision::objToMouse({ position.x + 5, position.y + 10 }, 40, 40))
    {
        Helpers::Information::ingameInforation(get_information());

    }
}
void Mage::My_turn()
{
    HighLightingMe(position.x + 5, position.y + 10);
}
void Mage::give_extra_resource(int er)
{
    if (hp > 0)
    {
        this->mp += er;
    }
}

void Mage::controlSkill()
{
    Weapon& keepWeapon = *myWeapon;
    Armor& keepArmor = *myArmor;
    set_weapon(nullptr);
    set_armor(nullptr);
    ad = 3;
    df = 1;
    maxHP = 8;
    attackRange = 3;
    mana_cost = 15;
    mana_regen = 0;
    for (auto s : skilltree->skills)
    {
        if (s->get_skillon())
        {
            ad += s->get_ad();
            maxHP += s->get_hp();
            df += s->get_df();
            attackRange += s->get_ra();
            mana_regen += s->get_regen();
            mana_cost -= s->get_mana_cost();
            unlimited = s->get_unlimited();
        }
    }
    if(mageSkill3.get_skillon() == true)
    {
        magicLevel = 2;
    }
    set_weapon(&keepWeapon);
    set_armor(&keepArmor);
}

void Thief::update()
{
    MaintenanceStatus();
}
void Thief::draw()
{
    if (isDead)
    {
        draw_image(objectImage["blood"],position.x+15, position.y-10,40, 40);
    }
    if (moveNum != 0)
    {
        move.draw_button();
    }
    draw_image(characterImage["Thief"], position.x + 5, position.y - 10, 40, 40);
    if (Helpers::Collision::objToMouse({ position.x + 5, position.y - 10 }, 40, 40))
    {
        Helpers::Information::ingameInforation(get_information());

    }
}
void Thief::My_turn()
{ HighLightingMe(position.x + 5, position.y - 10); }

void Thief::controlSkill()
{
    Weapon& keepWeapon = *myWeapon;
    Armor& keepArmor = *myArmor;
    set_weapon(nullptr);
    set_armor(nullptr);
    ad = 3;
    df = 0;
    maxHP = 7;
    attackRange = 1;
    dodge = 0;
    poison = 0;
    for (auto s : skilltree->skills)
    {
        if (s->get_skillon())
        {
            ad += s->get_ad();
            maxHP += s->get_hp();
            df += s->get_df();
            attackRange += s->get_ra();
            dodge += s->get_dodge();
            poison += s->get_poison();
            pickpocket = s->get_lockpicking();
            backmove = s->get_backmove();
        }
    }
    set_weapon(&keepWeapon);
    set_armor(&keepArmor);
}

void Archer::update() { MaintenanceStatus(); }
void Archer::draw() {
    if (isDead)
    {
        draw_image(objectImage["blood"],  position.x-5, position.y-10, 40, 40);
    }
    draw_image(characterImage["Archer"], position.x - 15, position.y - 10, 40, 40);
    if (Helpers::Collision::objToMouse({ position.x - 15, position.y - 10 }, 40, 40))
    {
        Helpers::Information::ingameInforation(get_information());

    }
}
void Archer::My_turn()
{
    HighLightingMe(position.x - 15, position.y - 10);
}

void Archer::controlSkill()
{
    Weapon& keepWeapon = *myWeapon;
    Armor& keepArmor = *myArmor;
    set_weapon(nullptr);
    set_armor(nullptr);
    ad = 4;
    df = 1;
    maxHP = 10;
    attackRange = 4;
    penetraion = 0;
    for (auto s : skilltree->skills)
    {
        if (s->get_skillon())
        {
            ad += s->get_ad();
            maxHP += s->get_hp();
            df += s->get_df();
            attackRange += s->get_ra();
            penetraion += s->get_penetration();
            doubleattack = s->get_attacktoken2();
        }
    }
    set_weapon(&keepWeapon);
    set_armor(&keepArmor);
}

string Character::get_class_name() const
{ return this->className; }
    /// <summary>
/// my plan 
/// </summary>
void Character::turn_setup() {
     dices.clear();
     tokens.clear();
     isMove = false;
     dices.push_back(Dice{WINDOW_WIDTH*0.08, WINDOW_HEIGHT * 0.05, 100});
     dices.push_back(Dice{WINDOW_WIDTH * -0.08, WINDOW_HEIGHT * 0.05, 100});
     tokens.push_back(Token{WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * -0.025, 40, EffectType::attack});
     tokens.push_back(Token{WINDOW_WIDTH * -0.03, WINDOW_HEIGHT * -0.025, 40, EffectType::move});
     extra_turn_setup();
}
void Mage::extra_turn_setup()
{
    tokens.push_back(Token{WINDOW_WIDTH * 0., WINDOW_HEIGHT * -0.09, 40, EffectType::mana});
}
void Thief::extra_turn_setup()
{
    if (backmove == true)
    {
        tokens.push_back(Token{ WINDOW_WIDTH * 0., WINDOW_HEIGHT * -0.09, 40, EffectType::BACK_MOVE });

    }
    passiveMove = false;
    moveNum = 0;
}
void Archer::extra_turn_setup()
{
    if (doubleattack == true)
    {
        tokens.push_back(Token{ WINDOW_WIDTH * 0., WINDOW_HEIGHT * -0.09, 40, EffectType::attack });
    }
}



bool Character::least_check_dices_rolled()
{
    for (auto& d : dices)
    {
        if (d.get_is_rolled() == true)
        {
            return true;
        }
    }
    return false;
}
bool Character::check_dices_rolled()
{
    for (auto& d : dices)
    {
        if (d.get_is_rolled() == false)
        {
            return false;
        }
    }
    return true;
}



void Character::dt_draw()
{
    for (auto& d : dices)
    {
        d.draw();
        if (d.get_is_rolled() == false)
        {
            d.click_me();
        }
    }
    for (auto& t : tokens)
    {
        t.Draw();
        if (least_check_dices_rolled() == true)
        {
            //token highLight
            t.click_me();
        }
    }
}
void Character::doubleUpdate()
{
    if (Isdouble == false)
    {
        if (dices.size() == 2)
        {
            if (dices[0].get_is_rolled() == true && dices[1].get_is_rolled() == true && dices[0].get_num() == dices[1].get_num())
            {
                Isdouble = true;
            }
        }
        else if (dices.size() == 1 && doubleCheck.size() == 1)
        {
            if (dices[0].get_is_rolled() == true && doubleCheck[0] == dices[0].get_num())
            {
                Isdouble = true;
            }
        }
        else if (dices.empty() && doubleCheck.size() == 2)
        {
            if (doubleCheck[0] == doubleCheck[1])
            {
                Isdouble = true;
            }
        }
    }
}


void Character::dt_update() {
    
    for (int i = 0;i<dices.size();++i)
    {
        dices[i].update();
    }
    
    
    for (auto i = 0;i< tokens.size();++i)
    {
        tokens[i].Update();
        if (tokens[i].getTokenDrop() == true)
        {
            for (auto j = 0;j< dices.size();++j)
            {
                if (dice_in_token(tokens[i], dices[j]) == true && tEffect.on == false )
                {
                    if((dynamic_cast<Thief*>(this) != nullptr) 
                        && dynamic_cast<Thief*>(this)->get_moveNum() != 0 
                        && (tokens[i].getTokenType() == EffectType::move || tokens[i].getTokenType() == EffectType::BACK_MOVE))
                    {
                        break;
                    }
                    tEffect.type    = tokens[i].getTokenType();
                    tEffect.howMuch = dices[j].get_num();
                    tEffect.on      = true;
                    tokens.erase(tokens.begin() + i);
                    doubleCheck.push_back(dices[j].get_num());
                    //doubleCheck.push_back(dices[j].get_num());
                    dices.erase(dices.begin() + j);
                }
            }
        }
    }
    if (tEffect.type == EffectType::move)
    {
        isMove = true;
    }
    
    doubleUpdate();
    make_one_token_pick();
}
void Character::make_one_token_pick()
{
    if (check_pick_over_one_token() == true)
    {
        for (auto& t : tokens)
        {
            t.init();
        }
    }
}

bool Character::check_pick_over_one_token()
{
    int pickNUm{0};
    for(auto& t:tokens)
    {
        if(t.get_token_pressed() == true)
        {
            ++pickNUm;
            if(pickNUm >1)
            {
                return true;
            }
        }
    }
    return false;
}
