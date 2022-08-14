/*
File name: UI.h
Project name: Dice Hero
Author(s): Major - Jihyeon Song, minor - Taeju kwon
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"
// ReSharper disable once CppInconsistentNaming
class UI
{
protected:
    double x;
    double y;
    double w;
    double h;
    double fontSize{0};
    double outlineWidth{5};

public:
    UI(double x_, double y_, double w_, double h_);
    virtual ~UI() = default;
    virtual void draw(){}
};

class Profile : public UI
{
    string name{};
    long double    now{};
    long double    max{};
    double    scaleVal{1};

    Color barcolor{};

public:
    Profile(string n,double x_, double y_, double w_, double h_, long double , long double, Color);
    void draw() override;
    void drawing(string sm, int a);
    void high_lighting();
    bool area()const;
    void set_now(long double);
    void set_max(long double);
    void set_name(string);
};

class Gold : public UI
{
protected:
    unsigned long long money {};

public:
    Gold(double x_, double y_, double w_, double h_);
    void draw() override;
    void set_money(unsigned long long m);
};