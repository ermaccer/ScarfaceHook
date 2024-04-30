#include "EffectsObject.h"

void EffectsObject::CreateEffect(int type, int unk, int unk2, Vector* pos, Vector* upMat)
{
	static uintptr_t pat = _pattern(PATID_EffectsObject_CreateEffect_Call);
	if (pat)
	{
		static int(__thiscall * funcAddr)(EffectsObject*, int, int, int, Vector*, Vector*) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			funcAddr(this, type, unk, unk2, pos, upMat);
	}
}

void EffectsObject::PlayPedExplosion(Vector* pos)
{
	static uintptr_t pat = _pattern(PATID_EffectsObject_PlayPedExplosion);
	if (pat)
		((void(__thiscall*)(EffectsObject*, Vector*))pat)(this, pos);
}

EffectsObject* EffectsObject::GetInstance()
{
	static uintptr_t pat = _pattern(PATID_EffectsObject_GetInstance_Call);
	if (pat)
	{
		static EffectsObject* (__cdecl * funcAddr)() = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			return funcAddr();
	}
	return nullptr;
}
