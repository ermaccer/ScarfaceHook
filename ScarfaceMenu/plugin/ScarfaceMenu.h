#pragma once
#include "..\scarface\Scarface.h"
#include "..\IniReader.h"
#include <vector>

#define MAX_TELEPORTS 200

enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	SUBMENU_SCRIPT,
	TOTAL_SUBMENUS
};


struct TeleporterPlace {
	Vector pos;
	char   name[260] = {};
};


struct FirstPersonSettings {
	bool enabled;
	float YAdjust;
};

class ScarfaceMenu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bCustomCameraPos = false;
	bool	 m_bCustomCameraFOV = false;
	bool	 m_bFreeCam = false;
	bool     m_bSpawnerCustomPosition = false;
	bool	 m_bAirbreak = false;
	bool	 m_bForceInvincibility = false;
	bool	 m_bHighPrioritySpawning = false;	
	bool     m_bCharacterUseWeapon = false;
	bool	 m_bInfiniteHealth = false;
	bool	 m_bInfiniteAmmo = false;

	Vector camPos = {};
	Vector customSpawnPos = {};
	Vector playerPos = {};
	float  m_fFreeCamSpeed = 50.0f;
	float  m_fAirbreakSpeed = 50.0f;
	float  m_fSpeed = 1.0f;
	float  camFov = 70.0f;

	int* m_pCurrentVarToChange = nullptr;


	FirstPersonSettings fps = {};
	CIniReader* locIni;

	char character[128] = {};
	char vehicle[128] = {};
	char weapon[128] = {};
	char cutscene[128] = {};
	char dbgItem[256] = {};
	char mission[128] = {};
	char characterSpawn[128] = {};
	char characterWeapon[128] = {};
	char teleportName[128] = {};


	void Init();
	void Draw();


	void DrawPlayerTab();
	void DrawSpawnerTab();
	void DrawCameraTab();
	void DrawWorldTab();
	void DrawSpeedTab();
	void DrawTeleporterTab();
	void DrawMiscTab();
	void DrawDebugTab();
	void DrawSettings();


	void DrawKeyBind(char* name, int* var);
	void KeyBind(int* var, char* bindName, char* name);



	void Process();

	void LoadLocationFile();
};

float GetDeltaTime();


extern ScarfaceMenu* TheMenu;

namespace ImGui {
	bool _Checkbox(const char* label, bool* v);
}
