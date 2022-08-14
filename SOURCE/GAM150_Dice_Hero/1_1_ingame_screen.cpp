/*
File name: 1_1_ingame_scene.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "1_1_ingame_screen.h"
#include "1_0_main_screen.h"
#include "IngameSceneHelper.h"


void IngameScene::tile_setup() {
    tiles_set();
    magicTower.set_position(tiles[magicTower.get_loca()].getTilePos());
}
void IngameScene::status_setup()
{
    ingameLevel   = status.level;
    ingameExpGoal = static_cast<int>(10 * pow(1.16, ingameLevel));
    for (auto i = 0; i < selected.size(); i++)
    {
        selected[i]->new_game_set();
        myCharacters.push_back(selected[i]);
    }
    selected.clear();
}

void IngameScene::setup() {
    difficulty = nowQuest->getCode();
    tile_setup();
    status_setup();
    player_turn_setup();
}


void IngameScene::player_turn_setup() {
    unsigned int deadNum{0};
    player_setup(deadNum);
    if (deadNum == myCharacters.size())
    {
        inInform.gold = ingameGold;
        inInform.exp = ingameLevel - status.level;
        SceneChangeInput::toFailScene();
    }
}

void IngameScene::turn_setup()
{
    player_turn_setup();
    object_turn_setup();
    ingame_boss_set();
    nowTurn += 1;
    events.push_event(EventLog{"Turn "+to_string(nowTurn),0.,WINDOW_WIDTH*0.15,RGB{0,0,0},100,2});
    peddler.newMagicSet();
    magicTower.newMagicSet();
}


void IngameScene::magic_gene()
{
    if (dynamic_cast<Mage*>(myMage)->get_mp() >= dynamic_cast<Mage*>(myMage)->get_cost()
        && playerMagics.size()< PlayerMagicMax)
    {
        dynamic_cast<Mage*>(myMage)->use_mana();
        AboutMagic::give_magic(playerMagics,1, dynamic_cast<Mage*>(myMage)->magicLevel);
        arts.PlaySound(getmagic);
    }

}


void IngameScene::update()
{
    if (doodle::Key == doodle::KeyboardButtons::Z && doodle::KeyIsPressed == false)
    {
        doodle::Key = doodle::KeyboardButtons::None;
        level_up();
        arts.PlaySound(levelup);
    }// level up cheat
    if(Helpers::Keyboard::Rl_key(KeyboardButtons::C) == true)//clear cheat
    {
        selected.clear();
        ingameGold = nowQuest->get_gold_goal();
        if (nowQuest->get_material_goal() != nullptr)
        {
            inInform.playerMatrial[nowQuest->get_material_goal()]++;
        }
    }
    if(Helpers::Keyboard::Rl_key(KeyboardButtons::G) == true)
    {
        AboutMagic::give_magic(playerMagics,1, dynamic_cast<Mage*>(myMage)->magicLevel);
    }
    if (Helpers::Keyboard::Rl_key(KeyboardButtons::H) == true)
    {
        AboutMagic::give_magic(playerMagics, 1, 1000);
    }

    if (turnEnd == true)
    {
        turn_setup();
        turnEnd = false;
    }

    show_portrait();
    update_target_of_effect();
    Thief_move();
    magic_gene();
    ingame_effect_update();
    ingame_magic_update();

    for (auto& c : myCharacters)
    {
        c->update();
        c->set_position(tiles[c->get_location()].getTilePos());
    }

    // ingame shop update
    if (myCharacters[whosTurn]->get_effect().type != EffectType::move)
    {
        magicTower.check_charLoca(myCharacters[whosTurn]->get_location());
        peddler.check_charLoca(myCharacters[whosTurn]->get_location());
    }
    magicTower.update();
    peddler.update();

    myCharacters[whosTurn]->dt_update();
    if (myCharacters[whosTurn]->get_is_double() == true && myCharacters[whosTurn]->get_provide_double() == false)//더블 시 레벨 업
    {
        level_up();
        events.push_event(EventLog{ "Double!!", WINDOW_WIDTH * 0., WINDOW_HEIGHT * 0.05,RGB{},50,7 });
        arts.PlaySound(levelup);
        myCharacters[whosTurn]->set_provide_double(true);
    }

    reward_update();
    level_up_update();
    if (myCharacters[whosTurn]->turn_end() == true)
    {
        myCharacters[whosTurn]->initial_used_dice_num();
        myCharacters[whosTurn]->initial_is_double();
        myCharacters[whosTurn]->set_provide_double(false);
        myCharacters[whosTurn]->is_stun() = false;
        effectTarget = {0};
        Mage* mc = dynamic_cast<Mage*>(myCharacters[whosTurn]);
        if(mc!=nullptr)
        {
            mc->do_mana_regen();
        }
        Warrior* wc = dynamic_cast<Warrior*>(myCharacters[whosTurn]);
        if(wc != nullptr && wc->check_rage() == true)
        {
            wc->use_rage();
            wc->turn_setup();
        }else
        {
            ++whosTurn;
        }
        clickedTileNum = 0;
        usedMagic      = false;
        ingame_goal_update();
    }
    if (whosTurn >= (int)myCharacters.size())
    {
        count_down_gold_box();
        count_PS_E();
        turnEnd  = true;
        whosTurn = 0;
    }
    if (exitButton.get_button_status()==true)
    {
        inInform.gold = ingameGold;
        inInform.exp = ingameLevel - status.level;
        SceneChangeInput::toFailScene();
    }
}


void IngameScene::ingame_magic_update()
{
    int y{0};
    int x{0};
    static constexpr int interval{165};
    static constexpr int Yinterval{ 145 };
    for (int i = 0;i< playerMagics.size();++i)
    {
        y = i / 3;
        x = i % 3;
        playerMagics[i]->set_pos(WINDOW_WIDTH * 0.244 + x * interval, WINDOW_HEIGHT * 0.4 - Yinterval * y);
        if (dynamic_cast<Mage*>(myCharacters[whosTurn]) != nullptr && playerMagics[i]->area() == true &&MouseIsPressed == true && (usedMagic == false || dynamic_cast<Mage*>(myCharacters[whosTurn])->get_unlimited() == true))
        {
            if (myCharacters[whosTurn]->get_effect().on == false)
            {
                myCharacters[whosTurn]->set_effect(playerMagics[i]->get_effect());
                characterRangeData = myCharacters[whosTurn]->get_attack_range();
                myCharacters[whosTurn]->set_attack_range(playerMagics[i]->get_effect().extraRange);
                myCharacters[whosTurn]->set_skill_on(true);
                delete playerMagics[i];
                playerMagics.erase(playerMagics.begin()+i);
            }
        }
    }
}




void IngameScene::level_up_update()
{
    if (ingameExp >= ingameExpGoal)
    {
        level_up();

        ingameExp = ingameExp - ingameExpGoal;
        ingameExpGoal = static_cast<int>(10 * pow(1.16, ingameLevel));
        if(ingameExp < ingameExpGoal)
        {
            arts.PlaySound(levelup);
        }
    }
}



void IngameScene::draw_background() const
{
    static constexpr double paperImageScale{1.2};
    static constexpr double BoardImageScaleX{ 0.65 };
    static constexpr double BoardImageScaleY{ 0.45 };
    static constexpr double Board2ImageScaleX{ 0.3 };
    static constexpr double Board2ImageScaleY{ 0.12 };

    draw_image(backgroundImage["Plane_"+to_string(now_chapter)],0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    //마법 위치 이미지, 괜찮은 사진 있으면 변경
    draw_image(objectImage["paper"],
        WINDOW_WIDTH/2 - objectImage["paper"].GetWidth()* paperImageScale /2,
        WINDOW_HEIGHT/2 - objectImage["paper"].GetHeight()* paperImageScale /2-10, 
        objectImage["paper"].GetWidth()* paperImageScale, objectImage["paper"].GetHeight()* paperImageScale);
    draw_image(objectImage["UI_board_Large_stone"], 
        WINDOW_WIDTH / 2 - objectImage["UI_board_Large_stone"].GetWidth() * BoardImageScaleX / 2,
        -WINDOW_HEIGHT / 2 + objectImage["UI_board_Large_stone"].GetHeight() * BoardImageScaleY / 2,
        objectImage["UI_board_Large_stone"].GetWidth() * BoardImageScaleX,
        objectImage["UI_board_Large_stone"].GetHeight() * BoardImageScaleY);
    draw_image(objectImage["UI_board_Large_stone"], -WINDOW_WIDTH * 0.425, -WINDOW_HEIGHT * 0.08,
               objectImage["UI_board_Large_stone"].GetWidth() * Board2ImageScaleX,
               objectImage["UI_board_Large_stone"].GetHeight() * Board2ImageScaleY);
}

void IngameScene::draw()
{
    draw_background();
    for (auto &t : tiles)
    {
        t.draw(static_cast<int>(now_chapter));
        //draw_rectangle(t.getTilePos().x, t.getTilePos().y, t.getTileWidth(), t.getTileHeight());
    }
    for (auto& t : tiles)
    {
        t.BEdraw();
    }
    for (int myTokenNum = 0; myTokenNum < myCharacters[whosTurn]->get_token_size(); ++myTokenNum)
    {
        if (myCharacters[whosTurn]->is_mouse_clicked_token(myTokenNum))
        {
            if (myCharacters[whosTurn]->get_token_type(myTokenNum) == EffectType::move || myCharacters[whosTurn]->get_token_type(myTokenNum) == EffectType::BACK_MOVE)
            {
                draw_possib_move_pos(myCharacters[whosTurn]->get_token_type(myTokenNum));
            }
            else if (myCharacters[whosTurn]->get_token_type(myTokenNum) == EffectType::attack)
            {
                draw_attack_range();
            }
            for (auto& d : myCharacters[whosTurn]->get_dice())
            {
                d.highLighting();
                d.click_me();
            }
        }
    }
    myCharacters[whosTurn]->My_turn();
    for (auto& c : myCharacters)
    {
        push_settings();
        set_font_size(HEADFONTSIZE);
        set_fill_color(0);
        c->draw();
        pop_settings();
    }
    myCharacters[whosTurn]->dt_draw();
    
    ingame_magic_draw();
    ingame_effect_draw();
    ui_draw();

    magicTower.draw("Magic tower");
    peddler.set_position(tiles[peddler.get_loca()].getTilePos());
    peddler.draw("Peddler");
}

void IngameScene::ingame_material_draw()const
{
    static const Image Inven{"assets/UI/IngameInven.png"};
    int i = 0;
     double x{},y{};
    for (auto& m : inInform.playerMatrial)
    {
        x={ -WINDOW_WIDTH * 0.47 + (i % 8) * (50 + 50) };
        y={ -WINDOW_HEIGHT * 0.3 + (i / 8) * (50 + 5) };
        push_settings();
        set_font_size(LISTFONTSIZE);
        set_fill_color(0, 0, 0);
        draw_image(Inven, x+15, y, 80,80);
        draw_text(": "+to_string(m.second),x+ MaterialImage[m.first->getName()].GetWidth()/2,y - MaterialImage[m.first->getName()].GetHeight()/2);
        pop_settings();
        m.first->draw(x, y);
        ++i;
    }
    i = 0;

    for (auto& m : inInform.playerMatrial)
    {
        x={ -WINDOW_WIDTH * 0.47 + (i % 8) * (50 + 50) };
        y={ -WINDOW_HEIGHT * 0.3 + (i / 8) * (50 + 5) };
        push_settings();
        set_fill_color(0, 0, 0);
        m.first->draw_info(x, y);
        pop_settings();
        ++i;
    }
}


void IngameScene::ingame_magic_draw()
{

    for (auto& m : playerMagics)
    {
        m->draw();
        if (m->area() == true)
        {
            draw_range_col(0, m->get_effect().extraRange, 0x4040d0f0);
        }
        if (dynamic_cast<Mage*>(myCharacters[whosTurn])!=nullptr 
            && (usedMagic == false || dynamic_cast<Mage*>(myCharacters[whosTurn])->get_unlimited() == true)){
            //magic highLight
            m->click_me();
        }
    }
}



void IngameScene::ui_draw()
{
    double      x = -WINDOW_WIDTH * 0.4;
    double      y = WINDOW_HEIGHT;
    double      w = WINDOW_WIDTH / 13;
    double      h = WINDOW_HEIGHT / 32;
    vector<UI*> profile{};

    for (int i = 0; i < myCharacters.size(); ++i)
    {
        profile.emplace_back(new Profile{myCharacters[i]->get_class_name(), x, y * (0.43 - 0.08 * i), w, h, 
            myCharacters[i]->get_hp(), myCharacters[i]->get_max_hp(), {120, 120, 255}});
    }

    if (dynamic_cast<Profile*>(profile[whosTurn]) != nullptr)

    {
        dynamic_cast<Profile*>(profile[whosTurn])->high_lighting();
    }
    for (int i = 0; i < profile.size(); ++i)
    {
        if (dynamic_cast<Profile*>(profile[i]) != nullptr)
        {
            if (dynamic_cast<Profile*>(profile[i])->area() == true)
            {
                Helpers::Information::ingameInforation(myCharacters[i]->get_information());
            }
        }
        profile[i]->draw();
        push_settings();
        int a = 1;
        if(i == whosTurn)
        {
            a = 2;
        }
        dynamic_cast<Profile*>(profile[i])->drawing(myCharacters[i]->get_class_name(), a);
        pop_settings();
    }


    if (magicTower.get_is_entered() == false || peddler.get_is_entered() == false)
    {
        if (clickedTileNum != 0)//초상화 UI
        {
            tiles[clickedTileNum].drawBEPortrait();
            tiles[clickedTileNum].draw_object_info();
        }
    }

    for (auto &t:tiles)
    {
        if (t.getEnemy() != nullptr && t.getEnemy()->monArea() == true)
        {
            t.draw_info("enemy");
        }
        else if (t.getBox() != nullptr && t.getBox()->boxArea() == true)
        {
            t.draw_info("box");
        }
    }
    for (int i = 0; i < playerMagics.size(); ++i)
    {
        if (playerMagics[i]->area() == true)
        {
            Helpers::Information::ingameInforation(playerMagics[i]->get_info());
        }
    }


    for (int i = 0; i < profile.size(); ++i)
    {
        delete profile[i];
    }
    profile.clear();
    
    gold.set_money(ingameGold);
    gold.draw();

    ingame_material_draw();

    //퀘스트별 목표
    goal_UI_draw();

	
   // LEVEL
    player.set_now(ingameExp);
    player.set_max(ingameExpGoal);
    player.set_name(to_string(ingameLevel));
    player.draw();

    // turn
    //const auto turnX = WINDOW_WIDTH * -0.48;
    //const auto turnY = WINDOW_HEIGHT * 0.3;

    //draw_text("Turn : " + to_string(nowTurn), turnX, turnY);
    pop_settings();


    exitButton.draw_button();
}



void IngameScene::ingame_effect_update()
{
    if (myCharacters[whosTurn]->get_effect().on == true)
    {
        switch (myCharacters[whosTurn]->get_effect().type)
        {
            case EffectType::attack:
                switch (effectTarget)
                {
                    case PortraitTarget::SOMETHING:
                        effectAnimationType = attack;
                        effectTarget        = NOTHING;
                        break;
                    case PortraitTarget::NOTHING:
                        do_effect();
                        effectAnimationType = {};
                        break;
                    case PortraitTarget::BOX:
                        attack_to_box();
                        effectAnimationType = {};
                        break;
                    case PortraitTarget::ENEMY:
                        attack_to_enemy();
                        effectAnimationType = {};
                        break;
                    default: break;
                }
                break;
            case EffectType::BACK_MOVE:
                if (dynamic_cast<Thief*>(myCharacters[whosTurn]) != nullptr)
                {
                    dynamic_cast<Thief*>(myCharacters[whosTurn])
                        ->set_moveNum(-myCharacters[whosTurn]->get_effect().howMuch);
                    dynamic_cast<Thief*>(myCharacters[whosTurn])->set_passive_move(true);
                    myCharacters[whosTurn]->initial_effect();
                    myCharacters[whosTurn]->get_effect().set_on(false);
                    clickedTileNum = 0;
                }
                break;
            case EffectType::move:
                
                if (dynamic_cast<Thief*>(myCharacters[whosTurn]) != nullptr)
                {
                    dynamic_cast<Thief*>(myCharacters[whosTurn])
                        ->set_moveNum(myCharacters[whosTurn]->get_effect().howMuch);
                    dynamic_cast<Thief*>(myCharacters[whosTurn])->set_passive_move(true);
                    myCharacters[whosTurn]->initial_effect();
                    myCharacters[whosTurn]->get_effect().set_on(false);
                    clickedTileNum = 0;
                    break;
                }
                else
                {
                    animationNum+=0.1;
                    if (myCharacters[whosTurn]->get_location() != myCharacters[whosTurn]->get_location()+static_cast<int>(animationNum))
                    {
                        arts.PlaySound(sounds::walk);
                        myCharacters[whosTurn]->set_location((myCharacters[whosTurn]->get_location() + 1) %
                                                             questTileCount);
                        myCharacters[whosTurn]->use_effect_howMuch();
                        st_point_heal();
                        animationNum = {0};
                    }
                    if (myCharacters[whosTurn]->get_effect().howMuch == 0)
                    {
                        do_effect();
                    }
                }
                
        
                break;
            
            case EffectType::mana:
                myCharacters[whosTurn]->give_extra_resource(myCharacters[whosTurn]->get_effect().howMuch);
                do_effect();
                break;
            case EffectType::MAGIC_TELEPORT:
                effectAnimationType = MAGIC_TELEPORT;
                if (do_magic_teleport() == true)
                {
                    st_point_heal();
                    do_magic();
                    effectAnimationType = {};
                }
                break;
            case EffectType::MAGIC_ATTACK:
                effectAnimationType = MAGIC_ATTACK;
                if (do_magic_attack() == true)
                {
                    do_magic();
                    effectAnimationType = {};
                }
                break;
            case EffectType::MAGIC_RESURRECTION:
                effectAnimationType = MAGIC_RESURRECTION;
                if (do_magic_resur() == true)
                {
                    do_magic();
                    effectAnimationType = {};
                }
                break;
            case EffectType::MAGIC_BOMB:
                effectAnimationType = MAGIC_BOMB;
                if (do_magic_bomb(myCharacters[whosTurn]->get_effect().EFFStart,
                                  myCharacters[whosTurn]->get_effect().EFFEnd) == true)
                {
                    do_magic();
                    effectAnimationType = {};
                }
                break;

            default: break;
        }
    }
}
