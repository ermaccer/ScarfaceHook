#pragma once

struct CVector {
	float x, y, z;
};

void runScript(const char* script);


// some simple wrapper
class Camera {
public:
	void SetPosition(CVector* pos);
};