#pragma once

#include "FPS.h"

const char* LayoutName = "FPSCounter";
const char* Pane_PicMode = "PicMode";

//0 = Shown
//1 = Hide requested
//2 = Currently in the process of hiding
//3 = Hiding
//4 = Show Requested
//5 = Currently in the process of showing [UNUSED]
namespace MR
{
    static u8 HiddenStatus = 2;
}

FPSCounter::FPSCounter() : LayoutActor(LayoutName, 0)
{

}

void FPSCounter::init(const JMapInfoIter& rIter)
{
    initLayoutManager(LayoutName, 1);

    MR::createAndAddPaneCtrl(this, Pane_PicMode, 1);

    appear();

    if (MR::HiddenStatus == 1 || MR::HiddenStatus == 2 || MR::HiddenStatus == 3)
    {
        f32 CurFps = 0.0f;
        MR::setTextBoxMessageRecursive(this, "FPS", L"FPS:");
        MR::setTextBoxMessageRecursive(this, "FPSCount", L"--.--");

        MR::startAnim(this, "Hide", 0);
        MR::setAnimFrameAndStop(this, 61.0f, 0);
        MR::HiddenStatus = 3;
    }
}

void FPSCounter::movement()
{
    f32 CurFps;
    s32 CurRM;
    if (MR::HiddenStatus == 1)
    {
        MR::HiddenStatus = 2;
        MR::startAnim(this, "Hide", 0);
        goto Final;
    }
    if (MR::HiddenStatus == 2)
    {
        if (MR::isAnimStopped(this, 0))
            MR::HiddenStatus = 3;
        goto Final;
    }

    if (MR::HiddenStatus == 3)
    {
        if (MR::testCorePadTrigger1(0))
        {
            MR::HiddenStatus = 4;
            MR::startAnim(this, "Show", 0);
        }
        goto Final;
    }

    if (MR::HiddenStatus == 4)
    {
        if (MR::isAnimStopped(this, 0))
            MR::HiddenStatus = 0;
        goto Final;
    }

    CurFps = MR::CurrentFPS;

    MR::setTextBoxMessageRecursive(this, "FPS", L"FPS:");
    MR::setTextBoxFormatRecursive(this, "FPSCount", L"%00.02f", CurFps);

    MR::startAnim(this, VIGetTvFormat() == VI_50FPS ? "Colors50Hz" : "Colors60Hz", 0);
    MR::setAnimFrameAndStop(this, MR::CurrentFPS, 0);


    if (MR::testCorePadTrigger1(0))
        MR::HiddenStatus = 1;


    if (MR::testCorePadTrigger2(0))
    {
        MR::RoundMode++;
        if (MR::RoundMode > 2)
            MR::RoundMode = 0;
    }

    CurRM = MR::RoundMode;
    if (VIGetTvFormat() == VI_50FPS && CurRM == 0)
        CurRM = 3; //50fps edition

    MR::startPaneAnim(this, Pane_PicMode, "Icon", 0);
    MR::setPaneAnimFrameAndStop(this, Pane_PicMode, static_cast<f32>(CurRM), 0);

Final:
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

        if (MR::RoundMode == 2)
        {
            s32 temp = static_cast<s32>(val > MinusOne ? FloatsPerSecond : val);
            MR::CurrentFPS = static_cast<f32>(temp);
            return;
        }
        if (MR::RoundMode == 1)
        {
            MR::CurrentFPS = val;
            return;
        }

        MR::CurrentFPS = val > MinusOne ? FloatsPerSecond : val;
    }


    FPSCounter* getFPSCounterLayout()
    {
        register CounterLayoutController* holder = getCounterLayoutController();
        if (holder == NULL)
            return NULL;
        register FPSCounter* MyLayout;
        __asm {
            lwz MyLayout, 0x4C(holder)
        }
        return MyLayout;
    }
    CounterLayoutController* getCounterLayoutController()
    {
        register GameSceneLayoutHolder* holder = MR::getGameSceneLayoutHolder();
        if (holder == NULL)
            return NULL;
        register CounterLayoutController* controller = NULL;
        __asm
        {
            lwz controller, 0x34(holder)
        }
        return controller;
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

void CreateFPSCounter(register CounterLayoutController* pLayout)
{
    MR::connectToSceneLayout(pLayout);

    if (!MR::isFileExist("/LayoutData/FPSCounter.arc", true))
    {
        register LayoutActor* f = NULL;
        __asm
        {
            stw f, 0x4C(pLayout)
        }
        return;
    }
    register LayoutActor* pFPS = new FPSCounter();
    __asm
    {
        stw pFPS, 0x4C(pLayout)
    }
    pFPS->initWithoutIter();
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