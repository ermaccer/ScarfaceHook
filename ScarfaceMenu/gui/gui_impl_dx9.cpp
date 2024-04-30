#include "gui_impl_dx9.h"

#include "log.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "font.h"

#include "../plugin/Menu.h"
#include "../plugin/Settings.h"
#include "notifications.h"

bool  GUIImplementationDX9::ms_bInit = false;
bool  GUIImplementationDX9::ms_bFailed = false;
bool  GUIImplementationDX9::ms_bShouldReloadFonts = false;
HWND  GUIImplementationDX9::ms_hWindow = 0;
WNDPROC GUIImplementationDX9::ms_pWndProc = 0;


void GUIImplementationDX9::Shutdown()
{
	if (!ms_bInit)
		return;

	ImGui_ImplWin32_Shutdown();
}

bool GUIImplementationDX9::ImGui_Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ImGui::CreateContext())
	{
		eLog::Message(__FUNCTION__, "Failed to create ImGui context!");
		return false;
	}

	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	if (!ImGui_ImplWin32_Init(ms_hWindow))
	{
		eLog::Message(__FUNCTION__, "Failed to init Win32 Backend!");
		return false;
	}
	
	if (!ImGui_ImplDX9_Init(pDevice))
	{
		eLog::Message(__FUNCTION__, "Failed to init DX9 Backend!");
		return false;
	}
	
	ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
	
	if (!ms_pWndProc)
	{
		eLog::Message(__FUNCTION__, "Failed to set Window Procedure! Error code: %d", GetLastError());
		return false;
	}
	
	ImGui_SetStyle();
	eLog::Message(__FUNCTION__, "INFO: Init OK");
	return true;
}

void GUIImplementationDX9::ImGui_SetStyle()
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

	ImGui_ReloadFont();
}

void GUIImplementationDX9::ImGui_ReloadFont()
{
	float fontSize = 16.0f;
	float fMenuScale = SettingsMgr->fMenuScale;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * fMenuScale);
	io.Fonts->Build();

	ImGui_ImplDX9_InvalidateDeviceObjects();

	if (ms_bShouldReloadFonts)
		ms_bShouldReloadFonts = false;
}

void GUIImplementationDX9::OnEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (ms_bFailed)
		return;

	if (!ms_bInit)
		OnEndScene_GUIStart(pDevice);

	ImGui_Process(pDevice);
}

float GUIImplementationDX9::GetDeltaTime()
{
	float delta = 1.0f / 60.0f;
	if (ms_bInit)
		delta = 1.0f / ImGui::GetIO().Framerate;

	return delta;
}

void GUIImplementationDX9::RequestFontReload()
{
	ms_bShouldReloadFonts = true;
}

void GUIImplementationDX9::InputWatcher()
{
	if (!ms_bInit)
		return;
}

LRESULT WINAPI GUIImplementationDX9::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		TheMenu->m_bIsFocused = false;
		break;
	case WM_SETFOCUS:
		TheMenu->m_bIsFocused = true;
		break;
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iHookMenuOpenKey)
			TheMenu->OnActivate();
		if (wParam == SettingsMgr->iToggleHUDKey)
			TheMenu->OnToggleHUD();
		if (wParam == SettingsMgr->iPlayLastAnimKey)
			TheMenu->OnPlayLastAnim();
		if (wParam == SettingsMgr->iToggleFirstPersonKey)
			TheMenu->OnToggleFPS();
		if (wParam == SettingsMgr->iHookSlowMoKey)
			TheMenu->OnToggleSlowMotion();
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

void GUIImplementationDX9::OnEndScene_GUIStart(LPDIRECT3DDEVICE9 pDevice)
{
	if (ms_bInit)
		return;

	D3DDEVICE_CREATION_PARAMETERS params;
	ZeroMemory(&params, sizeof(D3DDEVICE_CREATION_PARAMETERS));
	pDevice->GetCreationParameters(&params);
	ms_hWindow = params.hFocusWindow;
	ImGui_Init(pDevice);
	ms_bInit = true;
}

void GUIImplementationDX9::ImGui_Process(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ms_bInit)
		return;

	if (ms_bShouldReloadFonts)
		ImGui_ReloadFont();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	GUI_Process();


	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	TheMenu->Process();
}

void GUIImplementationDX9::GUI_Process()
{
	ImGui::GetIO().MouseDrawCursor = false;

	static bool ms_bFirstDraw = true;

	if (ms_bFirstDraw)
	{
		Notifications->SetNotificationTime(9500);
		Notifications->PushNotification("ScarfaceHook %s is running! Press %s to open the menu. Build date: %s\n", SCARFACEHOOK_VERSION, eKeyboardMan::KeyToString(SettingsMgr->iHookMenuOpenKey), __DATE__);
		ms_bFirstDraw = false;
	}

	Notifications->Draw();
	TheMenu->Draw();
}

void GUIImplementationDX9::OnBeforeReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}

void GUIImplementationDX9::OnAfterReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_CreateDeviceObjects();
}
