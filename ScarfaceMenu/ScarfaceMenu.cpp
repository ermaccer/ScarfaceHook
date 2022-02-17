#include "ScarfaceMenu.h"
#include "Scarface.h"
#include "imgui/imgui.h"
#include "IniReader.h"
#include <iostream>
#include <Windows.h>


const char* szCharacters[] = {
	"MCP_ArmyTony",
	"MCP_Assassin",
	"MCP_BlackSuitTony",
	"MCP_BluePinSuitShadesTony",
	"MCP_BluePinSuitTony",
	"MCP_BlueSuitTony",
	"MCP_Driver",
	"MCP_Enforcer",
	"MCP_GraySuitShadesTony",
	"MCP_GraySuitTony",
	"MCP_HawaiianShadesTony",
	"MCP_HawaiianTony",
	"MCP_SandyShadesTony",
	"MCP_SandyTony",
	"MCP_WhiteSuitShadesTony",
	"MCP_WhiteSuitTony",
};

ScarfaceMenu* TheMenu = new ScarfaceMenu();

void ScarfaceMenu::Init()
{
	CIniReader ini("");

	iFreeCameraKeyXPlus = ini.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0);
	iFreeCameraKeyXMinus = ini.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0);


	iFreeCameraKeyYPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0);
	iFreeCameraKeyYMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0);

	iFreeCameraKeyZPlus = ini.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0);
	iFreeCameraKeyZMinus = ini.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0);
}

void ScarfaceMenu::Render()
{
	if (!active)
		return;

	ImGui::Begin("ScarfaceHook by ermaccer");

	static char console[256] = {};

	ImGui::BeginTabBar("##tabs");



	if (ImGui::BeginTabItem("Player"))
	{
		static char character[64] = {};
		if (ImGui::BeginCombo("Skin", character))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
			{
				bool is_selected = (character == szCharacters[n]);
				if (ImGui::Selectable(szCharacters[n], is_selected))
					sprintf(character, szCharacters[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("Set Skin"))
		{
			static char scriptBuff[128] = {};
			sprintf(scriptBuff, "CVM_SetMainCharacterPackage(\"%s\");", character);
			runScript(scriptBuff);

		}

		CVector plrPos = *(CVector*)(0x7C68DC);
		ImGui::Text("Position");
		ImGui::InputFloat3("X | Y | Z", &plrPos.x);
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Camera"))
	{
		ImGui::InputFloat3("X | Y | Z", &camPos.x);
		ImGui::Checkbox("Freeze Camera", &freezeCam);

		ImGui::DragFloat("Free Camera Speed", &m_fFreeCameraSpeed);

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Script"))
	{
		ImGui::InputText("Script", console, sizeof(console));

		if (ImGui::Button("Run"))
			runScript(console);


		ImGui::EndTabItem();
	}


	ImGui::EndTabBar();

	ImGui::End();
}

void ScarfaceMenu::Process()
{
	if (freezeCam)
	{
		if (GetAsyncKeyState(iFreeCameraKeyXPlus))
			camPos.x += m_fFreeCameraSpeed;
		if (GetAsyncKeyState(iFreeCameraKeyXMinus))
			camPos.x -= m_fFreeCameraSpeed;
		if (GetAsyncKeyState(iFreeCameraKeyYPlus))
			camPos.y += m_fFreeCameraSpeed;
		if (GetAsyncKeyState(iFreeCameraKeyYMinus))
			camPos.y -= m_fFreeCameraSpeed;
		if (GetAsyncKeyState(iFreeCameraKeyZPlus))
			camPos.z += m_fFreeCameraSpeed;
		if (GetAsyncKeyState(iFreeCameraKeyZMinus))
			camPos.z -= m_fFreeCameraSpeed;
	}

}
