#pragma once
#include "Entity.h"
#include <vector>
class EntityList
{
public:
	EntityList(DWORD& ClientBaseAddr);
	std::vector<Entity> Entities;
private:
	void getEntities(DWORD ClientBaseAddr);
	
};