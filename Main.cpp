#include <iostream>
#include "LocalPlayer.h"
#include "Aimbot.h"
#include "EntityList.h"
#include "GlowHack.h"
#include "tlhelp32.h"
#include "Offsets.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "BunnyHop.h"
#include "TriggerBot.h"
#include "Drawing.h"
#include "ESP.h"
#include "hook.h"
#include "mem.h"

FILE* pFile = nullptr;
typedef HRESULT(APIENTRY* EndScene)(LPDIRECT3DDEVICE9 pDevice);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
static EndScene oEndScene;
HWND window =NULL;
WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int windowHeight, windowWidth;

DWORD ProcId;
DWORD wndProcID;
DWORD ClientBaseAddr;
DWORD EngineBaseAddr;
HMODULE hModule;
void* d3d9Device[119];

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
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void InitImGui(LPDIRECT3DDEVICE9 pDevice) {
	ImGui::CreateContext();
	D3DDEVICE_CREATION_PARAMETERS CP;
	pDevice->GetCreationParameters(&CP);
	window = CP.hFocusWindow;
	ImGuiIO& io = ImGui::GetIO();

	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);

	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.Fonts->AddFontDefault();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
bool show = false;
bool bhoptoggle = false;
int switchtab = 0;

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
	if (!init)
	{
		InitImGui(pDevice);
		D3DVIEWPORT9 viewPort;
		pDevice->GetViewport(&viewPort);
		windowHeight = viewPort.Height;
		windowWidth = viewPort.Width;
		init = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show = !show;
	}

	if (show) {
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("ImGui Window");
		if (ImGui::Button("Aimbot", ImVec2(100.0f, 0.0f))) {
			switchtab = 1;
		}
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("Visuals", ImVec2(100.0f, 0.0f))) {
			switchtab = 2;
		}
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("Misc", ImVec2(100.0f, 0.0f))) {
			switchtab = 3;
		}
		switch (switchtab)
		{
		case 1:
			Aimbot::Draw();
			break;
		case 2:
			Glowhack::Draw();
			ESP::Draw();
			break;
		case 3:
			ImGui::Checkbox("BunnyHop", &bhoptoggle);
			break;
		}
		
		
		
		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	
	DrawFilledRect(windowWidth / 2 - 2, windowHeight / 2 - 2, 4, 4, D3DCOLOR_ARGB(255, 255, 255, 255), pDevice);
	LocalPlayer localPlayer = LocalPlayer(ClientBaseAddr, EngineBaseAddr);
	EntityList entitylist(ClientBaseAddr);
	Aimbot aimbot(EngineBaseAddr);
	Glowhack glowhack(ClientBaseAddr);
	BunnyHop bunnyhop(ClientBaseAddr);
	TriggerBot triggerBot(ClientBaseAddr);
	ESP Esp(ClientBaseAddr, pDevice);

	if (GetAsyncKeyState(VK_XBUTTON2)) {
		if (entitylist.Entities.size() - 1 != 0)
		{
			aimbot.Run(localPlayer, entitylist);
		}
	}
	if (Glowhack::enabled)
	{
		glowhack.Run(entitylist, localPlayer);
	}
	if (GetAsyncKeyState(VK_SPACE) && bhoptoggle)
	{
		bunnyhop.Run(localPlayer);
	}
	if (TriggerBot::enabled) {
		triggerBot.Run(localPlayer, entitylist);
	}
	if (ESP::Enabled())
	{
		Esp.Run(entitylist, localPlayer);
	}
	return oEndScene(pDevice);
}

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(hwnd, &wndProcId);

	if (wndProcID != wndProcId)
		return TRUE; // skip to next window

	window = hwnd;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}
void mainHack() {
	/*AllocConsole();						//attaches console	
	freopen_s(&pFile, "CONOUT$", "w", stdout);
	std::cout << "We Can Use Console For Debugging!\n";*/

	ProcId = GetProcId(L"csgo.exe");
	ClientBaseAddr = GetModuleBase(L"client.dll", ProcId);
	EngineBaseAddr = GetModuleBase(L"engine.dll", ProcId);

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
		oEndScene = (EndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
	}
}

BOOL WINAPI DllMain(HMODULE hmodule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		hModule = hmodule;
		wndProcID = GetCurrentProcessId();
		DisableThreadLibraryCalls(hmodule);		
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainHack, NULL, NULL, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		
	}
	return TRUE;
}
