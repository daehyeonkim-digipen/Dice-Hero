/*
File name: MonsterSpawn.cpp
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "material.h"
#include "monsterSpawn.h"
#include "tile.h"


void Spawn::chapter_1(Tile* t, double difficult)
{
    const auto counter = random(24);
    const double  diff{pow(chapterRoot[now_chapter - 1], difficult)};
    switch (counter)
    {
        case 0: t->spawnBox(2 * diff); break;
        case 1: t->spawnGoldBox(20 * diff); break;
        case 2: t->spawnEnemy(commonMonster.get("Slime "), diff);
            t->give_mat_to_enemy(&stone);
            t->give_mat_to_enemy(&marble);
            t->give_mat_to_enemy(&sapling);
        break;
        case 3:
            t->spawnEnemy(commonMonster.get("Fairy "), diff);
            t->give_mat_to_enemy(&marble);
            t->give_mat_to_enemy(&fairyWing);
            break;
        case 4:
            t->spawnEnemy(commonMonster.get("Wolf "), diff);
            t->give_mat_to_enemy(&stone);
            t->give_mat_to_enemy(&firewood);
            t->give_mat_to_enemy(&wolfSkin);
            break;
        case 5:
        case 6:
        default: break;
    }
}
void Spawn::chapter_2(Tile* t, double difficult) {
    const auto counter = random(24);
    const double  diff{ pow(chapterRoot[now_chapter - 1], difficult-10) };
    switch (counter)
    {
        case 0: t->spawnBox(27 * diff); break;
        case 1: t->spawnGoldBox(270 * diff); break;
        case 2:
            t->spawnEnemy(commonMonster.get("Mummy "), diff);
            t->give_mat_to_enemy(&mummyBandage);
            t->give_mat_to_enemy(&oasisWater);
            break;
        case 3:
            t->spawnEnemy(commonMonster.get("Scorpion "), diff);
            t->give_mat_to_enemy(&scorpionClaw);
            t->give_mat_to_enemy(&scorpionSting);
            break;
        case 4:
            t->spawnEnemy(commonMonster.get("Cactus "), diff);
            t->give_mat_to_enemy(&cactusThorn);
            t->give_mat_to_enemy(&oasisWater);
            t->give_mat_to_enemy(&cactusFlower);
            break;
        case 5:
        case 6:
        default: break;
    }
}
void Spawn::chapter_3(Tile* t, double difficult) {

    const auto counter = random(18);
    const double  diff{ pow(chapterRoot[now_chapter - 1], difficult - 20) };
    switch (counter)
    {
        case 0: t->spawnBox(150 * diff); break;
        case 1: t->spawnGoldBox(1500 * diff); break;
        case 2:
            t->spawnEnemy(commonMonster.get("Steel Alloy Guard "), diff);
            t->give_mat_to_enemy(&lubricant);
            t->give_mat_to_enemy(&battery);
            t->give_mat_to_enemy(&titanAlloy);
            t->give_mat_to_enemy(&algorithmCPU);
            break;
        case 3:
            t->spawnEnemy(commonMonster.get("Steel Auto Turret "), diff);
            t->give_mat_to_enemy(&battery);
            t->give_mat_to_enemy(&robotScrew);
            t->give_mat_to_enemy(&autoGunBarrel);
            t->give_mat_to_enemy(&algorithmCPU);
            break;
        case 4: break;
        case 5:
        case 6:
        default: break;
    }
}
void Spawn::chapter_4(Tile* t, double difficult) {
    const auto counter = random(24);
    const double  diff{ pow(chapterRoot[now_chapter - 1], difficult - 24) };
    switch (counter)
    {
        case 0: t->spawnBox(1800 * diff); break;
        case 1: t->spawnGoldBox(18000 * diff); break;
        case 2: 
            t->spawnEnemy(commonMonster.get("Sea Snake "), diff);
            t->give_mat_to_enemy(&hydraTeeth);
            t->give_mat_to_enemy(&fragmentofWreck);
            t->give_mat_to_enemy(&pearl);
            break;
        case 3:
            t->spawnEnemy(commonMonster.get("The Soul of a Shipwreck "), diff);
            t->give_mat_to_enemy(&fragmentofSoul);
            break;
        case 4: 
            t->spawnEnemy(commonMonster.get("Himantolophus "), diff);
            t->give_mat_to_enemy(&fragmentofWreck);
            t->give_mat_to_enemy(&cephalopodInk);
            t->give_mat_to_enemy(&esca);
            
            break;
        case 5:
        case 6:
        default: break;
    }
}

void Spawn::chapter_5(Tile* t, double difficult) {
    const auto counter = random(24);
    const double  diff{ pow(chapterRoot[now_chapter - 1], difficult - 32) };
    switch (counter)
    {
        case 0: t->spawnBox(50000 * diff); break;
        case 1: t->spawnGoldBox(500000 * diff); break;
        case 2: 
            t->spawnEnemy(commonMonster.get("Imp "), diff);
            t->give_mat_to_enemy(&impSkull);
            t->give_mat_to_enemy(&soul);
            t->give_mat_to_enemy(&hellOre);
            t->give_mat_to_enemy(&diamond);
        break;
        case 3:
            t->spawnEnemy(commonMonster.get("Hound of Hell "), diff);
            t->give_mat_to_enemy(&soul);
            t->give_mat_to_enemy(&hellOre);
            break;
        case 4: 
            t->spawnEnemy(commonMonster.get("Mimic "), diff);
            t->give_mat_to_enemy(&soul);
            t->give_mat_to_enemy(&hellOre);
            t->give_mat_to_enemy(&mimicRing);
            t->give_mat_to_enemy(&mimicMap);
            t->give_mat_to_enemy(&diamond);
        break;
        case 5:
        case 6:
        default: break;
    }
}
void Spawn::chapter_6(Tile* t, double difficult) {
    const auto counter = random(24);
    const double  diff{ pow(chapterRoot[now_chapter-1], difficult - 37) };
    switch (counter)
    {
    case 0: t->spawnBox(1000000 * diff); break;
    case 1: t->spawnGoldBox(10000000 * diff); break;
    case 2: 
        t->spawnEnemy(commonMonster.get("Efreet "), diff);
        t->give_mat_to_enemy(&hellfire);
        t->give_mat_to_enemy(&sulfur);
        t->give_mat_to_enemy(&efreetLamp);
        break;
    case 3:
        t->spawnEnemy(commonMonster.get("Devil "), diff);
        t->give_mat_to_enemy(&sulfur);
        t->give_mat_to_enemy(&sinnerBlood);
        t->give_mat_to_enemy(&devilClaw);
        break;
    case 4: 
        t->spawnEnemy(commonMonster.get("Basilisk "), diff);
        t->give_mat_to_enemy(&sulfur);
        t->give_mat_to_enemy(&hellfire);
        t->give_mat_to_enemy(&sinnerBlood);
        t->give_mat_to_enemy(&basiliskEye);
        break;
    case 5:
    case 6:
    default: break;
    }
}


