#include "EntityList.h"
EntityList::EntityList(DWORD& ClientBaseAddr) {
	getEntities(ClientBaseAddr);
}
void EntityList::getEntities(DWORD ClientBaseAddr) {
	for (int i = 1; i <= 64; i++) //1 because 0 is localplayer
	{
		Entity tempEnt = Entity(ClientBaseAddr, i);
		if (tempEnt.isNotNull())
		{
			Entities.push_back(tempEnt);
		}
	}
}