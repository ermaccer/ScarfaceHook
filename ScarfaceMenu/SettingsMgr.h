#pragma once

class eSettingsManager {
public:
	eSettingsManager();
	
	bool bUseAlternateMethodToDisableInput;
	
	int iHookMenuOpenKey;
	int iHookSlowMoKey;

	int iToggleFirstPersonKey;
	int iPlayLastAnimKey;
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