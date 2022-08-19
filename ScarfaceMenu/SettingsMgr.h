#pragma once

class eSettingsManager {
public:
	eSettingsManager();
	
	int iHookMenuOpenKey;
	int iHookSlowMoKey;

	int iToggleFirstPersonKey;

	// free camera keys
	int iFreeCameraKeyForward;
	int iFreeCameraKeyBack;
	int iFreeCameraKeyLeft;
	int iFreeCameraKeyRight;
	int iFreeCameraKeyUp;
	int iFreeCameraKeyDown;

	int iFreeCameraKeyFOVPlus;
	int iFreeCameraKeyFOVMinus;

	float fMenuScale;

	void SaveSettings();
	void ResetKeys();
};

extern eSettingsManager* SettingsMgr;