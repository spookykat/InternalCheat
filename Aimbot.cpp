#include "Aimbot.h"
#include <iostream>
#include <corecrt_math_defines.h>
#include "Vectors.h"
#include "imgui/imgui.h"

bool Aimbot::throughWalls = false;

void Aimbot::Draw() {
	ImGui::Text("Aimbot");
	ImGui::Checkbox("TriggerBot", &TriggerBot::enabled);
	ImGui::Checkbox("Aim through walls", &Aimbot::throughWalls);
}
Aimbot::Aimbot(DWORD &engineBaseAddr) {
	this->pClientState = (DWORD*)(engineBaseAddr + offsets::ClientState);
}

void Aimbot::AimAt(LocalPlayer& localPlayer, Entity &Target) {
	Vector3 LocalPlayerPos = localPlayer.getVecOrigin();
	Vector3 LocalPlayerView = Vector3Add(LocalPlayerPos, localPlayer.GetCameraOffset());

	Vector3 TargetPos = Target.getVecOrigin();
	Vector3 TargetBonePos = Target.getBonePos(8); //8 is head

	Vector3 Delta = Vector3Subtract(TargetBonePos, LocalPlayerView);

	float pitch = -asin(Delta.z / sqrt(pow(Delta.x, 2) + pow(Delta.y, 2) + pow(Delta.z, 2))) * (180 / M_PI);
	float yaw = atan2(Delta.y, Delta.x) * (180 / M_PI);

	float* pPitch = (float*)(*pClientState + offsets::ViewAngles);
	float* pYaw = (float*)(*pClientState + offsets::ViewAngles + 0x4);

	*pPitch = pitch;
	*pYaw = yaw;
}
void Aimbot::Run(LocalPlayer& localPlayer, EntityList &entityList) {
	Entity Target = GetBestTarget(localPlayer, entityList);
	if (!Target.isEmpty())
	{
		AimAt(localPlayer, Target);
	}
	
}
Entity Aimbot::GetBestTarget(LocalPlayer& localPlayer, EntityList entityList) {
	Entity bestTarget;
	double shortestDistance = 9999999;
	Vector3 LocalPlayerPos = localPlayer.getVecOrigin();
	Vector3 LocalPlayerView = Vector3Add(LocalPlayerPos, localPlayer.GetCameraOffset());

	int LocalPlayerTeam = localPlayer.getTeamNum();
	for (int i = 0; i < entityList.Entities.size() - 1; i++) //  -1 because last one is just null?? 
	{
		if (!entityList.Entities[i].isDormant() &&  LocalPlayerTeam != entityList.Entities[i].getTeamNum() && entityList.Entities[i].getHealth() > 0 && (entityList.Entities[i].SpottedByMask() & (1 << localPlayer.getPlayerID()) || throughWalls))
		{
			Vector3 EntityPos = entityList.Entities[i].getVecOrigin();
			Vector3 Delta = Vector3Subtract(EntityPos, LocalPlayerView);
			double distance = sqrt(pow(Delta.x, 2) + pow(Delta.y, 2) + pow(Delta.z, 2));
			if (entityList.Entities[i].SpottedByMask() & (1 << localPlayer.getPlayerID())) {
				distance -= 10000;
			}
			if (distance < shortestDistance)
			{
				shortestDistance = distance; // vieze line <33 denis
				bestTarget = entityList.Entities[i];
			}
		}		
	}
	return bestTarget;
}