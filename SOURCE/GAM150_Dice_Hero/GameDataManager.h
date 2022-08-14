/*
File name: GameDataManager.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "scene_manager.h"
#include "top_header.h"

#include <string>
#include <vector>
class PlayerData
{
    static constexpr double WWidth{1600};
    static constexpr double WHeight{800};
    static constexpr double SWidth{ 200 };
    static constexpr double SHeight{ 100 };
    static constexpr double slotInterval{ 400 };
    static constexpr double slotSTX{ -400 };
    static constexpr double slotSTY{ -250 };
    static constexpr double simple_data_w{350};
    static constexpr double simple_data_h{300};
    static constexpr double simple_data_interval{100};
    Button slot1Button{ "1slot",     0,   0,
                        SWidth, SHeight, true };
    Button slot2Button{ "2slot",      0,   0,
                        SWidth, SHeight, true };
    Button slot3Button{ "3slot",      0,   0,
                        SWidth, SHeight, true };
    Button XButton{ "X",      0,   0,
                        100.,100., true };
    std::vector<Button*> slots{&slot1Button,&slot2Button,&slot3Button};
    std::vector<std::string> slot{
        "dataFile/slot1_save_data.txt",
        "dataFile/slot2_save_data.txt",
        "dataFile/slot3_save_data.txt",
        "dataFile/temporary_save_data.txt"
    };
    std::vector<std::string> slotName{
        "slot1",
        "slot2",
        "slot3",
        "temporary"
    };
    int choosen{3};
    bool eventOn{false};
public:
    static PlayerData& Instance()
    {
        static PlayerData instance;
        return instance;
    }
    void saveData();
    void loadData();
    int read_level_data(int i);
    long long read_money_data(int i);
    int read_clearStage_data(int i);
    void draw_simple_data(int i,double x,double y);
    void clear_data(int i);
    void draw_data_manage_window(std::string name = "Load",double x=0,double y=0);
    void update_load_window(double x=0, double y=0);
    void update_save_window(double x = 0, double y = 0);
    bool& event_on() { return eventOn; }
};

