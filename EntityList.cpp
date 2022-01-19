#include "EntityList.h"
EntityList::EntityList(DWORD& ClientBaseAddr) {
	getEntities(ClientBaseAddr);
}
void EntityList::getEntities(DWORD ClientBaseAddr) {
	for (int i = 0; i <= 64; i++) 
	{
		Entity tempEnt = Entity(ClientBaseAddr, i);
		if (tempEnt.isNotNull())
		{
			Entities.push_back(tempEnt);
		}
	}
}