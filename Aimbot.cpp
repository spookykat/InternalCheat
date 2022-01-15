#include "Aimbot.h"
#include <iostream>
#include <corecrt_math_defines.h>

Aimbot::Aimbot(LocalPlayer &localPlayer, DWORD &engineBaseAddr) {
	this->localPlayer = localPlayer;
	this->pClientState = (DWORD*)(engineBaseAddr + 0x00589FC4);
}

void Aimbot::AimAt(Entity &Target) {
	Vector3 LocalPlayerPos = localPlayer.getVecOrigin();
	Vector3 TargetPos = Target.getVecOrigin();
	Vector3 Delta = Vector3Subtract(TargetPos, LocalPlayerPos);
	float pitch = -asin(Delta.z / sqrt(pow(Delta.x, 2) + pow(Delta.y, 2) + pow(Delta.z, 2))) * (180 / M_PI);
	float yaw = atan2(Delta.y, Delta.x) * (180 / M_PI);

	float* pPitch = (float*)(*pClientState + 0x4D90);
	float* pYaw = (float*)(*pClientState + 0x4D90 + 0x4);

	*pPitch = pitch;
	*pYaw = yaw;
}
void Aimbot::Run(EntityList &entityList) {
	Entity Target = GetBestTarget(entityList);
	AimAt(Target);
}
Entity Aimbot::GetBestTarget(EntityList entityList) {
	Entity bestTarget;
	double shortestDistance = 9999999;
	Vector3 LocalPlayerPos = localPlayer.getVecOrigin();
	for (int i = 0; i < entityList.Entities.size() - 1; i++) //  -1 because last one is just null?? 
	{
		Vector3 EntityPos = entityList.Entities[i].getVecOrigin();
		Vector3 Delta = Vector3Subtract(EntityPos, LocalPlayerPos);
		double distance = sqrt(pow(Delta.x, 2) + pow(Delta.y, 2) + pow(Delta.z, 2));
		if (distance < shortestDistance)
		{
			shortestDistance = distance; // vieze line <33 denis
			bestTarget = entityList.Entities[i];
		}
	}
	return bestTarget;
}