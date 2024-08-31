#pragma once

class eSettingsManager {
public:
	eSettingsManager();
	bool bEnableConsoleWindow;

	int iHookMenuOpenKey;
	int iHookSlowMoKey;

	int iToggleFirstPersonKey;
	int iPlayLastAnimKey;
	int iToggleFreeCameraKey;
	int iToggleHUDKey;
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