#include "Entity.h"
Entity::Entity(){}

Entity::Entity(DWORD& ClientBaseAddr, int i){
	pEntityAddr = (DWORD*)(ClientBaseAddr + 0x4DD0AB4 + (i * 0x10));
	pRadarBase = (DWORD*)(ClientBaseAddr + 0x520582C);
	setName(i);
}

int Entity::getHealth() {
	pHealth = (int*)(*pEntityAddr + 0x100);
	return *pHealth;
}
Vector3 Entity::getVecOrigin() {
	pVecOrigin = (Vector3*)(*pEntityAddr + 0x138);
	return *pVecOrigin;
}
void Entity::setName(int i) {
	name = *(wchar_t*)(*pRadarBase + (0x1E0 * (i + 1)) + 0x24);
}