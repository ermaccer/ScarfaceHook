#include "Misc.h"
#include "Scarface.h"
#include <iostream>

static char scriptBuff[1024] = {};
void giveWeaponToPlayer(char* name)
{
	sprintf(scriptBuff, "$character = FindObject(\"MainCharacter\"); if ($character) $character.AddWeaponTemplateToInventory(\"%s\");",name);
	runScript(scriptBuff);
}

void setPlayerSkin(char* name)
{
	sprintf(scriptBuff, "CVM_SetMainCharacterPackage(\"%s\");", name);
	runScript(scriptBuff);
}

void clearWeapon(int id)
{
	sprintf(scriptBuff, "$character = FindObject(\"MainCharacter\"); if ($character) $character.RemoveWeaponFromInventory(%d);",id);
	runScript(scriptBuff);
}

void playCutscene(char* name)
{
	sprintf(scriptBuff, "stxdfoahmdk(\"%s\",\"\",\"NIS\");", name);
	runScript(scriptBuff);
}

void playMission(char* name)
{
	sprintf(scriptBuff, "PauseMissionReplay(\"%s\");", name);
	runScript(scriptBuff);
}

void setPlayerPosition(Vector pos)
{
	sprintf(scriptBuff, "$c = FindObject(\"MainCharacter\"); $c.position =\"%f %f %f\"; $c.ApplyChanges(); ", pos.X, pos.Y, pos.Z);
	runScript(scriptBuff);
}

void TonyTeleport(Vector pos)
{
	sprintf(scriptBuff, "TonyTeleport(\"%f %f %f\");", pos.X, pos.Y, pos.Z);
	runScript(scriptBuff);
}

unsigned int _hash(char* input)
{
	char* ptr; 
	char curChar;
	int v4;
	int v5;

	int fallback = 0;
	ptr = input;
	if (!input)
		return fallback;
	curChar = *input;
	if (!*input)
		return fallback;
	v4 = fallback & 0x7FFFFFFF;
	do
	{
		v5 = (65599 * v4) & 0x7FFFFFFF;
		*(int*)&curChar = curChar;
		if (curChar < 'a')
			*(int*)&curChar = curChar + ' ';
		++ptr;
		v4 = *(int*)&curChar ^ v5;
		curChar = *ptr;
	} while (*ptr);
	return v4 | 0x80000000;
}
