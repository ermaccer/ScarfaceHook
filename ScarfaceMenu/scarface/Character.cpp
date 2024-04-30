#include "Character.h"
#include "Misc.h"

CharacterObject* GetMainCharacter()
{
	static CharacterObject* pMainCharacter = nullptr;

	if (pMainCharacter == nullptr)
	{
		static uintptr_t pat = _pattern(PATID_Character_MainCharacter);
		if (pat)
		{
			unsigned int offset = *(unsigned int*)(pat);
			pMainCharacter = *(CharacterObject**)(offset);
		}
	}
	return pMainCharacter;
}

void CharacterObject::AddHealth(float value)
{
	static uintptr_t pat = _pattern(PATID_Character_AddHealth);
	if (pat)
		((void(__thiscall*)(CharacterObject*, float))pat)(this, value);
}

void CharacterObject::SetHealth(int value)
{
	*(int*)((int)this + 348) = value;
}

Vector* CharacterObject::GetBonePosition(int boneId)
{
	static Vector fallback = {};
	static uintptr_t pat = _pattern(PATID_Character_GetBonePosition_Call);
	if (pat)
	{
		static Vector*(__thiscall *funcAddr)(CharacterObject*, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			return funcAddr(this, boneId);
	}
	return &fallback;
}

void CharacterObject::InfiniteAmmo(bool status)
{
	*(bool*)((int)this + 728) = status;
}

void CharacterObject::PlayAnimation(char* name, int priority)
{
	unsigned int hash = _hash(name);

	static uintptr_t pat = _pattern(PATID_Character_PlayAnimation_Call);
	if (pat)
	{
		static void (__thiscall * funcAddr)(CharacterObject*, unsigned int*, int, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			funcAddr(this, &hash, priority, 0);
	}
}

void CharacterObject::ResetAnimation()
{
	static uintptr_t pat = _pattern(PATID_Character_ResetAnimation_Call);
	if (pat)
	{
		static void(__thiscall * funcAddr)(CharacterObject*, bool) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			funcAddr(this, 0);
	}
}

void CharacterObject::SetPhysicalMode(char* name)
{
	*(int*)((int)this + 1052) = _hash(name);
}
