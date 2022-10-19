#include "eDirectX9Hook.h"
#include "plugin/ScarfaceMenu.h"
#include "utils/MemoryMgr.h"
#include "font.h"
#include "eNotifManager.h"
#include "SettingsMgr.h"
#include "helper/eKeyboardMan.h"

using namespace Memory::VP;

HWND eDirectX9Hook::ms_hWindow;
WNDPROC eDirectX9Hook::ms_pWndProc;
uintptr_t eDirectX9Hook::ms_pHookJumpEndScene;
uintptr_t eDirectX9Hook::ms_pHookJumpReset;
bool eDirectX9Hook::ms_bInit;
bool eDirectX9Hook::ms_bShouldReloadFonts;



void eDirectX9Hook::Init()
{
	ms_hWindow = 0;
	ms_pWndProc = 0;
	ms_bInit = false;
	ms_bShouldReloadFonts = false;
	Notifications->Init();
}

void eDirectX9Hook::RegisterHook(uintptr_t addr, uintptr_t offset, eMethodType type)
{
	switch (type)
	{
	case Method_EndScene:
		ms_pHookJumpEndScene = offset;
		InjectHook(addr, Hook_EndScene, PATCH_JUMP);
		break;
	case Method_Reset:
		ms_pHookJumpReset = offset;
		InjectHook(addr, Hook_Reset, PATCH_JUMP);
		break;
	default:
		break;
	}
}

void __declspec(naked) eDirectX9Hook::Hook_EndScene()
{
	static LPDIRECT3DDEVICE9 pDevice = 0;
	_asm {
		mov esi, [esi + 560]
		mov  eax, [esi]
		mov pDevice, esi
		pushad
	}
	EndScene(pDevice);
	_asm {
		popad
		push    esi
		jmp ms_pHookJumpEndScene
	}
}

void __declspec(naked) eDirectX9Hook::Hook_Reset()
{
	_asm pushad
	ImGui_ImplDX9_InvalidateDeviceObjects();
	_asm {
		popad
		mov     eax, [esi]
		mov     ecx, [eax]
		push    ebx
		push    eax
		call    dword ptr[ecx + 64]
		pushad
	}
	ImGui_ImplDX9_CreateDeviceObjects();
	_asm {
		popad
		jmp	ms_pHookJumpReset
	}
}

void eDirectX9Hook::SetImGuiStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 6.0f;
	style->ItemSpacing = ImVec2(7, 5.5);
	style->FrameRounding = 2.0f;
	style->FramePadding = ImVec2(6, 4.25);

	for (int i = 0; i < ImGuiCol_COUNT; i++)
	{
		ImVec4 col = style->Colors[i];

		if (i == ImGuiCol_Text || i == ImGuiCol_TextDisabled ||
			i == ImGuiCol_WindowBg || i == ImGuiCol_MenuBarBg) continue;
		style->Colors[i] = { col.x * 2.25f, 0,0 , col.w };
	}
	ReloadImGuiFont();
}


void eDirectX9Hook::InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(ms_hWindow);
	ImGui_ImplDX9_Init(pDevice);
	SetImGuiStyle();
}

void eDirectX9Hook::ReloadImGuiFont()
{
	float fontSize = 16.0f;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * SettingsMgr->fMenuScale);
	io.Fonts->Build();
	ImGui_ImplDX9_InvalidateDeviceObjects();

	if (ms_bShouldReloadFonts)
		ms_bShouldReloadFonts = false;
}

void __stdcall eDirectX9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ms_bInit)
	{
		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);
		ms_hWindow = params.hFocusWindow;
		ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWL_WNDPROC, (LONG_PTR)WndProc);
		InitImGui(pDevice);

		ms_bInit = true;
	}

	if (ms_bShouldReloadFonts)
		ReloadImGuiFont();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = false;
	static bool draw = true;
	if (draw)
	{
		Notifications->SetNotificationTime(3500);
		Notifications->PushNotification("ScarfaceHook is running! Press %s to open the menu.", eKeyboardMan::KeyToString(SettingsMgr->iHookMenuOpenKey));
		draw = false;
	}


	Notifications->Draw();

	if (TheMenu->m_bIsActive)
		ImGui::GetIO().MouseDrawCursor = true;

	TheMenu->Draw();

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	TheMenu->Process();
}

LRESULT __stdcall eDirectX9Hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iHookMenuOpenKey)
			TheMenu->m_bIsActive ^= 1;
		if (wParam == SettingsMgr->iHookSlowMoKey)
		{
			TheMenu->m_bSlowMotion ^= 1;
			if (TheMenu->m_bSlowMotion)
			{
				runScript("PopTimeScale();");
				char buff[128];
				sprintf(buff, "PushTimeScale(%f);", TheMenu->m_fSpeed);
				runScript(buff);
			}
			else
				runScript("PopTimeScale();");
		}
		if (wParam == SettingsMgr->iPlayLastAnimKey)
		{
			if (GetMainCharacter())
				GetMainCharacter()->PlayAnimation(TheMenu->animName);
		}
		break;
	default:
		break;
	}
	if (TheMenu->m_bIsActive)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}


	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}