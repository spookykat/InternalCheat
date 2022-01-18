#include "LocalPlayer.h"
#include <iostream>


LocalPlayer::LocalPlayer(){}
LocalPlayer::LocalPlayer(DWORD &ClientBaseAddr){
	pEntityAddr = (DWORD*)(ClientBaseAddr + offsets::LocalPlayer);
};
Vector3 LocalPlayer::GetCameraOffset() {
	Vector3 CameraOffset = *(Vector3*)(*pEntityAddr + offsets::VecView);
	return CameraOffset;
}