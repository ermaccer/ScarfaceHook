#include "Character.h"

CharacterObject* GetMainCharacter()
{
	return *(CharacterObject**)(0x825A78);
}

void CharacterObject::AddHealth(float value)
{
	((void(__thiscall*)(CharacterObject*, float))0x577650)(this, value);
}

Vector* CharacterObject::GetBonePosition(int boneId)
{
	return 	((Vector * (__thiscall*)(CharacterObject*, int))0x572480)(this, boneId);
}

int CharacterObject::GetCurrentWeapon()
{
	return 	((int(__thiscall*)(CharacterObject*))0x5882A0)(this);
}

void CharacterObject::RemoveWeaponFromInventory(int weapon)
{
	((void(__thiscall*)(CharacterObject*))0x5875D0)(this);
}

int CharacterObject::IsCharacterInCar()
{
	return ((int(__thiscall*)(CharacterObject*))0x5873E0)(this);
}

AICommandSequencer* CharacterObject::GetAiCmdSeq()
{
	return ((AICommandSequencer*(__thiscall*)(CharacterObject*))0x574150)(this);
}

void CharacterObject::SetCurrentSeq(int id)
{
	*(int*)((int)this + 1092) = id;
}

void CharacterObject::InfiniteAmmo(bool status)
{
	*(bool*)((int)this + 728) = status;
}