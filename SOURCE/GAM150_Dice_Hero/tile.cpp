/*
File name: tile.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "tile.h"

#include "IngameSceneHelper.h"
bool Tile::getApex() const { return this->isTileApex; }
bool Tile::getMonsterOn() const { return this->isMonsterOn; }
bool Tile::getBoxOn() const { return this->isBoxOn; }
bool Tile::getGoldenBoxOn() const { return this->isGoldenBoxOn; }
Vec2 Tile::getTilePos() const { return this->tilePos; }

double Tile::getTileWidth() const { return this->tileWidth; }
double Tile::getTileHeight() const { return this->tileHeight; }


void Tile::setTilePos(double inputX, double inputY)
{
    this->tilePos.x = inputX;
    this->tilePos.y = inputY;
}
void   Tile::setApex(bool input) { isTileApex = input; }
void   Tile::setMonsterOn(bool input) { this->isMonsterOn = input; }
void   Tile::setBoxOn(bool input) { this->isBoxOn = input; }
void   Tile::setGoldenBoxOn(bool input) { this->isGoldenBoxOn = input; }
void   Tile::setTileSize(double inputW, double inputH)
{
    this->tileWidth  = inputW;
    this->tileHeight = inputH;
}


void Tile::computeObjPos(int plane)
{
    for (auto& obj : objPos)
    {
        if (plane == 1)
        {
            obj = Helpers::Position::randomCirclePos<1>(tilePos, 15.);
        }
        else if (plane == 2)
        {
            obj = Helpers::Position::randomCirclePos<2>(tilePos, 15.);
        }
        else if (plane == 3)
        {
            obj = Helpers::Position::randomCirclePos<3>(tilePos, 15.);
        }
        else if (plane == 4)
        {
            obj = Helpers::Position::randomCirclePos<4>(tilePos, 15.);
        }
        else
        {
            obj = Helpers::Position::randomCirclePos(tilePos, 15.);
        }
    }
}

/////
void Tile::spawnBox(double hp) {
    if (tileBox == nullptr)
    {
        isBoxOn = true;
        tileBox = new Box{hp, 32, 32};
    }
}
void Tile::spawnGoldBox(double hp)
{
    if (tileBox == nullptr)
    {
        isGoldenBoxOn = true;
        tileBox       = new GoldBox{hp, 35, 35};
    }
}


void Tile::spawnEnemy(EnemyData data, double diff)
{
    if (tileEnemy == nullptr)
    {
        isMonsterOn = true;
        tileEnemy   = new Enemy{data};
        tileEnemy->set_difficulty(diff);
    }
}
void Tile::spawnEnemy(EnemyData data, double diff, double minFrame, double maxFrame)
{
    if (tileEnemy == nullptr)
    {
        spawnEnemy(data, diff);
        tileEnemy->set_frame(minFrame, maxFrame);
    }
}
void Tile::give_mat_to_enemy(Material* m)const
{
    if (tileEnemy != nullptr)
    {
        tileEnemy->give_mat(m);
    }
}


void Tile::spawn_boss(Boss* b)
{
    if (tileEnemy == nullptr)
    {
        isMonsterOn = true;
        tileEnemy   = b;
    }
}





void Tile::BEdraw() const
{
    
    if (tileBox != nullptr)
    {
        tileBox->draw(objPos[0].x, objPos[0].y);
    }
    if (tileEnemy != nullptr)
    {
        tileEnemy->draw(objPos[1].x, objPos[1].y);
    }
}

void Tile::BEupdate() const
{
    if (tileBox != nullptr)
    {
        tileBox->update();
    }
    if (tileEnemy != nullptr)
    {
        tileEnemy->update();
    }
}
void Tile::Fire()
{
    static int Num{0};
    draw_image(enemyImage["Fire"][Num% enemyImage["Fire"].size()], tilePos.x, tilePos.y,120,120);
    Num = (Num + 1) % enemyImage["Fire"].size();
}


void Tile::drawBEPortrait() const
{
    if (tileBox != nullptr)
    {
        tileBox->drawPortrait();
    }
    if (tileEnemy != nullptr)
    {
        tileEnemy->draw_portrait(); 
    }
}
string Tile::choosePortrait() const
{
    if (tileBox != nullptr)
    {
        if (tileBox->get_port().area() == true && MouseIsPressed == true)
        {
            return "Box";
        }
    }
    if (tileEnemy != nullptr)
    {
        if (tileEnemy->get_port().area() == true && MouseIsPressed == true)
        {
            return "Enemy";
        }
    }
    return "";
}

void Tile::draw(int current_chapter)
{
    push_settings();
    if (hexCol != 0)
    {
        set_tint_color(HexColor{hexCol}); // Another way: overlap image or draw image by condition
    }
    draw_image(tileImage[current_chapter * tileOffset], tilePos.x, tilePos.y, tileWidth, tileHeight);
    pop_settings();
    hexCol = 0;
}


void Tile::draw_info(string object) const
{
    if (object == "box")
    {
        Helpers::Information::ingameInforation(tileBox->get_port().get_name()+
            "\nHP: " + Helpers::floatData::to_one_point_string(tileBox->get_hp()));
    }
    else if (object == "enemy")
    {
        Helpers::Information::ingameInforation(tileEnemy->get_port().get_name() + 
            "\nHP: " + Helpers::floatData::to_one_point_string(tileEnemy->get_hp()));
    }
}
void Tile::draw_object_info() const
{
    if (tileBox != nullptr)
    {
        if (tileBox->get_port().area() == true )
        {
            draw_info("box");
        }
    }
    if (tileEnemy != nullptr)
    {
        if (tileEnemy->get_port().area() == true )
        {
            draw_info("enemy");
        }
    }
}


void Tile::initialBox()
{
    isBoxOn = false;
    isGoldenBoxOn = false;
    delete tileBox;
    tileBox = nullptr;
}
void Tile::initialEnemy()
{
    isMonsterOn = false;
    delete tileEnemy;
    tileEnemy = nullptr;
}