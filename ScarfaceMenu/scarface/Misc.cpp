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

void setCamPosition(char* name, Vector pos)
{

}

void TonyTeleport(Vector pos)
{
	sprintf(scriptBuff, "TonyTeleport(\"%f %f %f\");", pos.X, pos.Y, pos.Z);
	runScript(scriptBuff);
}
