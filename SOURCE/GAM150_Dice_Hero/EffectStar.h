/*
File name: EffectStar.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "Effect_base.h"
#include "top_header.h"

class EffectStar:public Effect
{
    Vec2 position{};
    double animationSpeed{10};
    double size{10};
    double animation{255};
    int    x{0};
    unsigned int color{0xffffffff};
    double          angle{};

public:
    EffectStar(Vec2 pos,unsigned int col = 0xffffffff,double stSize = 10,double speed = 10):
    position(pos), animationSpeed(speed),size(stSize),color(col){}
    void draw() override
    {
        push_settings();
        set_rectangle_mode(RectMode::Center);
        apply_translate(position.x,position.y);
        apply_rotate(angle);
        set_fill_color(HexColor{color});
        no_outline();
        draw_rectangle(0,0,size/10+noise(x)*size);
        ++x;
        pop_settings();
    }
    void update() override
    {
        animation -= animationSpeed;
        angle += PI / noise(x) / animationSpeed;
        if (animation<0)
        {
            animationEnd = true;
        }
    }
};


namespace highLightingEffect
{
    class RectHighLight
    {
        double angle{};
        double angleSpeed{TWO_PI / 30};
        double    tx{};
        double ty{};
        int    x{};
        double y{};
    public:
        void operator()(Vec2 pos,double wid,double hei,bool twice = false , unsigned int col = 0xffffff80)
        {
            if ((angle<=PI/4 || angle>=PI*7/4) || (angle >=PI*3/4 && angle<=PI*5/4))
            {
                tx = (wid + noise(x, y) * wid / 10) * cos(angle) / abs(cos(angle));
                ty = sin(angle) * (hei + noise(x, y) * hei / 10);
            }
            else
            {
                tx = cos(angle) * (wid + noise(x, y) * wid / 10);
                ty = (hei + noise(x, y) * hei / 10) * sin(angle) / abs(sin(angle));
            }
            events.push_event(EffectStar{{pos.x + tx, pos.y + ty}, col});
            ++x;
            y += 0.2;
            angle += angleSpeed;
            if(twice == true) // fix it later
            {
                if ((angle <= PI / 4 || angle >= PI * 7 / 4) || (angle >= PI * 3 / 4 && angle <= PI * 5 / 4))
                {
                    tx = (wid + noise(x, y) * wid / 10) * cos(angle) / abs(cos(angle));
                    ty = sin(angle) * (hei + noise(x, y) * hei / 10);
                }
                else
                {
                    tx = cos(angle) * (wid + noise(x, y) * wid / 10);
                    ty = (hei + noise(x, y) * hei / 10) * sin(angle) / abs(sin(angle));
                }
                events.push_event(EffectStar{ {pos.x + tx, pos.y + ty}, col });
                ++x;
                y += 0.2;
                angle += angleSpeed;
            }
            if (angle>TWO_PI)
            {
                angle -= TWO_PI;
            }
        }
    };
    class CircleHighLight
    {
        double angle{};
        double angleSpeed{TWO_PI/30};
        int    x{};
        double    y{};
    public:
        void operator()(Vec2 pos,  double leng, unsigned int col = 0xffffff80)
        {
            events.push_event(EffectStar{{pos.x + cos(angle) * (leng + noise(x,y) * leng / 10),
                                          pos.y + sin(angle) * (leng + noise(x,y) * leng / 10)},
                                         col});
            ++x;
            y+=0.2;
            angle += angleSpeed;
        }
    };
    class CircleHighLightJustCircle
    {
        double    x{};
        double    y{};
    public:
        void operator()(Vec2 pos, double leng)
        {
            push_settings();
            set_outline_color(noise(x, y) * 255,220);
            set_outline_width(5);
            set_fill_color(0, 0);
            draw_ellipse(pos.x,pos.y,leng*2);
            pop_settings();
            x+=0.002;
            y += 0.002;
        }
    };
}
