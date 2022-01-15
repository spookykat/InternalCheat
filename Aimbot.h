#pragma once
#include "LocalPlayer.h"
class Aimbot
{
public:
	Aimbot(LocalPlayer &localplayer, DWORD &engineBaseAddr);
	void AimAt(Entity& Target);
	void Toggle() { enabled = !enabled; }
	bool IsToggled() { return enabled; }
private:
	LocalPlayer localPlayer;
	DWORD* pClientState;
	bool enabled = false;
};

