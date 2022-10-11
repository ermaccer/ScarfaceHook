#pragma once
#include "Vector.h"

class EffectsObject {
public:
	void CreateEffect(int type, int unk, int unk2, Vector* pos, Vector* upMat);
	void PlayPedExplosion(Vector* pos);
	static EffectsObject* GetInstance();
};