#include "ScarfaceMenu.h"
#include "Scarface.h"
#include "imgui/imgui.h"
#include <Windows.h>

bool ScarfaceMenu::active = false;

void ScarfaceMenu::Render()
{
	if (!active)
		return;

	ImGui::Begin("Scarface");

	static char console[256] = {};

	ImGui::InputText("Script", console, sizeof(console));

	if (ImGui::Button("Run"))
	{
		runScript(console);
		MessageBeep(MB_ICONWARNING);
	}


	ImGui::End();
}
