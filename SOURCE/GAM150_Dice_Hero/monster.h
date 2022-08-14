/*
File name: monster.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include  "portrait.h"
//#include "sfml"

class Material;
class Character;
class Tile;
struct EnemyData
{
    double hp{1};
    double maxHp{1};
    double w{};
    double h{};
    unsigned long long    exp{};
    unsigned long long    gold{};
    string name{};
    EnemyData() = default;
    EnemyData(string data);
    EnemyData(double hp, double w, double h);
    EnemyData(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string& name);
    EnemyData(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string&& name);
    void set_difficulty(double);
    double  difficulty{1};
};


class Enemy
{
    struct poisionStatus
    {
        int turn{};
        double damage{};
    };
    poisionStatus PS{};

protected:
    
    double      x{};
    double      y{};
    EnemyData   data{};
    bool   dead{false};
    Portrait port{BOARD_CENTER.x+PORT_POS_X, 0, PORT_WID, PORT_HEI};
    double      imageNum{0};
    double      frameMin{0.01};
    double      frameMax{0.1};
    vector<Material*> mat{};





    std::vector<Character*>* characters{};
    std::vector<Tile>*       tiles;
    static constexpr int     ALL_TILE_NUM{36};
    const int                location{18};
    int  lastT{};
    int  lastWho{};
    int* turn{};
    int* whoseTurn{};

    enum class Pattern_state
    {
        ENTER,
        UPDATE,
        END,
        WAITING_NEW,
    };

    class State
    {
    protected:
        double             time{0};
        double       timeRemaining{1800};
        const unsigned int ATcolor{0x902020f0};

        vector<int> AttackLoca{};

    public:
        
        virtual void enter(Enemy*)  = 0;
        virtual void draw(Enemy*)   = 0;
        virtual void update(Enemy*) = 0;
        virtual void end(Enemy*)    = 0;
        virtual void warning(Enemy*) const;
        virtual double damage(Enemy* e) const { return e->data.maxHp/10 * e->data.difficulty; }
    };
    class NullState : public State
    {
    public:
        void enter(Enemy*) override {}
        void draw(Enemy*) override {}
        void update(Enemy* b) override { b->get_currState() = Pattern_state::END; }
        void end(Enemy*) override {}
    };

    Pattern_state currState{Pattern_state::ENTER};
    NullState     nullState{};
    State*        currentState{&nullState};

    void Maintenance_status()
    {
        if (data.hp <= 0)
        {
            dead = true;
        }
    }



public:
    Enemy() = default;
    Enemy(double hp, double w, double h);
    Enemy(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string& name);
    Enemy(double hp, double w, double h, unsigned long long exp, unsigned long long gold, string&& name);
    Enemy(EnemyData data);
    virtual ~Enemy(){};
    virtual void draw(double, double);
    bool         monArea() const;
    void         draw_portrait() ;
    Portrait     get_port() const { return port; }
    void         set_difficulty(double diff) { data.set_difficulty(diff); }
    virtual void update();

    void   give_damage(double damage);
    double get_hp() const;
    bool   is_dead() const { return dead; }
    virtual unsigned long long  get_exp() { return data.exp; }
    virtual unsigned long long  get_max_gold() { return data.gold; }
    virtual void set_frame(double min, double max)
    {
        frameMin = min;
        frameMax = max;
    }
    string get_name() { return data.name; }
    Vec2 get_pos() { return { x,y }; }
    void set_PS(double damage);
    void count_PS();

    void give_mat(Material* m);
    vector<Material*> get_mat() const { return mat; }
    Pattern_state&    get_currState() { return currState; }
    State*&           get_currentState() { return currentState; }
    void              give_target(std::vector<Character*>& ch) { characters = &ch; }
    void              give_tile(std::vector<Tile>& t) { tiles = &t; }
    void              give_turn(int& t) { turn = &t; }
    void              give_whoseTurn(int& w) { whoseTurn = &w; }

    std::vector<Tile>*       get_tile() const { return tiles; }
    std::vector<Character*>* get_char() const { return characters; }

};

class BossAttackEffect : public Effect
{
    double animationNum{};
    double x{};
    double y{};
    static constexpr int size{96};
public:
    void draw() override
    {
        draw_image(enemyImage["BossAttack"][static_cast<int>(animationNum)% enemyImage["BossAttack"].size()],x,y,size,size);
        animationNum += 0.5;
        if (animationNum >= enemyImage["BossAttack"].size())
        {
            animationEnd = true;
        }
    }
    BossAttackEffect(double x, double y) : x{ x }, y{ y } {}
};


class Boss : public Enemy
{
protected:
    int              waitingTime{ 180 };

    
    class RandAttack : public State
    {
    public:
        void enter(Enemy* b) override;
        void draw(Enemy* b) override;
        void update(Enemy* b) override;
        void end(Enemy* b) override;
    };
    class EvenOddAttack : public State
    {

    public:
        void enter(Enemy* b) override;
        void draw(Enemy* b) override;
        void update(Enemy* b) override;
        void end(Enemy* b) override;
    };
    class TargetAttack : public State
    {

    public:
        void enter(Enemy* b) override;
        void draw(Enemy* b) override;
        void update(Enemy* b) override;
        void end(Enemy* b) override;
    };
    class PeripheralAttack : public State
    {
        const int         waiting{2};
    protected:
        void warning(Enemy*) const override;
    public:
        void enter(Enemy* b) override;
        void draw(Enemy* b) override;
        void update(Enemy* b) override;
        void end(Enemy* b) override;
        
    };
    class PushAttack : public State
    {
    protected:
        int pushNum{ };
    public:
        PushAttack(int PNum = random(2, 6)):pushNum(PNum){}
        void enter(Enemy* b) override;
        void draw(Enemy* b) override;
        void update(Enemy* b) override;
        void end(Enemy* b) override;
    };
    class OneRandAttack : public RandAttack
    {
    protected:
    public:
        OneRandAttack(double TimeR = 800) { timeRemaining = TimeR; }
        void enter(Enemy*) override;
        double damage(Enemy* e) const override;
    };
    class DoTAttack : public PeripheralAttack
    {
        double dotDamage{};
    public:
        DoTAttack(double dotD = 0.002):dotDamage(dotD) {timeRemaining = 800; }
        void draw(Enemy*) override;
        void update(Enemy*) override;
        double damage(Enemy* e) const override;
    };
    class StunAttack:public RandAttack
    {
    public:
        void update(Enemy*) override;
        double damage(Enemy* e) const override;
    };
    class CollapseAttack:public PeripheralAttack
    {
    public:
        void enter(Enemy*) override;
        void update(Enemy*) override;
    };
    //자폭
    //주변 도트뎀
    //기절
    //

    
    virtual void pick_pattern(){}
public:
    using Enemy::Enemy;
    
    void draw(double posX, double posY) override {
        Enemy::draw(posX, posY);
        currentState->draw(this);
    }
    virtual void pattern_update();
    void                 update() override
    {
        Maintenance_status();
        pattern_update();
    }
    [[nodiscard]]string get_name() const { return data.name; }


};

class Ent : public Boss
{
    RandAttack randAttackState{};
    PeripheralAttack peripheralAttackState{};
    PushAttack       pushAttackState{};

public:
    using Boss::Boss;
void pick_pattern() override;
};
class Genie : public Boss
{
    EvenOddAttack    evenOddAttackState{};
    PeripheralAttack peripheralAttackState{};
    DoTAttack dotAttack{};
    PushAttack       pushAttackState{};

public:
    using Boss::Boss;
    void pick_pattern() override;
};
class Titan : public Boss
{
    PeripheralAttack peripheralAttackState{};
    PushAttack       pushAttackState{};
    StunAttack stunAttack{};
    CollapseAttack collapseAttack{};
    OneRandAttack oneRandAttack{60};
public:
    using Boss::Boss;
    void pick_pattern() override;
};
class KraKen : public Boss
{
    EvenOddAttack evenOddAttack{};
    CollapseAttack pushAttackState{};
    RandAttack randAttack{};
    TargetAttack targetAttack{};
public:
    using Boss::Boss;
    void pick_pattern() override;
};
class BlackDragon : public Boss
{
    EvenOddAttack evenOddAttack{};
    TargetAttack targetAttack{};
    OneRandAttack oneRandAttack{200};
    RandAttack randAttack{};

public:
    using Boss::Boss;
    void pick_pattern() override;
};


class DevilKing : public Boss
{
    EvenOddAttack evenOddAttack{};
    TargetAttack targetAttack{};
    OneRandAttack oneRandAttack{ 400 };
    RandAttack randAttack{};
    StunAttack stunAttack{};
    PeripheralAttack peripheralAttackState{};
    CollapseAttack collapseAttack{};
    PushAttack pushAttack{random(5,8)};
    DoTAttack doTAttack{0.005};

public:
    using Boss::Boss;
    void pick_pattern() override;
};





class CommonMonsterSet
{
    map<string, EnemyData> enemiesData{};
public:
    CommonMonsterSet(){}
    virtual ~CommonMonsterSet() = default;

    virtual void  set_data();
    EnemyData get(string name) { return enemiesData[name]; }
};
class BossMonsterSet : CommonMonsterSet// planing
{
public:
    using CommonMonsterSet::CommonMonsterSet;
    void      set_data()override{}
};
inline CommonMonsterSet commonMonster{};
inline BossMonsterSet   bossMonster{};

class Box
{
protected:
    double   x{};
    double   y{};
    double hp{};
    double maxHP{};
    double wid{};
    double hei{};
    bool   open{false};
    bool hide{false};
    Portrait port{BOARD_CENTER.x - PORT_POS_X, 0, PORT_WID, PORT_HEI};

public:
    Box(double hp, double w, double h);
    //virtual void         setup();
    virtual void draw(double posX, double posY);
    void         drawPortrait() ;
    Portrait     get_port() const { return port; }
    double get_max_hp() { return maxHP; }
    double       get_hp() const { return hp; }
    virtual void update();
    void         give_damage(double damage);
    bool         isOpen() const;
    int          getObject()const;
    virtual void countDownForGoldBox() {}
    bool         isHide() const { return hide; }
    bool         boxArea()const;
    Vec2        get_pos() { return Vec2{ x, y }; }
};

class GoldBox : public Box
{
    int countDown{};

public:
    GoldBox(double hp, double w, double h);
    //void setup() override;
    void draw(double posX, double posY) override;

    void update() override;
    void countDownForGoldBox() override;
};

