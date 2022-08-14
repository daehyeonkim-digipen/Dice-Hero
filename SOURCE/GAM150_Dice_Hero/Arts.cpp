/*
File name: Arts.cpp
Project name: Dice Hero
Author(s): Major - Daehyeon Kim
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Arts.h"
#include "scene_manager.h"

void Arts::PlaySound([[maybe_unused]]int index)
{
    for (auto& sound : Sounds)
    {
        if (sound.getStatus() != sf::SoundSource::Playing)
        {
            sound.setBuffer(SoundBuffers[index]);
            sound.setVolume(effectSound);
            sound.play();
            return;
        }
    }
    Sounds.emplace_back(SoundBuffers[index]);
    Sounds.back().setVolume(effectSound);
    Sounds.back().play();
}

void Arts::PlayBGM([[maybe_unused]] sf::Music* input)
{
    if(nowPlayBGM != nullptr)
    {
        nowPlayBGM->stop();
    }
    nowPlayBGM = input;
    nowPlayBGM->setLoop(true);
    nowPlayBGM->setVolume(bgmSound);
    nowPlayBGM->play();
}

void Arts::LoadSound([[maybe_unused]] const std::string& file_path)
{
    SoundBuffers.emplace_back();
    sf::SoundBuffer& buffer = SoundBuffers.back();
    if (!buffer.loadFromFile(file_path))
    {
        Helpers::error("failed to load " + file_path);
    }
}

void Arts::setup()
{
    //if (!Play_BGM.openFromFile("assets/Sounds/BGM/Play_BGM.ogg"))
    //{
    //    Helpers::error("Failed to load the music file: assets/Sounds/BGM/Play_BGM.ogg");
    //}
    //if (!Forest_BGM.openFromFile("assets/Sounds/BGM/Forest_BGM.ogg"))
    //{
    //    Helpers::error("Failed to load the music file: assets/Sounds/BGM/Forest_BGM.ogg");
    //}
    //if (!Desert_BGM.openFromFile("assets/Sounds/BGM/Desert_BGM.ogg"))
    //{
    //    Helpers::error("Failed to load the music file: assets/Sounds/BGM/Desert_BGM.ogg");
    //}


    //if (!Skypia_BGM.openFromFile("assets/Sounds/BGM/Skypia_BGM.ogg"))
    //{
    //    Helpers::error("Failed to load the music file: assets/Sounds/BGM/Skypia_BGM.ogg");
    //}
    //if (!Abyss_BGM.openFromFile("assets/Sounds/BGM/Abyss_BGM.ogg"))
    //{
    //    Helpers::error("Failed to load the music file: assets/Sounds/BGM/Abyss_BGM.ogg");
    //}
    //if (!HellGate_BGM.openFromFile("assets/Sounds/BGM/HellGate_BGM.ogg"))
    //{
    //    Helpers::error("Failed to load the music file: assets/Sounds/BGM/HellGate_BGM.ogg");
    //}
    //if (!Hell_BGM.openFromFile("assets/Sounds/BGM/Hell_BGM.ogg"))
    //{
    //    Helpers::error("Failed to load the music file: assets/Sounds/BGM/Hell_BGM.ogg");
    //}
    //
    //
    //
    //LoadSound("assets/Sounds/Effect/Click_Sound.ogg");
    //LoadSound("assets/Sounds/Effect/Male_die.ogg");
    //LoadSound("assets/Sounds/Effect/Female_die.ogg");
    //LoadSound("assets/Effect/Sound/warrior_sound.ogg");
    //LoadSound("assets/Effect/Sound/mage_Sound1.ogg");
    //LoadSound("assets/Effect/Sound/mage_Sound2.ogg");
    //LoadSound("assets/Effect/Sound/thief_Sound1.ogg");
    //LoadSound("assets/Effect/Sound/thief_Sound2.ogg");
    //LoadSound("assets/Effect/Sound/archer_Sound1.ogg");
    //LoadSound("assets/Effect/Sound/archer_Sound2.ogg");
    nowPlayBGM = nullptr;

    cout << "Sound Load End" << endl;

}
void Arts::ExtraSetup1()
{
    if (!Play_BGM.openFromFile("assets/Sounds/BGM/Play_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/Play_BGM.ogg");
    }
    if (!Forest_BGM.openFromFile("assets/Sounds/BGM/Forest_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/Forest_BGM.ogg");
    }
    
    cout << "Sound Load 1 End" << endl;

}
void Arts::ExtraSetup2()
{
    if (!Desert_BGM.openFromFile("assets/Sounds/BGM/Desert_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/Desert_BGM.ogg");
    }
    if (!Skypia_BGM.openFromFile("assets/Sounds/BGM/Skypia_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/Skypia_BGM.ogg");
    }
    if (!Abyss_BGM.openFromFile("assets/Sounds/BGM/Abyss_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/Abyss_BGM.ogg");
    }
    if (!HellGate_BGM.openFromFile("assets/Sounds/BGM/HellGate_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/HellGate_BGM.ogg");
    }
    if (!Hell_BGM.openFromFile("assets/Sounds/BGM/Hell_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/Hell_BGM.ogg");
    }
    if (!Ending_BGM.openFromFile("assets/Sounds/BGM/Ending_BGM.ogg"))
    {
        Helpers::error("Failed to load the music file: assets/Sounds/BGM/Ending_BGM.ogg");
    }
    cout << "Sound Load 2 End" << endl;

}
void Arts::ExtraSetup3()
{
    LoadSound("assets/Sounds/Effect/Click_Sound.ogg");
    LoadSound("assets/Sounds/Effect/Male_die.ogg");
    LoadSound("assets/Sounds/Effect/Female_die.ogg");
    LoadSound("assets/Sounds/Effect/enemy_die.ogg");
    LoadSound("assets/Sounds/Effect/roll_sound.ogg");
    LoadSound("assets/Sounds/Effect/token_sound1.ogg");
    LoadSound("assets/Sounds/Effect/token_sound2.ogg");
    LoadSound("assets/Sounds/Effect/walk_sound.ogg");
    LoadSound("assets/Sounds/Effect/getmagic_sound.ogg");
    LoadSound("assets/Sounds/Effect/learnskill_sound.ogg");
    LoadSound("assets/Sounds/Effect/levelup_sound.ogg");
    LoadSound("assets/Effect/Sound/warrior_sound.ogg");
    LoadSound("assets/Effect/Sound/mage_Sound1.ogg");
    LoadSound("assets/Effect/Sound/mage_Sound2.ogg");
    LoadSound("assets/Effect/Sound/thief_Sound1.ogg");
    LoadSound("assets/Effect/Sound/thief_Sound2.ogg");
    LoadSound("assets/Effect/Sound/archer_Sound1.ogg");
    LoadSound("assets/Effect/Sound/archer_Sound2.ogg");
    LoadSound("assets/Effect/Sound/fireball_Sound1.ogg");
    LoadSound("assets/Effect/Sound/fireball_Sound2.ogg");
    LoadSound("assets/Effect/Sound/bomb_Sound.ogg");
    LoadSound("assets/Effect/Sound/teleport_Sound1.ogg");
    LoadSound("assets/Effect/Sound/teleport_Sound2.ogg");
    LoadSound("assets/Effect/Sound/resur_Sound.ogg");
    cout << "Sound Load 3 End" << endl;
}



void Arts::barUpdate()
{
    const double BGMBarY = WINDOW_HEIGHT * 0.05;
    const double EffectBarY = -WINDOW_HEIGHT * 0.15;
    draw_rectangle(0, BGMBarY, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.03); // basic bar
    draw_rectangle(0, EffectBarY, WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.03); // basic bar
    squareBGM.rectX = Helpers::math::p5js_map(bgmSound, 0.f, 100.f, -WINDOW_WIDTH * 0.15f, WINDOW_WIDTH * 0.15f);
    squareEffect.rectX = Helpers::math::p5js_map(effectSound, 0.f, 100.f, -WINDOW_WIDTH * 0.15f, WINDOW_WIDTH * 0.15f);
    if (Helpers::Collision::objToMouse({ squareBGM.rectX, BGMBarY }, WINDOW_WIDTH * 0.03, WINDOW_WIDTH * 0.03) == true && MouseIsPressed)
    {
        squareBGM.isClicked = true;
    }
    if (Helpers::Collision::objToMouse({ squareEffect.rectX, EffectBarY }, WINDOW_WIDTH * 0.03, WINDOW_WIDTH * 0.03) == true && MouseIsPressed)
    {
        squareEffect.isClicked = true;
    }
    if(wasMousePressed && !MouseIsPressed)
    {
        squareBGM.isClicked = false;
        squareEffect.isClicked = false;
    }
    if(squareBGM.isClicked)
    {
        squareBGM.rectX = static_cast<float>(get_mouse_x());
    }
    if (squareEffect.isClicked)
    {
        squareEffect.rectX = static_cast<float>(get_mouse_x());
    }
    if (squareBGM.rectX > WINDOW_WIDTH * 0.15f)
    {
        squareBGM.rectX = WINDOW_WIDTH * 0.15f;
    }
    else if (squareBGM.rectX < -WINDOW_WIDTH * 0.15f)
    {
        squareBGM.rectX = -WINDOW_WIDTH * 0.15f;
    }
    if (squareEffect.rectX > WINDOW_WIDTH * 0.15f)
    {
        squareEffect.rectX = WINDOW_WIDTH * 0.15f;
    }
    else if (squareEffect.rectX < -WINDOW_WIDTH * 0.15f)
    {
        squareEffect.rectX = -WINDOW_WIDTH * 0.15f;
    }
    push_settings();
    set_fill_color(chapterColor[now_chapter][3], chapterColor[now_chapter][4],
                   chapterColor[now_chapter][5]);
    draw_rectangle(squareBGM.rectX, BGMBarY, WINDOW_WIDTH * 0.03, WINDOW_WIDTH * 0.03); //pitch bar
    draw_rectangle(squareEffect.rectX, EffectBarY, WINDOW_WIDTH * 0.03, WINDOW_WIDTH * 0.03); //pitch bar
    set_font_size(HEADFONTSIZE);
    no_outline();
    draw_text("BGM volume", -WINDOW_WIDTH * 0.15, WINDOW_HEIGHT * 0.1);
    draw_text("Effect volume", -WINDOW_WIDTH * 0.15, -WINDOW_HEIGHT * 0.1);
    effectSound = Helpers::math::p5js_map(squareEffect.rectX, -WINDOW_WIDTH * 0.15f, WINDOW_WIDTH * 0.15f, 0.f, 100.f);
    bgmSound = Helpers::math::p5js_map(squareBGM.rectX, -WINDOW_WIDTH * 0.15f, WINDOW_WIDTH * 0.15f, 0.f, 100.f);
    nowPlayBGM->setVolume(bgmSound);
    pop_settings();
}

