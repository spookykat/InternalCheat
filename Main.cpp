#include <iostream>
#include "Windows.h"
#include "LocalPlayer.h"
#include "Aimbot.h"
#include "EntityList.h"
#include "GlowHack.h"
FILE* pFile = nullptr;

void mainHack() {
	AllocConsole();						//attaches console	
	freopen_s(&pFile, "CONOUT$", "w", stdout);
	std::cout << "We Can Use Console For Debugging!\n";
	DWORD ClientBaseAddr = (DWORD)GetModuleHandle(L"client.dll");
	DWORD EngineBaseAddr = (DWORD)GetModuleHandle(L"engine.dll");

	LocalPlayer localPlayer = LocalPlayer(ClientBaseAddr, EngineBaseAddr);
	Aimbot aimbot(localPlayer, EngineBaseAddr);
	Glowhack glowhack(ClientBaseAddr);
	while (true)
	{
		if (GetAsyncKeyState(VK_XBUTTON2)) {
			EntityList entitylist(ClientBaseAddr);
			if (entitylist.Entities.size() - 1 != 0)
			{
				aimbot.Run(entitylist);
			}
		}
		EntityList entitylist(ClientBaseAddr);
		glowhack.Run(entitylist,localPlayer);
	}
}

BOOL WINAPI DllMain(HMODULE hmodule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hmodule);		
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainHack, NULL, NULL, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		
	}
	return TRUE;
}
