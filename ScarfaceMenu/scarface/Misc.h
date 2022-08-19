#pragma once
#include "Scarface.h"

void giveWeaponToPlayer(char* name);
void setPlayerSkin(char* name);
void clearWeapon(int id);
void playCutscene(char* name);
void playMission(char* name);
void setPlayerPosition(Vector pos);
void setCamPosition(char* name, Vector pos);
void TonyTeleport(Vector pos);