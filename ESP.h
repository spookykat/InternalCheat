#pragma once
#include "Vectors.h"
#include "EntityList.h"
#include <d3d9.h>
#include "Drawing.h"
#include "LocalPlayer.h"

extern int windowHeight, windowWidth;
class ESP
{
public:
	ESP(DWORD& ClientBaseAddr, LPDIRECT3DDEVICE9& pDevice);
	void DrawSnaplines(EntityList entityList, LocalPlayer localPlayer);
private:
	bool WorldToScreen(Vector3 pos, Vector2 &screen);
	D3DMATRIX viewMatrix;
	LPDIRECT3DDEVICE9& pDevice;
};
