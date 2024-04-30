#pragma once
#include "../utils.h"
#include "Base.h"

// some simple wrapper
class Camera : public BaseObject {
public:
	void SetPositionHooked(Vector* pos);
	void SetPosition(Vector* pos);
	void SetFOV(float FOV);

	void UnknownCollision();

};


extern Camera* TheCamera;
