/*
File name: scene_manager.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"
#include "EffectStar.h"
#include "Arts.h"
class Scene //scene_manager.h
{
protected:
    
    bool isSceneSet = false;

public:
    virtual ~Scene() = default;
    bool get_is_scene_set() const { return this->isSceneSet; }
    void setting()
    {
        this->setup();
        isSceneSet = true;
    }
    virtual void setup(){}
    virtual void update(){}
    virtual void draw(){}
};


class Button
{
    highLightingEffect::CircleHighLight circleHighLight{};
    bool canHighlight{true};
public:
    Vec2 Pos{0, 0};
    string name{"button name"};
    double buttonWidth = 0;
    double buttonHeight = 0;
    bool   isButtonPressed = false;
    int    buttonCode      = 0;
    bool   working         = true;
public:
    Button() = default;
    Button(string, double, double, double, double);
    Button(string, double, double, double, double, bool);
    Button(string, double, double, double, double, int, bool);
    bool   mouse_on_check() const;
    void   draw_button();
    bool   get_button_status();
    void   set_button_position(Vec2);
    int    get_button_code() const;
    string get_button_name() const;
    void   set_button_working(bool);
    bool   get_button_working();
    void click_me(unsigned int col = 0xffffffff) {
        if (canHighlight == true)
        {
            circleHighLight.operator()(Pos, buttonWidth * 5 / 12, col);
        }
        canHighlight = true;
    }
    bool& can_high_lighting() { return canHighlight; }
    
};


class RightSideUIButton : public Button
{
    Vec2 startPos{};
    double hideLeng{};

public:
    using Button::Button;
    RightSideUIButton(string name, double height)
        : Button(name, WINDOW_WIDTH * 0.47, height, 135, 60),
    startPos(Pos), hideLeng(buttonWidth){}
    void Draw()
    {
        Pos.x = startPos.x + hideLeng*5/6;
        draw_button();
        if (Helpers::Collision::objToMouse({WINDOW_WIDTH/2,0}, WINDOW_WIDTH/4, WINDOW_HEIGHT) == true)
        {
            if (hideLeng > 0 )
            {
                hideLeng-=10;
            }
            else
            {
                hideLeng = 0;
            }
        }
        else
        {
            if (hideLeng <buttonWidth)
            {
                hideLeng += 20;
            }
            else
            {
                hideLeng = buttonWidth;
            }
        }
    }
};

namespace SceneChangeInput //scene_manager.h
{
    inline void toPlay()
    {
        currentNumber   = SceneNumber::play_scene;
        isNumberChanged = true;
    }
    inline void toGameMain()
    {
        currentNumber   = SceneNumber::game_scene_main;
        isNumberChanged = true;
    }
    inline void toGameQuest()
    {
        currentNumber   = SceneNumber::game_scene_quest;
        isNumberChanged = true;
    }
    inline void toIngame()
    {
        currentNumber = SceneNumber::game_scene_ingame;
        isNumberChanged = true;
    }
    inline void toSetting()
    {
        currentNumber = SceneNumber::setting_scene;
        isNumberChanged = true;
    }
    inline void toCredit()
    {
        currentNumber = SceneNumber::credit_scene;
        isNumberChanged = true;
    }
    inline void toEnding()
    {
        currentNumber = SceneNumber::ending_scene;
        isNumberChanged = true;
    }
    inline void toCompleteScene()
    {
        currentNumber   = SceneNumber::game_complete_scene;
        isNumberChanged = true;
    }
    inline void toFailScene()
    {
        currentNumber   = SceneNumber::game_fail_scene;
        isNumberChanged = true;
    }
    inline void toGameForge()
    {
        currentNumber   = SceneNumber::game_scene_forge;
        isNumberChanged = true;
    }
    inline void toGameChamber()
    {
        currentNumber   = SceneNumber::game_scene_chamber;
        isNumberChanged = true;
    }
    inline void toGameInventory()
    {
        currentNumber   = SceneNumber::game_scene_inventory;
        isNumberChanged = true;
    }
    inline void toGameStat()
    {
        currentNumber = SceneNumber::game_stat_scene;
        isNumberChanged = true;
    }
}
inline Button cancelButton("X", 0, 0, WINDOW_HEIGHT / 20, WINDOW_HEIGHT / 20);