# SMG2 FPS Display
This SMG2 mod will add a FPS Display to your game. Very useful for mod developers to make sure that the levels run at a smooth 60fps.


https://user-images.githubusercontent.com/44330283/180044183-d2acde4a-68ba-4d6d-9e8f-df58f9278143.mp4

***Note: Dolphin doesn't emulate game lag, so this layout is useless on emulator.***

## Supported Regions
The following regions and video modes are supported:
| Region | TV Type / TV Resolution |
| :---: | -------- |
| USA | `Standard TV (480i)` <br/>`EDTV or HDTV (480p)` |
| PAL | `50Hz (576i)`<br/>`60Hz (480i)`<br/>`EDTV or HDTV (480p)` |
| JAP | `プログレッシブ`<br/>`インターレース` |
| KOR | `프로그레시브`<br/>`인터레이스` |
| TAW | `プログレッシブ`<br/>`インターレース` |


## How it works
Every frame will have it's FPS calculated and displayed to your screen in the layout on the top of the screen.<br/>The background colour of the layout will change as the number of frames changes.<br/>Below is a table of what the colours mean:
| Colour Range | Frame Range<br/>(60 FPS) | Frame Range<br/>(50 FPS) | Description |
| :---: | :-----: | :---: | ---- |
| 🔵 -> 🟢 | 60 - 55 | 50 - 45 | This is the perfect range. If you mod ticks inbetween here, you should be good to go. |
| 🟢 -> 🟡 | 55 - 50 | 45 - 40 | This is a good range. Even vanilla SMG2 drops this low at times. Your mod can drop to this range at times, but preferably as rare as possible. |
| 🟡 -> 🔴 | 50 - 40 | 40 - 35 | This range is rather bad. While SMG2 does appear to drop to 40 FPS at exceptional occurences, you really don't want this to happen in your mod. |
| 🔴 -> ⚫ | 40 - 00 | 35 - 00 | Reaching this range is an achievement in its own regard. |

## Supported Extensions
- [Galaxy Level Engine](https://github.com/SuperHackio/GalaxyLevelEngine) :heavy_check_mark:
- [SMG2-Project-Template](https://github.com/SunakazeKun/SMG2-Project-Template) :heavy_check_mark:
(You will need to compile Project Template yourself to include the FPS counter)

## Build Instructions
This mod requires **[Syati](https://github.com/SunakazeKun/Syati)**.

Clone Syati, then clone this repository. Once cloned, merge the contents of this repository into Syati's folder.</br>
If prompted to replace files, click "Yes".</br>
You also need the **CodeWarror Compiler (4.3.0.182)** and **[Kamek](https://github.com/Treeki/Kamek).**

Syati will come with some pre-made source files, you may delete those if you want (but do not delete init.cpp).

On the [Releases](https://github.com/SuperHackio/SMG2-FPSCounterLayout/releases) page, you can find a pre-compile file. This is for hacks that don't use any other Syati code (like Project Template).

## Special Thanks
to [Galaxy Master](https://github.com/MasterofGalaxies) for helping me figure out the math needed to calculate the FPS.
