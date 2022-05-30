#include "LocalPlayer.h"
#include <iostream>


LocalPlayer::LocalPlayer(){}
LocalPlayer::LocalPlayer(DWORD &ClientBaseAddr, DWORD &EngineBaseAddr){
	pEntityAddr = (DWORD*)(ClientBaseAddr + offsets::LocalPlayer);
	this->clientState = *(DWORD*)(EngineBaseAddr + offsets::ClientState);
};
Vector3 LocalPlayer::GetCameraOffset() {
	Vector3 CameraOffset = *(Vector3*)(*pEntityAddr + offsets::VecView);
	return CameraOffset;
}
int LocalPlayer::getPlayerID() {
	return *(int*)(clientState + offsets::GetLocalPlayer);
}
BYTE LocalPlayer::getFlag() {
	return *(BYTE*)(*pEntityAddr + offsets::Flag);
}
int LocalPlayer::getCrossID() {
	return *(int*)(*pEntityAddr + offsets::CrosshairId);
}