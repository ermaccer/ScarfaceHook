#include "CVManager.h"
#include "Template.h"
#include "Sound.h"
#include <iostream>
#include "..\eNotifManager.h"
#include "..\plugin\ScarfaceMenu.h"

SpawnData::SpawnData()
{
	((void(__thiscall*)(SpawnData*))0x604320)(this);
}

int CVManager::CreateVehicle(int type, int object, SpawnData* spawnData, Vector& position, Vector& rotation, float unkReal)
{
	return ((int(__thiscall*)(CVManager*, int, int, SpawnData*, Vector&, Vector&, float, int, int, int, int, int, int, int, int, int))0x4EDDF0)
		(this, type, object, spawnData, position, rotation, unkReal, 0, 0, 0, 0, 0, -1, 0, 0, 0);
}

int CVManager::CreateCharacter(int object, SpawnData* spawnData, Vector& position, Vector& rotation)
{
	return ((int(__thiscall*)(CVManager*, int, SpawnData*, Vector&, Vector&, int, int, int, int))0x4ED390)
		(this, object, spawnData, position, rotation, 1, 0, 0, 0);
}

CVManager* CVManager::GetInstance()
{
	return *(CVManager**)(0x822AF8);
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

