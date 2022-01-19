#include "Entity.h"

Entity::Entity(){
	isNull = true;
}

Entity::Entity(DWORD& ClientBaseAddr, int i){
	pEntityAddr = (DWORD*)(ClientBaseAddr + offsets::Entitylist + (i * 0x10));
	pRadarBase = (DWORD*)(ClientBaseAddr + offsets::RadarBase);
	setName(i);
}

int Entity::getHealth() {
	pHealth = (int*)(*pEntityAddr + offsets::Health);
	return *pHealth;
}
Vector3 Entity::getVecOrigin() {
	pVecOrigin = (Vector3*)(*pEntityAddr + offsets::VecOrigin);
	return *pVecOrigin;
}
void Entity::setName(int i) {
	name = *(wchar_t*)(*pRadarBase + (0x1E0 * (i + 1)) + 0x24);
}
bool Entity::isDormant() {
	Dormant = *(bool*)(*pEntityAddr + offsets::bDormant);
	return Dormant;
}
int Entity::getTeamNum() {
	teamNum = *(int*)(*pEntityAddr + offsets::TeamNum);
	return teamNum;
}
Vector3 Entity::getBonePos(int boneID) {
	Vector3 bonePos;
	DWORD boneMatrix = *(DWORD*)(*pEntityAddr + offsets::BoneMatrix);
	bonePos.x = *(float*)(boneMatrix + 0x30 * boneID + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * boneID + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * boneID + 0x2C);
	return bonePos;
}
DWORD Entity::getGlowIndex() {
	return *(DWORD*)(*pEntityAddr + offsets::GlowIndex);
}
int Entity::SpottedByMask() {
	return *(int*)(*pEntityAddr + offsets::SpottedByMask);
}