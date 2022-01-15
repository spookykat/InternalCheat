#pragma once
#include "Windows.h"
#include "Vector3.h"
class Entity
{
public:
	Entity();
	Entity(DWORD& ClientBaseAddr, int i);
	int getHealth();
	Vector3 getVecOrigin();
private:
	int* pHealth;
	Vector3* pVecOrigin;
protected:
	DWORD* pEntityAddr;
};

