#pragma once
#include "Scarface.h"

class ScarfaceMenu {
public:
	bool active = false;
	bool freezeCam = false;
	CVector camPos = {};
	float  m_fFreeCameraSpeed = 0.05f;

	int iFreeCameraKeyXPlus;
	int iFreeCameraKeyXMinus;
	int iFreeCameraKeyYPlus;
	int iFreeCameraKeyYMinus;
	int iFreeCameraKeyZPlus;
	int iFreeCameraKeyZMinus;


	void Init();
	void Render();
	void Process();
};

extern ScarfaceMenu* TheMenu;