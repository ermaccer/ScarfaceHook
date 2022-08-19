#include <Windows.h>
#include <d3d9.h>
#include "minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef long(__stdcall* D3DEndScene)(LPDIRECT3DDEVICE9);
typedef long(__stdcall* D3DReset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

class eDirectX9Hook {
public:
	static D3DEndScene m_pEndScene;
	static D3DReset    m_pReset;
	static HWND ms_hWindow;
	static WNDPROC ms_pWndProc;
	static ImGuiStyle	ms_localStyleCopy;

	static uintptr_t	ms_pFuncPtrs[2];

	static bool ms_bInit;
	static bool ms_bShouldReloadFonts;

	static char ms_wndName[256];

	static void	   Init(const char* name);
	static void    SetImGuiStyle();
	static void    InitImGui(LPDIRECT3DDEVICE9 pDevice);
	static void	   ReloadImGuiFont();

	static long __stdcall EndScene_Hook(LPDIRECT3DDEVICE9 pDevice);
	static long __stdcall Reset_Hook(LPDIRECT3DDEVICE9 pDevice,D3DPRESENT_PARAMETERS *pPresentationParameters);
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static IDirect3D9* __stdcall Direct3DCreate9_Hook(UINT SDKVersion);

	static void Destroy();

};
