#include "TimeOfDay.h"
TODObject* TODObject::TOD;

void TODObject::SetTime(int hour, int minute)
{
	((void(__thiscall*)(TODObject*, int, int, int))0x5EC8D0)(this, hour, minute, 0);
}

void TODObject::EnableRain(bool status)
{
	((void(__thiscall*)(TODObject*, bool))0x5EC880)(this, status);
}

TODObject* TODObject::Hook_TODObject_Constructor(int a2, int a3)
{
	TOD = this;
	return ((TODObject * (__thiscall*)(TODObject*, int, int))0x5EC9B0)(this, a2, a3);
}
