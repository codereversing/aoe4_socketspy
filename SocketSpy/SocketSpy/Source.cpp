#define _CRT_SECURE_NO_WARNINGS

#include "HookEngine.h"
#include "Hooks.h"

#include <cstdio>
#include <iostream>

using namespace SocketSpy;

__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID reserved)
{
	static HookEngine hookEngine{};

	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		if (AllocConsole()) {
			(void)freopen("CONOUT$", "w", stdout);
			(void)freopen("CONOUT$", "w", stderr);
			SetConsoleTitle(L"Console");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cerr << "DLL Loaded" << std::endl;
		}

		(void)hookEngine.Hook("Ws2_32.dll", "send", sendHook);
		// (void)hookEngine.Hook("Ws2_32.dll", "recv", recvHook);
	}

	if (dwReason == DLL_PROCESS_DETACH) {
		(void)hookEngine.Unhook("Ws2_32.dll", "send");
		// (void)hookEngine.Unhook("Ws2_32.dll", "recv");
	}

	return TRUE;
}