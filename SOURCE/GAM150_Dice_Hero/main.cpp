// ReSharper disable All
#include "main_header.h"
#include "GameDataManager.h"
#include "crtdbg.h"
#include <cstdlib>

#include <thread>
#define _CRTDBG_MAP_ALLOC

#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

int main(void) try
 {
    //sortMaterials();
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    

    std::chrono::time_point now{ std::chrono::system_clock::now() };
    std::chrono::time_point lastTick{ std::chrono::system_clock::now() };

    create_window("Dice Hero by Team MuYaHo", WINDOW_WIDTH, WINDOW_HEIGHT);
    set_frame_of_reference(FrameOfReference::RightHanded_OriginCenter);
    set_rectangle_mode(RectMode::Center);
    set_image_mode(RectMode::Center);
    set_image_mode(RectMode::Center);
    clear_background(0);
    Image logo{ "assets/digipen.png" };
    draw_image(logo,0,0);
    const int gameFont = create_distance_field_bitmap_font("assets/Boogaloo-Regular.fnt");
    set_font(gameFont);
    update_window();

    auto SetUP1 = [&]()
    {
        arts.ExtraSetup1();
        arts.ExtraSetup2();
        arts.ExtraSetup3();
    };
    auto SetUP2 = [&]()
    {
        ButtonImage::imageSet();
        ItemImage::equipmentImageSet1();
    };
    auto SetUP3 = [&]()
    {
        data::readData();
    };
    auto SetUP4 = [&]()
    {
        mainUIImage::imageSet();
        
    };
    auto SetUP5 = [&]()
    {
        ItemImage::imageSet();
        IngameImage::imageSet();
    };
    auto SetUP6 = [&]()
    {
        ItemImage::equipmentImageSet2();
    };

    now = { std::chrono::system_clock::now() };
    cout << std::chrono::duration<double>(now - lastTick).count() << endl;
    lastTick = { std::chrono::system_clock::now() };

    std::thread load_t1(SetUP1),
        load_t2(SetUP2),
        load_t3(SetUP3);

    load_t1.join();
    load_t2.join();
    load_t3.join();

    std::thread load_t4(SetUP4),
    load_t5(SetUP5),
    load_t6(SetUP6);

    now = { std::chrono::system_clock::now() };
    cout << std::chrono::duration<double>(now - lastTick).count() << endl;
    lastTick = { std::chrono::system_clock::now() };


    //original load
    //IngameImage::imageSet();
    //ButtonImage::imageSet();
    //mainUIImage::imageSet();
    //ItemImage::imageSet();
    //data::readData();
    sortEssence();

    arts.setup();

    
    load_t4.join();
    load_t5.join();
    load_t6.join();


    now = { std::chrono::system_clock::now() };
    cout << std::chrono::duration<double>(now - lastTick).count()<<endl;
    lastTick = { std::chrono::system_clock::now() };
    std::chrono::system_clock::time_point fpsCalcTime{lastTick};
    int                     frameCount{};
    while (is_window_closed() == false) // main.cpp
    {                                   // frame lock
        now = { std::chrono::system_clock::now() };
        double                  dt{std::chrono::duration<double>(now - lastTick).count()};
        static constexpr int          TargetFPS{30};
        if (dt > 1. / TargetFPS)
        {
            if(dt > 2. / TargetFPS)
            {
                dt = 1. / TargetFPS;
            }
            sceneChanger();
            update_window();
            clear_background(255);

            if (nowScene->get_is_scene_set() == false)
            {
                nowScene->setting();
            }
            nowScene->update();
            nowScene->draw();

            events.Do();
            wasMousePressed = MouseIsPressed;

            ++frameCount;
            lastTick = now;
            if (frameCount > TargetFPS*5)
            {
                const double fpsCalc{std::chrono::duration<double>(now - fpsCalcTime).count()};
                const double averageFrameRate{frameCount / (fpsCalc)};
                cout<<("FPS:  " + std::to_string(averageFrameRate))<<endl;
                frameCount  = 0;
                fpsCalcTime = lastTick;
            }

        }
    }
    PlayerData::Instance().saveData();
    IngameImage::imageDelete();
    ButtonImage::imageDelete();
    ItemImage::imageClear();
    mainUIImage::imageClear();

    if (load_t1.joinable())load_t1.detach();
    if (load_t2.joinable())load_t2.detach();
    if (load_t3.joinable())load_t3.detach();
    if (load_t4.joinable())load_t4.detach();
    if (load_t5.joinable())load_t5.detach();
    if (load_t6.joinable())load_t6.detach();

    _CrtDumpMemoryLeaks();
	return 0; 
}
catch (exception& e)
{
    cerr << "Error: " << e.what() << endl;
    return -1;
}

void on_mouse_pressed(MouseButtons button)
{
    if (button == MouseButtons::Left)
    {
        if (nowScene != nullptr)
        {
            arts.PlaySound(Click);

        }
    }
}



void on_mouse_released(MouseButtons button)
{
    if (button == MouseButtons::Left)
    {

        events.push_event(clickEffect{get_mouse_x(),get_mouse_y()});
        //events.push_event(EventLog{"!", get_mouse_x(), get_mouse_y()});
        //events.push_event(EventLog{"Level UP", get_mouse_x(), get_mouse_y()});
        //events.push_event(EventLog{"Test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", get_mouse_x(), get_mouse_y()});
    }
}

