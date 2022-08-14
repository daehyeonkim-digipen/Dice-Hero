/*
File name: IngameSceneHelper.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "Ingame_image.h"


namespace Helpers
{
    namespace Information
    {
        inline void ingameInforation(string info)
        {
            static constexpr double BoardImageScaleX{ 0.65 };
            static constexpr double BoardImageScaleY{ 0.45 };
            push_settings();
            //set_rectangle_mode(RectMode::Corner);
            //set_fill_color(220);
            //draw_rectangle(WINDOW_WIDTH * 0.2, -WINDOW_HEIGHT * 0.25, WINDOW_WIDTH * 0.27, -WINDOW_HEIGHT * 0.2);
            draw_image(objectImage["UI_board_Large_parchment"],
                WINDOW_WIDTH / 2 - objectImage["UI_board_Large_stone"].GetWidth() * BoardImageScaleX / 2,
                -WINDOW_HEIGHT / 2 + objectImage["UI_board_Large_stone"].GetHeight() * BoardImageScaleY / 2,
                objectImage["UI_board_Large_parchment"].GetWidth() * BoardImageScaleX,
                objectImage["UI_board_Large_parchment"].GetHeight() * BoardImageScaleY);
            draw_image(objectImage["Exclamation_Gray"], WINDOW_WIDTH * 0.335, -WINDOW_HEIGHT * 0.2);
            set_fill_color(0);
            set_font_size(25);
            draw_text(info, WINDOW_WIDTH * 0.22, -WINDOW_HEIGHT * 0.3);
            pop_settings();
        }
    }
}
