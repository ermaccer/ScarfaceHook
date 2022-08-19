#include "hooks.h"
#include "scarface/Camera.h"
#include "scarface/TimeOfDay.h"
#include "utils/MemoryMgr.h"
#include "plugin/ScarfaceMenu.h"

using namespace Memory::VP;

void hooks::Init()
{
	Patch(0x746D40, &Camera::SetPosition);
	Patch(0x747008, &Camera::SetPosition);
	Patch(0x747138, &Camera::SetPosition);
	Patch(0x747208, &Camera::SetPosition);
	Patch(0x7472E0, &Camera::SetPosition);
	Patch(0x7473B0, &Camera::SetPosition);
	InjectHook(0x5EC412, &TODObject::Hook_TODObject_Constructor);
	Patch(0x769658, &Camera::sub_69EA90);
	Patch(0x76A6E8, &Camera::sub_69EA90);
	Patch(0x76B5C0, &Camera::sub_69EA90);
}

void hooks::DisableInput()
{
	Patch<char>(0x57AB88, 0x74);
}

void hooks::DisableMouse()
{
	Patch<char>(0x55EABF, 0x74);
}

void hooks::EnableInput()
{
	Patch<char>(0x57AB88, 0x75);
}

void hooks::EnableMouse()
{
	Patch<char>(0x55EABF, 0x75);
}
