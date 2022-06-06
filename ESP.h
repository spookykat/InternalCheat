#pragma once
#include "Vectors.h"
#include "EntityList.h"
#include <d3d9.h>
#include "Drawing.h"
#include "LocalPlayer.h"
#include "Entity.h"
extern int windowHeight, windowWidth;
class ESP
{
public:
	ESP(DWORD& ClientBaseAddr, LPDIRECT3DDEVICE9& pDevice);
	void Run(EntityList entityList, LocalPlayer localPlayer);
	static void Draw();
	static bool snapLineEnabled;
	static bool boxesEnabled;
	static bool Enabled() { return (snapLineEnabled || boxesEnabled); }
private:
	bool WorldToScreen(Vector3 pos, Vector2 &screen);
	D3DMATRIX viewMatrix;
	LPDIRECT3DDEVICE9& pDevice;
	void DrawSnaplines(Entity entity, D3DCOLOR color);
	void DrawEspBox2D(Entity entity, D3DXCOLOR color);
	static float enemyColor[4];
	static float teamColor[4];
	static int snaplineThickness;
	static int BoxThickness;
};
