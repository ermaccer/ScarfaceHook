#pragma once
#include "..\pch.h"

enum EPatternID {
	PATID_Camera_SetPosition,
	PATID_Camera_SetFOV,
	PATID_Camera_CollisionFunction,
	PATID_Camera_CollisionFunction_Hook,
	PATID_Character_MainCharacter,
	PATID_Character_AddHealth,
	PATID_Character_GetBonePosition_Call,
	PATID_Character_PlayAnimation_Call,
	PATID_Character_ResetAnimation_Call,
	PATID_CVManager_Instance,
	PATID_CVManager_CreateVehicle_Call,
	PATID_CVManager_CreateCharacter_Call,
	PATID_SpawnData_Ctor,
	PATID_EffectsObject_CreateEffect_Call,
	PATID_EffectsObject_PlayPedExplosion,
	PATID_EffectsObject_GetInstance_Call,
	PATID_FindExplosion_Call,
	PATID_ExplosionTemplate_Explode_Call,
	PATID_runScript_Call,
	PATID_Frontend_PlaySound_Call,
	PATID_TemplateManager_Instance,
	PATID_GetTemplateData,
	PATID_Template_Load,
	PATID_Template_Unload,
	PATID_TODObject_SetTime_Call,
	PATID_TODObject_EnableRain_Call,
	PATID_TODObject_Instance,
	PATID_DisableInput,
	PATID_DisableMouse,
	PATID_DinputCoopLevel,
	PATID_gTonyInvincible,
	PATID_FallDamage1,
	PATID_FallDamage2,
	PATID_Total_Patterns
};


class PatternSolver {
public:
	static uintptr_t ms_patterns[PATID_Total_Patterns];

	static uintptr_t GetPattern(const char* szPattern, int offset);

	static void			Initialize();
	static int			GetNumPatternsOK();
	static bool			CheckMissingPatterns();
	static const char*	GetPatternName(int id);

};


uintptr_t _pattern(EPatternID id);