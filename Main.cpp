#include <iostream>
#include "LocalPlayer.h"
#include "Aimbot.h"
#include "EntityList.h"
#include "GlowHack.h"
#include "tlhelp32.h"
#include "Offsets.h"
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "BunnyHop.h"
#include "TriggerBot.h"
#include "Drawing.h"
#include "ESP.h"

FILE* pFile = nullptr;
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
static EndScene oEndScene;
HWND window =NULL;
WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int windowHeight, windowWidth;

DWORD ProcId;
DWORD ClientBaseAddr;
DWORD EngineBaseAddr;
HMODULE hModule;

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

void InitImGui(LPDIRECT3DDEVICE9 pDevice) {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
bool show = false;
bool glowhacktoggle = false;
bool bhoptoggle = false;
bool triggerToggle = false;
bool espTracers = false;
bool aimThroughWall = false;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
	if (!init)
	{
		InitImGui(pDevice);
		D3DVIEWPORT9 viewPort;
		pDevice->GetViewport(&viewPort);
		windowHeight = viewPort.Height;
		windowWidth = viewPort.Width;
		init = true;
	}

	if (GetAsyncKeyState(VK_END)) {
		kiero::shutdown();
		return 0;
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
		
		ImGui::Checkbox("GlowHack", &glowhacktoggle);
		ImGui::Checkbox("BunnyHop", &bhoptoggle);
		ImGui::Checkbox("TriggerBot", &triggerToggle);
		ImGui::Checkbox("Tracers", &espTracers);
		ImGui::Checkbox("Aim through walls", &aimThroughWall);
		ImGui::End();
		
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	DrawFilledRect(windowWidth / 2 - 2, windowHeight / 2 - 2, 4, 4, D3DCOLOR_ARGB(255, 255, 255, 255), pDevice);

	LocalPlayer localPlayer = LocalPlayer(ClientBaseAddr, EngineBaseAddr);
	EntityList entitylist(ClientBaseAddr);
	Aimbot aimbot(EngineBaseAddr, aimThroughWall);
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
	if (glowhacktoggle)
	{
		glowhack.Run(entitylist, localPlayer);
	}
	if (GetAsyncKeyState(VK_SPACE) && bhoptoggle)
	{
		bunnyhop.Run(localPlayer);
	}
	if (triggerToggle) {
		triggerBot.Run(localPlayer, entitylist);
	}
	if (espTracers)
	{
		Esp.DrawSnaplines(entitylist, localPlayer);
	}
	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(hwnd, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
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

	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
}

BOOL WINAPI DllMain(HMODULE hmodule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		hModule = hmodule;
		DisableThreadLibraryCalls(hmodule);		
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainHack, NULL, NULL, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		
	}
	return TRUE;
}
