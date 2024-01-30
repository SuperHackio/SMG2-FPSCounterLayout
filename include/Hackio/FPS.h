#pragma once

#include "syati.h"
#include "revolution/vi.h"

#define VI_50FPS (VI_PAL || VI_MPAL)

class FPSCounter : public LayoutActor
{
public:
    FPSCounter();

    virtual void init(const JMapInfoIter& rIter);
    virtual void movement();


    virtual void appear();
    virtual void kill();
};

class GameSceneLayoutHolder;
namespace MR
{
    s32 lastTick;
    s32 currentTick;
    f32 CurrentFPS;
    //0 = Default
    //1 = Precise
    //2 = Rounded
    u8 RoundMode;

    void CalcFPS();
    FPSCounter* getFPSCounterLayout();
    CounterLayoutController* getCounterLayoutController();
    bool IsExistFPSCounterLayout();

    //this should be in Syati...
    GameSceneLayoutHolder* getGameSceneLayoutHolder();
    void setAnimFrameAndStop(LayoutActor*, f32, u32);
}