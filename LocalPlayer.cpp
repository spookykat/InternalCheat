#include "LocalPlayer.h"
#include <iostream>

LocalPlayer::LocalPlayer(){}
LocalPlayer::LocalPlayer(DWORD &ClientBaseAddr){
	pEntityAddr = (DWORD*)(ClientBaseAddr + 0xDB558C);
};