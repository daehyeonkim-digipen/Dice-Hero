/*
File name: 1_2_endgame_screen.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
#include "game_header.h"



class EndGameScene : public Scene
{

protected:
    unsigned long long money{};
    long double exp{};
    bool animationEnd{false};
    Button       next{"X", WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.17,70,70};
    int code;
    virtual void reward_animation(){}
    virtual void animation_end(){}
    void animation_skip();
    void         make_button();
    virtual void         go_main_scene();
    void         draw_background() const;
    void draw_material()const;

public:
    EndGameScene(long double e);
    EndGameScene(unsigned long long m, long double e);
    //void setup()override{}
    void update() override;
    //void draw() override;
};

class ClearScene : public EndGameScene
{
    long double moneyAnimation{};
    long double expAnimation{};
    int    matNum{};
    bool   boss{false};
    
    void reward_animation()override;
    void   animation_end() override;

public:
    ClearScene(unsigned long long m, long double e,int mat,bool b);
    void setup() override;
    void draw() override;
    void go_main_scene() override;
};

class FailScene : public EndGameScene
{
    long double moneyAnimation{};
    long double expAnimation{};

    void reward_animation() override;
public:
    FailScene(unsigned long long m, long double e);
    void draw() override;
};
