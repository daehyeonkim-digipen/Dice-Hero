/*
File name: monster.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "monster.h"
#include "fstream"
#include <sstream>
#include "game_header.h"
#include "tile.h"

EnemyData::EnemyData(double hp, double w, double h) : hp{hp}, w{w}, h{h} { maxHp = hp; }
EnemyData::EnemyData(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string& name):EnemyData(hp,w,h) {
    this->exp  = {exp};
    this->gold = {gold};
    this->name = {name};
}
EnemyData::EnemyData(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string&& name) : EnemyData(hp, w, h) {
    this->exp = { exp };
    this->gold = { gold };
    this->name = { name };
}



Enemy::Enemy(double hp, double w, double h) : data(hp,w,h) {
}
Enemy::Enemy(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string& name) : Enemy{{hp, w, h, exp, gold, name}} {}
Enemy::Enemy(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string&& name) : Enemy{ EnemyData{hp, w, h, exp, gold, std::move(name)} } {}

Enemy::Enemy(EnemyData data) : data(data)
{ port.naming(data.name); }

void Enemy::give_mat(Material* m)
{ mat.push_back(m); }


void Enemy::update()
{ Maintenance_status(); }
void Enemy::give_damage(double damage) { data.hp -= damage; }

double Enemy::get_hp() const { return data.hp; }

void   Enemy::draw(double posX, double posY)
{
    x = posX;
    y = posY;
    if (enemyImage[data.name].empty() == true)
    {
        push_settings();

        draw_rectangle(posX, posY, data.w, data.h);

        set_fill_color(0);
        set_font_size(25);
        draw_text(data.name, posX, posY);
        pop_settings();
    }
    else
    {
        draw_image(enemyImage[data.name][(int)imageNum], posX, posY, data.w, data.h);
        imageNum = (imageNum + random(frameMin, frameMax));
        if (imageNum >= enemyImage[data.name].size())
        {
            imageNum = 0;
        }
    }
    
}

bool Enemy::monArea()const
{
    if (Helpers::Collision::objToMouse({x, y}, data.w, data.h))
    {
        return true;
    }
    return false;
}


void Enemy::draw_portrait()
{
    
    port.draw();
}


void Enemy::set_PS(double damage)
{
    PS.damage =  data.hp * damage;
    PS.turn = 3;
}
void Enemy::count_PS()
{
    if(PS.turn > 0)
    {
        --PS.turn;
        data.hp -= PS.damage;
        if(PS.turn == 0)
        {
            PS.damage = 0;
        }
    }
}




void Enemy::State::warning(Enemy* b) const
{
    Helpers::Drawing::draw_bar(
        time / timeRemaining,
        {b->tiles->at(b->location).getTilePos().x + 100,
            b->tiles->at(b->location).getTilePos().y});
}



void Boss::RandAttack::enter(Enemy*)
{
    for (int i = 0; i < random(5, 10); ++i)
    {
        AttackLoca.push_back(doodle::random(0, ALL_TILE_NUM - 1));
    }
}
void Boss::RandAttack::draw(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    for (auto& rand : AttackLoca)
    {
        push_settings();

        b->tiles->at(rand).set_tint_col(ATcolor);
        pop_settings();
    }
    warning(b);
    
}
void Boss::RandAttack::update(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);

    if (time < timeRemaining)
    {
        ++time;
    }
    else
    {
        
        for (auto& rand : AttackLoca)
        {
            for (auto& c : *(b->get_char()))
            {
                if (rand == c->get_location())
                {
                    c->give_damage(damage(boss));
                }
            }
            events.push_event(BossAttackEffect{ b->tiles->at(rand).getTilePos().x,b->tiles->at(rand).getTilePos().y });
        }
        
        b->get_currState() = Pattern_state::END;
    }
}
void Boss::RandAttack::end(Enemy* )
{
    time = 0;
    AttackLoca.clear();
}

void Boss::EvenOddAttack::draw(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    for (auto& loca: AttackLoca)
    {
        b->tiles->at(loca).set_tint_col(ATcolor);
    }
    warning(b);
}
void Boss::EvenOddAttack::enter(Enemy* )
{
    int EvenOdd{random(0,10)%2};
    for (int i = 0; i < ALL_TILE_NUM; ++i)
    {
        if (i%2 == EvenOdd)
        {
            AttackLoca.push_back(i);
        }
    }
}
void Boss::EvenOddAttack::update(Enemy* b)
{
    Boss* boss = dynamic_cast<Boss*>(b);

    if (time < timeRemaining)
    {
        ++time;
    }
    else
    {
        
        for (auto& loca : AttackLoca)
        {
            for (auto& c : *(b->get_char()))
            {
                if (loca == c->get_location())
                {
                    c->give_damage(damage(b));
                }
            }
            events.push_event(BossAttackEffect{ boss->tiles->at(loca).getTilePos().x,boss->tiles->at(loca).getTilePos().y });

        }
        
        b->get_currState() = Pattern_state::END;
    }
}
void Boss::EvenOddAttack::end(Enemy*)
{
    time = 0;
    AttackLoca.clear();
}

void Boss::TargetAttack::draw(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    for (auto& loca : AttackLoca)
    {
        b->tiles->at(loca).set_tint_col(ATcolor);
    }
    warning(b);
}
void Boss::TargetAttack::enter(Enemy*boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    for (auto & loca:*b->characters)
    {
            AttackLoca.push_back(loca->get_location());
    }
}
void Boss::TargetAttack::update(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    if (time < timeRemaining)
    {
        ++time;
    }
    else
    {
        
        for (auto& loca : AttackLoca)
        {
            for (auto& c : *(b->get_char()))
            {
                if (loca == c->get_location())
                {
                    c->give_damage(damage(boss));
                }
            }
            events.push_event(BossAttackEffect{ b->tiles->at(loca).getTilePos().x,b->tiles->at(loca).getTilePos().y });

        }
        
        b->get_currState() = Pattern_state::END;
    }
}
void Boss::TargetAttack::end(Enemy*)
{
    time = 0;
    AttackLoca.clear();
}


void Boss::PeripheralAttack::warning(Enemy*boss) const
{
    Boss* b = dynamic_cast<Boss*>(boss);
    Helpers::Drawing::draw_remain(
        "Remain Turn: " + to_string(waiting - (*(b->turn) - b->lastT)),
        {b->tiles->at(b->location).getTilePos().x + 100,
            b->tiles->at(b->location).getTilePos().y});
}

void Boss::PeripheralAttack::draw(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    for (auto& loca : AttackLoca)
    {
        b->tiles->at(loca).set_tint_col(ATcolor);
    }
    warning(b);
}
void Boss::PeripheralAttack::enter(Enemy* boss)
{
    Boss*     b = dynamic_cast<Boss*>(boss);
    const int num{random(2,6)};
    for (int i = -num;i<=num;++i)
    {
        AttackLoca.push_back((b->location + ALL_TILE_NUM + i) % ALL_TILE_NUM);
    }
}
void Boss::PeripheralAttack::update(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    if ((*(b->turn) - b->lastT) >=2)
    {
        
        for (auto& loca : AttackLoca)
        {
            for (auto& c : *(b->get_char()))
            {
                if (loca == c->get_location())
                {
                    c->give_damage(damage(boss));
                }
            }
            events.push_event(BossAttackEffect{ b->tiles->at(loca).getTilePos().x,b->tiles->at(loca).getTilePos().y });

        }
        
        b->get_currState() = Pattern_state::END;
    }
}
void Boss::PeripheralAttack::end(Enemy*)
{
    time = 0;
    AttackLoca.clear();
}


void Boss::PushAttack::draw(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    for (auto& loca : AttackLoca)
    {
        b->tiles->at(loca).set_tint_col(ATcolor);
    }
    warning(b);
}
void Boss::PushAttack::enter(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    for (auto& loca : *b->characters)
    {
        AttackLoca.push_back(loca->get_location());
    }
}
void Boss::PushAttack::update(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    if (time < timeRemaining)
    {
        ++time;
    }
    else
    {
        
        for (auto& loca : AttackLoca)
        {
            for (auto& c : *(b->get_char()))
            {
                if (loca == c->get_location())
                {
                    c->give_damage(damage(boss));
                    c->set_location((c->get_location() + ALL_TILE_NUM - pushNum) % ALL_TILE_NUM);
                }
            }
            events.push_event(BossAttackEffect{ b->tiles->at(loca).getTilePos().x,b->tiles->at(loca).getTilePos().y });

        }
        b->get_currState() = Pattern_state::END;
    }
}
void Boss::PushAttack::end(Enemy*)
{
    time = 0;
    AttackLoca.clear();
    pushNum = 0;
}
 
void Boss::OneRandAttack::enter(Enemy*)
{ AttackLoca.push_back(doodle::random(0, ALL_TILE_NUM - 1)); }
double Boss::OneRandAttack::damage(Enemy* e) const {
    Boss * b = dynamic_cast<Boss*>(e);

    return b->data.maxHp * 10 * dynamic_cast<Boss*>(e)->data.difficulty; }


void Boss::DoTAttack::draw(Enemy* e)
{
    PeripheralAttack::draw(e);

    Boss* b = dynamic_cast<Boss*>(e);
    for (auto& loca : AttackLoca)
    {
    b->tiles->at(loca).Fire();
    }
}

void   Boss::DoTAttack::update(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);

    
    for (auto& loca : AttackLoca)
    {
        for (auto& c : *(b->get_char()))
        {
            if (loca == c->get_location())
            {
                c->give_damage(damage(boss));
            }
        }
    }
    if (time < timeRemaining)
    {
        ++time;
    }
    else
    {
        b->get_currState() = Pattern_state::END;
    }
}
double Boss::DoTAttack::damage(Enemy* e) const {
    Boss* b = dynamic_cast<Boss*>(e);
    return b->data.maxHp * dotDamage * dynamic_cast<Boss*>(e)->data.difficulty; }
void   Boss::StunAttack::update(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    if (time < timeRemaining)
    {
        ++time;
    }
    else
    {
        
        for (auto& loca : AttackLoca)
        {
            for (auto& c : *(b->get_char()))
            {
                if (loca == c->get_location())
                {
                    c->give_damage(damage(boss));
                    c->is_stun() = true;
                }
            }
            events.push_event(BossAttackEffect{ b->tiles->at(loca).getTilePos().x,b->tiles->at(loca).getTilePos().y });

        }
        b->get_currState() = Pattern_state::END;
    }
}
double Boss::StunAttack::damage(Enemy* e) const
{
    return 1 * dynamic_cast<Boss*>(e)->data.difficulty;
}
void Boss::CollapseAttack::enter(Enemy*)
{
    for (int i = 0;i < ALL_TILE_NUM;++i)
    {
        AttackLoca.push_back(i);
    }
}
void Boss::CollapseAttack::update(Enemy* boss)
{
    Boss* b = dynamic_cast<Boss*>(boss);
    if ((*(b->turn) - b->lastT) >= 2)
    {
        for (auto& c : *(b->get_char()))
        {
            for (auto& loca : AttackLoca)
            {
                if (loca == c->get_location())
                {
                    c->set_location(random(1, ALL_TILE_NUM));
                    events.push_event(BossAttackEffect{ b->tiles->at(loca).getTilePos().x,b->tiles->at(loca).getTilePos().y });
                }
            }
            b->get_currState() = Pattern_state::END;
        }
    }
}



void Boss::pattern_update()
{
    switch (currState)
    {
    case Pattern_state::ENTER:
        lastT = *turn;
        lastWho = *whoseTurn;
        currentState->enter(this);
        currState = Pattern_state::UPDATE;
        break;
    case Pattern_state::UPDATE:
        currentState->update(this); break;
    case Pattern_state::END:
        currentState->end(this);
        currState = Pattern_state::WAITING_NEW;
        break;
    case Pattern_state::WAITING_NEW:
        //pattern select
        if (waitingTime > 0)
        {
            --waitingTime;
        }
        else
        {
            pick_pattern();
            currState = Pattern_state::ENTER;
        }
        break;
    default:
        currState = Pattern_state::WAITING_NEW;
        break;
    }
}

void Ent::pick_pattern()
{
    if (data.hp < data.maxHp / 2)
    {
        int patternNum{ random(0, 12) % 4 };
        switch (patternNum)
        {
        case 0: currentState = &randAttackState; break;
        case 1: currentState = &peripheralAttackState; break;
        case 2: currentState = &pushAttackState; break;
        default:waitingTime = 180;break;
        }
    }
    else
    {
        int patternNum{ random(0, 10) % 5 };
        switch (patternNum)
        {
        case 0: currentState = &randAttackState; break;
        case 1: currentState = &pushAttackState; break;
        default:waitingTime = 180;break;
        }
    }
    waitingTime = 180;
}
void Genie::pick_pattern()
{
    if (data.hp < data.maxHp / 4)
    {
        int patternNum{ random(0, 6) % 5 };
        switch (patternNum)
        {
        case 0: currentState = &evenOddAttackState; break;
        case 1: currentState = &pushAttackState; break;
        case 2: currentState = &peripheralAttackState;break;
        case 3: currentState = &dotAttack;break;
        default:waitingTime = 180;break;
        }
    }
    else if(data.hp < data.maxHp/2)
    {
        int patternNum{ random(0, 12) % 5 };
        switch (patternNum)
        {
        case 0: currentState = &dotAttack; break;
        case 1: currentState = &peripheralAttackState; break;
        case 2: currentState = &pushAttackState; break;
        default:waitingTime = 180;break;
        }
    }
    else
    {
        int patternNum{ random(0, 12) % 5 };
        switch (patternNum)
        {
        case 1: currentState = &peripheralAttackState; break;
        case 2: currentState = &pushAttackState; break;
        default:waitingTime = 180;break;
        }
    }
    waitingTime = 180;
}
void Titan::pick_pattern()
{
    if(data.hp<data.maxHp/5)
    {
        int patternNum{ random(0, 5) % 4 };
        switch (patternNum)
        {
        case 0: currentState = &oneRandAttack; break;
        case 1: currentState = &stunAttack; break;
        case 2: currentState = &peripheralAttackState;break;
        case 3: currentState = &collapseAttack;break;
        default:waitingTime = 180;break;
        }
    }else if (data.hp < data.maxHp / 2)
    {
        int patternNum{ random(0, 10) % 5 };
        switch (patternNum)
        {
        case 0: currentState = &oneRandAttack; break;
        case 1: currentState = &collapseAttack; break;
        case 2: currentState = &peripheralAttackState;break;
        case 3: currentState = &stunAttack;break;
        case 4:currentState = &pushAttackState;break;
        default:waitingTime = 180;break;
        }
    }
    else
    {
        int patternNum{ random(0, 12) % 4 };
        switch (patternNum)
        {
        case 0: currentState = &pushAttackState; break;
        case 1: currentState = &peripheralAttackState; break;
        case 2: currentState = &collapseAttack; break;
        default:waitingTime = 180;break;
        }
    }
    waitingTime = 180;
}
void KraKen::pick_pattern()
{
    if (data.hp < data.maxHp / 5)
    {
        const int patternNum{ random(0, 5) % 4 };
        switch (patternNum)
        {
        case 0: currentState = &evenOddAttack; break;
        case 1: currentState = &targetAttack; break;
        case 2: currentState = &pushAttackState;break;
        default:waitingTime = 180;break;
        }
    }
    else if (data.hp < data.maxHp / 2)
    {
        const int patternNum{ random(0, 10) % 6 };
        switch (patternNum)
        {
        case 0: currentState = &randAttack; break;
        case 1: currentState = &pushAttackState; break;
        case 2: currentState = &evenOddAttack;break;
        case 3:currentState = &pushAttackState;break;
        default:waitingTime = 180;break;
        }
    }
    else
    {
        const int patternNum{ random(0, 12) % 5 };
        switch (patternNum)
        {
        case 0: currentState = &pushAttackState; break;
        case 1: currentState = &randAttack; break;
        case 2: currentState = &targetAttack; break;
        default:waitingTime = 180;break;
        }
    }
    waitingTime = 180;
}

void BlackDragon::pick_pattern()
{
    if (data.hp < data.maxHp / 5)
    {
        const int patternNum{ random(0, 3) % 3 };
        switch (patternNum)
        {
        case 0: currentState = &randAttack; break;
        case 1:currentState = &evenOddAttack;break;
        default:waitingTime = 180;break;
        }
    }
    else if (data.hp < data.maxHp / 2)
    {
        const int patternNum{ random(0, 10) % 6 };
        switch (patternNum)
        {
        case 0: currentState = &randAttack; break;
        case 1: currentState = &oneRandAttack; break;
        case 2: currentState = &evenOddAttack;break;
        case 3:currentState = &targetAttack;break;
        default:waitingTime = 180;break;
        }
    }
    else
    {
        const int patternNum{ random(0, 12) % 6 };
        switch (patternNum)
        {
        case 0: currentState = &oneRandAttack; break;
        case 1: currentState = &randAttack; break;
        case 2: currentState = &targetAttack; break;
        default:waitingTime = 180;break;
        }
    }
    waitingTime = 180;
}
void DevilKing::pick_pattern()
{
    if (data.hp < data.maxHp / 10)
    {
        const int patternNum{ random(0, 10) % 3 };
        switch (patternNum)
        {
        case 0:currentState = &evenOddAttack;break;
        case 1:currentState = &targetAttack;break;
        default:waitingTime = 180;break;
        }
    }
    else if (data.hp < data.maxHp / 5)
    {
        const int patternNum{ random(0, 10) % 5 };
        switch (patternNum)
        {
        case 0: currentState = &doTAttack; break;
        case 1:currentState = &evenOddAttack;break;
        case 2:currentState = &collapseAttack;break;
        case 3:currentState = &targetAttack;break;
        case 4:currentState = &stunAttack;break;
        default:waitingTime = 180;break;
        }
    }
    else if (data.hp < data.maxHp / 2)
    {
        const int patternNum{ random(0, 10) % 6 };
        switch (patternNum)
        {
        case 0: currentState = &randAttack; break;
        case 1: currentState = &oneRandAttack; break;
        case 2: currentState = &pushAttack;break;
        case 3:currentState = &collapseAttack;break;
        case 4:currentState = &peripheralAttackState;break;
        default:waitingTime = 180;break;
        }
    }
    else
    {
        const int patternNum{ random(0, 16) % 8 };
        switch (patternNum)
        {
        case 0: currentState = &oneRandAttack; break;
        case 1: currentState = &randAttack; break;
        case 2: currentState = &doTAttack; break;
        case 3: currentState = &pushAttack;break;
        case 4: currentState = &stunAttack;break;
        default:waitingTime = 180;break;
        }
    }
    waitingTime = 180;
}








//KingOrc::KingOrc(double hp, double w, double h) : Boss(hp, w, h) { name = "KingOrc"; }


Box::Box( double hp, double w, double h)
    : maxHP{ hp }, hp { hp }, wid{ w }, hei{ h }
{ port.naming("Box"); }
void Box::draw(double posX, double posY)
{
    x = posX;
    y = posY;
    doodle::push_settings();
    //doodle::set_rectangle_mode(RectMode::Center);
    /*doodle::set_fill_color(50, 50, 50);

    doodle::draw_rectangle(posX, posY, wid, hei);
    doodle::set_font_size(8.);*/
    //doodle::draw_text(std::to_string(now), posX, posY + hei / 2);
    draw_image(boxImage["box"], posX, posY, wid, hei);
    doodle::pop_settings();
}
void Box::update()
{
    if (hp <= 0)
    {
        open = {true};
    }
}

void        Box::give_damage(double damage) { hp -= damage; }
bool Box::isOpen() const { return open; }
int         Box::getObject() const{ return doodle::random(0, 100); }
void Box::drawPortrait()

{
    port.draw();
}





GoldBox::GoldBox( double hp, double w, double h) : Box(hp, w, h)
{
    countDown = {doodle::random(3, 7)};
    port.naming("Gold box");
}

void GoldBox::draw(double posX, double posY)
{
    x = posX;
    y = posY;
    doodle::push_settings();
    //doodle::set_rectangle_mode(RectMode::Center);
    //doodle::set_fill_color(255, 255, 0);
    //doodle::draw_rectangle(posX , posY, wid, hei);
    //doodle::set_font_size(8.);
    //doodle::draw_text(std::to_string(now), posX, posY + hei / 2);

    draw_image(boxImage["goldBox"], posX, posY, wid, hei);
    doodle::pop_settings();
}
void GoldBox::update()
{
    if (hp <= 0)
    {
        open = {true};
    }
    if (countDown <= 0)
    {
        hide = {true};
    }
}
void GoldBox::countDownForGoldBox()
{
    //cout << countDown << endl;
    --countDown;
}


bool Box::boxArea() const
{
    if (Helpers::Collision::objToMouse({x, y}, wid, hei))
    {
        return true;
    }
    return false;
}



EnemyData::EnemyData(string data)
{
    std::istringstream lineData(data);
    lineData >> hp;
    lineData >> w;
    lineData >> h;
    lineData >> exp;
    lineData >> gold;
    string text{};
    //lineData >> name;
    while (lineData >> text)
    {
        if (text == "Name:")
        {
            while(lineData >> text)
            {
                if (text == ".")
                {
                    break;
                }
                name += text + " ";
            }
        }
        else if (text == "Explane:")
        {
            while (lineData >> text)
            {
                if (text == ".")
                {
                    break;
                }
                //설명 넣기
            }
        }
    }
    if (name.empty() == true)
    {
        name = "No Image";
    }
    maxHp = hp;

}
void EnemyData::set_difficulty(double diff)
{
    //난이도 조절
    hp *= diff;
    maxHp *= diff;
    exp = static_cast<int>(exp * diff);
    gold = static_cast<int>(gold * diff);
    difficulty = diff;
}


void CommonMonsterSet::set_data()
{
    ifstream data("dataFile/commonMonsterData.txt");
    std::string line;
    while (std::getline(data, line))
    {
        EnemyData Edata{line};
        enemiesData[Edata.name] = {Edata};
    }
    data.close();
    
}
