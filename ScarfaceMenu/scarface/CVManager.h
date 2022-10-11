#pragma once
#include "Vector.h"
#include "Character.h"

class SpawnData
{
public:

	char* name;
	char* field_4;
	char field_8;
	char field_9;
	char field_A;
	char field_B;
	char* templateName;
	char* weaponTemplateName;
	char field_14;
	char field_15;
	char field_16;
	char field_17;
	char field_18;

	SpawnData();
};


template < class T > class GameSet {
public:
	char pad[48];
	T** pData;
	int unk;
	short count;

	int Count() { return count; }
	T* Get(int id) { if (id <= count) return pData[id]; else return nullptr; }
};


class CVManager {
public:
	int CreateVehicle(int type, int object, SpawnData* spawnData, Vector& position, Vector& rotation, float unkReal);
	int CreateCharacter(int object, SpawnData* spawnData, Vector& position, Vector& rotation);


	static CVManager* GetInstance();

	GameSet<CharacterObject>* GetCharacters();
};


// wrappers

void SpawnCar(char* name, Vector* position);
void SpawnCharacter(char* name, Vector* position);
