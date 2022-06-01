#include "ESP.h"
#include "Offsets.h"
#include <Windows.h>


ESP::ESP(DWORD& ClientBaseAddr, LPDIRECT3DDEVICE9& pDevice) : pDevice(pDevice) {
	viewMatrix = *(D3DMATRIX*)(ClientBaseAddr + offsets::ViewMatrix);
}
bool ESP::WorldToScreen(Vector3 pos, Vector2& screen) {
	Vector4 clipCoords;
	clipCoords.x = pos.x * viewMatrix.m[0][0] + pos.y * viewMatrix.m[0][1] + pos.z * viewMatrix.m[0][2] + viewMatrix.m[0][3];
	clipCoords.y = pos.x * viewMatrix.m[1][0] + pos.y * viewMatrix.m[1][1] + pos.z * viewMatrix.m[1][2] + viewMatrix.m[1][3];
	clipCoords.z = pos.x * viewMatrix.m[1][0] + pos.y * viewMatrix.m[1][1] + pos.z * viewMatrix.m[1][2] + viewMatrix.m[1][3];
	clipCoords.w = pos.x * viewMatrix.m[3][0] + pos.y * viewMatrix.m[3][1] + pos.z * viewMatrix.m[3][2] + viewMatrix.m[3][3];

	if (clipCoords.w < 0.1f)
		return false;

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}
void ESP::DrawSnaplines(EntityList entityList, LocalPlayer localPlayer) {
	if (entityList.Entities.size() != 0)
	{
		for (int i = 0; i < entityList.Entities.size() - 1; i++) //-1 because last one is null
		{
			if (!(entityList.Entities[i].getHealth() > 0) && !entityList.Entities[i].isDormant())
				continue;

			D3DCOLOR color;
			if (entityList.Entities[i].getTeamNum() != localPlayer.getTeamNum()) {
				color = D3DCOLOR_ARGB(255, 255, 0, 0);
			}
			else {
				color = D3DCOLOR_ARGB(255, 0, 0, 255);
			}
			Vector2 entPos2D;
			
			if (WorldToScreen(entityList.Entities[i].getVecOrigin(), entPos2D))
				DrawLine(entPos2D.x, entPos2D.y, windowWidth / 2, windowHeight, 2, color, pDevice);
		}
	}
}