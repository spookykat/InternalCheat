#pragma once
#include <Windows.h>
#include "EntityList.h"
#include "LocalPlayer.h"

class TriggerBot {
public:
	TriggerBot(DWORD &ClientBaseAddr);
	void Run(LocalPlayer &localPlayer,EntityList &entityList);
	static bool enabled;
private:
	DWORD& ClientBaseAddr;
};