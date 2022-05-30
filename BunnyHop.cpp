#include "BunnyHop.h"
#include "Offsets.h"

BunnyHop::BunnyHop(DWORD& ClientBaseAddr) {
	this->ClientBaseAddr = ClientBaseAddr;
}
void BunnyHop::Run(LocalPlayer localPlayer) {
	BYTE flag = localPlayer.getFlag();
	if (flag & (1 << 0))
	{
		DWORD* ForceJump = (DWORD*)(ClientBaseAddr + offsets::ForceJump);
		*ForceJump = 6;
	}
}