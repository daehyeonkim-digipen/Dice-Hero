/*
File name: Arts.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "top_header.h"

#include <thread>

class Button;

enum sounds
{
    Click,
    Male_Die,
    Female_Die,
    enemy_die,
    dice,
    token1,
    token2,
    walk,
    getmagic,
    getskill,
    levelup,
    w,
    m1,
    m2,
    t1,
    t2,
    a1,
    a2,
    fb1,
    fb2,
    bm,
    tp1,
    tp2,
    rus
};

struct Arts
{
public:
    std::vector<sf::SoundBuffer>  SoundBuffers{};
    std::vector<sf::Sound>        Sounds{};
    sf::Music                     Play_BGM;
    sf::Music                     Forest_BGM;
    sf::Music                     Desert_BGM;
    sf::Music                     Skypia_BGM;
    sf::Music                     Abyss_BGM;
    sf::Music                     HellGate_BGM;
    sf::Music                     Hell_BGM;
    sf::Music                     Ending_BGM;
    sf::Music*                    nowPlayBGM;

    
    void                         LoadSound(const std::string& file_path);
    void                         PlaySound(int index);
    void                         PlayBGM(sf::Music* input);
    void                         setup();
    void ExtraSetup1();
    void ExtraSetup3();
    void ExtraSetup2();
    void                         barUpdate();
    float&                            getEffectSound() { return effectSound; }
    float&                          getBGMSound() { return bgmSound; }

private:
    struct drag
    {
        bool isClicked = false;
        float rectX = 0;
    };
    drag squareBGM;
    drag squareEffect;
    float effectSound = 50;
    float bgmSound = 50;
};


inline Arts arts;