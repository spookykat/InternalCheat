#pragma once
#include "Windows.h"
#include "Vector3.h"
#include <string>
#include "Offsets.h"
class Entity
{
public:
	Entity();
	Entity(DWORD& ClientBaseAddr, int i);
	int getHealth();
	Vector3 getVecOrigin();
	bool isNotNull() { return !*pEntityAddr == NULL; }
	bool isEmpty() { return isNull; }
	wchar_t getName() { return name; }
	bool isDormant();
	int getTeamNum();
	Vector3 getBonePos(int boneID);
private:
	int* pHealth;
	Vector3* pVecOrigin;
	DWORD* pRadarBase;
	wchar_t name;
	bool Dormant;
	int teamNum;
	bool isNull;
	void setName(int i);
protected:
	DWORD* pEntityAddr;
};