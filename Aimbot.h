#pragma once
#include "LocalPlayer.h"
#include "EntityList.h"
#include "Offsets.h"
class Aimbot
{
public:
	Aimbot(LocalPlayer &localplayer, DWORD &engineBaseAddr);
	void AimAt(Entity& Target);
	void Toggle() { enabled = !enabled; }
	bool IsToggled() { return enabled; }
	void Run(EntityList &entityList);
private:
	LocalPlayer localPlayer;
	DWORD* pClientState;
	bool enabled = false;
	Entity GetBestTarget(EntityList entityList);
};

