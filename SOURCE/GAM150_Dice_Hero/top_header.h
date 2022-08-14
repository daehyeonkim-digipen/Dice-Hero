/*
File name: top_header.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Junsu Jang, Jihyeon Song
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include <iostream>
#include "fstream"
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <doodle/doodle.hpp>
#include <typeinfo>
#include "TextEvent.h"
#include <SFML/Audio.hpp>


#define PlayerMagicMax 6

inline bool chamberTutorial{true};//tutorial
inline bool forgeTutorial{false};//tutorial
inline bool equipmentTutorial{false};//tutorial

using namespace std;
using namespace doodle;

enum class SceneNumber
{
    splash,
    play_scene,
    game_scene_main,
    game_scene_quest,
    game_scene_forge,
    game_scene_chamber,
    game_scene_inventory,
    game_scene_ingame,
    setting_scene,
    credit_scene,
    ending_scene,
    game_complete_scene,
    game_fail_scene,
    game_stat_scene,
    
};

inline SceneNumber currentNumber = SceneNumber::splash;
inline bool        isNumberChanged = true;
inline bool        isGodModeOn     = false;

struct Vec2
{
    double x{0}, y{0};
};

constexpr int        WINDOW_WIDTH     = 1920;
constexpr int        WINDOW_HEIGHT    = 1020;
constexpr Vec2       BOARD_CENTER{0,0};

namespace Helpers
{
    [[noreturn]] inline void error(const std::string& s) { throw std::runtime_error(s); }


    namespace Distance
    {
        inline double objToObj(const Vec2 obj1, const Vec2 obj2)
        {
            const auto x = obj1.x - obj2.x;
            const auto y = obj1.y - obj2.y;
            return sqrt(x * x + y * y);
        }
        inline double objToMouse(const Vec2 obj)
        {
            const auto x = obj.x - get_mouse_x();
            const auto y = obj.y - get_mouse_y();
            return sqrt(x * x + y * y);
        }
	}
	namespace Collision
    {
        inline bool objToObj(const Vec2 obj1, const double obj1Width, const double obj1Height, const Vec2 obj2,
                             const double obj2Width, const double obj2Height)
        {
            const auto width1  = obj1Width / 2;
            const auto height1 = obj1Height / 2;
            const auto width2  = obj2Width / 2;
            const auto height2 = obj2Height / 2;
            if (obj1.x + width1 <= obj2.x - width2 && obj1.y + height1 <= obj2.y - height2 &&
                obj1.x - width1 >= obj2.x + width2 && obj1.y - height1 >= obj2.y + height2)
            {
                return false;
            }
            return true;
        }
        inline bool objToMouse(const Vec2 obj, const double objWidth, const double objHeight)
        { 
            const auto width  = objWidth / 2;
            const auto height = objHeight / 2;
            if (get_mouse_x() <= obj.x + width && get_mouse_x() >= obj.x - width && get_mouse_y() <= obj.y + height &&
                get_mouse_y() >= obj.y - height)
            {
                return true;
            }
            return false;
        }
    }

    namespace Keyboard
    {
        inline bool Rl_key(doodle::KeyboardButtons b)// Temporary
        {
            if (doodle::Key == b && doodle::KeyIsPressed == false)
            {
                doodle::Key = doodle::KeyboardButtons::None;
                return true;
            }
            return false;
        }
    }

    namespace MouseButton
    {
        inline bool Rl_Button(doodle::MouseButtons b) // Temporary
        {
            if (doodle::MouseButton == b && doodle::MouseIsPressed == false)
            {
                doodle::MouseButton = doodle::MouseButtons::None;
                return true;
            }
            doodle::MouseButton = doodle::MouseButtons::None;
            return false;
        }
    }

    namespace Position
    {
        inline void computeAnotherMaxInCircle(double &rad,double &x)
        {
            rad *= 2;
            rad *= rad;
            rad -= x * x;
            rad = sqrt(rad);
        }
        template <int plane = 0>
        inline Vec2 randomCirclePos(Vec2 center,double rad )
        { 
            double x{random(-rad,rad)};
            computeAnotherMaxInCircle(rad, x);
            
            double y{random(-rad, rad)};
            return Vec2{center.x + x, center.y + y};
        }
        template <>
        inline Vec2 randomCirclePos<1>(Vec2 center, double rad)
        {
            double x{random(0., rad)};

            computeAnotherMaxInCircle(rad, x);

            double y{random(0., rad)};
            return Vec2{center.x + x, center.y + y};
        }
        template <>
        inline Vec2 randomCirclePos<2>(Vec2 center, double rad)
        {
            double x{random(-rad, 0.)};

            computeAnotherMaxInCircle(rad, x);

            double y{random(0., rad)};
            return Vec2{center.x+x, center.y+y};
        }
        template <>
        inline Vec2 randomCirclePos<3>(Vec2 center, double rad)
        {
            double x{random(-rad, 0.)};

            computeAnotherMaxInCircle(rad, x);

            double y{random(-rad, 0.)};
            return Vec2{center.x + x, center.y + y};
        }
        template <>
        inline Vec2 randomCirclePos<4>(Vec2 center, double rad)
        {
            double x{random(0., rad)};

            computeAnotherMaxInCircle(rad, x);

            double y{random(-rad, 0.)};
            return Vec2{center.x + x, center.y + y};
        }
        template<typename obj, typename C>
        void sibal(obj enemy, C Ch) {enemy->give_damage(Ch->get_effect().howMuch *
            Ch->get_dice_factor() *
            Ch->get_ad()); }
    }

    namespace Drawing
    {
        inline void fill_color(unsigned int col) { set_fill_color(HexColor{col}); }
        inline void draw_bar(double percent = 0, Vec2 pos = {}, double wid = 200, double hei = 50,
                             unsigned int col = 0x000000ff)
        {
            push_settings();
            set_rectangle_mode(RectMode::Corner);
            fill_color(0xffffffff);
            draw_rectangle(pos.x,pos.y,wid,hei);
            no_outline();
            fill_color(col);
            draw_rectangle(pos.x,pos.y,wid*percent,hei);
            pop_settings();
        }
        inline void draw_remain(string remain, Vec2 pos = {}, double wid = 200, double hei = 50,
                             unsigned int col = 0x000000ff)
        {
            push_settings();
            set_rectangle_mode(RectMode::Corner);
            fill_color(0xffffffff);
            draw_rectangle(pos.x, pos.y, wid, hei);
            fill_color(col);
            set_font_size(hei/2);
            draw_text(remain,pos.x, pos.y);
            pop_settings();
        }
    }

    namespace floatData
    {
        inline string to_one_point_string(long double val)
        {
            return to_string((long long)val)+"."+ to_string((long long)(val * 10) % 10);
        }
    }

    namespace math
    {
        template<typename T>
        inline T p5js_map(T value, T low1, T high1, T low2, T high2)
        {
            return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
        }
    }
}

#pragma once
inline map<string, Image> buttonImage{};
inline map<string, Image> backgroundObjImage{};

namespace ButtonImage
{
    inline void imageSet()
    {
        buttonImage["outline0"] = Image{"assets/UI/button/outline1.png"};
        buttonImage["outline1"] = Image{"assets/UI/button/outline1.png"};
        buttonImage["outline2"] = Image{"assets/UI/button/outline2.png"};
        buttonImage["outline3"] = Image{"assets/UI/button/outline3.png"};
        buttonImage["outline4"] = Image{"assets/UI/button/outline4.png"};
        buttonImage["outline5"] = Image{"assets/UI/button/outline5.png"};
        buttonImage["outline6"] = Image{"assets/UI/button/outline6.png"};

        buttonImage["Cheat1.1"]          = Image{"assets/UI/button/Cheat1.1.png"};
        buttonImage["Cheat1.2"]          = Image{"assets/UI/button/Cheat1.2.png"};
        buttonImage["Cheat2.1"]          = Image{"assets/UI/button/Cheat2.1.png"};
        buttonImage["Cheat2.2"]          = Image{"assets/UI/button/Cheat2.2.png"};
        buttonImage["Cheat3.1"]          = Image{"assets/UI/button/Cheat3.1.png"};
        buttonImage["Cheat3.2"]          = Image{"assets/UI/button/Cheat3.2.png"};
        buttonImage["Cheat4.1"]          = Image{"assets/UI/button/Cheat4.1.png"};
        buttonImage["Cheat4.2"]          = Image{"assets/UI/button/Cheat4.2.png"};
        buttonImage["Cheat5.1"]          = Image{"assets/UI/button/Cheat5.1.png"};
        buttonImage["Cheat5.2"]          = Image{"assets/UI/button/Cheat5.2.png"};
        buttonImage["Cheat6.1"]          = Image{"assets/UI/button/Cheat6.1.png"};
        buttonImage["Cheat6.2"]          = Image{"assets/UI/button/Cheat6.2.png"};

        buttonImage["Credit0.1"] = Image{"assets/UI/button/Credit0.1.png"};
        buttonImage["Credit0.2"] = Image{"assets/UI/button/Credit0.2.png"};
        buttonImage["Credit1.1"] = Image{"assets/UI/button/Credit1.1.png"};
        buttonImage["Credit1.2"] = Image{"assets/UI/button/Credit1.2.png"};
        buttonImage["Credit2.1"] = Image{"assets/UI/button/Credit2.1.png"};
        buttonImage["Credit2.2"] = Image{"assets/UI/button/Credit2.2.png"};
        buttonImage["Credit3.1"] = Image{"assets/UI/button/Credit3.1.png"};
        buttonImage["Credit3.2"] = Image{"assets/UI/button/Credit3.2.png"};
        buttonImage["Credit4.1"] = Image{"assets/UI/button/Credit4.1.png"};
        buttonImage["Credit4.2"] = Image{"assets/UI/button/Credit4.2.png"};
        buttonImage["Credit5.1"] = Image{"assets/UI/button/Credit5.1.png"};
        buttonImage["Credit5.2"] = Image{"assets/UI/button/Credit5.2.png"};
        buttonImage["Credit6.1"] = Image{"assets/UI/button/Credit6.1.png"};
        buttonImage["Credit6.2"] = Image{"assets/UI/button/Credit6.2.png"};

        buttonImage["OK1.1"]                    = Image{"assets/UI/button/OK1.1.png"};
        buttonImage["OK1.2"]                    = Image{"assets/UI/button/OK1.2.png"};
        buttonImage["OK2.1"]                    = Image{"assets/UI/button/OK2.1.png"};
        buttonImage["OK2.2"]                    = Image{"assets/UI/button/OK2.2.png"};
        buttonImage["OK3.1"]                    = Image{"assets/UI/button/OK3.1.png"};
        buttonImage["OK3.2"]                    = Image{"assets/UI/button/OK3.2.png"};
        buttonImage["OK4.1"]                    = Image{"assets/UI/button/OK4.1.png"};
        buttonImage["OK4.2"]                    = Image{"assets/UI/button/OK4.2.png"};
        buttonImage["OK5.1"]                    = Image{"assets/UI/button/OK5.1.png"};
        buttonImage["OK5.2"]                    = Image{"assets/UI/button/OK5.2.png"};
        buttonImage["OK6.1"]                    = Image{"assets/UI/button/OK6.1.png"};
        buttonImage["OK6.2"]                    = Image{"assets/UI/button/OK6.2.png"};

        buttonImage["Inventory1.1"] = Image{"assets/UI/button/Inventory1.1.png"};
        buttonImage["Inventory1.2"] = Image{"assets/UI/button/Inventory1.2.png"};
        buttonImage["Inventory2.1"] = Image{"assets/UI/button/Inventory2.1.png"};
        buttonImage["Inventory2.2"] = Image{"assets/UI/button/Inventory2.2.png"};
        buttonImage["Inventory3.1"] = Image{"assets/UI/button/Inventory3.1.png"};
        buttonImage["Inventory3.2"] = Image{"assets/UI/button/Inventory3.2.png"};
        buttonImage["Inventory4.1"] = Image{"assets/UI/button/Inventory4.1.png"};
        buttonImage["Inventory4.2"] = Image{"assets/UI/button/Inventory4.2.png"};
        buttonImage["Inventory5.1"] = Image{"assets/UI/button/Inventory5.1.png"};
        buttonImage["Inventory5.2"] = Image{"assets/UI/button/Inventory5.2.png"};
        buttonImage["Inventory6.1"] = Image{"assets/UI/button/Inventory6.1.png"};
        buttonImage["Inventory6.2"] = Image{"assets/UI/button/Inventory6.2.png"};  

        buttonImage["Setting0.1"] = Image{"assets/UI/button/Setting0.1.png"};
        buttonImage["Setting0.2"] = Image{"assets/UI/button/Setting0.2.png"};
        buttonImage["Setting1.1"] = Image{"assets/UI/button/Setting1.1.png"};
        buttonImage["Setting1.2"] = Image{"assets/UI/button/Setting1.2.png"};
        buttonImage["Setting2.1"] = Image{"assets/UI/button/Setting2.1.png"};
        buttonImage["Setting2.2"] = Image{"assets/UI/button/Setting2.2.png"};
        buttonImage["Setting3.1"] = Image{"assets/UI/button/Setting3.1.png"};
        buttonImage["Setting3.2"] = Image{"assets/UI/button/Setting3.2.png"};
        buttonImage["Setting4.1"] = Image{"assets/UI/button/Setting4.1.png"};
        buttonImage["Setting4.2"] = Image{"assets/UI/button/Setting4.2.png"};
        buttonImage["Setting5.1"] = Image{"assets/UI/button/Setting5.1.png"};
        buttonImage["Setting5.2"] = Image{"assets/UI/button/Setting5.2.png"};
        buttonImage["Setting6.1"] = Image{"assets/UI/button/Setting6.1.png"};
        buttonImage["Setting6.2"] = Image{"assets/UI/button/Setting6.2.png"};

        buttonImage["Extract1.1"] = Image{"assets/UI/button/Extract1.1.png"};
        buttonImage["Extract1.2"] = Image{"assets/UI/button/Extract1.2.png"};
        buttonImage["Extract2.1"] = Image{"assets/UI/button/Extract2.1.png"};
        buttonImage["Extract2.2"] = Image{"assets/UI/button/Extract2.2.png"};
        buttonImage["Extract3.1"] = Image{"assets/UI/button/Extract3.1.png"};
        buttonImage["Extract3.2"] = Image{"assets/UI/button/Extract3.2.png"};
        buttonImage["Extract4.1"] = Image{"assets/UI/button/Extract4.1.png"};
        buttonImage["Extract4.2"] = Image{"assets/UI/button/Extract4.2.png"};
        buttonImage["Extract5.1"] = Image{"assets/UI/button/Extract5.1.png"};
        buttonImage["Extract5.2"] = Image{"assets/UI/button/Extract5.2.png"};
        buttonImage["Extract6.1"] = Image{"assets/UI/button/Extract6.1.png"};
        buttonImage["Extract6.2"] = Image{"assets/UI/button/Extract6.2.png"};

        buttonImage["Reset1.1"] = Image{"assets/UI/button/Reset1.1.png"};
        buttonImage["Reset1.2"] = Image{"assets/UI/button/Reset1.2.png"};
        buttonImage["Reset2.1"] = Image{"assets/UI/button/Reset2.1.png"};
        buttonImage["Reset2.2"] = Image{"assets/UI/button/Reset2.2.png"};
        buttonImage["Reset3.1"] = Image{"assets/UI/button/Reset3.1.png"};
        buttonImage["Reset3.2"] = Image{"assets/UI/button/Reset3.2.png"};
        buttonImage["Reset4.1"] = Image{"assets/UI/button/Reset4.1.png"};
        buttonImage["Reset4.2"] = Image{"assets/UI/button/Reset4.2.png"};
        buttonImage["Reset5.1"] = Image{"assets/UI/button/Reset5.1.png"};
        buttonImage["Reset5.2"] = Image{"assets/UI/button/Reset5.2.png"};
        buttonImage["Reset6.1"] = Image{"assets/UI/button/Reset6.1.png"};
        buttonImage["Reset6.2"] = Image{"assets/UI/button/Reset6.2.png"};

        buttonImage["Chamber1.1"] = Image{"assets/UI/button/Chamber1.1.png"};
        buttonImage["Chamber1.2"] = Image{"assets/UI/button/Chamber1.2.png"};
        buttonImage["Chamber2.1"] = Image{"assets/UI/button/Chamber2.1.png"};
        buttonImage["Chamber2.2"] = Image{"assets/UI/button/Chamber2.2.png"};
        buttonImage["Chamber3.1"] = Image{"assets/UI/button/Chamber3.1.png"};
        buttonImage["Chamber3.2"] = Image{"assets/UI/button/Chamber3.2.png"};
        buttonImage["Chamber4.1"] = Image{"assets/UI/button/Chamber4.1.png"};
        buttonImage["Chamber4.2"] = Image{"assets/UI/button/Chamber4.2.png"};
        buttonImage["Chamber5.1"] = Image{"assets/UI/button/Chamber5.1.png"};
        buttonImage["Chamber5.2"] = Image{"assets/UI/button/Chamber5.2.png"};
        buttonImage["Chamber6.1"] = Image{"assets/UI/button/Chamber6.1.png"};
        buttonImage["Chamber6.2"] = Image{"assets/UI/button/Chamber6.2.png"};

        buttonImage["Stat1.1"] = Image{"assets/UI/button/Stat1.1.png"};
        buttonImage["Stat1.2"] = Image{"assets/UI/button/Stat1.2.png"};
        buttonImage["Stat2.1"] = Image{"assets/UI/button/Stat2.1.png"};
        buttonImage["Stat2.2"] = Image{"assets/UI/button/Stat2.2.png"};
        buttonImage["Stat3.1"] = Image{"assets/UI/button/Stat3.1.png"};
        buttonImage["Stat3.2"] = Image{"assets/UI/button/Stat3.2.png"};
        buttonImage["Stat4.1"] = Image{"assets/UI/button/Stat4.1.png"};
        buttonImage["Stat4.2"] = Image{"assets/UI/button/Stat4.2.png"};
        buttonImage["Stat5.1"] = Image{"assets/UI/button/Stat5.1.png"};
        buttonImage["Stat5.2"] = Image{"assets/UI/button/Stat5.2.png"};
        buttonImage["Stat6.1"] = Image{"assets/UI/button/Stat6.1.png"};
        buttonImage["Stat6.2"] = Image{"assets/UI/button/Stat6.2.png"};

        buttonImage["Buy1.1"] = Image{"assets/UI/button/Buy1.1.png"};
        buttonImage["Buy1.2"] = Image{"assets/UI/button/Buy1.2.png"};
        buttonImage["Buy2.1"] = Image{"assets/UI/button/Buy2.1.png"};
        buttonImage["Buy2.2"] = Image{"assets/UI/button/Buy2.2.png"};
        buttonImage["Buy3.1"] = Image{"assets/UI/button/Buy3.1.png"};
        buttonImage["Buy3.2"] = Image{"assets/UI/button/Buy3.2.png"};
        buttonImage["Buy4.1"] = Image{"assets/UI/button/Buy4.1.png"};
        buttonImage["Buy4.2"] = Image{"assets/UI/button/Buy4.2.png"};
        buttonImage["Buy5.1"] = Image{"assets/UI/button/Buy5.1.png"};
        buttonImage["Buy5.2"] = Image{"assets/UI/button/Buy5.2.png"};
        buttonImage["Buy6.1"] = Image{"assets/UI/button/Buy6.1.png"};
        buttonImage["Buy6.2"] = Image{"assets/UI/button/Buy6.2.png"};

        buttonImage["Back0.1"] = Image{"assets/UI/button/Back0.1.png"};
        buttonImage["Back0.2"] = Image{"assets/UI/button/Back0.2.png"};
        buttonImage["Back1.1"] = Image{"assets/UI/button/Back1.1.png"};
        buttonImage["Back1.2"] = Image{"assets/UI/button/Back1.2.png"};
        buttonImage["Back2.1"] = Image{"assets/UI/button/Back2.1.png"};
        buttonImage["Back2.2"] = Image{"assets/UI/button/Back2.2.png"};
        buttonImage["Back3.1"] = Image{"assets/UI/button/Back3.1.png"};
        buttonImage["Back3.2"] = Image{"assets/UI/button/Back3.2.png"};
        buttonImage["Back4.1"] = Image{"assets/UI/button/Back4.1.png"};
        buttonImage["Back4.2"] = Image{"assets/UI/button/Back4.2.png"};
        buttonImage["Back5.1"] = Image{"assets/UI/button/Back5.1.png"};
        buttonImage["Back5.2"] = Image{"assets/UI/button/Back5.2.png"};
        buttonImage["Back6.1"] = Image{"assets/UI/button/Back6.1.png"};
        buttonImage["Back6.2"] = Image{"assets/UI/button/Back6.2.png"};

        buttonImage["Menu1.1"] = Image{"assets/UI/button/Menu1.1.png"};
        buttonImage["Menu1.2"] = Image{"assets/UI/button/Menu1.2.png"};
        buttonImage["Menu2.1"] = Image{"assets/UI/button/Menu2.1.png"};
        buttonImage["Menu2.2"] = Image{"assets/UI/button/Menu2.2.png"};
        buttonImage["Menu3.1"] = Image{"assets/UI/button/Menu3.1.png"};
        buttonImage["Menu3.2"] = Image{"assets/UI/button/Menu3.2.png"};
        buttonImage["Menu4.1"] = Image{"assets/UI/button/Menu4.1.png"};
        buttonImage["Menu4.2"] = Image{"assets/UI/button/Menu4.2.png"};
        buttonImage["Menu5.1"] = Image{"assets/UI/button/Menu5.1.png"};
        buttonImage["Menu5.2"] = Image{"assets/UI/button/Menu5.2.png"};
        buttonImage["Menu6.1"] = Image{"assets/UI/button/Menu6.1.png"};
        buttonImage["Menu6.2"] = Image{"assets/UI/button/Menu6.2.png"};


        buttonImage["Chapter1.1"] = Image{"assets/UI/button/Chapter1.1.png"};
        buttonImage["Chapter1.2"] = Image{"assets/UI/button/Chapter1.2.png"};
        buttonImage["Chapter2.1"] = Image{"assets/UI/button/Chapter2.1.png"};
        buttonImage["Chapter2.2"] = Image{"assets/UI/button/Chapter2.2.png"};
        buttonImage["Chapter3.1"] = Image{"assets/UI/button/Chapter3.1.png"};
        buttonImage["Chapter3.2"] = Image{"assets/UI/button/Chapter3.2.png"};
        buttonImage["Chapter4.1"] = Image{"assets/UI/button/Chapter4.1.png"};
        buttonImage["Chapter4.2"] = Image{"assets/UI/button/Chapter4.2.png"};
        buttonImage["Chapter5.1"] = Image{"assets/UI/button/Chapter5.1.png"};
        buttonImage["Chapter5.2"] = Image{"assets/UI/button/Chapter5.2.png"};
        buttonImage["Chapter6.1"] = Image{"assets/UI/button/Chapter6.1.png"};
        buttonImage["Chapter6.2"] = Image{"assets/UI/button/Chapter6.2.png"};

        buttonImage["Quest1.1"] = Image{"assets/UI/button/Quest1.1.png"};
        buttonImage["Quest1.2"] = Image{"assets/UI/button/Quest1.2.png"};
        buttonImage["Quest2.1"] = Image{"assets/UI/button/Quest2.1.png"};
        buttonImage["Quest2.2"] = Image{"assets/UI/button/Quest2.2.png"};
        buttonImage["Quest3.1"] = Image{"assets/UI/button/Quest3.1.png"};
        buttonImage["Quest3.2"] = Image{"assets/UI/button/Quest3.2.png"};
        buttonImage["Quest4.1"] = Image{"assets/UI/button/Quest4.1.png"};
        buttonImage["Quest4.2"] = Image{"assets/UI/button/Quest4.2.png"};
        buttonImage["Quest5.1"] = Image{"assets/UI/button/Quest5.1.png"};
        buttonImage["Quest5.2"] = Image{"assets/UI/button/Quest5.2.png"};
        buttonImage["Quest6.1"] = Image{"assets/UI/button/Quest6.1.png"};
        buttonImage["Quest6.2"] = Image{"assets/UI/button/Quest6.2.png"};

        buttonImage["Apply1.1"] = Image{"assets/UI/button/Apply1.1.png"};
        buttonImage["Apply1.2"] = Image{"assets/UI/button/Apply1.2.png"};
        buttonImage["Apply2.1"] = Image{"assets/UI/button/Apply2.1.png"};
        buttonImage["Apply2.2"] = Image{"assets/UI/button/Apply2.2.png"};
        buttonImage["Apply3.1"] = Image{"assets/UI/button/Apply3.1.png"};
        buttonImage["Apply3.2"] = Image{"assets/UI/button/Apply3.2.png"};
        buttonImage["Apply4.1"] = Image{"assets/UI/button/Apply4.1.png"};
        buttonImage["Apply4.2"] = Image{"assets/UI/button/Apply4.2.png"};
        buttonImage["Apply5.1"] = Image{"assets/UI/button/Apply5.1.png"};
        buttonImage["Apply5.2"] = Image{"assets/UI/button/Apply5.2.png"};
        buttonImage["Apply6.1"] = Image{"assets/UI/button/Apply6.1.png"};
        buttonImage["Apply6.2"] = Image{"assets/UI/button/Apply6.2.png"};

        buttonImage["Material1.1"] = Image{"assets/UI/button/Material1.1.png"};
        buttonImage["Material1.2"] = Image{"assets/UI/button/Material1.2.png"};
        buttonImage["Material2.1"] = Image{"assets/UI/button/Material2.1.png"};
        buttonImage["Material2.2"] = Image{"assets/UI/button/Material2.2.png"};
        buttonImage["Material3.1"] = Image{"assets/UI/button/Material3.1.png"};
        buttonImage["Material3.2"] = Image{"assets/UI/button/Material3.2.png"};
        buttonImage["Material4.1"] = Image{"assets/UI/button/Material4.1.png"};
        buttonImage["Material4.2"] = Image{"assets/UI/button/Material4.2.png"};
        buttonImage["Material5.1"] = Image{"assets/UI/button/Material5.1.png"};
        buttonImage["Material5.2"] = Image{"assets/UI/button/Material5.2.png"};
        buttonImage["Material6.1"] = Image{"assets/UI/button/Material6.1.png"};
        buttonImage["Material6.2"] = Image{"assets/UI/button/Material6.2.png"};

        buttonImage["Essence1.1"] = Image{"assets/UI/button/Essence1.1.png"};
        buttonImage["Essence1.2"] = Image{"assets/UI/button/Essence1.2.png"};
        buttonImage["Essence2.1"] = Image{"assets/UI/button/Essence2.1.png"};
        buttonImage["Essence2.2"] = Image{"assets/UI/button/Essence2.2.png"};
        buttonImage["Essence3.1"] = Image{"assets/UI/button/Essence3.1.png"};
        buttonImage["Essence3.2"] = Image{"assets/UI/button/Essence3.2.png"};
        buttonImage["Essence4.1"] = Image{"assets/UI/button/Essence4.1.png"};
        buttonImage["Essence4.2"] = Image{"assets/UI/button/Essence4.2.png"};
        buttonImage["Essence5.1"] = Image{"assets/UI/button/Essence5.1.png"};
        buttonImage["Essence5.2"] = Image{"assets/UI/button/Essence5.2.png"};
        buttonImage["Essence6.1"] = Image{"assets/UI/button/Essence6.1.png"};
        buttonImage["Essence6.2"] = Image{"assets/UI/button/Essence6.2.png"};

        buttonImage["Thief1.1"] = Image{"assets/UI/button/Thief1.1.png"};
        buttonImage["Thief1.2"] = Image{"assets/UI/button/Thief1.2.png"};
        buttonImage["Thief2.1"] = Image{"assets/UI/button/Thief2.1.png"};
        buttonImage["Thief2.2"] = Image{"assets/UI/button/Thief2.2.png"};
        buttonImage["Thief3.1"] = Image{"assets/UI/button/Thief3.1.png"};
        buttonImage["Thief3.2"] = Image{"assets/UI/button/Thief3.2.png"};
        buttonImage["Thief4.1"] = Image{"assets/UI/button/Thief4.1.png"};
        buttonImage["Thief4.2"] = Image{"assets/UI/button/Thief4.2.png"};
        buttonImage["Thief5.1"] = Image{"assets/UI/button/Thief5.1.png"};
        buttonImage["Thief5.2"] = Image{"assets/UI/button/Thief5.2.png"};
        buttonImage["Thief6.1"] = Image{"assets/UI/button/Thief6.1.png"};
        buttonImage["Thief6.2"] = Image{"assets/UI/button/Thief6.2.png"};

        buttonImage["Mage1.1"] = Image{"assets/UI/button/Mage1.1.png"};
        buttonImage["Mage1.2"] = Image{"assets/UI/button/Mage1.2.png"};
        buttonImage["Mage2.1"] = Image{"assets/UI/button/Mage2.1.png"};
        buttonImage["Mage2.2"] = Image{"assets/UI/button/Mage2.2.png"};
        buttonImage["Mage3.1"] = Image{"assets/UI/button/Mage3.1.png"};
        buttonImage["Mage3.2"] = Image{"assets/UI/button/Mage3.2.png"};
        buttonImage["Mage4.1"] = Image{"assets/UI/button/Mage4.1.png"};
        buttonImage["Mage4.2"] = Image{"assets/UI/button/Mage4.2.png"};
        buttonImage["Mage5.1"] = Image{"assets/UI/button/Mage5.1.png"};
        buttonImage["Mage5.2"] = Image{"assets/UI/button/Mage5.2.png"};
        buttonImage["Mage6.1"] = Image{"assets/UI/button/Mage6.1.png"};
        buttonImage["Mage6.2"] = Image{"assets/UI/button/Mage6.2.png"};

        buttonImage["Archer1.1"] = Image{"assets/UI/button/Archer1.1.png"};
        buttonImage["Archer1.2"] = Image{"assets/UI/button/Archer1.2.png"};
        buttonImage["Archer2.1"] = Image{"assets/UI/button/Archer2.1.png"};
        buttonImage["Archer2.2"] = Image{"assets/UI/button/Archer2.2.png"};
        buttonImage["Archer3.1"] = Image{"assets/UI/button/Archer3.1.png"};
        buttonImage["Archer3.2"] = Image{"assets/UI/button/Archer3.2.png"};
        buttonImage["Archer4.1"] = Image{"assets/UI/button/Archer4.1.png"};
        buttonImage["Archer4.2"] = Image{"assets/UI/button/Archer4.2.png"};
        buttonImage["Archer5.1"] = Image{"assets/UI/button/Archer5.1.png"};
        buttonImage["Archer5.2"] = Image{"assets/UI/button/Archer5.2.png"};
        buttonImage["Archer6.1"] = Image{"assets/UI/button/Archer6.1.png"};
        buttonImage["Archer6.2"] = Image{"assets/UI/button/Archer6.2.png"};

        buttonImage["Warrior1.1"] = Image{"assets/UI/button/Warrior1.1.png"};
        buttonImage["Warrior1.2"] = Image{"assets/UI/button/Warrior1.2.png"};
        buttonImage["Warrior2.1"] = Image{"assets/UI/button/Warrior2.1.png"};
        buttonImage["Warrior2.2"] = Image{"assets/UI/button/Warrior2.2.png"};
        buttonImage["Warrior3.1"] = Image{"assets/UI/button/Warrior3.1.png"};
        buttonImage["Warrior3.2"] = Image{"assets/UI/button/Warrior3.2.png"};
        buttonImage["Warrior4.1"] = Image{"assets/UI/button/Warrior4.1.png"};
        buttonImage["Warrior4.2"] = Image{"assets/UI/button/Warrior4.2.png"};
        buttonImage["Warrior5.1"] = Image{"assets/UI/button/Warrior5.1.png"};
        buttonImage["Warrior5.2"] = Image{"assets/UI/button/Warrior5.2.png"};
        buttonImage["Warrior6.1"] = Image{"assets/UI/button/Warrior6.1.png"};
        buttonImage["Warrior6.2"] = Image{"assets/UI/button/Warrior6.2.png"};

        buttonImage["Common1.1"] = Image{ "assets/UI/button/Common1.1.png" };
        buttonImage["Common1.2"] = Image{ "assets/UI/button/Common1.2.png" };
        buttonImage["Common2.1"] = Image{ "assets/UI/button/Common2.1.png" };
        buttonImage["Common2.2"] = Image{ "assets/UI/button/Common2.2.png" };
        buttonImage["Common3.1"] = Image{ "assets/UI/button/Common3.1.png" };
        buttonImage["Common3.2"] = Image{ "assets/UI/button/Common3.2.png" };
        buttonImage["Common4.1"] = Image{ "assets/UI/button/Common4.1.png" };
        buttonImage["Common4.2"] = Image{ "assets/UI/button/Common4.2.png" };
        buttonImage["Common5.1"] = Image{ "assets/UI/button/Common5.1.png" };
        buttonImage["Common5.2"] = Image{ "assets/UI/button/Common5.2.png" };
        buttonImage["Common6.1"] = Image{ "assets/UI/button/Common6.1.png" };
        buttonImage["Common6.2"] = Image{ "assets/UI/button/Common6.2.png" };


        buttonImage["Rare1.1"] = Image{ "assets/UI/button/Rare1.1.png" };
        buttonImage["Rare1.2"] = Image{ "assets/UI/button/Rare1.2.png" };
        buttonImage["Rare2.1"] = Image{ "assets/UI/button/Rare2.1.png" };
        buttonImage["Rare2.2"] = Image{ "assets/UI/button/Rare2.2.png" };
        buttonImage["Rare3.1"] = Image{ "assets/UI/button/Rare3.1.png" };
        buttonImage["Rare3.2"] = Image{ "assets/UI/button/Rare3.2.png" };
        buttonImage["Rare4.1"] = Image{ "assets/UI/button/Rare4.1.png" };
        buttonImage["Rare4.2"] = Image{ "assets/UI/button/Rare4.2.png" };
        buttonImage["Rare5.1"] = Image{ "assets/UI/button/Rare5.1.png" };
        buttonImage["Rare5.2"] = Image{ "assets/UI/button/Rare5.2.png" };
        buttonImage["Rare6.1"] = Image{ "assets/UI/button/Rare6.1.png" };
        buttonImage["Rare6.2"] = Image{ "assets/UI/button/Rare6.2.png" };


        buttonImage["Unique1.1"] = Image{ "assets/UI/button/Unique1.1.png" };
        buttonImage["Unique1.2"] = Image{ "assets/UI/button/Unique1.2.png" };
        buttonImage["Unique2.1"] = Image{ "assets/UI/button/Unique2.1.png" };
        buttonImage["Unique2.2"] = Image{ "assets/UI/button/Unique2.2.png" };
        buttonImage["Unique3.1"] = Image{ "assets/UI/button/Unique3.1.png" };
        buttonImage["Unique3.2"] = Image{ "assets/UI/button/Unique3.2.png" };
        buttonImage["Unique4.1"] = Image{ "assets/UI/button/Unique4.1.png" };
        buttonImage["Unique4.2"] = Image{ "assets/UI/button/Unique4.2.png" };
        buttonImage["Unique5.1"] = Image{ "assets/UI/button/Unique5.1.png" };
        buttonImage["Unique5.2"] = Image{ "assets/UI/button/Unique5.2.png" };
        buttonImage["Unique6.1"] = Image{ "assets/UI/button/Unique6.1.png" };
        buttonImage["Unique6.2"] = Image{ "assets/UI/button/Unique6.2.png" };


        buttonImage["Epic1.1"] = Image{ "assets/UI/button/Epic1.1.png" };
        buttonImage["Epic1.2"] = Image{ "assets/UI/button/Epic1.2.png" };
        buttonImage["Epic2.1"] = Image{ "assets/UI/button/Epic2.1.png" };
        buttonImage["Epic2.2"] = Image{ "assets/UI/button/Epic2.2.png" };
        buttonImage["Epic3.1"] = Image{ "assets/UI/button/Epic3.1.png" };
        buttonImage["Epic3.2"] = Image{ "assets/UI/button/Epic3.2.png" };
        buttonImage["Epic4.1"] = Image{ "assets/UI/button/Epic4.1.png" };
        buttonImage["Epic4.2"] = Image{ "assets/UI/button/Epic4.2.png" };
        buttonImage["Epic5.1"] = Image{ "assets/UI/button/Epic5.1.png" };
        buttonImage["Epic5.2"] = Image{ "assets/UI/button/Epic5.2.png" };
        buttonImage["Epic6.1"] = Image{ "assets/UI/button/Epic6.1.png" };
        buttonImage["Epic6.2"] = Image{ "assets/UI/button/Epic6.2.png" };


        buttonImage["Start1.1"] = Image{"assets/UI/button/Start1.1.png"};
        buttonImage["Start1.2"] = Image{"assets/UI/button/Start1.2.png"};
        buttonImage["Start2.1"] = Image{"assets/UI/button/Start2.1.png"};
        buttonImage["Start2.2"] = Image{"assets/UI/button/Start2.2.png"};
        buttonImage["Start3.1"] = Image{"assets/UI/button/Start3.1.png"};
        buttonImage["Start3.2"] = Image{"assets/UI/button/Start3.2.png"};
        buttonImage["Start4.1"] = Image{"assets/UI/button/Start4.1.png"};
        buttonImage["Start4.2"] = Image{"assets/UI/button/Start4.2.png"};
        buttonImage["Start5.1"] = Image{"assets/UI/button/Start5.1.png"};
        buttonImage["Start5.2"] = Image{"assets/UI/button/Start5.2.png"};
        buttonImage["Start6.1"] = Image{"assets/UI/button/Start6.1.png"};
        buttonImage["Start6.2"] = Image{"assets/UI/button/Start6.2.png"};

        buttonImage["Unequip1.1"] = Image{"assets/UI/button/Unequip1.1.png"};
        buttonImage["Unequip1.2"] = Image{"assets/UI/button/Unequip1.2.png"};
        buttonImage["Unequip2.1"] = Image{"assets/UI/button/Unequip2.1.png"};
        buttonImage["Unequip2.2"] = Image{"assets/UI/button/Unequip2.2.png"};
        buttonImage["Unequip3.1"] = Image{"assets/UI/button/Unequip3.1.png"};
        buttonImage["Unequip3.2"] = Image{"assets/UI/button/Unequip3.2.png"};
        buttonImage["Unequip4.1"] = Image{"assets/UI/button/Unequip4.1.png"};
        buttonImage["Unequip4.2"] = Image{"assets/UI/button/Unequip4.2.png"};
        buttonImage["Unequip5.1"] = Image{"assets/UI/button/Unequip5.1.png"};
        buttonImage["Unequip5.2"] = Image{"assets/UI/button/Unequip5.2.png"};
        buttonImage["Unequip6.1"] = Image{"assets/UI/button/Unequip6.1.png"};
        buttonImage["Unequip6.2"] = Image{"assets/UI/button/Unequip6.2.png"};

        buttonImage["Forge1.1"] = Image{"assets/UI/button/Forge1.1.png"};
        buttonImage["Forge1.2"] = Image{"assets/UI/button/Forge1.2.png"};
        buttonImage["Forge2.1"] = Image{"assets/UI/button/Forge2.1.png"};
        buttonImage["Forge2.2"] = Image{"assets/UI/button/Forge2.2.png"};
        buttonImage["Forge3.1"] = Image{"assets/UI/button/Forge3.1.png"};
        buttonImage["Forge3.2"] = Image{"assets/UI/button/Forge3.2.png"};
        buttonImage["Forge4.1"] = Image{"assets/UI/button/Forge4.1.png"};
        buttonImage["Forge4.2"] = Image{"assets/UI/button/Forge4.2.png"};
        buttonImage["Forge5.1"] = Image{"assets/UI/button/Forge5.1.png"};
        buttonImage["Forge5.2"] = Image{"assets/UI/button/Forge5.2.png"};
        buttonImage["Forge6.1"] = Image{"assets/UI/button/Forge6.1.png"};
        buttonImage["Forge6.2"] = Image{"assets/UI/button/Forge6.2.png"};

        buttonImage["Equipment1.1"] = Image{"assets/UI/button/Equipment1.1.png"};
        buttonImage["Equipment1.2"] = Image{"assets/UI/button/Equipment1.2.png"};
        buttonImage["Equipment2.1"] = Image{"assets/UI/button/Equipment2.1.png"};
        buttonImage["Equipment2.2"] = Image{"assets/UI/button/Equipment2.2.png"};
        buttonImage["Equipment3.1"] = Image{"assets/UI/button/Equipment3.1.png"};
        buttonImage["Equipment3.2"] = Image{"assets/UI/button/Equipment3.2.png"};
        buttonImage["Equipment4.1"] = Image{"assets/UI/button/Equipment4.1.png"};
        buttonImage["Equipment4.2"] = Image{"assets/UI/button/Equipment4.2.png"};
        buttonImage["Equipment5.1"] = Image{"assets/UI/button/Equipment5.1.png"};
        buttonImage["Equipment5.2"] = Image{"assets/UI/button/Equipment5.2.png"};
        buttonImage["Equipment6.1"] = Image{"assets/UI/button/Equipment6.1.png"};
        buttonImage["Equipment6.2"] = Image{"assets/UI/button/Equipment6.2.png"};

        buttonImage["X0.1"] = Image{"assets/UI/button/X0.1.png"};
        buttonImage["X0.2"] = Image{"assets/UI/button/X0.2.png"};
        buttonImage["X1.1"] = Image{"assets/UI/button/X1.1.png"};
        buttonImage["X1.2"] = Image{"assets/UI/button/X1.2.png"};
        buttonImage["X2.1"] = Image{"assets/UI/button/X2.1.png"};
        buttonImage["X2.2"] = Image{"assets/UI/button/X2.2.png"};
        buttonImage["X3.1"] = Image{"assets/UI/button/X3.1.png"};
        buttonImage["X3.2"] = Image{"assets/UI/button/X3.2.png"};
        buttonImage["X4.1"] = Image{"assets/UI/button/X4.1.png"};
        buttonImage["X4.2"] = Image{"assets/UI/button/X4.2.png"};
        buttonImage["X5.1"] = Image{"assets/UI/button/X5.1.png"};
        buttonImage["X5.2"] = Image{"assets/UI/button/X5.2.png"};
        buttonImage["X6.1"] = Image{"assets/UI/button/X6.1.png"};
        buttonImage["X6.2"] = Image{"assets/UI/button/X6.2.png"};

        buttonImage["Up0.1"] = Image{ "assets/UI/button/up0.1.png" };
        buttonImage["Up0.2"] = Image{ "assets/UI/button/up0.2.png" };
        buttonImage["Up1.1"] = Image{ "assets/UI/button/up1.1.png" };
        buttonImage["Up1.2"] = Image{ "assets/UI/button/up1.2.png" };
        buttonImage["Up2.1"] = Image{ "assets/UI/button/up2.1.png" };
        buttonImage["Up2.2"] = Image{ "assets/UI/button/up2.2.png" };
        buttonImage["Up3.1"] = Image{ "assets/UI/button/up3.1.png" };
        buttonImage["Up3.2"] = Image{ "assets/UI/button/up3.2.png" };
        buttonImage["Up4.1"] = Image{ "assets/UI/button/up4.1.png" };
        buttonImage["Up4.2"] = Image{ "assets/UI/button/up4.2.png" };
        buttonImage["Up5.1"] = Image{ "assets/UI/button/up5.1.png" };
        buttonImage["Up5.2"] = Image{ "assets/UI/button/up5.2.png" };
        buttonImage["Up6.1"] = Image{ "assets/UI/button/up6.1.png" };
        buttonImage["Up6.2"] = Image{ "assets/UI/button/up6.2.png" };

        buttonImage["Down0.1"] = Image{ "assets/UI/button/down0.1.png" };
        buttonImage["Down0.2"] = Image{ "assets/UI/button/down0.2.png" };
        buttonImage["Down1.1"] = Image{ "assets/UI/button/down1.1.png" };
        buttonImage["Down1.2"] = Image{ "assets/UI/button/down1.2.png" };
        buttonImage["Down2.1"] = Image{ "assets/UI/button/down2.1.png" };
        buttonImage["Down2.2"] = Image{ "assets/UI/button/down2.2.png" };
        buttonImage["Down3.1"] = Image{ "assets/UI/button/down3.1.png" };
        buttonImage["Down3.2"] = Image{ "assets/UI/button/down3.2.png" };
        buttonImage["Down4.1"] = Image{ "assets/UI/button/down4.1.png" };
        buttonImage["Down4.2"] = Image{ "assets/UI/button/down4.2.png" };
        buttonImage["Down5.1"] = Image{ "assets/UI/button/down5.1.png" };
        buttonImage["Down5.2"] = Image{ "assets/UI/button/down5.2.png" };
        buttonImage["Down6.1"] = Image{ "assets/UI/button/down6.1.png" };
        buttonImage["Down6.2"] = Image{ "assets/UI/button/down6.2.png" };


        buttonImage["1chapter1.1"] = Image{"assets/UI/button/1chapter1.png"};
        buttonImage["1chapter1.2"] = Image{"assets/UI/button/1chapter2.png"};
        buttonImage["1chapter2.1"] = Image{"assets/UI/button/1chapter1.png"};
        buttonImage["1chapter2.2"] = Image{"assets/UI/button/1chapter2.png"};
        buttonImage["1chapter3.1"] = Image{"assets/UI/button/1chapter1.png"};
        buttonImage["1chapter3.2"] = Image{"assets/UI/button/1chapter2.png"};
        buttonImage["1chapter4.1"] = Image{"assets/UI/button/1chapter1.png"};
        buttonImage["1chapter4.2"] = Image{"assets/UI/button/1chapter2.png"};
        buttonImage["1chapter5.1"] = Image{"assets/UI/button/1chapter1.png"};
        buttonImage["1chapter5.2"] = Image{"assets/UI/button/1chapter2.png"};
        buttonImage["1chapter6.1"] = Image{"assets/UI/button/1chapter1.png"};
        buttonImage["1chapter6.2"] = Image{"assets/UI/button/1chapter2.png"};

        buttonImage["2chapter1.1"] = Image{"assets/UI/button/2chapter1.png"};
        buttonImage["2chapter1.2"] = Image{"assets/UI/button/2chapter2.png"};
        buttonImage["2chapter2.1"] = Image{"assets/UI/button/2chapter1.png"};
        buttonImage["2chapter2.2"] = Image{"assets/UI/button/2chapter2.png"};
        buttonImage["2chapter3.1"] = Image{"assets/UI/button/2chapter1.png"};
        buttonImage["2chapter3.2"] = Image{"assets/UI/button/2chapter2.png"};
        buttonImage["2chapter4.1"] = Image{"assets/UI/button/2chapter1.png"};
        buttonImage["2chapter4.2"] = Image{"assets/UI/button/2chapter2.png"};
        buttonImage["2chapter5.1"] = Image{"assets/UI/button/2chapter1.png"};
        buttonImage["2chapter5.2"] = Image{"assets/UI/button/2chapter2.png"};
        buttonImage["2chapter6.1"] = Image{"assets/UI/button/2chapter1.png"};
        buttonImage["2chapter6.2"] = Image{"assets/UI/button/2chapter2.png"};

        buttonImage["3chapter1.1"] = Image{"assets/UI/button/3chapter1.png"};
        buttonImage["3chapter1.2"] = Image{"assets/UI/button/3chapter2.png"};
        buttonImage["3chapter2.1"] = Image{"assets/UI/button/3chapter1.png"};
        buttonImage["3chapter2.2"] = Image{"assets/UI/button/3chapter2.png"};
        buttonImage["3chapter3.1"] = Image{"assets/UI/button/3chapter1.png"};
        buttonImage["3chapter3.2"] = Image{"assets/UI/button/3chapter2.png"};
        buttonImage["3chapter4.1"] = Image{"assets/UI/button/3chapter1.png"};
        buttonImage["3chapter4.2"] = Image{"assets/UI/button/3chapter2.png"};
        buttonImage["3chapter5.1"] = Image{"assets/UI/button/3chapter1.png"};
        buttonImage["3chapter5.2"] = Image{"assets/UI/button/3chapter2.png"};
        buttonImage["3chapter6.1"] = Image{"assets/UI/button/3chapter1.png"};
        buttonImage["3chapter6.2"] = Image{"assets/UI/button/3chapter2.png"};

        buttonImage["4chapter1.1"] = Image{"assets/UI/button/4chapter1.png"};
        buttonImage["4chapter1.2"] = Image{"assets/UI/button/4chapter2.png"};
        buttonImage["4chapter2.1"] = Image{"assets/UI/button/4chapter1.png"};
        buttonImage["4chapter2.2"] = Image{"assets/UI/button/4chapter2.png"};
        buttonImage["4chapter3.1"] = Image{"assets/UI/button/4chapter1.png"};
        buttonImage["4chapter3.2"] = Image{"assets/UI/button/4chapter2.png"};
        buttonImage["4chapter4.1"] = Image{"assets/UI/button/4chapter1.png"};
        buttonImage["4chapter4.2"] = Image{"assets/UI/button/4chapter2.png"};
        buttonImage["4chapter5.1"] = Image{"assets/UI/button/4chapter1.png"};
        buttonImage["4chapter5.2"] = Image{"assets/UI/button/4chapter2.png"};
        buttonImage["4chapter6.1"] = Image{"assets/UI/button/4chapter1.png"};
        buttonImage["4chapter6.2"] = Image{"assets/UI/button/4chapter2.png"};

        buttonImage["5chapter1.1"] = Image{"assets/UI/button/5chapter1.png"};
        buttonImage["5chapter1.2"] = Image{"assets/UI/button/5chapter2.png"};
        buttonImage["5chapter2.1"] = Image{"assets/UI/button/5chapter1.png"};
        buttonImage["5chapter2.2"] = Image{"assets/UI/button/5chapter2.png"};
        buttonImage["5chapter3.1"] = Image{"assets/UI/button/5chapter1.png"};
        buttonImage["5chapter3.2"] = Image{"assets/UI/button/5chapter2.png"};
        buttonImage["5chapter4.1"] = Image{"assets/UI/button/5chapter1.png"};
        buttonImage["5chapter4.2"] = Image{"assets/UI/button/5chapter2.png"};
        buttonImage["5chapter5.1"] = Image{"assets/UI/button/5chapter1.png"};
        buttonImage["5chapter5.2"] = Image{"assets/UI/button/5chapter2.png"};
        buttonImage["5chapter6.1"] = Image{"assets/UI/button/5chapter1.png"};
        buttonImage["5chapter6.2"] = Image{"assets/UI/button/5chapter2.png"};

        buttonImage["6chapter1.1"] = Image{"assets/UI/button/6chapter1.png"};
        buttonImage["6chapter1.2"] = Image{"assets/UI/button/6chapter2.png"};
        buttonImage["6chapter2.1"] = Image{"assets/UI/button/6chapter1.png"};
        buttonImage["6chapter2.2"] = Image{"assets/UI/button/6chapter2.png"};
        buttonImage["6chapter3.1"] = Image{"assets/UI/button/6chapter1.png"};
        buttonImage["6chapter3.2"] = Image{"assets/UI/button/6chapter2.png"};
        buttonImage["6chapter4.1"] = Image{"assets/UI/button/6chapter1.png"};
        buttonImage["6chapter4.2"] = Image{"assets/UI/button/6chapter2.png"};
        buttonImage["6chapter5.1"] = Image{"assets/UI/button/6chapter1.png"};
        buttonImage["6chapter5.2"] = Image{"assets/UI/button/6chapter2.png"};
        buttonImage["6chapter6.1"] = Image{"assets/UI/button/6chapter1.png"};
        buttonImage["6chapter6.2"] = Image{"assets/UI/button/6chapter2.png"};

        buttonImage["closed2"] = Image{ "assets/UI/button/2closechapter1.png" };
        buttonImage["closed3"] = Image{ "assets/UI/button/3closechapter1.png" };
        buttonImage["closed4"] = Image{ "assets/UI/button/4closechapter1.png" };
        buttonImage["closed5"] = Image{ "assets/UI/button/5closechapter1.png" };
        buttonImage["closed6"] = Image{ "assets/UI/button/6closechapter1.png" };

        buttonImage["Gold1.1"]     = Image{"assets/UI/button/Gold.1.png"};
        buttonImage["Gold1.2"]     = Image{"assets/UI/button/Gold.2.png"};
        buttonImage["Gold2.1"]     = Image{"assets/UI/button/Gold.1.png"};
        buttonImage["Gold2.2"]     = Image{"assets/UI/button/Gold.2.png"};
        buttonImage["Gold3.1"]     = Image{"assets/UI/button/Gold.1.png"};
        buttonImage["Gold3.2"]     = Image{"assets/UI/button/Gold.2.png"};
        buttonImage["Gold4.1"]     = Image{"assets/UI/button/Gold.1.png"};
        buttonImage["Gold4.2"]     = Image{"assets/UI/button/Gold.2.png"};
        buttonImage["Gold5.1"]     = Image{"assets/UI/button/Gold.1.png"};
        buttonImage["Gold5.2"]     = Image{"assets/UI/button/Gold.2.png"};
        buttonImage["Gold6.1"]     = Image{"assets/UI/button/Gold.1.png"};
        buttonImage["Gold6.2"]     = Image{"assets/UI/button/Gold.2.png"};
    
        buttonImage["Material11.1"] = Image{"assets/UI/button/Material11.1.png"};
        buttonImage["Material11.2"] = Image{"assets/UI/button/Material11.2.png"};

        buttonImage["Material21.1"] = Image{"assets/UI/button/Material21.1.png"};
        buttonImage["Material21.2"] = Image{"assets/UI/button/Material21.2.png"};

        buttonImage["Boss11.1"] = Image{"assets/UI/button/Boss11.1.png"};
        buttonImage["Boss11.2"] = Image{"assets/UI/button/Boss11.2.png"};

        buttonImage["StartGame0.1"] = Image{"assets/UI/button/startgame1.png"};
        buttonImage["StartGame0.2"] = Image{"assets/UI/button/startgame2.png"};
        buttonImage["StartGame1"] = Image{"assets/UI/button/startgame1.png"};
        buttonImage["StartGame2"] = Image{"assets/UI/button/startgame2.png"};

        buttonImage["1slot0.1"] = Image{"assets/UI/button/1slot1.1.png"};
        buttonImage["1slot0.2"] = Image{"assets/UI/button/1slot1.2.png"};

        buttonImage["2slot0.1"] = Image{"assets/UI/button/2slot1.1.png"};
        buttonImage["2slot0.2"] = Image{"assets/UI/button/2slot1.2.png"};

        buttonImage["3slot0.1"] = Image{"assets/UI/button/3slot1.1.png"};
        buttonImage["3slot0.2"] = Image{"assets/UI/button/3slot1.2.png"};

        buttonImage["Square1.1"] = Image{"assets/UI/button/square1.png"};
        buttonImage["Square1.2"] = Image{"assets/UI/button/square1.png"};
        buttonImage["Square2.1"] = Image{"assets/UI/button/square2.png"};
        buttonImage["Square2.2"] = Image{"assets/UI/button/square2.png"};
        buttonImage["Square3.1"] = Image{"assets/UI/button/square3.png"};
        buttonImage["Square3.2"] = Image{"assets/UI/button/square3.png"};
        buttonImage["Square4.1"] = Image{"assets/UI/button/square4.png"};
        buttonImage["Square4.2"] = Image{"assets/UI/button/square4.png"};
        buttonImage["Square5.1"] = Image{"assets/UI/button/square5.png"};
        buttonImage["Square5.2"] = Image{"assets/UI/button/square5.png"};
        buttonImage["Square6.1"] = Image{"assets/UI/button/square6.png"};
        buttonImage["Square6.2"] = Image{"assets/UI/button/square6.png"};

        buttonImage["Quit0.1"] = Image{"assets/UI/button/Quit0.1.png"};
        buttonImage["Quit0.2"] = Image{"assets/UI/button/Quit0.2.png"};
        buttonImage["Quit1.1"] = Image{"assets/UI/button/Quit1.1.png"};
        buttonImage["Quit1.2"] = Image{"assets/UI/button/Quit1.2.png"};
        buttonImage["Quit2.1"] = Image{"assets/UI/button/Quit2.1.png"};
        buttonImage["Quit2.2"] = Image{"assets/UI/button/Quit2.2.png"};
        buttonImage["Quit3.1"] = Image{"assets/UI/button/Quit3.1.png"};
        buttonImage["Quit3.2"] = Image{"assets/UI/button/Quit3.2.png"};
        buttonImage["Quit4.1"] = Image{"assets/UI/button/Quit4.1.png"};
        buttonImage["Quit4.2"] = Image{"assets/UI/button/Quit4.2.png"};
        buttonImage["Quit5.1"] = Image{"assets/UI/button/Quit5.1.png"};
        buttonImage["Quit5.2"] = Image{"assets/UI/button/Quit5.2.png"};
        buttonImage["Quit6.1"] = Image{"assets/UI/button/Quit6.1.png"};
        buttonImage["Quit6.2"] = Image{"assets/UI/button/Quit6.2.png"};

        buttonImage["Trade1.1"] = Image{"assets/UI/button/Trade1.1.png"};
        buttonImage["Trade1.2"] = Image{"assets/UI/button/Trade1.2.png"};
        buttonImage["Trade2.1"] = Image{"assets/UI/button/Trade2.1.png"};
        buttonImage["Trade2.2"] = Image{"assets/UI/button/Trade2.2.png"};
        buttonImage["Trade3.1"] = Image{"assets/UI/button/Trade3.1.png"};
        buttonImage["Trade3.2"] = Image{"assets/UI/button/Trade3.2.png"};
        buttonImage["Trade4.1"] = Image{"assets/UI/button/Trade4.1.png"};
        buttonImage["Trade4.2"] = Image{"assets/UI/button/Trade4.2.png"};
        buttonImage["Trade5.1"] = Image{"assets/UI/button/Trade5.1.png"};
        buttonImage["Trade5.2"] = Image{"assets/UI/button/Trade5.2.png"};
        buttonImage["Trade6.1"] = Image{"assets/UI/button/Trade6.1.png"};
        buttonImage["Trade6.2"] = Image{"assets/UI/button/Trade6.2.png"};

        backgroundObjImage["data_manage_window"] = Image{"assets/background/load-box.png"};

        cout << "UI Load End" << endl;
    }

    inline void imageDelete()
    {
        buttonImage.clear();
        backgroundObjImage.clear();
    }
}

enum chapters
{
    start = 0,
    forest,
    desert,
    skypia,
    abyss,
    hellgate,
    hell
};
inline double chapterRoot[6] = { 1.3, 1.3, 2, 1.5, 1.8, 2.1 };
inline double chapterNumber[6] = { 10, 10, 4, 8, 5, 5 };

inline int  now_chapter     = start;
inline bool wasMousePressed = false;
inline bool isGameLoaded = false;
inline vector<Image> chapterBackgrounds;
inline vector<Image> questBackgrounds;
inline int CHAPTER0_COLOR[] = { 185, 242, 253, 24, 38, 24 };

inline int CHAPTER1_COLOR[] = {149, 179, 149, 42, 72, 42};

inline int CHAPTER2_COLOR[] = {255, 224, 130, 192, 128, 31};

inline int CHAPTER3_COLOR[] = {186, 213, 232, 133, 169, 195};

inline int CHAPTER4_COLOR[] = {87, 101, 156, 45, 45, 110};

inline int CHAPTER5_COLOR[] = {158, 130, 94, 77, 52, 2};

inline int CHAPTER6_COLOR[] = {189, 108, 108, 124, 19, 19};

inline vector<int*> chapterColor = { CHAPTER0_COLOR, CHAPTER1_COLOR, CHAPTER2_COLOR, CHAPTER3_COLOR,
                             CHAPTER4_COLOR, CHAPTER5_COLOR, CHAPTER6_COLOR};

inline int WARRIOR_COLOR[] = {147, 57, 57};
inline int MAGE_COLOR[] = {144, 107, 181};
inline int THIEF_COLOR[] = {86, 100, 61};
inline int ARCHER_COLOR[] = {134, 198, 154};

inline vector<int*> characterColor = {WARRIOR_COLOR, MAGE_COLOR, THIEF_COLOR, ARCHER_COLOR};

constexpr int LISTFONTSIZE = 35;
constexpr int DIALOGUESIZE = 45; //창 뜨거나, 인게임 오른쪽 하단
constexpr int HEADFONTSIZE = 55;
constexpr int TOPSIZE = 75; //Mission 
constexpr int DICENUMBER = 120; //주사위 숫자, Press the Mouse to Start
constexpr double gap = WINDOW_HEIGHT * 0.015;
constexpr int NEEDTOFIX = 100;