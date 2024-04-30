#include "ExplosionTemplate.h"

ExplosionTemplate* FindExplosion(const char* type)
{
	static uintptr_t pat = _pattern(PATID_FindExplosion_Call);
	if (pat)
	{
		static ExplosionTemplate* (__cdecl * funcAddr)(const char*, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			return funcAddr(type, 0);
	}
	return nullptr;
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

	static uintptr_t pat = _pattern(PATID_ExplosionTemplate_Explode_Call);
	if (pat)
	{
		static ExplosionTemplate* (__thiscall * funcAddr)(ExplosionTemplate*, Matrix*, int, float, int, int, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			funcAddr(this, &mat, 0, 1.0f, 0, 0, 0);
	}
}
