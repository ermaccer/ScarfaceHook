#include "Template.h"

Template* GetTemplateData(char* name, int type)
{
	return ((Template*(__thiscall*)(int, char*, int))0x6027F0)(*(int*)0x82C020, name, type);
}

void Template::Load(int type)
{
	((void(__thiscall*)(Template*, int))0x5F7980)(this, type);
}

void Template::Unload(int type)
{
	((void(__thiscall*)(Template*, int))0x5F76A0)(this, type);
}

bool Template::IsLoaded()
{
	int flag = *(int*)((int)this + 22);
	return (flag & 127) == 0;
}

int Template::GetType()
{
	return *(unsigned __int8*)((int)this + 31) >> 4;
}
