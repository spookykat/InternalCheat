#pragma once
#include <Windows.h>
#include "EntityList.h"
#include "LocalPlayer.h"
class Glowhack
{
public:
	Glowhack(DWORD &ClientBaseAddr);
	void Run(EntityList entityList, LocalPlayer localPlayer);
	static void Draw();
	static bool enabled;
private:
	DWORD glowObjectManager;
	DWORD ClientBaseAddr;
	static float enemyColor[4];
	static float teamColor[4];
};