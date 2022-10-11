#include "Character.h"
#include "Misc.h"

CharacterObject* GetMainCharacter()
{
	return *(CharacterObject**)(0x825A78);
}

void CharacterObject::AddHealth(float value)
{
	((void(__thiscall*)(CharacterObject*, float))0x577650)(this, value);
}

void CharacterObject::SetHealth(int value)
{
	*(int*)((int)this + 348) = value;
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

void CharacterObject::PlayAnimation(char* name, int priority)
{
	unsigned int hash = _hash(name);
	((void(__thiscall*)(CharacterObject*, unsigned int*, int, int))0x576FC0)(this, &hash ,priority,0);
}

void CharacterObject::ResetAnimation()
{
	((void(__thiscall*)(CharacterObject*, bool))0x574990)(this, 0);
}

void CharacterObject::SetPhysicalMode(char* name)
{
	*(int*)((int)this + 1052) = _hash(name);
}
