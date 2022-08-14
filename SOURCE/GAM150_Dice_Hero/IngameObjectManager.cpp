/*
File name: IngameObjectManager.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "IngameObjectManager.h"
#include "1_1_ingame_screen.h"
#include "tile.h"
#include "game_header.h"
#include "monsterSpawn.h"
#include "AttackEffect.h"
#include "MagicEffect.h"
void IngameObjectManager::tiles_set()
{
    double           tileX = 0;
    double           tileY = -420;
    const double apexWidth = tileImage[1000].GetWidth() * 0.8;
    const double apexHeight = tileImage[1000].GetHeight() * 0.8;
    const double tileWidth  = tileImage[10].GetWidth() * 0.8;
    const double tileHeight = tileImage[10].GetHeight() * 0.8;
    for (auto i = 0; i < questTileCount; i++)
    {
        Tile tile;
        tile.setTilePos(tileX, tileY);
        if (i < questTileCount / 4)
        {
            if (i == 0)
            {
                tile.setTileSize(apexWidth, apexHeight);
                tile.setApex(true);
                tile.set_tileOffset(1000);
                tileX -= apexWidth / 2.7;
                tileY += apexHeight / 2.9;
                tile.computeObjPos(3);
            }
            else if (i == questTileCount / 4 - 1)
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(100);
                tileX -= apexWidth / 2.7;
                tileY += apexHeight / 2.7;
                tile.computeObjPos(3);

            }
            else
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(100);
                tileX -= tileWidth / 2.7;
                tileY += tileHeight / 2.7;
                tile.computeObjPos(3);
            }
        }
        else if (i < questTileCount / 2)
        {
            if (i == questTileCount / 4)
            {
                tile.setTileSize(apexWidth, apexHeight);
                tile.setApex(true);
                tile.set_tileOffset(100000);
                tileX += apexWidth / 2.7;
                tileY += apexHeight / 2.7;

                tile.computeObjPos(1);
            }
            else if (i == questTileCount / 2 - 1)
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(10);
                tileX += apexWidth / 2.7;
                tileY += apexHeight / 2.7;
                tile.computeObjPos(1);
            }
            else
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(10);
                tileX += tileWidth / 2.7;
                tileY += tileHeight / 2.7;
                tile.computeObjPos(1);
            }
        }
        else if (i < 3 * questTileCount / 4)
        {
            if (i == questTileCount / 2)
            {
                tile.setTileSize(apexWidth, apexHeight);
                tile.setApex(true);
                tile.set_tileOffset(10000);
                tileX += apexWidth / 2.7;
                tileY -= apexHeight / 2.7;
                tile.computeObjPos(1);
            }
            else if (i == 3 * questTileCount / 4 - 1)
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(100);
                tileX += apexWidth / 2.7;
                tileY -= apexHeight / 2.7;
                tile.computeObjPos(1);
            }
            else
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(100);
                tileX += tileWidth / 2.7;
                tileY -= tileHeight / 2.7;
                tile.computeObjPos(1);
            }
        }
        else
        {
            if (i == 3 * questTileCount / 4)
            {
                tile.setTileSize(apexWidth, apexHeight);
                tile.setApex(true);
                tile.set_tileOffset(1000000);
                tileX -= apexWidth / 2.7;
                tileY -= apexHeight / 2.7;
                tile.computeObjPos(2);
            }
            else if (i == questTileCount - 1)
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(10);
                tileX -= apexWidth / 2.7;
                tileY -= apexHeight / 2.7;
                tile.computeObjPos(2);
            }
            else
            {
                tile.setTileSize(tileWidth, tileHeight);
                tile.set_tileOffset(10);
                tileX -= tileWidth / 2.7;
                tileY -= tileHeight / 2.7;
                tile.computeObjPos(2);
            }
        }
        tile.setTileIndex(i);
        //compute tile obj pos
        tiles.push_back(tile);
    }
}


void IngameObjectManager::player_setup(unsigned int &deadNum)
{
    for (auto& c : myCharacters)
    {
        c->turn_setup();
        if (tiles[c->get_location()].getMonsterOn() == true && tiles[c->get_location()].getEnemyDead() == false)
        {
            //플레이어 타일에 몬스터가 서있을 떄
            c->give_damage((tiles[c->get_location()].getEnemyHP())); //방어력 공식 적용 ㅇㅖ정
        }
        if (c->get_hp() <= 0) //죽으면 엔드씬으로, 수정 예정
        {
            ++deadNum;
            if(c->getisdead() == false)
            {
                c->getisdead() = true;
                if (c->myClass == Warrior_C || c->myClass == Thief_C)
                {
                    arts.PlaySound(Male_Die);
                }
                else
                {
                    arts.PlaySound(Female_Die);
                }
            } 
        }
    }
}


void IngameObjectManager::st_point_heal()
{
    if (myCharacters[whosTurn]->get_location() == 0)
    {
        myCharacters[whosTurn]->set_hp(myCharacters[whosTurn]->get_hp() + 5); // 시작점에 갈 시 회복
    }
}


void IngameObjectManager::spawn_objects(int i)
{
    switch (now_chapter)
    {
        case 1: Spawn::chapter_1(&tiles[i], difficulty); break;
        case 2: Spawn::chapter_2(&tiles[i], difficulty); break;
        case 3: Spawn::chapter_3(&tiles[i], difficulty); break;
        case 4: Spawn::chapter_4(&tiles[i], difficulty); break;
        case 5: Spawn::chapter_5(&tiles[i], difficulty); break;
        case 6: Spawn::chapter_6(&tiles[i], difficulty);break;
        default:Spawn::chapter_1(&tiles[i], difficulty);break;
    }
}

void IngameObjectManager::object_turn_setup()
{
    for (auto i = 0; i < questTileCount; i++)
    {
        if (tiles[i].getApex() == false)
        {
            spawn_objects(i);
        }
    }
    
}

void IngameObjectManager::count_down_gold_box()
{
    for (auto& t : tiles)
    {
        if (t.getBox() != nullptr)
        {
            t.getBox()->countDownForGoldBox();
        }
    }
}
void IngameObjectManager::count_PS_E()
{
    for (auto& t : tiles)
    {
        if (t.getEnemy() != nullptr)
        {
            t.getEnemy()->count_PS();
        }
    }
}


void IngameObjectManager::show_portrait()
{
    // clickedTileNum = myCharacters[whosTurn]->getLocation();
    if (myCharacters[whosTurn]->get_effect().type == EffectType::attack)
    {
        for (int i = 0; i < myCharacters[whosTurn]->get_attack_range(); ++i)
        {
            Tile t = tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount];
            if (t.tile_area() == true && MouseIsPressed == true)
            {
                clickedTileNum = (myCharacters[whosTurn]->get_location() + i) % questTileCount;
            }
        }
    }
}

void IngameObjectManager::check_target_exist()
{
    for (int i = 0; i < myCharacters[whosTurn]->get_attack_range(); ++i)
    {
        Tile t = tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount];
        if (t.getBox() != nullptr || t.getEnemy() != nullptr)
        {
            effectTarget = SOMETHING;
        }
    }
}

void IngameObjectManager::update_target_of_effect() /////
{
    check_target_exist();
    if (effectTarget == SOMETHING)
    {
        if (tiles[clickedTileNum].choosePortrait() == "Box")
        {
            effectTarget = BOX;
        }
        if (tiles[clickedTileNum].choosePortrait() == "Enemy")
        {
            effectTarget = ENEMY;
        }
    }
}

void IngameObjectManager::Thief_move()
{
    if (myCharacters[whosTurn]->get_effect().on == false)
    {
        Thief* TF = dynamic_cast<Thief*>(myCharacters[whosTurn]);
        if (TF != nullptr && TF->get_passive_move() == true)
        {
            if (TF->get_move_button().get_button_status() == true)
            {
                arts.PlaySound(sounds::walk);
                if (TF->get_moveNum() > 0)
                {
                    TF->set_location((myCharacters[whosTurn]->get_location() + 1) % questTileCount);
                    TF->set_moveNum(TF->get_moveNum() - 1);
                }
                else if (TF->get_moveNum() < 0)
                {
                    TF->set_location((myCharacters[whosTurn]->get_location() - 1 + questTileCount) % questTileCount);
                    TF->set_moveNum(TF->get_moveNum() + 1);
                    
                }
                st_point_heal();
                TF->get_move_button().set_button_working(false);
                if (TF->get_moveNum() == 0)
                {
                    TF->use_dice();
                    TF->set_passive_move(false);
                }
            }
            else
            {
                TF->get_move_button().set_button_working(true);
            }

        }

    }
}



void IngameObjectManager::get_gold(unsigned long long g)
{
    ingameGold += g;
    events.push_event(EventLog{ "+" + to_string(g), WINDOW_WIDTH * -0.47, -WINDOW_HEIGHT * 0.2,RGB{},25,7 });
}
void IngameObjectManager::get_exp(unsigned long long e)
{
    ingameExp += e;
    events.push_event(EventLog{ "+" + to_string(e), WINDOW_WIDTH * -0.35, -WINDOW_HEIGHT * 0.4,RGB{},25,7 });
}
void IngameObjectManager::level_up(int l)
{
    ingameLevel += l;
    events.push_event(EventLog{ "Level up!", WINDOW_WIDTH * -0.46, -WINDOW_HEIGHT * 0.37,RGB{},40,7 });
}



void IngameObjectManager::box_reward_percent(Box* b)
{
    const auto reward{b->getObject()};
    const int  howMuch{static_cast<int> (b->get_max_hp() * 0.1) };
    if (reward < 50)
    {
        // trap
        myCharacters[whosTurn]->give_damage(2 * howMuch);
        get_exp(howMuch);
    }
    else
    {
        // money
        get_gold(2 * howMuch);
        get_exp(1 * howMuch);
    }
}
void IngameObjectManager::gold_box_reward_percent(Box* b)
{
    const auto reward{b->getObject()};
    const int howMuch{static_cast<int> (b->get_max_hp() * 0.1)};
    if (reward < 90)
    {
        // money
        get_gold( 3 * howMuch);
    }
    else
    {
        // more money
        get_gold(7 * howMuch);
    }
}
void IngameObjectManager::enemy_reward_percentage(Enemy* e)
{
    get_exp(e->get_exp());
    get_gold(e->get_max_gold());
    if( e->get_name() == "DevilKing" && !status.clear)
    {
        inInform.playerMatrial[&devilkingWish]++;
    } else
    {
        for (auto& m : e->get_mat())
        {
            const int percent{ 5 - m->getValue() };
            const int ranNum{ doodle::random(0, 20) };
            if (percent > ranNum)
            {
                inInform.playerMatrial[m]++;
                events.push_event(EventLog{ "Get " + m->getName() + "!!!",e->get_pos().x ,e->get_pos().y,RGB{},25,7 });
            }
        }
    }
}


void IngameObjectManager::reward_update()
{
    for (auto& t : tiles)
    {
        t.BEupdate();
        if (t.getBox() != nullptr)
        {
            if (t.getBox()->isOpen() == true)
            {
                // box reward
                if (t.getBoxOn() == true)
                {
                    box_reward_percent(t.getBox());
                }
                else if (t.getGoldenBoxOn() == true)
                {
                    gold_box_reward_percent(t.getBox());
                }
                t.initialBox();
                t.setBoxOn(false);
                t.setGoldenBoxOn(false);
            }
            else if (t.getBox()->isHide() == true)
            {
                // goldbox is hiding
                t.initialBox();
                t.setGoldenBoxOn(false);
            }
        }
        if (t.getEnemy() != nullptr && t.getEnemy()->is_dead() == true)
        {
            // enemy reward, exp
            arts.PlaySound(sounds::enemy_die);
            enemy_reward_percentage(t.getEnemy());
            t.initialEnemy();
            t.setMonsterOn(false);
        }
    }
}

IngameObjectManager::Cursor::Cursor(string file):cursorimg(file)
{
}

void IngameObjectManager::Cursor::draw()
{
    push_settings();
    apply_translate(get_mouse_x(),get_mouse_y());
    apply_rotate(angle);

    draw_image(cursorimg, 0, 0);
    angle+=0.01;
    pop_settings();
}




void IngameObjectManager::draw_attack_range()
{
    draw_range_col(0, myCharacters[whosTurn]->get_attack_range(), 0x30ff00f0);
    cursor.draw();
}
void IngameObjectManager::draw_range_col(int st, int end, unsigned col)
{
    for (int i = st; i < end; ++i)
    {
        tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount].set_tint_col(col);
    }
    
}


void IngameObjectManager::draw_possib_move_pos(EffectType t)
{
    if (myCharacters[whosTurn]->get_is_move() == false)
    {
        for (auto& d : myCharacters[whosTurn]->get_dice())
        {
            if (t == EffectType::move)
            {
                tiles[(myCharacters[whosTurn]->get_location() + d.get_num()) % questTileCount].set_tint_col(0x808080f0);

            }
            else if(t == EffectType::BACK_MOVE)
            {
                tiles[(myCharacters[whosTurn]->get_location() - d.get_num() + questTileCount) % questTileCount].set_tint_col(0x808080f0);
            }
        }
    }
}





void IngameObjectManager::do_effect()
{
    myCharacters[whosTurn]->initial_effect();
    myCharacters[whosTurn]->use_dice();
    myCharacters[whosTurn]->get_effect().set_on(false);
    clickedTileNum = 0;
}
void IngameObjectManager::do_magic()
{
    myCharacters[whosTurn]->initial_effect();
    usedMagic      = true;
    clickedTileNum = 0;
    myCharacters[whosTurn]->set_attack_range(characterRangeData);
    characterRangeData = {};
    myCharacters[whosTurn]->set_skill_on(false);
}

void IngameObjectManager::attack_to_box()
{
    const auto gd = [&](int tile, int turn, int dice, bool a = false) {
        if (tiles[tile].getBox() != nullptr)
        {
            tiles[tile].getBox()->give_damage(dice *
                myCharacters[turn]->get_dice_factor() *
                myCharacters[turn]->get_ad());
        }
        if (a )
        {
            tiles[tile].getEnemy()->give_damage(dice *
                myCharacters[turn]->get_dice_factor() *
                myCharacters[turn]->get_ad());
        }
        myCharacters[turn]->use_dice();
    };
    Warrior* wa{ dynamic_cast<Warrior*>(myCharacters[whosTurn]) };
    if (wa != nullptr) {
        events.push_event(WarriorEffect{ tiles[clickedTileNum].getBox()->get_pos() });
        gd(clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch);

    }
    Mage* ma{ dynamic_cast<Mage*>(myCharacters[whosTurn]) };
    if (ma != nullptr) {
        events.push_event(MageEffect{ ma->get_position(),tiles[clickedTileNum].getBox()->get_pos(), gd ,clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch });
    }
    Thief* th{ dynamic_cast<Thief*>(myCharacters[whosTurn]) };
    if (th != nullptr) {// thief skill drain
        events.push_event(ThiefEffect{ tiles[clickedTileNum].getBox()->get_pos() });
        if(th->get_pickpocket() == true)
        {
            if (tiles[clickedTileNum].getBox() != nullptr)
            {
                tiles[clickedTileNum].getBox()->give_damage(
                    myCharacters[whosTurn]->get_effect().howMuch 
                    * (3 * (now_chapter / 2 + 1)-1) 
                    *myCharacters[whosTurn]->get_dice_factor() 
                    * myCharacters[whosTurn]->get_ad());
            }
        }
        gd(clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch);

    }
    Archer* ar{ dynamic_cast<Archer*>(myCharacters[whosTurn]) };
    if (ar != nullptr)
    {

        Box* box = tiles[clickedTileNum].getBox();
        box->give_damage(box->get_hp() * ar->get_penetraion());
        if (ar->get_penetraion() > 0 && tiles[clickedTileNum].getEnemy() != nullptr)
        {
            events.push_event(ArcherEffect{ ar->get_position(),tiles[clickedTileNum].getBox()->get_pos() , gd ,clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch, true });
            box->give_damage(box->get_hp() * ar->get_penetraion());
        }
        else
        {
            events.push_event(ArcherEffect{ ar->get_position(),tiles[clickedTileNum].getBox()->get_pos() , gd ,clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch, false });
        }
    }
    myCharacters[whosTurn]->initial_effect();
    myCharacters[whosTurn]->get_effect().set_on(false);
    clickedTileNum = 0;
}

void IngameObjectManager::attack_to_enemy()
{
    const auto gd = [&](int tile, int turn, int dice, bool a = false) {
        if(tiles[tile].getEnemy()!=nullptr)
        {
            tiles[tile].getEnemy()->give_damage(dice*
            myCharacters[turn]->get_dice_factor() *
            myCharacters[turn]->get_ad());
        }
        if(a)
        {
            tiles[tile].getBox()->give_damage(dice *
                myCharacters[turn]->get_dice_factor() *
                myCharacters[turn]->get_ad());
        }
        myCharacters[turn]->use_dice();
    };
    Warrior* wa{dynamic_cast<Warrior*>(myCharacters[whosTurn])};
    if(wa != nullptr)// warrior skill drain
    {
        events.push_event(WarriorEffect{ tiles[clickedTileNum].getEnemy()->get_pos() });
        if(wa->get_drain() == true)
        {
            wa->heal_hp(myCharacters[whosTurn]->get_effect().howMuch *
            myCharacters[whosTurn]->get_dice_factor() *
            myCharacters[whosTurn]->get_ad());
        }
        gd(clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch);
    }
    Mage* ma{ dynamic_cast<Mage*>(myCharacters[whosTurn]) };
    if (ma != nullptr) {
        
        events.push_event(MageEffect{ ma->get_position(),tiles[clickedTileNum].getEnemy()->get_pos() , gd ,clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch });
    }
    Thief* th{dynamic_cast<Thief*>(myCharacters[whosTurn])};
    if(th!=nullptr)
    {
        events.push_event(ThiefEffect{ tiles[clickedTileNum].getEnemy()->get_pos()});
        double percent = random(0.,0.2);
        if (th->get_poison() >= percent)
        {
            tiles[clickedTileNum].getEnemy()->set_PS(th->get_poison() * 0.1);
        }
        gd(clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch);

    }
    Archer* ar{ dynamic_cast<Archer*>(myCharacters[whosTurn]) };
    if (ar != nullptr)
    {
        Enemy* enemy = tiles[clickedTileNum].getEnemy();
        if(ar->get_penetraion() > 0 && tiles[clickedTileNum].getBox() != nullptr)
        {
            events.push_event(ArcherEffect{ ar->get_position(),tiles[clickedTileNum].getEnemy()->get_pos() , gd ,clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch , true});
            enemy->give_damage(enemy->get_hp() * ar->get_penetraion());
        } else
        {
            events.push_event(ArcherEffect{ ar->get_position(),tiles[clickedTileNum].getEnemy()->get_pos() , gd ,clickedTileNum, whosTurn, myCharacters[whosTurn]->get_effect().howMuch , false});
        }
    }

    myCharacters[whosTurn]->initial_effect();
    myCharacters[whosTurn]->get_effect().set_on(false);
    clickedTileNum = 0;
}


bool IngameObjectManager::do_magic_teleport()
{
    auto tp = [&](int turn, int arrive)
    {
        myCharacters[turn]->set_location((myCharacters[turn]->get_location() + arrive) % questTileCount);
    };
    for (int i = 0; i < myCharacters[whosTurn]->get_attack_range(); ++i)
    {
        Tile &t = tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount];

        if (/*Helpers::Collision::objToMouse({t.getTilePos().x, t.getTilePos().y}, t.getTileWidth(), t.getTileHeight()) ==
                true*/t.tile_area() == true &&
            MouseIsPressed == true)
        {
            events.push_event(TeleportEffect(myCharacters[whosTurn]->get_position().x, myCharacters[whosTurn]->get_position().y, t.getTilePos().x, t.getTilePos().y, whosTurn, i, tp));
            return true;
        }
    }
    return false;
}
bool IngameObjectManager::do_magic_attack()
{
    const auto gdb = [&](Tile& tile, int turn, int dmg) {
        if (tile.getBox() != nullptr)
        {
            tile.getBox()->give_damage(dmg * 0.5 *
                myCharacters[turn]->get_ad());
        }
        if (tile.getEnemy() != nullptr){
            tile.getEnemy()->give_damage(dmg * 0.5 *
                myCharacters[turn]->get_ad());
        }
     };
    for (int i = 0; i < myCharacters[whosTurn]->get_attack_range(); ++i)
    {
        Tile &t = tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount];
        if (/*Helpers::Collision::objToMouse({t.getTilePos().x, t.getTilePos().y}, t.getTileWidth(), t.getTileHeight()) ==
                true*/t.tile_area() == true &&
            MouseIsPressed == true)
        {
            events.push_event(FireballEffect(myCharacters[whosTurn]->get_position().x, myCharacters[whosTurn]->get_position().y, t.getTilePos().x, t.getTilePos().y, t,whosTurn, gdb, myCharacters[whosTurn]->get_effect().howMuch));
            return true;
        }
    }
    return false;
}
bool IngameObjectManager::do_magic_resur()
{
    for (int i = 0; i < myCharacters[whosTurn]->get_attack_range(); ++i)
    {
        Tile &t = tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount];
        if (/*Helpers::Collision::objToMouse({t.getTilePos().x, t.getTilePos().y}, t.getTileWidth(), t.getTileHeight()) ==
                true*/t.tile_area() == true &&
            MouseIsPressed == true)
        {
            for (auto& m : myCharacters)
            {
                if (m->get_location() == (myCharacters[whosTurn]->get_location() + i) % questTileCount &&
                    m->get_hp() <= 0)
                {
                    m->set_hp(m->get_max_hp()*0.8);
                    m->getisdead() = false;
                    events.push_event(ResurrectionEfect(m->get_position().x, m->get_position().y));
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

bool IngameObjectManager::do_magic_bomb(int st, int end)
{
    const auto gd = [&](int turn, int i, int st, int end, int dmg)
    {
        for (int r = st; r <= end; ++r)
        {
            Tile& ET{ tiles[(myCharacters[turn]->get_location() + i + r + questTileCount) % questTileCount] };
            if (ET.getBox() != nullptr)
            {
                ET.getBox()->give_damage(dmg* 0.5 *
                    myCharacters[turn]->get_ad());
            }
            if (ET.getEnemy() != nullptr)
            {
                ET.getEnemy()->give_damage(dmg * 0.5 *
                    myCharacters[turn]->get_ad());
            }
        }
    };

    for (int i = 0; i < myCharacters[whosTurn]->get_attack_range(); ++i)
    {
        Tile &t = tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount];

        if (/*Helpers::Collision::objToMouse({t.getTilePos().x, t.getTilePos().y}, t.getTileWidth(), t.getTileHeight()) ==
            true*/t.tile_area() == true)
        {
            if (MouseIsPressed == true)
            {
                events.push_event(BombEffect(t.getTilePos().x, t.getTilePos().y, i, whosTurn, st, end, gd, myCharacters[whosTurn]->get_effect().howMuch));
                return true;
            }
        }
    }
    return false;
}








void IngameObjectManager::ingame_effect_draw()
{
    switch (effectAnimationType)
    {
        case EffectType::attack:
            draw_attack_range();
            draw_effect_range();
            break;
        case EffectType::move:             
            
            break;
        case EffectType::mana: break;
        case EffectType::MAGIC_TELEPORT:
            draw_attack_range();
            draw_effect_range();
            break;
        case EffectType::MAGIC_ATTACK:
            draw_attack_range();
            draw_effect_range();
            break;
        case EffectType::MAGIC_RESURRECTION:
            draw_attack_range();
            draw_effect_range();
            break;
        case EffectType::MAGIC_BOMB:
            draw_attack_range();
            draw_effect_range(myCharacters[whosTurn]->get_effect().EFFStart,
                              myCharacters[whosTurn]->get_effect().EFFEnd);
            break;

        default: 
            break;
    }
}

void IngameObjectManager::draw_effect_range(int st, int end)// 타일 범위 만들기, 
{
    for (int i = 0; i < myCharacters[whosTurn]->get_attack_range(); ++i)
    {
        Tile &t = tiles[(myCharacters[whosTurn]->get_location() + i) % questTileCount];
            
        if (t.tile_area() == true)
        {
            push_settings();
            no_outline();
            set_fill_color(255, 0, 0, 80);
            for (int r = st; r <= end; ++r)
            {
                Tile &ET{tiles[(myCharacters[whosTurn]->get_location() + i + r + questTileCount) % questTileCount]};

                draw_ellipse(ET.getTilePos().x, ET.getTilePos().y, 2*ET.get_tile_circle_leng());
            }
            pop_settings();
        }
        t.click_me();
    }
}