/*
File name: 1_2_endgame_scene.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_2_endgame_screen.h"
#include "1_1_ingame_screen.h"
EndGameScene::EndGameScene(long double e) : exp{e} {}
EndGameScene::EndGameScene(unsigned long long m, long double e): money{m}, exp{e} {}
ClearScene::ClearScene(unsigned long long m, long double e, int mat, bool b) : EndGameScene{m*2, e}, matNum(mat),boss(b)
{
    if (dynamic_cast<MaterialQuest*>(nowQuest) != nullptr)
    {
        //Mat reward
        inInform.playerMatrial[nowQuest->get_material_goal()]++;
    }
    if (dynamic_cast<BossQuest*>(nowQuest) != nullptr && boss == true)
    {
        // boss reward
    }
    code = nowQuest->getCode();
}
FailScene::FailScene(unsigned long long m, long double e):EndGameScene(m,e){}


void EndGameScene::animation_skip()
{
    if (Helpers::Collision::objToMouse({0, -WINDOW_HEIGHT * 0.2}, WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.5) &&
        MouseIsPressed == true)
    {
        animation_end();
    }
}
void EndGameScene::make_button()
{
    if (animationEnd == true)
    {
        next.draw_button();
    }
}
void EndGameScene::go_main_scene()
{
    if (animationEnd == true && next.get_button_status() == true)
    {
        //씬 변경
        status.money += this->money;
        status.exp += this->exp;
        for (auto it : inInform.playerMatrial)
        {
            status.inventoryMaterial[it.first] += it.second;
        }
        delete nowQuest;
        nowQuest = nullptr;
        inInform.reset();
        // 캐릭터 체력 초기화, 실패 시 차감
        SceneChangeInput::toGameMain();
    }
}
void EndGameScene::draw_background() const
{
    draw_image(objectImage["woodenTable"],0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    draw_image(objectImage["paper"], 0, 0, WINDOW_WIDTH * 0.65, WINDOW_HEIGHT * 0.6);
}



void EndGameScene::update()
{
    reward_animation();
    animation_skip();
    go_main_scene();
}    //보상확인 버튼 누르면 보상 주고 메인으로 이동




void EndGameScene::draw_material() const
{
    int i = 0;
    double x{}, y{};
    for (auto& m : inInform.playerMatrial)
    {
        x = { -WINDOW_WIDTH * 0.15 + (i % 10) * (50 + 50) };
        y = { -WINDOW_HEIGHT * 0.2 + (i / 10) * (50 + 5) };
        m.first->draw(x, y);
        push_settings();
        set_font_size(LISTFONTSIZE);
        draw_text(": " + to_string(m.second), x + MaterialImage[m.first->getName()].GetWidth() / 2, y - MaterialImage[m.first->getName()].GetHeight() / 2);
        pop_settings();
        ++i;
    }
    i = 0;
    for (auto& m : inInform.playerMatrial)
    {
        x = { -WINDOW_WIDTH * 0.15 + (i % 10) * (50 + 50) };
        y = { -WINDOW_HEIGHT * 0.2 + (i / 10) * (50 + 5) };
        m.first->draw_info(x, y);
        ++i;
    }
}





void ClearScene::draw()
{
    draw_background();
    
    push_settings();
    set_fill_color(0);
    set_font_size(TOPSIZE);
    no_outline();
    draw_text("Mission Accomplished", -WINDOW_WIDTH * 0.09, WINDOW_HEIGHT * 0.35);

    set_font_size(HEADFONTSIZE);
    draw_text("Money : " + to_string((unsigned long long)moneyAnimation), -WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.15);
    draw_text("EXP   : " + to_string((unsigned long long)expAnimation), -WINDOW_WIDTH * 0.15, -WINDOW_HEIGHT * 0.);
    if (dynamic_cast<MaterialQuest*>(nowQuest) != nullptr)
    {
        draw_text(dynamic_cast<MaterialQuest*>(nowQuest)->get_material_goal()->getName(),

                  -WINDOW_WIDTH * 0.15,
                  WINDOW_HEIGHT * -0.1);
    }
    if (dynamic_cast<BossQuest*>(nowQuest) !=nullptr && boss == true)
    {
        draw_text(dynamic_cast<BossQuest*>(nowQuest)->get_boss_name() + " : V",
                  -WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * -0.1);
    }
    draw_material();

    pop_settings();
    make_button();
}

void ClearScene::go_main_scene()
{
    if (animationEnd == true && next.get_button_status() == true)
    {
        //씬 변경
        status.money += this->money;
        status.exp += this->exp;
        for (auto it : inInform.playerMatrial)
        {
            status.inventoryMaterial[it.first] += it.second;
        }
        delete nowQuest;
        nowQuest = nullptr;
        inInform.reset();
        // 캐릭터 체력 초기화, 실패 시 차감
        if (code == 42)//퀘스트 코드로 해야하지 않나
        {
            status.clear = true;
            SceneChangeInput::toEnding();
        }
        else
        {
            SceneChangeInput::toGameMain();
        }
    }
}

void ClearScene::reward_animation()
{
    if (moneyAnimation < money)
    {
        moneyAnimation += money / 60.l;
    }
    else if (expAnimation < exp)
    {
        moneyAnimation = static_cast<long double>(money);
        expAnimation += exp / 60;
    }
    else if (animationEnd == false)
    {
        expAnimation = exp;
        animation_end();
    }
}
void ClearScene::animation_end()
{
    animationEnd   = true;
    if (status.openStage == code)
    {
        ++status.openStage;
    }
}




void ClearScene::setup()
{
    if (status.openStage == 1)//tutorial
    {
        inInform.playerMatrial[&sapling]++;
        inInform.playerMatrial[&stone]++;
    }
}




void FailScene::draw()
{
    draw_background();
    push_settings();
    //set_rectangle_mode(RectMode::Center);
    //draw_rectangle(0, 0, WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.5);
    set_font_size(TOPSIZE);
    no_outline();
    set_fill_color(0);
    draw_text("Mission Failed", -WINDOW_WIDTH * 0.09, WINDOW_HEIGHT * 0.35);
    set_font_size(HEADFONTSIZE);
    draw_text("Money : " + to_string((unsigned long long)money), -WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.1);
    draw_text("EXP   : " + to_string((unsigned long long)exp), -WINDOW_WIDTH * 0.15, -WINDOW_HEIGHT * 0.1);

    draw_material();
    pop_settings();
    make_button();
}


void FailScene::reward_animation()
{
    if (moneyAnimation < money)
    {
        moneyAnimation += money / 60.l;
    }
    else if (expAnimation < exp)
    {
        moneyAnimation = static_cast<long double>(money);
        expAnimation += exp / 60;
    }
    else if (animationEnd == false)
    {
        expAnimation = exp;
        animationEnd = true;
    }
}





