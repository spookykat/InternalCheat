#include <d3d9.h>
#include <d3dx9.h>


#pragma once
void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);