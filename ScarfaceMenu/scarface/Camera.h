#pragma once
#include "Base.h"

// some simple wrapper
class Camera : public BaseObject {
public:
	void SetPosition(Vector* pos);

	void SetFOV(float FOV);

	void sub_69EA90(Matrix* data);

};


extern Camera* TheCamera;
