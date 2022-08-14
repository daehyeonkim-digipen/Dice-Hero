/*
File name: ingame_image.h
Project name: Dice Hero
Author(s): Major - Junsu Jang, minor - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"
inline map<string,vector<Image>> enemyImage{};
inline map<string, Image> boxImage{};
inline map<string, Image> objectImage{};
inline map<string, Image>        backgroundImage{};
inline map<string, Image>        characterImage{};
inline map<int, Image>           tileImage{};
inline map<string, vector<Image>> WarriorAttackImage{};
inline map<string, vector<Image>> MageAttackImage{};
inline map<string, vector<Image>> ThiefAttackImage{};
inline map<string, vector<Image>> ArcherAttackImage{};
inline map<string, vector<Image>> MagicImage{};
inline map<string, Image>         magicImage2{};
inline map<string, Image>      profileImage{};



//inline map<string, vector<Image>> Essence{};

namespace IngameImage
{
    inline void imageSet() //실험용
    {
        for (int i = 1; i < 7; ++i)
        {
            WarriorAttackImage["Normal"].emplace_back(Image{ "assets/Effect/Sprite/Warrior/classic_0" + to_string(i) + ".png" });
        }
        for (int i = 1; i < 8; ++i)
        {
            MageAttackImage["Normal"].emplace_back(Image{ "assets/Effect/Sprite/Mage/normal_" + to_string(i) + ".png" });
            MageAttackImage["Hit"].emplace_back(Image{ "assets/Effect/Sprite/Mage/hit_" + to_string(i) + ".png" });
        }
        for (int i = 1; i < 7; ++i)
        {
            ThiefAttackImage["Normal"].emplace_back(Image{ "assets/Effect/Sprite/Thief/normal_" + to_string(i) + ".png" });
        }
        for (int i = 1; i < 7; ++i)
        {
            ArcherAttackImage["Normal"].emplace_back(Image{ "assets/Effect/Sprite/Archer/normal_" + to_string(i) + ".png" });
        }

        for (int i = 1; i < 6; i++)
        {
            MagicImage["Fireball"].emplace_back(Image("assets/Effect/Sprite/Magic/Fireball_" + to_string(i) + ".png"));
        }

        magicImage2["bombexp"] = Image("assets/Effect/Sprite/Magic/bomb.png");
        magicImage2["teleport"] = Image("assets/Effect/Sprite/Magic/teleport.png");
        magicImage2["resurrection"] = Image("assets/Effect/Sprite/Magic/resur.png");

        for (int i = 1; i < 7; ++i)
        {
            enemyImage["Slime "].emplace_back(Image{"assets/Blue_slime/Slime_blue_animation" + to_string(i) + ".png"});
        }
        for (int i = 1; i < 15; ++i)
        {
            enemyImage["Mimic "].emplace_back(Image{"assets/mimic/mimic" + to_string(i) + ".png"});
        }

        enemyImage["Wolf "].emplace_back(Image{ "assets/monsters/wolf.png" });
        enemyImage["Fairy "].emplace_back(Image{ "assets/monsters/fairy.png" });
        enemyImage["Scorpion "].emplace_back(Image{ "assets/monsters/Scorpion.png" });
        enemyImage["Cactus "].emplace_back(Image{ "assets/monsters/Cactus.png" });
        enemyImage["Mummy "].emplace_back(Image{ "assets/monsters/mummy.png" });
        enemyImage["Imp "].emplace_back(Image{ "assets/monsters/imp.png" });
        enemyImage["Sea Snake "].emplace_back(Image{ "assets/monsters/Sea Snake.png" });
        enemyImage["Himantolophus "].emplace_back(Image{"assets/materials/chapter4/esca.png"});
        enemyImage["Steel Alloy Guard "].emplace_back(Image{ "assets/monsters/Steel Alloy Guard.png" });
        enemyImage["Steel Auto Turret "].emplace_back(Image{ "assets/monsters/Steel Auto Turret.png" });
        enemyImage["The Soul of a Shipwreck "].emplace_back(Image{ "assets/monsters/The Soul of a Shipwreck.png" });
        enemyImage["Hound of Hell "].emplace_back(Image{ "assets/monsters/Hound of Hell.png" });
        enemyImage["Efreet "].emplace_back(Image{ "assets/monsters/Efreet.png" });
        enemyImage["Devil "].emplace_back(Image{ "assets/monsters/Devil.png" });
        enemyImage["Basilisk "].emplace_back(Image{ "assets/monsters/Basilisk.png" });



        enemyImage["Ent"].emplace_back(Image{ "assets/monsters/ent.png" });
        enemyImage["Genie"].emplace_back(Image{ "assets/monsters/Genie.png" });
        enemyImage["Titan"].emplace_back(Image{ "assets/monsters/titan.png" });
        enemyImage["KraKen"].emplace_back(Image{ "assets/monsters/kraken.png" });
        enemyImage["Black Dragon"].emplace_back(Image{ "assets/monsters/BlackDragon.png" });
        enemyImage["DevilKing"].emplace_back(Image{ "assets/monsters/DevilKing.png" });
        for (int i = 1;i <= 5;++i)
        {
            enemyImage["BossAttack"].emplace_back(Image{"assets/Effect/Sprite/Boss/Fire-Wrath__0"+to_string(i)+".png"});
        }
        for (int i = 16;i <= 20;++i)
        {
            enemyImage["Fire"].emplace_back(Image{ "assets/Effect/Sprite/Boss/Fire-Wrath__" + to_string(i) + ".png" });
        }

        boxImage["box"]               = Image{"assets/box/basic/box.png"};
        boxImage["goldBox"]           = Image{"assets/box/gold/Goldbox.png"};
        enemyImage["Box"].emplace_back(boxImage["box"]);
        enemyImage["Gold box"].emplace_back(boxImage["goldBox"]);


        objectImage["paper"]          = Image{"assets/paper/paper.png"};
        objectImage["woodenTable"]    = Image{"assets/paper/WoodenTable_cut.png"};
        objectImage["Attack Token"]   = Image{"assets/token/token2.png"};
        objectImage["Move Token"]     = Image{"assets/token/token1.png"};
        objectImage["Mana Token"]     = Image{"assets/token/token3.png"};
        objectImage["blood"] = Image{ "assets/character/blood.png" };
        objectImage["No image"]       = Image{"assets/NoImage/NoImage1.png"};
        objectImage["Magic tower"] = Image{"assets/ingameShop/Magic_tower.png"};
        objectImage["Peddler"] = Image{"assets/ingameShop/ingame_shop_peddler.png"};
        objectImage["Exclamation_Gray"] = Image{ "assets/UI/wooden_board/Exclamation_Gray.png" };
        objectImage["Exclamation_Red"] = Image{ "assets/UI/wooden_board/Exclamation_Red.png" };
        objectImage["UI_board_Large_parchment"] = Image{ "assets/UI/wooden_board/UI_board_Large_parchment.png" };
        objectImage["UI_board_Large_stone"] = Image{ "assets/UI/wooden_board/UI_board_Large_stone.png" };

        backgroundImage["Plane_1"] = Image{"assets/background/greenPlane.png"};
        backgroundImage["Plane_2"] = Image{"assets/background/desert.png"};
        backgroundImage["Plane_3"] = Image{"assets/background/sky.png"};
        backgroundImage["Plane_4"] = Image{ "assets/background/DeepSea.png" };
        backgroundImage["Plane_5"] = Image{ "assets/background/Underground.png" };
        backgroundImage["Plane_6"] = Image{ "assets/background/hell.png" };

        characterImage["Archer"] = Image{ "assets/character/archer1.png" };
        characterImage["Mage"] = Image{ "assets/character/mage1.png" };
        characterImage["Thief"] = Image{ "assets/character/thief1.png" };
        characterImage["Warrior"] = Image{ "assets/character/warrior1.png" };

        profileImage["ArcherProfile"] = Image{"assets/character/archerProfile.png"};
        profileImage["MageProfile"] = Image{"assets/character/mageProfile.png"};
        profileImage["ThiefProfile"] = Image{"assets/character/thiefProfile.png"};
        profileImage["WarriorProfile"] = Image{"assets/character/warriorProfile.png"};


        tileImage[10]      = Image{"assets/UI/tile/tile1-1.png"};
        tileImage[100]     = Image{"assets/UI/tile/tile1-2.png"};
        tileImage[1000]    = Image{"assets/UI/tile/tile1-3.png"};
        tileImage[10000]   = Image{"assets/UI/tile/tile1-4.png"};
        tileImage[100000]  = Image{"assets/UI/tile/tile1-5.png"};
        tileImage[1000000] = Image{"assets/UI/tile/tile1-6.png"};
        tileImage[20]      = Image{"assets/UI/tile/tile2-1.png"};
        tileImage[200]     = Image{"assets/UI/tile/tile2-2.png"};
        tileImage[2000]    = Image{"assets/UI/tile/tile2-3.png"};
        tileImage[20000]   = Image{"assets/UI/tile/tile2-4.png"};
        tileImage[200000]  = Image{"assets/UI/tile/tile2-5.png"};
        tileImage[2000000] = Image{"assets/UI/tile/tile2-6.png"};
        tileImage[30]      = Image{"assets/UI/tile/tile3-1.png"};
        tileImage[300]     = Image{"assets/UI/tile/tile3-2.png"};
        tileImage[3000]    = Image{"assets/UI/tile/tile3-3.png"};
        tileImage[30000]   = Image{"assets/UI/tile/tile3-4.png"};
        tileImage[300000]  = Image{"assets/UI/tile/tile3-5.png"};
        tileImage[3000000] = Image{"assets/UI/tile/tile3-6.png"};
        tileImage[40]      = Image{"assets/UI/tile/tile4-1.png"};
        tileImage[400]     = Image{"assets/UI/tile/tile4-2.png"};
        tileImage[4000]    = Image{"assets/UI/tile/tile4-3.png"};
        tileImage[40000]   = Image{"assets/UI/tile/tile4-4.png"};
        tileImage[400000]  = Image{"assets/UI/tile/tile4-5.png"};
        tileImage[4000000] = Image{"assets/UI/tile/tile4-6.png"};
        tileImage[50]      = Image{"assets/UI/tile/tile5-1.png"};
        tileImage[500]     = Image{"assets/UI/tile/tile5-2.png"};
        tileImage[5000]    = Image{"assets/UI/tile/tile5-3.png"};
        tileImage[50000]   = Image{"assets/UI/tile/tile5-4.png"};
        tileImage[500000]  = Image{"assets/UI/tile/tile5-5.png"};
        tileImage[5000000] = Image{"assets/UI/tile/tile5-6.png"};
        tileImage[60]      = Image{"assets/UI/tile/tile6-1.png"};
        tileImage[600]     = Image{"assets/UI/tile/tile6-2.png"};
        tileImage[6000]    = Image{"assets/UI/tile/tile6-3.png"};
        tileImage[60000]   = Image{"assets/UI/tile/tile6-4.png"};
        tileImage[600000]  = Image{"assets/UI/tile/tile6-5.png"};
        tileImage[6000000] = Image{"assets/UI/tile/tile6-6.png"};
        cout << "Ingame Image Load End" << endl;

    }
    inline void imageDelete()
    {
        enemyImage.clear();
        boxImage.clear();
        objectImage.clear();
        backgroundImage.clear();
        tileImage.clear();
    }
}

