#pragma once
#include "Vector.h"

// right, up, forward, pos
class Matrix {
public:
	float M[4][4];
	

	Vector GetForward();
	Vector GetUp();
	Vector GetRight();
	Vector GetPos();
};