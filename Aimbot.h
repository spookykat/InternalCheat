#pragma once
#include "LocalPlayer.h"
#include "EntityList.h"
#include "Offsets.h"
class Aimbot
{
public:
	Aimbot(DWORD &engineBaseAddr);
	void AimAt(LocalPlayer& localPlayer, Entity& Target);
	void Toggle() { enabled = !enabled; }
	bool IsToggled() { return enabled; }
	void Run(LocalPlayer& localPlayer, EntityList &entityList);
private:
	DWORD* pClientState;
	bool enabled = false;
	Entity GetBestTarget(LocalPlayer& localPlayer, EntityList entityList);
};

