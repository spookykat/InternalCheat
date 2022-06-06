#include "ESP.h"
#include "Offsets.h"
#include <Windows.h>
#include "imgui/imgui.h"

int ESP::BoxThickness = 2;
int ESP::snaplineThickness = 2;
bool ESP::snapLineEnabled = false;
bool ESP::boxesEnabled = false;
float ESP::teamColor[4] = { 0, 0, 1, 1 };
float ESP::enemyColor[4] = { 1, 0.0f, 0.0f, 1 };

void ESP::Draw() {
	ImGui::Text("ESP");
	ImGui::Checkbox("Snaplines", &ESP::snapLineEnabled);
	ImGui::Checkbox("Boxes", &ESP::boxesEnabled);
	ImGui::ColorEdit4("Team Color ESP", ESP::teamColor);
	ImGui::ColorEdit4("Enemy Color ESP", ESP::enemyColor);
}
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
void ESP::Run(EntityList entityList, LocalPlayer localPlayer) {
	if (entityList.Entities.size() != 0)
	{
		for (int i = 1; i < entityList.Entities.size() - 1; i++) //-1 because last one is null
		{
			if (!(entityList.Entities[i].getHealth() > 0) || entityList.Entities[i].isDormant())
				continue;

			D3DCOLOR color;
			if (entityList.Entities[i].getTeamNum() != localPlayer.getTeamNum()) {
				color = ImGUIColorToD3DXColor(ESP::enemyColor);
			}
			else {
				color = ImGUIColorToD3DXColor(ESP::teamColor);
			}
			if (ESP::boxesEnabled)
				DrawEspBox2D(entityList.Entities[i], color);
			if (ESP::snapLineEnabled)
				DrawSnaplines(entityList.Entities[i], color);
		}
	}
}
void ESP::DrawSnaplines(Entity entity, D3DCOLOR color) {
	Vector2 entPos2D;
	if (WorldToScreen(entity.getVecOrigin(), entPos2D))
		DrawLine(entPos2D.x, entPos2D.y, windowWidth / 2, windowHeight, snaplineThickness, color, pDevice);
}
void ESP::DrawEspBox2D(Entity entity, D3DXCOLOR color) {
	Vector2 feetPos2D, headPos2D;
	if (WorldToScreen(entity.getVecOrigin(), feetPos2D)) {
		Vector3 headPos = entity.getBonePos(8);
		WorldToScreen(Vector3Add(headPos, Vector3(0,0,7)), headPos2D);
		
		int height = abs(headPos2D.y - feetPos2D.y);
		int width = height / 2;
		Vector2 topleft, topright, bottomleft, bottomright;
		topleft.x = headPos2D.x - width / 2;
		topright.x = headPos2D.x + width / 2;
		topleft.y = topright.y = headPos2D.y;

		bottomleft.x = topleft.x;
		bottomright.x = topright.x;
		bottomright.y = bottomleft.y = feetPos2D.y;

		DrawLine(topleft, topright, ESP::BoxThickness, color, pDevice);
		DrawLine(bottomleft, bottomright, ESP::BoxThickness, color, pDevice);
		DrawLine(topright, bottomright, ESP::BoxThickness, color, pDevice);
		DrawLine(topleft, bottomleft, ESP::BoxThickness, color, pDevice);
	}
	
};