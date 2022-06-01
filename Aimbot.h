#pragma once
#include "LocalPlayer.h"
#include "EntityList.h"
#include "Offsets.h"
class Aimbot
{
public:
	Aimbot(DWORD &engineBaseAddr, bool throughWall);
	void AimAt(LocalPlayer& localPlayer, Entity& Target);
	void Run(LocalPlayer& localPlayer, EntityList &entityList);
private:
	DWORD* pClientState;
	bool throughWall;
	Entity GetBestTarget(LocalPlayer& localPlayer, EntityList entityList);
};

