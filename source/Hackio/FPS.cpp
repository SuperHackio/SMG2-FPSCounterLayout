#pragma once

#include "Hackio/FPS.h"

const char* LayoutName = "FPSCounter";

FPSCounter::FPSCounter() : LayoutActor(LayoutName, 0)
{
    
}

void FPSCounter::init(const JMapInfoIter &rIter)
{
	initLayoutManager(LayoutName, 1);
    
    appear();
}

void FPSCounter::movement()
{
    MR::setTextBoxMessageRecursive(this, "FPS", L"FPS:");
    MR::setTextBoxFormatRecursive(this, "FPSCount", L"%00.02f", MR::CurrentFPS);
    
    MR::startAnim(this, VIGetTvFormat() == VI_50FPS ? "Colors50Hz"  : "Colors60Hz", 0);
    MR::setAnimFrameAndStop(this, MR::CurrentFPS, 0);
    
    LayoutActor::movement();
}


void FPSCounter::appear()
{
    LayoutActor::appear();
}

void FPSCounter::kill()
{
}

namespace MR
{
    void CalcFPS()
    {
        f64 TicksPerFrame = VIGetTvFormat() == VI_50FPS ? 1013494.0 : 1013512.0;
        f64 FramesPerSecond = VIGetTvFormat() == VI_50FPS ? 50.0 : 60.0;
        f32 FloatsPerSecond = VIGetTvFormat() == VI_50FPS ? 50.0f : 60.0f;
        f32 MinusOne = FloatsPerSecond - 1.f;
        
        MR::currentTick = static_cast<s32>(OSGetTick());
        f64 difference = static_cast<f64>(MR::currentTick - MR::lastTick);
        lastTick = MR::currentTick;
        if (MR::isNearZero(static_cast<f32>(difference), 0.1f))
        {
            MR::CurrentFPS = 0.f; //safety feature
            return;
        }
        f32 val = static_cast<f32>((TicksPerFrame / difference) * FramesPerSecond);
        MR::CurrentFPS = val > MinusOne ? FloatsPerSecond : val;
    }
    
    
    FPSCounter* getFPSCounterLayout()
    {
        CounterLayoutController* holder = getCounterLayoutController();
        if (holder == NULL)
            return NULL;
        return (FPSCounter*)holder->_4C;
    }
    CounterLayoutController* getCounterLayoutController()
    {
        GameSceneLayoutHolder* holder = MR::getGameSceneLayoutHolder();
        if (holder == NULL)
            return NULL;
        asm("lwz r3, 0x34(r3)"); //me when I can't do what I want in C++
        return; //IGNORE THIS WARNING!
    }
    bool IsExistFPSCounterLayout()
    {
        GameSceneLayoutHolder* holder = MR::getGameSceneLayoutHolder();
        if (holder == NULL)
            return false;
        return getFPSCounterLayout() != 0;
    }
}



//This will be a part of CounterLayoutController
//So we'll need to edit that with Kamek... Great


//Edit CounterLayoutController
kmWrite32(0x80471780, 0x38600050); //li r3, 0x4C -> li r3, 0x50

void CreateFPSCounter(CounterLayoutController* pLayout)
{
	MR::connectToSceneLayout(pLayout);

    pLayout->_4C = new FPSCounter();
    pLayout->_4C->initWithoutIter();
}

//We'll be storing this at 0x4C
kmCall(0x804657A0, CreateFPSCounter); //Add branch to create code


void DoMovementFPSCounter(NerveExecutor* nrv)
{
    nrv->updateNerve();
    if (MR::IsExistFPSCounterLayout())
        MR::getFPSCounterLayout()->movement();
}

void DoDrawFPSCounter()
{
    if (MR::IsExistFPSCounterLayout())
        MR::getFPSCounterLayout()->draw();
}

void DoCalcAnimFPSCounter()
{
    if (MR::IsExistFPSCounterLayout())
        MR::getFPSCounterLayout()->calcAnim();
    
    MR::isStageWorldMap();
}

kmCall(0x804518A8, DoMovementFPSCounter);
kmBranch(0x804589B8, DoDrawFPSCounter);
kmCall(0x80451948, DoCalcAnimFPSCounter);

#if defined TWN || defined KOR
kmBranch(0x804B6B44, MR::CalcFPS);
#else
kmBranch(0x804B6AD4, MR::CalcFPS);
#endif
