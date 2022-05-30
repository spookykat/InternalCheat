#include "TriggerBot.h"

TriggerBot::TriggerBot(DWORD& ClientBaseAddr) : ClientBaseAddr(ClientBaseAddr) {
}

void TriggerBot::Run(LocalPlayer& localPlayer, EntityList& entityList) {
	int target = localPlayer.getCrossID();
	if (target - 1 >= 0 && target -1 <= 64)
	{
		if (localPlayer.getTeamNum() != entityList.Entities[target - 1].getTeamNum() && entityList.Entities[target - 1].getHealth() > 0)
		{
			DWORD* ForceJump = (DWORD*)(ClientBaseAddr + offsets::ForceAttack);
			*ForceJump = 6;
		}
	}
	
}