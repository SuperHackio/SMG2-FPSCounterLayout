# SMG2 FPS Display
This SMG2 mod will add a FPS Display to your game. Very useful for mod developers to make sure that the levels run at a smooth 60fps.


https://user-images.githubusercontent.com/44330283/180044183-d2acde4a-68ba-4d6d-9e8f-df58f9278143.mp4

***Note: Dolphin doesn't emulate game lag, so this layout is useless on emulator.***

## Supported Regions
| Region |  | Notes |
| :---: | :---: | -------- |
| USA | :heavy_check_mark: | NTSC60 |
| PAL | :heavy_check_mark: | Supports PAL50, PAL-M50, and PAL60 (aka. EURGB60).<br/>If using PAL50 or PAL-M50, the max framerate is 50.00 FPS. |
| JAP | :heavy_check_mark: | NTSC60 |
| KOR | :heavy_check_mark: | NTSC60 |
| TAW | :heavy_check_mark: | NTSC60 |

*Note: The debug video mode `DEBUG_PAL` is not supported.*

## How it works
Every frame will have it's FPS calculated and displayed to your screen in the layout on the top of the screen.<br/>The background of the layout will change as the number of frames changes.<br/>Below is a table of what the colours mean:
| Colour Range | Frame Range<br/>(60 FPS) | Frame Range<br/>(50 FPS) | Description |
| :---: | :-----: | :---: | ---- |
| 🔵 -> 🟢 | 60 - 55 | 50 - 45 | This is perfect to good FPS. You can get away with a little bit of green in your mod release. |
| 🟢 -> 🟡 | 55 - 50 | 44 - 40 | This is good to okay FPS. You shouldn't have this in your mod. If you do, it should be as minimal as possible. |
| 🟡 -> 🔴 | 50 - 40 | 40 - 35 | This is okay to bad FPS. You shouldn't have this in your mod at all. |
| 🔴 -> ⚫ | 40 - 00 | 35 - 00 | This is bad to forbidden FPS. Unplayable. Don't release a mod that has this. |

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
Special thanks to [Galaxy Master](https://github.com/MasterofGalaxies) for helping me figure out the math needed to calculate the FPS.
