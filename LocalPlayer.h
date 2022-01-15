#pragma once
#include <string>
#include "Windows.h"
#include "Vector3.h"
#include "Entity.h"

class LocalPlayer : public Entity
{
public:
	LocalPlayer();
	LocalPlayer(DWORD &ClientBaseAddr);

private:
};

