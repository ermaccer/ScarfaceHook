#include "EffectsObject.h"

void EffectsObject::CreateEffect(int type, int unk, int unk2, Vector* pos, Vector* upMat)
{
	((void(__thiscall*)(EffectsObject*, int, int, int, Vector*, Vector*))0x5E7FD0)(this, type, unk, unk2, pos, upMat);
}

void EffectsObject::PlayPedExplosion(Vector* pos)
{
	((void(__thiscall*)(EffectsObject*, Vector*))0x5E8A70)(this, pos);
}

EffectsObject* EffectsObject::GetInstance()
{
	return ((EffectsObject * (__cdecl*)())0x5E8350)();
}
