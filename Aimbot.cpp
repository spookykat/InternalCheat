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