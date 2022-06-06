#pragma once
#ifndef VECTORS_H  
#define VECTORS_H
struct Vector2 {
	float x, y;
};
struct Vector3
{
	float x, y, z;
	Vector3(){};
	Vector3(int x, int y, int z) : x(x), y(y), z(z) {}
};
struct Vector4 {
	float x, y, z, w;
};

Vector3 Vector3Subtract(Vector3 x, Vector3 y);
Vector3 Vector3Add(Vector3 x, Vector3 y);
#endif