#include "ControllerInput.h"

int& dword_8251A4 = *(int*)0x8251A4;

ControllerInput& input = *(ControllerInput*)(0x825AD8);

int GetDeviceID(const char* name, int unk, int flag)
{
    if ((dword_8251A4 & flag) == 0)
        dword_8251A4 |= flag;
    return  ((float(__cdecl*)(const char*, int))0x6DC190)(name, unk);
}

ControllerInput& GetControllerInput()
{
    return input;
}

float ControllerInput::GetFloatValue(char* device)
{
    int devId = GetDeviceID(device, 0, 256);
	return ((float(__thiscall*)(ControllerInput*, int))0x42C690)(this, devId);
}
