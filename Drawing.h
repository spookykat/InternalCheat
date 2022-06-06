#include <d3d9.h>
#include <d3dx9.h>
#include "Vectors.h"

#pragma once
void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void DrawLine(Vector2 source, Vector2 destination, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
D3DCOLOR ImGUIColorToD3DXColor(float Color[4]);