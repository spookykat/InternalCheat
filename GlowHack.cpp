#include "GlowHack.h"
#include "GlowObject.h"
#include "Offsets.h"
#include <iostream>
Glowhack::Glowhack(DWORD &ClientBaseAddr) {
	glowObjectManager = *(DWORD*)(ClientBaseAddr + offsets::GlowObjectManager);
}
void Glowhack::Run(EntityList entityList, LocalPlayer localPlayer) {
	GlowObject glowObject;
	for (int i = 0; i < entityList.Entities.size() - 1; i++) //-1 because last one is null
	{
		if (!entityList.Entities[i].isDormant())
		{
			if (localPlayer.getTeamNum() != entityList.Entities[i].getTeamNum())
			{
				glowObject.r = 1.f;
				glowObject.g = 0.f;
				glowObject.b = 0.f;
				glowObject.a = 1.f;
			}
			else
			{
				glowObject.r = 0.f;
				glowObject.g = 0.f;
				glowObject.b = 1.f;
				glowObject.a = 1.f;
			}
			GlowObject* TargetGlowObject = (GlowObject*)(glowObjectManager + (entityList.Entities[i].getGlowIndex() * 0x38) + 0x8);
			bool* renderWhenOcculed = (bool*)(glowObjectManager + (entityList.Entities[i].getGlowIndex() * 0x38) + 0x28);
			bool* renderWhenUnOcculed = (bool*)(glowObjectManager + (entityList.Entities[i].getGlowIndex() * 0x38) + 0x29);
			
			*TargetGlowObject = glowObject;
			*renderWhenOcculed = true;
			*renderWhenUnOcculed = false;
			
		}
	}
}