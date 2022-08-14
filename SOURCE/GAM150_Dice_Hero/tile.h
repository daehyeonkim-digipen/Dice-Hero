/*
File name: tile.h
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"
#include "monster.h"
class Tile
{
private:
    Vec2   tilePos{0, 0};
    double tileWidth     = 0;
    double tileHeight    = 0;
    bool   isTileApex    = false;
    bool   isBoxOn       = false;
    bool   isGoldenBoxOn = false;
    bool   isMonsterOn   = false;
    ///
    Box*   tileBox{nullptr};
    Enemy* tileEnemy{nullptr};

    bool isDown = false;
    Vec2 objPos[2]{};
    int    tileIndex = 0;

    int tileOffset{};

    unsigned int hexCol{0x00000000};

    double tileCircleLeng{45};
    highLightingEffect::CircleHighLightJustCircle circleHighLight{};

public:


    void   setTileIndex(int input) { tileIndex = input; }
    //Vec2   get_obj_pos(int i)const { return objPos[i]; }
    void   computeObjPos(int plane = 0);
    bool   get_is_down() const{ return isDown; }
    void   set_is_down(bool input) { isDown = input; }
    int    get_tileOffset() const{ return tileOffset; }
    void   set_tileOffset(int off) { tileOffset = off; }
    void   draw_info(string) const;
    void   setTilePos(double, double);
    void   setTileSize(double, double);
    Vec2   getTilePos() const;
    double getTileWidth() const;
    double getTileHeight() const;
    void   setApex(bool);
    bool   getApex() const;
    bool   getBoxOn() const;
    bool   getGoldenBoxOn() const;
    bool   getMonsterOn() const;
    void   setMonsterOn(bool);
    void   setBoxOn(bool);
    void   setGoldenBoxOn(bool);
    ///
    void spawnBox(double hp);
    void spawnGoldBox(double hp);

    void          spawn_boss(Boss* b);
    void            spawnEnemy(EnemyData data, double diff);
    void            spawnEnemy(EnemyData data, double diff,double minFrame,double maxFrame);
    void            give_mat_to_enemy(Material* m)const;
    void          initialBox();
    void            initialEnemy();
    bool   getEnemyDead() const { return tileEnemy->is_dead(); }
    double getEnemyHP() const { return tileEnemy->get_hp(); }
    Box*   getBox() const { return tileBox; }
    Enemy* getEnemy() const { return tileEnemy; }
    void            draw(int current_chapter);
    void            set_tint_col(unsigned int hex) { hexCol = hex; }
    void            reset_tint_col() { hexCol = 0; }
    void   BEdraw() const;
    void   BEupdate() const;
    void   drawBEPortrait() const;
    void   draw_object_info() const;
    string        choosePortrait() const;
    bool            tile_area() const { return Helpers::Distance::objToMouse({tilePos.x, tilePos.y}) <= tileCircleLeng; }
    double get_tile_circle_leng() const { return tileCircleLeng; }
    void            click_me() { circleHighLight.operator()(tilePos, tileCircleLeng); }
    void Fire();
};