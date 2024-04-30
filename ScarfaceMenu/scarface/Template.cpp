#include "Template.h"

TemplateManager* GetTemplateManager()
{
	static TemplateManager* pTemplateManager = nullptr;

	if (pTemplateManager == nullptr)
	{
		static uintptr_t pat = _pattern(PATID_TemplateManager_Instance);
		if (pat)
		{
			unsigned int offset = *(unsigned int*)(pat);
			pTemplateManager = *(TemplateManager**)(offset);
		}
	}
	return pTemplateManager;
}

Template* GetTemplateData(char* name, int type)
{
	static uintptr_t pat = _pattern(PATID_GetTemplateData);
	if (pat && GetTemplateManager())
		return ((Template*(__thiscall*)(TemplateManager*, char*, int))pat)(GetTemplateManager(), name, type);

	return nullptr;
}

void Template::Load(int type)
{
	static uintptr_t pat = _pattern(PATID_Template_Load);
	if (pat)
		((void(__thiscall*)(Template*, int))pat)(this, type);
}

void Template::Unload(int type)
{
	static uintptr_t pat = _pattern(PATID_Template_Unload);
	if (pat)
		((void(__thiscall*)(Template*, int))pat)(this, type);
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
