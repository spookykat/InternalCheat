#pragma once
#include "LocalPlayer.h"
#include "EntityList.h"
#include "Offsets.h"
#include "TriggerBot.h"
class Aimbot
{
public:
	Aimbot(DWORD &engineBaseAddr);
	void AimAt(LocalPlayer& localPlayer, Entity& Target);
	void Run(LocalPlayer& localPlayer, EntityList &entityList);
	static void Draw();
	static bool throughWalls;
private:
	DWORD* pClientState;
	Entity GetBestTarget(LocalPlayer& localPlayer, EntityList entityList);
};

