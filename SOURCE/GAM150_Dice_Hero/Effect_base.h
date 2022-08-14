/*
File name: Effect_base.h
Project name: Dice Hero
Author(s): Major - Junsu Jang
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include <list>
#include <memory>

class Effect
{
protected:
    bool animationEnd{false};

public:
    virtual ~Effect() = default;
    virtual void draw() {}
    virtual void update() {}
    friend bool  checkEventDead(std::shared_ptr<Effect> & eff);
};

inline bool checkEventDead(std::shared_ptr<Effect> &eff) { return eff.get()->animationEnd == true; }

class EffectsDrawing
{
    std::list<std::shared_ptr<Effect>> events{};
    std::list<std::shared_ptr<Effect>> eventque{};

    void eventque_manage()//hmmS
    {

    }
    //list effect1(포인터)
		//list int* intp1 -> new someclass()
		//int 
public:
    void Do()
    {
        for (auto& e : events)
        {
            e.get()->update();
            e.get()->draw();
        }
        events.remove_if(checkEventDead);
        eventque_manage();
    }
    template<typename T>
    void push_event(T event)
    {
	    events.push_back(std::make_shared<T>(event));
    }//push_event(new Fireball(정보))
    void clear() { events.clear(); }
    template<typename T>
    void add_event_que(T event){ eventque.push_back(std::make_shared<T>(event)); }
};
//push_event(new fireball())
inline EffectsDrawing events{};