#pragma once
#include <Windows.h>
#include "LocalPlayer.h"
class BunnyHop {
public:
	BunnyHop(DWORD& ClientBaseAddr);
	void Run(LocalPlayer localPlayer);
private:
	DWORD ClientBaseAddr;
};