#pragma once


class Template {
public:
	int unk;
	char* name; //8
	char pad[14];
	int  flags;

	void Load(int type);
	void Unload(int type);

	bool IsLoaded();

	int GetType();
};

Template* GetTemplateData(char* name, int type);