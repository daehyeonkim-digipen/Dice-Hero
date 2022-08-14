/*
File name: RGB.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
struct RGB
{
    double R{};
    double G{};
    double B{};
    RGB() = default;
    RGB(double r, double g, double b) : R(r), G(g), B(b) {}
};