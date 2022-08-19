#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Base.h"
#include "AI.h"
#include "String.h"

enum eBones {
	BONE_HEAD = 13,
};

class CharacterObject : public BaseObject {
public:
	void AddHealth(float value);
	Vector* GetBonePosition(int boneId);

	int GetCurrentWeapon();
	void RemoveWeaponFromInventory(int weapon);

	int IsCharacterInCar();

	AICommandSequencer* GetAiCmdSeq();

	void SetCurrentSeq(int id);
	void InfiniteAmmo(bool status);
};


CharacterObject* GetMainCharacter();