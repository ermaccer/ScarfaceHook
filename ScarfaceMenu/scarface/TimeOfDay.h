#pragma once
class TODObject {
public:

	void SetTime(int hour, int minute);
	void EnableRain(bool status);

	TODObject* Hook_TODObject_Constructor(int a2, int a3);
	static TODObject* TOD;
};

