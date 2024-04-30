#pragma once
#include <vector>
#include "../utils/IniReader.h"
#include "../scarface/Scarface.h"
#include "../helper/eKeyboardMan.h"

#define SCARFACEHOOK_VERSION "1.4"

#define MAX_TELEPORTS 200
//#define CLIP_POS

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
	float XAdjust;
	float ZAdjust;
};

class ScarfaceMenu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bIsFocused = false;
	bool	 m_bSlowMotion = false;
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
	bool	 m_bDisableFallDamage = false;
	bool	 m_bHideHUD = false;

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
	char animName[256] = {};

	ScarfaceMenu();

	void	 OnActivate();
	void	 OnToggleSlowMotion();
	void	 OnToggleFreeCamera();
	void	 OnToggleHUD();
	void	 OnPlayLastAnim();
	void	 OnToggleFPS();


	void	 Draw();
	void	 DrawPlayerTab();
	void	 DrawSpawnerTab();
	void	 DrawCameraTab();
	void	 DrawWorldTab();
	void	 DrawSpeedTab();
	void	 DrawTeleporterTab();
	void	 DrawMiscTab();
	void	 DrawDebugTab();
	void	 DrawSettings();


	void DrawKeyBind(char* name, int* var);
	void KeyBind(int* var, char* bindName, char* name);



	void Process();

	void LoadLocationFile();
};

void SetFallDamageValue(int val);
void ExplodeAllPeds();
void MakeAllPedsDance();

extern ScarfaceMenu* TheMenu;

namespace ImGui {
	bool _Checkbox(const char* label, bool* v);
}
