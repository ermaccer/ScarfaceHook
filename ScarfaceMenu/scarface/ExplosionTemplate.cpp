#include "ExplosionTemplate.h"

ExplosionTemplate* FindExplosion(const char* type)
{
	return ((ExplosionTemplate* (__cdecl*)(const char*, int))0x5E92D0)(type, 0);
}

void ExplosionTemplate::Explode(Vector* position)
{
	Matrix mat = { };
	mat.M[0][0] = 1.0f;
	mat.M[1][1] = 1.0f;
	mat.M[2][2] = 1.0f;
	mat.M[3][3] = 1.0f;

	mat.M[3][0] = position->X;
	mat.M[3][1] = position->Y;
	mat.M[3][2] = position->Z;


	((void(__thiscall*)(ExplosionTemplate*, Matrix*, int, float, int, int, int))0x616100)(this, &mat, 0, 1.0f, 0, 0, 0);
}
