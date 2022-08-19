#pragma once

class AICommandSequencer {
public:
	int RegisterAction(const char* name);

	void Wait(int unk, float time);
	void PlayAnim(const char* name, int flag, int loop);

	void RunAction();
};