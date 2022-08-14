/*
File name: token.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"
#include "Ingame_image.h"
#include "EffectStar.h"
enum EffectType
{
    None = 0,
    attack = 1,
    move,
    BACK_MOVE,
    mana,
    MAGIC_TELEPORT,
    MAGIC_ATTACK,
    MAGIC_RESURRECTION,
    MAGIC_BOMB,
};
struct EffectInfo
{
    int       howMuch{};
    EffectType type{};
    bool      on{false};
    int        extraRange{};
    int        EFFStart{0};
    int        EFFEnd{1};
    void      set_on(bool b) { on = b; }
};
class Token
{
    Vec2 stPoint{};
    Vec2       position{0, 0};
    EffectType type{};
    double     size{};
    bool       tokenPressed{false};
    bool       anotherTokenChooose{false};
    bool       tokenDrop{false};
    bool       avoiding{false};
    highLightingEffect::CircleHighLight circleHighLight{};
    void restrict_area();
    void avoid(double x, double y);
    void avoidAnotherToken();

public:
    Token();
    Token(double x, double y, double sz, EffectType t);
    void Update();
    void Draw() const;
    bool tokenArea(double x, double y) const;
    bool          getTokenDrop() const;
    EffectType    getTokenType() const;
    double getTokenX() const { return position.x; }
    double getTokenY() const { return position.y; }
    double getsize() const { return size; }
    double        getdistfromxy(double x, double y) const;
    void init();
    bool get_token_pressed()const { return tokenPressed; }
    void          click_me() { circleHighLight.operator()(position, size); }
};

