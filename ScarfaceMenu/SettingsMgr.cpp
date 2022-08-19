#include "IniReader.h"
#include "SettingsMgr.h"
#include <Windows.h>

eSettingsManager* SettingsMgr = new eSettingsManager;

eSettingsManager::eSettingsManager()
{
	CIniReader ini("");
	CIniReader user("scfhook_user.ini");

	// user first
	iHookMenuOpenKey = user.ReadInteger("Settings", "iHookMenuOpenKey", 0xFF);

	if (iHookMenuOpenKey == 0xFF)
		iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);

	// user first
	iHookSlowMoKey = user.ReadInteger("Settings", "iHookSlowMoKey", 0xFF);

	if (iHookSlowMoKey == 0xFF)
		iHookSlowMoKey = ini.ReadInteger("Settings", "iHookSlowMoKey", VK_F5);


	iFreeCameraKeyFOVPlus = user.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0xFF);
	if (iFreeCameraKeyFOVPlus == 0xFF)
		iFreeCameraKeyFOVPlus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0);

	iFreeCameraKeyFOVMinus = user.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0xFF);
	if (iFreeCameraKeyFOVMinus == 0xFF)
		iFreeCameraKeyFOVMinus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0);


	iFreeCameraKeyForward = user.ReadInteger("Settings", "iFreeCameraKeyForward", 0xFF);
	if (iFreeCameraKeyForward == 0xFF)
		iFreeCameraKeyForward = ini.ReadInteger("Settings", "iFreeCameraKeyForward", 0);

	iFreeCameraKeyBack = user.ReadInteger("Settings", "iFreeCameraKeyBack", 0xFF);
	if (iFreeCameraKeyBack == 0xFF)
		iFreeCameraKeyBack = ini.ReadInteger("Settings", "iFreeCameraKeyBack", 0);


	iFreeCameraKeyLeft = user.ReadInteger("Settings", "iFreeCameraKeyLeft ", 0xFF);
	if (iFreeCameraKeyLeft == 0xFF)
		iFreeCameraKeyLeft = ini.ReadInteger("Settings", "iFreeCameraKeyLeft", 0);

	iFreeCameraKeyRight = user.ReadInteger("Settings", "iFreeCameraKeyRight", 0xFF);
	if (iFreeCameraKeyRight == 0xFF)
		iFreeCameraKeyRight = ini.ReadInteger("Settings", "iFreeCameraKeyRight", 0);

	iFreeCameraKeyUp = user.ReadInteger("Settings", "iFreeCameraKeyUp", 0xFF);
	if (iFreeCameraKeyUp == 0xFF)
		iFreeCameraKeyUp = ini.ReadInteger("Settings", "iFreeCameraKeyUp", 0);

	iFreeCameraKeyDown = user.ReadInteger("Settings", "iFreeCameraKeyDown", 0xFF);
	if (iFreeCameraKeyDown == 0xFF)
		iFreeCameraKeyDown = ini.ReadInteger("Settings", "iFreeCameraKeyDown", 0);

	iToggleFirstPersonKey = user.ReadInteger("Settings", "iToggleFirstPersonKey", 0xFF);
	if (iToggleFirstPersonKey == 0xFF)
		iToggleFirstPersonKey = ini.ReadInteger("Settings", "iToggleFirstPersonKey", 0);

	fMenuScale = user.ReadFloat("MenuSettings", "fMenuScale", 1.0f);

	if (fMenuScale < 1.0f)
		fMenuScale = 1.0f;

}

void eSettingsManager::SaveSettings()
{
	CIniReader user("scfhook_user.ini");
	user.WriteFloat("MenuSettings", "fMenuScale", fMenuScale);
	user.WriteInteger("Settings", "iHookMenuOpenKey", iHookMenuOpenKey);
	user.WriteInteger("Settings", "iFreeCameraKeyForward", iFreeCameraKeyForward);
	user.WriteInteger("Settings", "iFreeCameraKeyBack", iFreeCameraKeyBack);
	user.WriteInteger("Settings", "iFreeCameraKeyLeft", iFreeCameraKeyLeft);
	user.WriteInteger("Settings", "iFreeCameraKeyRight", iFreeCameraKeyRight);
	user.WriteInteger("Settings", "iFreeCameraKeyUp", iFreeCameraKeyUp);
	user.WriteInteger("Settings", "iFreeCameraKeyDown", iFreeCameraKeyDown);
	user.WriteInteger("Settings", "iToggleFirstPersonKey", iToggleFirstPersonKey);
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
	iHookSlowMoKey = VK_F5;
}
