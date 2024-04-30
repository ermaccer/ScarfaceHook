#include "CVManager.h"
#include "Template.h"
#include "Sound.h"
#include <iostream>
#include "..\gui\notifications.h"
#include "..\plugin\Menu.h"

SpawnData::SpawnData()
{
	static uintptr_t pat = _pattern(PATID_SpawnData_Ctor);
	if (pat)
		((void(__thiscall*)(SpawnData*))pat)(this);
}

int CVManager::CreateVehicle(int type, int object, SpawnData* spawnData, Vector& position, Vector& rotation, float unkReal)
{
	static uintptr_t pat = _pattern(PATID_CVManager_CreateVehicle_Call);
	if (pat)
	{
		static int(__thiscall * funcAddr)(CVManager*, int, int, SpawnData*, Vector&, Vector&, float, int, int, int, int, int, int, int, int, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			return funcAddr(this, type, object, spawnData, position, rotation, unkReal, 0, 0, 0, 0, 0, -1, 0, 0, 0);
	}
	return 0;
}

int CVManager::CreateCharacter(int object, SpawnData* spawnData, Vector& position, Vector& rotation)
{
	static uintptr_t pat = _pattern(PATID_CVManager_CreateCharacter_Call);
	if (pat)
	{
		static int(__thiscall * funcAddr)(CVManager*, int, SpawnData*, Vector&, Vector&, int, int, int, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			return funcAddr(this, object, spawnData, position, rotation, 1, 0, 0, 0);
	}
	return 0;
}

CVManager* CVManager::GetInstance()
{
	static CVManager* pCVManager = nullptr;

	if (pCVManager == nullptr)
	{
		static uintptr_t pat = _pattern(PATID_CVManager_Instance);
		if (pat)
		{
			unsigned int offset = *(unsigned int*)(pat);
			pCVManager = *(CVManager**)(offset);
		}
	}
	return pCVManager;
}

GameSet<CharacterObject>* CVManager::GetCharacters()
{
	return *(GameSet<CharacterObject>**)(this + 64);
}


void SpawnCar(char* name, Vector* position)
{
	// get template

	Template* templateInfo = GetTemplateData(name, 1);
	if (templateInfo)
	{
		SpawnData data;
		data.name = "CreatedCar";
		data.field_4 = "";
		data.templateName = templateInfo->name;

		int priority = 1;
		if (TheMenu->m_bHighPrioritySpawning)
			priority = 64;

		templateInfo->Load(priority);

		Vector rotation = { 0, 0, 0 };
		Vector pos = *position;

		if (templateInfo->IsLoaded())
		{
			if (int ptr = CVManager::GetInstance()->CreateVehicle(templateInfo->GetType(), NULL, &data, pos, rotation, 0.0f))
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Vehicle %s [0x%X] created!", name, ptr);
				templateInfo->Unload(priority);
			}
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Failed to create %s!", name, ptr);
			}
		}
		else
		{
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Required assets for %s are not loaded yet, try again.", name);
		}

	}
	else
	{
		Notifications->SetNotificationTime(3500);
		Notifications->PushNotification("Cannot find template info for %s", name);
	}

}

void SpawnCharacter(char* name, Vector* position)
{// get template

	Template* templateInfo = GetTemplateData(name, 0);
	if (templateInfo)
	{
		SpawnData data;
		data.name = "CreatedChar";
		data.field_4 = "";
		data.templateName = templateInfo->name;

		if (TheMenu->m_bCharacterUseWeapon)
			data.weaponTemplateName = TheMenu->characterWeapon;

		int priority = 1;
		if (TheMenu->m_bHighPrioritySpawning)
			priority = 64;

		templateInfo->Load(priority);

		Vector rotation = { 0, 0, 0 };
		Vector pos = *position;

		if (templateInfo->IsLoaded())
		{
			if (CharacterObject* ptr = (CharacterObject*)CVManager::GetInstance()->CreateCharacter(NULL, &data, pos, rotation))
			{
				Notifications->SetNotificationTime(2500);

				if (TheMenu->m_bCharacterUseWeapon)
					Notifications->PushNotification("Character %s [0x%X] created with %s!", name, ptr, data.weaponTemplateName);
				else
					Notifications->PushNotification("Character %s [0x%X] created!", name, ptr);
				templateInfo->Unload(priority);
			}
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Failed to create %s!", name, ptr);
			}
		}
		else
		{
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Required assets for %s are not loaded yet, try again.", name);
		}

	}
	else
	{
		Notifications->SetNotificationTime(3500);
		Notifications->PushNotification("Cannot find template info for %s", name);
	}

}

