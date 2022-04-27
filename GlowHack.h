#pragma once
#include <Windows.h>
#include "EntityList.h"
#include "LocalPlayer.h"
class Glowhack
{
public:
	Glowhack(DWORD &ClientBaseAddr);
	void Run(EntityList entityList, LocalPlayer localPlayer);
private:
	DWORD glowObjectManager;
	DWORD ClientBaseAddr;
};