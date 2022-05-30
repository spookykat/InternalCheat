#pragma once
#include <string>
#include "Windows.h"
#include "Vector3.h"
#include "Entity.h"
#include "Offsets.h"

class LocalPlayer : public Entity
{
public:
	LocalPlayer();
	LocalPlayer(DWORD &ClientBaseAddr, DWORD &EngineBaseAddr);
	Vector3 GetCameraOffset();
	int getPlayerID();
	byte getFlag();
	int getCrossID();
private:
	DWORD clientState;
};

