#include "eDirectX9Hook.h"
#include "plugin/ScarfaceMenu.h"
#include "utils/MemoryMgr.h"
#include "font.h"
#include "eNotifManager.h"
#include "SettingsMgr.h"
#include "eDirectInput8Hook.h"
#include "helper/eKeyboardMan.h"

using namespace Memory::VP;

D3DEndScene eDirectX9Hook::m_pEndScene;
HWND eDirectX9Hook::ms_hWindow;
WNDPROC eDirectX9Hook::ms_pWndProc;
D3DReset eDirectX9Hook::m_pReset;

bool eDirectX9Hook::ms_bInit;
bool eDirectX9Hook::ms_bShouldReloadFonts;

char eDirectX9Hook::ms_wndName[256] = {};
uintptr_t	eDirectX9Hook::ms_pFuncPtrs[2] = {};

// raw input
RAWINPUTDEVICE rawDevice[1];

void eDirectX9Hook::Init(const char* name)
{
	m_pEndScene = 0;
	ms_hWindow = 0;
	ms_pWndProc = 0;
	ms_bInit = false;
	ms_bShouldReloadFonts = false;
	Notifications->Init();
	sprintf(ms_wndName, name);
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

long __stdcall eDirectX9Hook::EndScene_Hook(LPDIRECT3DDEVICE9 pDevice)
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
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

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
	return m_pEndScene(pDevice);
}

long __stdcall eDirectX9Hook::Reset_Hook(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = m_pReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();
	return hr;
}

LRESULT __stdcall eDirectX9Hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iHookMenuOpenKey)
			TheMenu->m_bIsActive ^= 1;
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

IDirect3D9* __stdcall eDirectX9Hook::Direct3DCreate9_Hook(UINT SDKVersion)
{
	IDirect3D9* d3d = Direct3DCreate9(SDKVersion);

	HWND hWnd = FindWindowA(ms_wndName, 0);
	if (hWnd)
	{
		if (d3d)
		{
			MH_Initialize();
			D3DPRESENT_PARAMETERS pp = {};
			pp.hDeviceWindow = hWnd;
			pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			pp.Windowed = true;

			IDirect3DDevice9* pDevice = nullptr;
			if (FAILED(d3d->CreateDevice(0, D3DDEVTYPE_HAL, pp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &pDevice)))
			{
				d3d->Release();
				return false;
			}
			
			void** vTable = (void**)(*(int*)pDevice);
			uintptr_t ms_pFuncPtrs[2];
			ms_pFuncPtrs[0] = (uintptr_t)vTable[42];
			ms_pFuncPtrs[1] = (uintptr_t)vTable[16];


			if (MH_CreateHook((void*)ms_pFuncPtrs[0], EndScene_Hook, (LPVOID*)&m_pEndScene) != MH_OK || MH_EnableHook((void*)ms_pFuncPtrs[0]) != MH_OK)
			{
				MessageBox(0, "Failed to hook EndScene!",0,0);
			}
			if (MH_CreateHook((void*)ms_pFuncPtrs[1], Reset_Hook, (LPVOID*)&m_pReset) != MH_OK || MH_EnableHook((void*)ms_pFuncPtrs[1]) != MH_OK)
			{
				MessageBox(0, "Failed to hook Reset!", 0, 0);
			}
			
			// no longer needed
			pDevice->Release();
		}
	}

	return d3d;
}

void eDirectX9Hook::Destroy()
{
	MH_DisableHook((void*)ms_pFuncPtrs[0]);
	MH_DisableHook((void*)ms_pFuncPtrs[1]);
}
