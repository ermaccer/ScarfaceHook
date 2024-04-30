#pragma once
#include "../utils.h"
#include "Template.h"
#include "Vector.h"
#include "Matrix.h"

class ExplosionTemplate : public Template {
public:
	void Explode(Vector* position);
};


ExplosionTemplate* FindExplosion(const char* type);