/*
File name: UI.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Jihyeon Song, Taeju Kwon, Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "UI.h"
#include "game_header.h"
#include "Ingame_image.h"
using namespace doodle;

UI::UI(double x_, double y_, double w_, double h_) : x{x_}, y{y_}, w{w_}, h{h_}, fontSize{sqrt(w_ * h_) / 4} {};
Profile::Profile(string n, double x_, double y_, double w_, double h_, long double now, long double m, Color myc)
    : name{n}, UI(x_, y_, w_, h_), now{now}, max(m), barcolor(myc) {};
Gold::Gold(double x_, double y_, double w_, double h_) : UI(x_, y_, w_, h_){};


 void Profile::draw()
{
 	 push_settings();
     const auto barW      = w * (static_cast<double>(now / max) > 1 ? 1 : static_cast<double>(now / max));
     const auto nowNumber = Helpers::floatData::to_one_point_string(now);
     const auto maxNumber = Helpers::floatData::to_one_point_string(max);
     //겉 사각형
     set_outline_width(outlineWidth);
     apply_translate(x + w * 0.8 * (scaleVal - 1), y);
     apply_scale(scaleVal);
     draw_rectangle(0,0, w, h);
     pop_settings();
     //속 사각형
     push_settings();
     set_rectangle_mode(RectMode::Corner);
     apply_translate(x + w *0.8 * (scaleVal - 1) - w * scaleVal /2, y-(h - outlineWidth/scaleVal) * scaleVal/2);
     apply_scale(scaleVal);
     no_outline();
     set_fill_color(barcolor);
     draw_rectangle(0,0, barW, h - outlineWidth/scaleVal);
     set_rectangle_mode(RectMode::Center);
     pop_settings();
     //
     push_settings();
     apply_translate((x - ((nowNumber.size() + 2) * fontSize * 2 / 3) / 2) + (scaleVal-1) * w/2, y - h / 4);
     set_fill_color(0);
     set_font_size(fontSize * scaleVal / 1.2);
     no_outline();
     draw_text(nowNumber + " / " +  maxNumber, 0,0);
     pop_settings();
     //레벨 원 크기
     push_settings();
     const auto circleR = h * 3 / 2;
     const auto circleX = x - w * 3 / 4;
     const auto circleY = y;
     apply_translate(circleX, circleY);
     apply_scale(scaleVal);
     
     set_fill_color(255);
     draw_ellipse(0,0, circleR);
     pop_settings();

     push_settings();
     set_fill_color(0);
     no_outline();
     //set_font_size(fontSize * 2 * scaleVal / name.size());
     set_font_size(fontSize);
     apply_translate(circleX - name.size() * fontSize * scaleVal / 5.5, circleY - h / 3);
     
     draw_text(name, 0,0);
     pop_settings();
     scaleVal = 1;
}

void Profile::drawing(string s, int a)
{
    const auto circleR = h * 3 / 2;
    const auto circleX = x - w * 3 / 4;
    const auto circleY = y;
    draw_image(profileImage[s + "Profile"], circleX, circleY, circleR * a, circleR * a);
}

void Profile::high_lighting() 
{
    scaleVal = 2;
    push_settings();

    const auto circleR = h * 7 / 4;
    const auto circleX = x - w * 3 / 4;
    const auto circleY = y;

    apply_translate(circleX, circleY);
    apply_scale(scaleVal);
    set_fill_color(255, 255, 0);
    draw_ellipse(0,0, circleR);

    pop_settings();
}
bool Profile::area()const
{
    const auto circleX = x - w * 3 / 4;
    const auto circleY = y;
    return Helpers::Distance::objToMouse({circleX, circleY}) <= h * 3 / 4 *scaleVal;
}

void Profile::set_now(long double input) { now = input; }

void Profile::set_max(long double input) { max = input; }

void Profile::set_name(string  input) { name = input; }


void Gold::set_money(unsigned long long m)
{ money = m; }

void Gold::draw()
{
	push_settings();

    const auto coinX = x;
    const auto coinY = y;
    const auto coinW = w;
    const auto coinH = h;

    Image gold{"assets/UI/gold.png"};
    draw_image(gold, coinX, coinY, coinW, coinH);

    int a = 0;
    if(now_chapter > 3)
    {
        a = 200;
    }
    set_fill_color(a);
    set_font_size(HEADFONTSIZE);
    draw_text(":  " + to_string(money), coinX + 2 * coinW/3, coinY- coinH/5);
    pop_settings();
}