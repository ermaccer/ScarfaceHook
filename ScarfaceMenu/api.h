#pragma once
#include "scarface/Vector.h"

extern "C" __declspec(dllexport) bool ScarfaceHook_GetMenuActive();
extern "C" __declspec(dllexport) void ScarfaceHook_GetPlayerPosition(Vector* out);
