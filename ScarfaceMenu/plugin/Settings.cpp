#include "Settings.h"
#include "../utils/IniReader.h"
#include "Menu.h"
#include <Windows.h>

eSettingsManager* SettingsMgr = new eSettingsManager;

eSettingsManager::eSettingsManager()
{
	CIniReader ini("");
	CIniReader user("scfhook_user.ini");

	// user first
	bEnableConsoleWindow = ini.ReadBoolean("Settings", "bEnableConsoleWindow", true);


	iHookMenuOpenKey = user.ReadInteger("Settings", "iHookMenuOpenKey", -1);
	if (iHookMenuOpenKey == -1) iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);

	iHookSlowMoKey = user.ReadInteger("Settings", "iHookSlowMoKey", -1);
	if (iHookSlowMoKey == -1) iHookSlowMoKey = ini.ReadInteger("Settings", "iHookSlowMoKey", VK_F5);

	iToggleFreeCameraKey = user.ReadInteger("Settings", "iToggleFreeCameraKey", -1);
	if (iToggleFreeCameraKey == -1) iToggleFreeCameraKey = 0;

	iToggleHUDKey = user.ReadInteger("Settings", "iToggleHUDKey", -1);
	if (iToggleHUDKey == -1) iToggleHUDKey = 0;

	iPlayLastAnimKey = user.ReadInteger("Settings", "iPlayLastAnimKey", -1);
	if (iPlayLastAnimKey == -1) iPlayLastAnimKey = 0;

	iFreeCameraKeyFOVPlus = user.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", -1);
	if (iFreeCameraKeyFOVPlus == -1) iFreeCameraKeyFOVPlus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0);

	iFreeCameraKeyFOVMinus = user.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", -1);
	if (iFreeCameraKeyFOVMinus == -1) iFreeCameraKeyFOVMinus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0);

	iFreeCameraKeyForward = user.ReadInteger("Settings", "iFreeCameraKeyForward", -1);
	if (iFreeCameraKeyForward == -1) iFreeCameraKeyForward = ini.ReadInteger("Settings", "iFreeCameraKeyForward", 0);

	iFreeCameraKeyBack = user.ReadInteger("Settings", "iFreeCameraKeyBack", -1);
	if (iFreeCameraKeyBack == -1) iFreeCameraKeyBack = ini.ReadInteger("Settings", "iFreeCameraKeyBack", 0);

	iFreeCameraKeyLeft = user.ReadInteger("Settings", "iFreeCameraKeyLeft ", -1);
	if (iFreeCameraKeyLeft == -1) iFreeCameraKeyLeft = ini.ReadInteger("Settings", "iFreeCameraKeyLeft", 0);

	iFreeCameraKeyRight = user.ReadInteger("Settings", "iFreeCameraKeyRight", -1);
	if (iFreeCameraKeyRight == -1) iFreeCameraKeyRight = ini.ReadInteger("Settings", "iFreeCameraKeyRight", 0);

	iFreeCameraKeyUp = user.ReadInteger("Settings", "iFreeCameraKeyUp", -1);
	if (iFreeCameraKeyUp == -1) iFreeCameraKeyUp = ini.ReadInteger("Settings", "iFreeCameraKeyUp", 0);

	iFreeCameraKeyDown = user.ReadInteger("Settings", "iFreeCameraKeyDown", -1);
	if (iFreeCameraKeyDown == -1) iFreeCameraKeyDown = ini.ReadInteger("Settings", "iFreeCameraKeyDown", 0);

	iToggleFirstPersonKey = user.ReadInteger("Settings", "iToggleFirstPersonKey", -1);
	if (iToggleFirstPersonKey == -1) iToggleFirstPersonKey = ini.ReadInteger("Settings", "iToggleFirstPersonKey", 0);

	fMenuScale = user.ReadFloat("MenuSettings", "fMenuScale", 1.0f);

	TheMenu->fps.XAdjust = user.ReadFloat("FPSettings", "xadjust", 0.0f);
	TheMenu->fps.YAdjust = user.ReadFloat("FPSettings", "yadjust", 0.0f);
	TheMenu->fps.ZAdjust = user.ReadFloat("FPSettings", "zadjust", 0.0f);


	if (fMenuScale < 1.0f)
		fMenuScale = 1.0f;

}

void eSettingsManager::SaveSettings()
{
	CIniReader user("scfhook_user.ini");
	user.WriteFloat("MenuSettings", "fMenuScale", fMenuScale);
	user.WriteInteger("Settings", "iHookMenuOpenKey", iHookMenuOpenKey);
	user.WriteInteger("Settings", "iHookSlowMoKey", iHookSlowMoKey);
	user.WriteInteger("Settings", "iPlayLastAnimKey", iPlayLastAnimKey);
	user.WriteInteger("Settings", "iFreeCameraKeyForward", iFreeCameraKeyForward);
	user.WriteInteger("Settings", "iFreeCameraKeyBack", iFreeCameraKeyBack);
	user.WriteInteger("Settings", "iFreeCameraKeyLeft", iFreeCameraKeyLeft);
	user.WriteInteger("Settings", "iFreeCameraKeyRight", iFreeCameraKeyRight);
	user.WriteInteger("Settings", "iFreeCameraKeyUp", iFreeCameraKeyUp);
	user.WriteInteger("Settings", "iFreeCameraKeyDown", iFreeCameraKeyDown);
	user.WriteInteger("Settings", "iFreeCameraKeyFOVPlus", iFreeCameraKeyFOVPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyFOVMinus", iFreeCameraKeyFOVMinus);
	user.WriteInteger("Settings", "iToggleFreeCameraKey", iToggleFreeCameraKey);
	user.WriteInteger("Settings", "iToggleHUDKey", iToggleHUDKey);
	user.WriteInteger("Settings", "iToggleFirstPersonKey", iToggleFirstPersonKey);
	user.WriteFloat("FPSettings", "xadjust", TheMenu->fps.XAdjust);
	user.WriteFloat("FPSettings", "yadjust", TheMenu->fps.YAdjust);
	user.WriteFloat("FPSettings", "zadjust", TheMenu->fps.ZAdjust);

	CIniReader ini("ScarfaceHook.ini");
	ini.WriteBoolean("Settings", "bEnableConsoleWindow", bEnableConsoleWindow);
}

void eSettingsManager::ResetKeys()
{
	iHookMenuOpenKey = VK_F1;
	iFreeCameraKeyForward = 104;
	iFreeCameraKeyBack = 98;
	iFreeCameraKeyLeft = 100;
	iFreeCameraKeyRight = 102;
	iFreeCameraKeyUp = 103;
	iFreeCameraKeyDown = 97;
	iFreeCameraKeyFOVPlus = 107;
	iFreeCameraKeyFOVMinus = 109;
	iHookSlowMoKey = VK_F5;
	iPlayLastAnimKey = VK_F6;
	iToggleFreeCameraKey = 0;
	iToggleHUDKey = 0;
}
