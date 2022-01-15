#pragma once
#include "Windows.h"
#include "Vector3.h"
#include <string>
class Entity
{
public:
	Entity();
	Entity(DWORD& ClientBaseAddr, int i);
	int getHealth();
	Vector3 getVecOrigin();
	bool isNotNull() { return !*pEntityAddr == NULL; }
	wchar_t getName() { return name; }
private:
	int* pHealth;
	Vector3* pVecOrigin;
	DWORD* pRadarBase;
	wchar_t name;
	void setName(int i);
protected:
	DWORD* pEntityAddr;
};

