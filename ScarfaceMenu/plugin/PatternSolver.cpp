#include "PatternSolver.h"
#include "..\utils\Patterns.h"
#include "..\gui\log.h"
#include <chrono>

uintptr_t PatternSolver::ms_patterns[PATID_Total_Patterns];


uintptr_t PatternSolver::GetPattern(const char* szPattern, int offset)
{
    uintptr_t addr = 0;
    try {
        addr = (uintptr_t)hook::txn::get_pattern(szPattern, offset);
    }
    TXN_CATCH();

    return addr;
}

void PatternSolver::Initialize()
{
    eLog::Message(__FUNCTION__, "Starting pattern search");

    for (int i = 0; i < PATID_Total_Patterns; i++)
        ms_patterns[i] = 0;

    auto begin = std::chrono::high_resolution_clock::now();

    ms_patterns[PATID_Camera_SetPosition] = GetPattern("8B C1 8B 4C 24 04 8B 11 89 50 64 8B 51 04 89 50 68 8B 49 08 89 48 6C 8B 88 ? ? ? ? 8B 11 83 C0 34 89 44 24 04 FF 62 64", 0);
    ms_patterns[PATID_Camera_SetFOV] = GetPattern("8B 44 24 04 D9 44 24 04 D8 0D ? ? ? ? 89 41 74 8B 89 ? ? ? ? 8B 41 14 8B 11 50 51 D9 1C 24 FF 52 1C C2 04 00", 0);
    ms_patterns[PATID_Camera_CollisionFunction] = GetPattern("51 D9 41 04 8B 41 18 D9 41 08 8B 51 10 D9 C9 89 04 24 D9 59 10 8B 41 20 89 41 08 D9 59 20 8B 04 24 D9 41 30 89 51 04 D9 E0 8B 51 24 D9 41 34 89 41 24 D9 E0 89 51 18 D9 41 38 D9 E0 D9 C1 D8 49 10 D9 C3 D8 09 DE C1 D9 C1 D8 49 20 DE C1 D9 59 30 D9 C1", 0);
    ms_patterns[PATID_Camera_CollisionFunction_Hook] = GetPattern("8B FA B9 ? ? ? ? F3 A5 8B CA C6 85 ? ? ? ? ? E8 ? ? ? ? 83 85 ? ? ? ? ? 5F 5E", 18);
    ms_patterns[PATID_Character_MainCharacter] = GetPattern("8B 0D ? ? ? ? 85 C9 74 09 E8 ? ? ? ? 84 C0 75 5F 83 7C 24 ? ? 7E 43", 2);
    ms_patterns[PATID_Character_AddHealth] = GetPattern("51 56 8B F1 57 8B BE ? ? ? ? 89 7C 24 08 DB 44 24 08 D8 1D ? ? ? ? DF E0 F6 C4 41 7A 08 5F 33 C0 5E 59 C2 04 00", 0);
    ms_patterns[PATID_Character_GetBonePosition_Call] = GetPattern("6A 0D E8 ? ? ? ? 8B 08 8B 50 04 8B 40 08 89 4C 24 08 89 4C 24 44 8D 4C 24 14 51", 2);
    ms_patterns[PATID_Character_PlayAnimation_Call] = GetPattern("8B CE E8 ? ? ? ? 8D 4C 24 54 C7 44 24 ? ? ? ? ? E8 ? ? ? ? 8B CE", 2);
    ms_patterns[PATID_Character_ResetAnimation_Call] = GetPattern("8B 0D ? ? ? ? 6A 00 E8 ? ? ? ? 8B 15 ? ? ? ? 8B 82 ? ? ? ? 85 C0", 8);
    ms_patterns[PATID_CVManager_Instance] = GetPattern("8B 15 ? ? ? ? 8B 42 40 0F BF 48 38 33 FF 85 C9 89 44 24 14", 2);
    ms_patterns[PATID_CVManager_CreateVehicle_Call] = GetPattern("E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 6A 00 8B C8 E8 ? ? ? ? 8B C8 E8 ? ? ? ? 8B F8 85 FF 74 48 8B CF E8 ? ? ? ? 8B F0 68 ? ? ? ? 8B CE E8 ? ? ? ? 8B CE E8 ? ? ? ? 68 ? ? ? ? 6A 00 6A FF", 0);
    ms_patterns[PATID_CVManager_CreateCharacter_Call] = GetPattern("E8 ? ? ? ? 8B F8 85 FF 74 37 01 9E ? ? ? ? 6A 00 8B CF E8 ? ? ? ? 8B C8 E8 ? ? ? ? 68 ? ? ? ? 6A 00", 0);
    ms_patterns[PATID_SpawnData_Ctor] = GetPattern("8B C1 33 C9 89 08 89 48 04 89 48 08 89 48 0C 89 48 10 89 48 14 C6 40 18 03 C6 40 19 01", 0);
    ms_patterns[PATID_EffectsObject_CreateEffect_Call] = GetPattern("51 6A 04 56 C7 44 24 ? ? ? ? ? C7 44 24 ? ? ? ? ? C7 44 24 ? ? ? ? ? E8 ? ? ? ? 8B C8 E8", 35);
    ms_patterns[PATID_EffectsObject_PlayPedExplosion] = GetPattern("83 EC 40 57 8B F9 8B 87 ? ? ? ? 50 E8 ? ? ? ? 83 C4 04 85 C0 74 56 8B 8F ? ? ? ? 56 51 E8 ? ? ? ? 8B 70 64", 0);
    ms_patterns[PATID_EffectsObject_GetInstance_Call] = GetPattern("51 6A 04 56 C7 44 24 ? ? ? ? ? C7 44 24 ? ? ? ? ? C7 44 24 ? ? ? ? ? E8 ? ? ? ? 8B C8 E8", 28);
    ms_patterns[PATID_FindExplosion_Call] = GetPattern("E8 ? ? ? ? 83 C4 08 8D 8E ? ? ? ? 50 E8 ? ? ? ? 8B 96 ? ? ? ? 80 E6 F3 80 CE 03", 0);
    ms_patterns[PATID_ExplosionTemplate_Explode_Call] = GetPattern("52 8B 91 ? ? ? ? 68 ? ? ? ? 52 83 C6 8C 56 8B C8 E8", 19);
    ms_patterns[PATID_runScript_Call] = GetPattern("E8 ? ? ? ? 8B 4C 24 28 51 6A 4C E8 ? ? ? ? 83 C4 1C 85 C0 5F 5E", 0);
    ms_patterns[PATID_Frontend_PlaySound_Call] = GetPattern("68 ? ? ? ? 89 86 ? ? ? ? E8 ? ? ? ? 8B 06 83 C4 04", 11);
    ms_patterns[PATID_TemplateManager_Instance] = GetPattern("8B 0D ? ? ? ? 6A 01 50 E8 ? ? ? ? 8B 8E", 2);
    ms_patterns[PATID_GetTemplateData] = GetPattern("8B 44 24 08 83 F8 02 56 57 8B F9 75 23 33 F6 90 8B 44 24 0C 56 50 8B CF E8 ? ? ? ? 85 C0 75 0A 83 C6 01 83 FE 02 7C E7", 0);
    ms_patterns[PATID_Template_Load] = GetPattern("56 8B F1 8A 4C 24 08 B2 01 84 CA 74 03 00 56 19 F6 C1 02 74 14 8A 46 17 53 8A D8 80 E3 FE 80 C3 02 22 C2 32 D8 88 5E 17 5B F6 C1 04 74 03", 0);
    ms_patterns[PATID_Template_Unload] = GetPattern("53 8A 5C 24 08 F6 C3 01 74 0C 8A 41 19 84 C0 74 05 2C 01 88 41 19 F6 C3 02 74 15 8A 51 17 8A C2 D0 E8 74 0C 2C 01 02 C0 80 E2 01 0A C2 88 41 17 F6 C3 04", 0);
    ms_patterns[PATID_TODObject_SetTime_Call] = GetPattern("8B 56 08 83 C4 04 50 52 FF D7 83 C4 04 50 8B CB E8 ? ? ? ? 5F", 16);
    ms_patterns[PATID_TODObject_EnableRain_Call] = GetPattern("8A 83 ? ? ? ? 50 E8 ? ? ? ? 83 C4 10 5F 5E 5B", 7);
    ms_patterns[PATID_TODObject_Instance] = GetPattern("83 3D ? ? ? ? ? 74 2B 8D 44 24 04", 2);
    ms_patterns[PATID_DisableInput] = GetPattern("75 22 8B 0D ? ? ? ? 51 E8 ? ? ? ? 83 C4 04", 0);
    ms_patterns[PATID_DisableMouse] = GetPattern("64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 10 55 8B 6C 24 24 85 ED 75 1C 8B 44 24 28 8B 4C 24 2C 89 28 89 29 5D", 0);
    ms_patterns[PATID_DinputCoopLevel] = GetPattern("6A 05 8B CB FF 52 10 50 56 FF 57 34", 1);
    ms_patterns[PATID_gTonyInvincible] = GetPattern("38 05 ? ? ? ? 74 0E 33 C0 89 43 10 88 43 30 89 86 ? ? ? ? 80 7C 24", 2);
    ms_patterns[PATID_FallDamage1] = GetPattern("C7 45 ? ? ? ? ? EB 03 89 4D 00 83 3B 03", 3);
    ms_patterns[PATID_FallDamage2] = GetPattern("C7 45 ? ? ? ? ? 8B CE E8 ? ? ? ? 84 C0 74 2E 68 ? ? ? ?", 3);

    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    auto timeSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    eLog::Message(__FUNCTION__, "Checked %d patterns in %dms (%ds)", PATID_Total_Patterns, time.count(), timeSeconds.count());

}

int PatternSolver::GetNumPatternsOK()
{
    int patternNum = 0;

    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i]) patternNum++;
    return patternNum;
}

bool PatternSolver::CheckMissingPatterns()
{
    int missingPatterns = 0;
    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i] == 0)
        {
            missingPatterns++;
            eLog::Message(__FUNCTION__, "ERROR: Could not find %s!", GetPatternName(i));
        }
    return missingPatterns > 0;
}

const char* PatternSolver::GetPatternName(int id)
{
    if (id >= PATID_Total_Patterns)
        return "UNKNOWN";

    static const char* szPatternNames[PATID_Total_Patterns] = {
         "Camera_SetPosition",
         "Camera_SetFOV",
         "Camera_CollisionFunction",
         "Camera_CollisionFunction_Hook",
         "Character_MainCharacter",
         "Character_AddHealth",
         "Character_GetBonePosition_Call",
         "Character_PlayAnimation_Call",
         "Character_ResetAnimation_Call",
         "CVManager_Instance",
         "CVManager_CreateVehicle_Call",
         "CVManager_CreateCharacter_Call",
         "SpawnData_Ctor",
         "EffectsObject_CreateEffect_Call",
         "EffectsObject_PlayPedExplosion",
         "EffectsObject_GetInstance_Call",
         "FindExplosion_Call",
         "ExplosionTemplate_Explode_Call",
         "runScript_Call",
         "Frontend_PlaySound_Call",
         "TemplateManager_Instance",
         "GetTemplateData",
         "Template_Load",
         "Template_Unload",
         "TODObject_SetTime_Call",
         "TODObject_EnableRain_Call",
         "TODObject_Instance",
         "DisableInput",
         "DisableMouse",
         "DinputCoopLevel",
         "gTonyInvincible",
         "FallDamage1",
         "FallDamage2",
    };   

    return szPatternNames[id];
}

uintptr_t _pattern(EPatternID id)
{
    if (id >= PATID_Total_Patterns)
        return 0;

    return PatternSolver::ms_patterns[id];
}
