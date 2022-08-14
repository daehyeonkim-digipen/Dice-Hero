/*
File name: 3_1_ending_scene.h
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
class EndingScene : public Scene
{
    struct creditText
    {
        string text{};
        double ypos{ -WINDOW_HEIGHT / 2 };
    };
    ifstream data;
    std::string line;
    list<creditText> texts{};
    double textInterval{  };


    Button endingBackButton{ "X", +WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.45, WINDOW_HEIGHT / 14, WINDOW_HEIGHT / 14 };
    int speed = 5;
public:
    void setup() override;
    void update() override;
    void draw() override;
    ~EndingScene()override;
};