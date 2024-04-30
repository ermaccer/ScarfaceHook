#pragma once
#include "../utils.h"
#include "Vector.h"
#include "Matrix.h"
#include "Base.h"
#include "String.h"

enum eBones {
	BONE_HEAD = 13,
};

class CharacterObject : public BaseObject {
public:
	void AddHealth(float value);
	void SetHealth(int value);
	Vector* GetBonePosition(int boneId);

	void InfiniteAmmo(bool status);

	void PlayAnimation(char* name, int priority = 90);
	void ResetAnimation();
	void SetPhysicalMode(char* name);
};


CharacterObject* GetMainCharacter();