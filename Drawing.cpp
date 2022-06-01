#include "Drawing.h"
#include <d3dx9core.h>

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET,color, 0, 0);
}
void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice) {
	ID3DXLine* LineL;
	D3DXCreateLine(pDevice, &LineL);
	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	LineL->SetWidth(thickness);
	LineL->Draw(Line, 2, color);
	LineL->Release();
}
