#pragma once
#ifndef VECTOR3_H  
#define VECTOR3_H
struct Vector3
{
	float x, y, z;
};

Vector3 Vector3Subtract(Vector3 x, Vector3 y);
Vector3 Vector3Add(Vector3 x, Vector3 y);
#endif