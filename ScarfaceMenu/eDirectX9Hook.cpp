#include "eDirectX9Hook.h"
#include "ScarfaceMenu.h"

EndScene eDirectX9Hook::m_pEndScene;
HWND eDirectX9Hook::ms_hWindow;
WNDPROC eDirectX9Hook::ms_pWndProc;
Reset eDirectX9Hook::m_pReset;

bool eDirectX9Hook::ms_bInit;
bool eDirectX9Hook::ms_bShouldReloadFonts;

void eDirectX9Hook::Init()
{
	m_pEndScene = 0;
	ms_hWindow = 0;
	ms_pWndProc = 0;
	ms_bInit = false;
	ms_bShouldReloadFonts = false;
}


void eDirectX9Hook::InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(ms_hWindow);
	ImGui_ImplDX9_Init(pDevice);
}


long __stdcall eDirectX9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
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


	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = true;


	TheMenu->Render();
	TheMenu->Process();
	//TheMenu->Draw();

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return m_pEndScene(pDevice);
}

long __stdcall eDirectX9Hook::Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_CreateDeviceObjects();
	return m_pReset(pDevice, pPresentationParameters);
}

LRESULT __stdcall eDirectX9Hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_F1)
			TheMenu->active ^= 1;
		break;
	default:
		break;
	}

	if (TheMenu->active)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI DirectXHookThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&eDirectX9Hook::m_pEndScene, eDirectX9Hook::EndScene);
			kiero::bind(16, (void**)&eDirectX9Hook::m_pReset, eDirectX9Hook::Reset);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}