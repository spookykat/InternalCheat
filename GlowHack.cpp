#include "GlowHack.h"
#include "GlowObject.h"
#include "Offsets.h"
#include <iostream>
#include "imgui/imgui.h"

float Glowhack::teamColor[4] = {0, 0, 1, 1};
float Glowhack::enemyColor[4] = {1, 0.0f, 0.0f, 1 };
bool Glowhack::enabled = false;
void Glowhack::Draw() {
	ImGui::Text("GlowHack");
	ImGui::Checkbox("Enabled", &Glowhack::enabled);
	ImGui::ColorEdit4("Team Color", Glowhack::teamColor);
	ImGui::ColorEdit4("Enemy Color", Glowhack::enemyColor);
}
Glowhack::Glowhack(DWORD &ClientBaseAddr) {
	this->ClientBaseAddr = ClientBaseAddr;
	glowObjectManager = *(DWORD*)(ClientBaseAddr + offsets::GlowObjectManager);
}
void Glowhack::Run(EntityList entityList, LocalPlayer localPlayer) {
	GlowObject glowObject;
	if (entityList.Entities.size() != 0)
	{
		for (int i = 0; i < entityList.Entities.size() - 1; i++) //-1 because last one is null
		{
			if (!entityList.Entities[i].isDormant() && entityList.Entities[i].getHealth() != 0)
			{

				if (localPlayer.getTeamNum() != entityList.Entities[i].getTeamNum())
				{
					glowObject = ColorToGlowObject(enemyColor);
				}
				else
				{
					glowObject = ColorToGlowObject(teamColor);
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
}