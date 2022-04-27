#include <iostream>
#include "Windows.h"
#include "LocalPlayer.h"
#include "Aimbot.h"
#include "EntityList.h"
#include "GlowHack.h"
#include "tlhelp32.h"

FILE* pFile = nullptr;



DWORD GetModuleBase(const wchar_t* ModuleName, DWORD ProcessId) {
	MODULEENTRY32 ModuleEntry = { 0 };
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);


	if (!SnapShot)
		return NULL;


	ModuleEntry.dwSize = sizeof(ModuleEntry);


	if (!Module32First(SnapShot, &ModuleEntry))
		return NULL;


	do {
		if (!wcscmp(ModuleEntry.szModule, ModuleName)) {
			CloseHandle(SnapShot);
			return (DWORD)ModuleEntry.modBaseAddr;
		}
	} while (Module32Next(SnapShot, &ModuleEntry));


	CloseHandle(SnapShot);
	return NULL;
}
DWORD GetProcId(const wchar_t* procName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do {
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

void mainHack() {
	AllocConsole();						//attaches console	
	freopen_s(&pFile, "CONOUT$", "w", stdout);
	std::cout << "We Can Use Console For Debugging!\n";

	DWORD ProcId = GetProcId(L"csgo");
	DWORD ClientBaseAddr = GetModuleBase(L"client.dll", ProcId);
	DWORD EngineBaseAddr = GetModuleBase(L"engine.dll", ProcId);

	bool lastToggle = false;
	bool currentToggle = false;
	bool GlowEnable = false;
	while (true)
	{
		lastToggle = currentToggle;
		currentToggle = GetAsyncKeyState(VK_NUMPAD0) & 0x01;
		
		LocalPlayer localPlayer = LocalPlayer(ClientBaseAddr, EngineBaseAddr);
		EntityList entitylist(ClientBaseAddr);
		Aimbot aimbot(EngineBaseAddr);
		Glowhack glowhack(ClientBaseAddr);
		
		if (GetAsyncKeyState(VK_XBUTTON2)) {
			if (entitylist.Entities.size() - 1 != 0)
			{
				aimbot.Run(localPlayer, entitylist);
			}
		}
		if (currentToggle && lastToggle != currentToggle)
		{
			GlowEnable = !GlowEnable;
		}
		if (GlowEnable)
		{
			glowhack.Run(entitylist, localPlayer);
		}
		
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
