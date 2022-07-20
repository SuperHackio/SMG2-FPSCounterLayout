#pragma once

#include "revolution.h"
#include "Game/Screen/LayoutActor.h"

class ItemSwapLayout;
class CounterLayoutController : public LayoutActor {
public:
	static bool isWaitToDisappearCounter(const LayoutActor *);
    
    s32 _2C;
    s8 _30;
    s32 _34;
    s32 _38;
    s32 _3C;
    s32 _40;
    s32 _44;
    s32 _48;
    
    //this one belongs to the a custom layout. Don't add this to Syati lol.
    LayoutActor* _4C;
    
};
