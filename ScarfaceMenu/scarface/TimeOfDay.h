#pragma once
#include "../utils.h"


class TODObject {
public:

	void SetTime(int hour, int minute);
	void EnableRain(bool status);
};

TODObject* GetTODObject();