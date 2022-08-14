/*
File name: dice.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "EffectStar.h"
#include "top_header.h"
#include "RGB.h"

struct Vector3D
{
    double x{};
    double y{};
    double z{};
};
inline Vector3D operator+(Vector3D& v1, Vector3D& v2)
{
    return {v1.x + v2.x,v1.y+v2.y,v1.z+v2.z};
}

inline Vector3D operator*(const double rM[3][3], Vector3D vec) {
    Vector3D re{};
    re.x = rM[0][0] * vec.x + rM[0][1] * vec.y + rM[0][2] * vec.z;
    re.y = rM[1][0] * vec.x + rM[1][1] * vec.y + rM[1][2] * vec.z;
    re.z = rM[2][0] * vec.x + rM[2][1] * vec.y + rM[2][2] * vec.z;

    return re;
}



class Square3D
{
    Vector3D centerPos{};
    double length{};
    RGB                 outLineColor{155, 155, 0};
    RGB                 diceColor{255, 255, 0};
    vector<Vector3D> point{};
    vector<vector<int>> side{

        {0, 2, 4, 6},
        {0, 2, 3, 1},
        {0, 6, 7, 1},
        {5, 4, 6, 7},
        {5, 3, 1, 7},
        {5, 4, 2, 3},

    };

    [[nodiscard]] int find_closed_point() const
    {
        int re{0};
        for (int i = 1;i<point.size();++i)
        {
            if (point[re].z < point[i].z)
            {
                re = i;
            }
            
        }
        return re;
    }

    [[nodiscard]] vector<int> find_side(int p) const
    {
        vector<int> sides{};
        for (int i = 0;i<side.size();++i)
        {
            for (const auto& poi:side[i])
            {
                if (poi == p)
                {
                    sides.push_back(i);
                    break;
                }
            }
            if (sides.size()== 3)
            {
                break;
            }
        }
        return sides;
        
    }

public:
    Square3D() = default;
    Square3D(double posx, double posy, double posz, double leng) : centerPos{posx,posy,posz},length(leng)
    {
        const double dist{length/2};

        point.push_back(Vector3D{dist, dist, dist});
        point.push_back(Vector3D{dist, dist, -dist});
        point.push_back(Vector3D{-dist, dist, dist});
        point.push_back(Vector3D{-dist, dist, -dist});
        point.push_back(Vector3D{-dist, -dist, dist});
        point.push_back(Vector3D{-dist, -dist, -dist});
        point.push_back(Vector3D{dist, -dist, dist});
        point.push_back(Vector3D{dist, -dist, -dist});

    }
    virtual  ~Square3D() = default;
    void rolling(double angle)
    {
        const double cosT{cos(angle)};
        const double sinT{sin(angle)};
        const double rotaX[3][3]{{1, 0, 0}, {0, cosT, -sinT}, {0, sinT, cosT}};
        const double rotaY[3][3]{{cosT, 0, sinT}, {0, 1, 0}, {-sinT, 0, cosT}};
        const double rotaZ[3][3]{{cosT, -sinT, 0}, {sinT, cosT, 0}, {0, 0, 1}};

        for (auto& p:point)
        {
            p = rotaX * p;
            p = rotaY * p;
            p = rotaZ * p;
        }
    }
    
    void draw()
    {
        vector<int> sides{find_side(find_closed_point())};
        push_settings();
        apply_translate(centerPos.x,centerPos.y);
        set_fill_color(diceColor.R,diceColor.G,diceColor.B);
        set_outline_color(outLineColor.R, outLineColor.G, outLineColor.B);
        set_outline_width(5);
        for (auto& s:sides)
        {
            draw_quad(point[side[s][0]].x, point[side[s][0]].y, point[side[s][1]].x, point[side[s][1]].y,
                      point[side[s][2]].x, point[side[s][2]].y, point[side[s][3]].x, point[side[s][3]].y);
        }
        outLineColor = {155, 155, 0};
        pop_settings();
    }
    void                   highLighting() { outLineColor = {255, 255, 120}; }
    [[nodiscard]] Vector3D get_Vector()const { return centerPos; }
    [[nodiscard]] double   get_size() const { return length; }
};

class Dice
{
    Square3D square{};
    /*Vec2   position{0, 0};*/
    //double size           = 100;
    int    number{0};
    int    maxNumber{6};
    bool   isRolled{false};
    bool   dicePressed{false};
    bool   animationEnd{false};
    int    count{35};
    bool   is_released() const;
    highLightingEffect::RectHighLight rectHighLight{};


public:
    Dice(double x, double y, double sz);
    Vec2 get_pos() const;
    void roll();
    bool dice_area() const;
    void update();
    void highLighting() { square.highLighting(); }
    void draw();
    void set_max_num(int num);
    int  get_num() const { return number; }
    bool get_is_rolled() const { return isRolled; }
    void do_roll();
    bool get_animation_end() const;
    void reset()
    {
        isRolled = false;
        animationEnd = false;
        number       = 0;
        count={70};
    }
    void click_me()
    {
        rectHighLight.operator()({square.get_Vector().x, square.get_Vector().y}, square.get_size()/2+10, square.get_size()/2+10);
    }
};
