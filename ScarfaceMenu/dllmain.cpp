// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

#include "gui/dx9hook.h"
#include "gui/log.h"
#include "gui/notifications.h"

#include "plugin/Menu.h"
#include "plugin/Settings.h"

#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"

#include <Commctrl.h>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32.lib")

using namespace Memory::VP;

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	eLog::Message(__FUNCTION__, "INFO: ScarfaceHook Begin!");

	Notifications->Init();
	if (_pattern(PATID_Camera_SetPosition))
		InjectHook(_pattern(PATID_Camera_SetPosition), &Camera::SetPositionHooked, PATCH_JUMP);
	if (_pattern(PATID_Camera_CollisionFunction_Hook))
		InjectHook(_pattern(PATID_Camera_CollisionFunction_Hook), &Camera::UnknownCollision, PATCH_CALL);
	if (_pattern(PATID_DinputCoopLevel))
		Patch<char>(_pattern(PATID_DinputCoopLevel), 6);

	HANDLE h = 0;

	h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX9Hook_Thread), 0, NULL, 0);

	if (!(h == nullptr)) CloseHandle(h);
}

bool ValidateGameVersion()
{
	PatternSolver::Initialize();

	if (PatternSolver::CheckMissingPatterns())
	{
		int nButtonPressed = 0;
		TASKDIALOGCONFIG config;
		ZeroMemory(&config, sizeof(TASKDIALOGCONFIG));

		const TASKDIALOG_BUTTON buttons[] = {
			{ IDOK, L"Launch anyway\nThe game might crash or have missing features!" },
			{ IDNO, L"Exit" }
		};
		config.cbSize = sizeof(config);

		config.dwFlags = TDF_ENABLE_HYPERLINKS | TDF_CAN_BE_MINIMIZED | TDF_USE_COMMAND_LINKS;
		config.pszMainIcon = TD_WARNING_ICON;

		config.pszWindowTitle = L"Warning";
		config.pszMainInstruction = L"ScarfaceHook";
		config.pszContent = L"Could not start ScarfaceHook!\n\n"
			L"One or more code patterns could not be found, this might indicate"
			L" that game version is not supported or the plugin has not been updated.\n\n"
			L"ScarfaceHook officially is only tested with no-cd 1.0.0.1 and 1.0.0.2 US versions.\n"
			L"Check log for more details.\n";


		config.pButtons = buttons;
		config.cButtons = ARRAYSIZE(buttons);

		if (SUCCEEDED(TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL)))
		{
			switch (nButtonPressed)
			{
			case IDOK:
				return true;
				break;
			case IDNO:
				exit(0);
				break;
			default:
				break;
			}
		}
	}
	return true;
}


extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		eLog::Initialize();

		if (ValidateGameVersion())
		{
			OnInitializeHook();
		}

	}
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		GUIImplementationDX9::Shutdown();
		break;
	}
	return TRUE;
}