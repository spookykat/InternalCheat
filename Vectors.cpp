#include "Vectors.h"

Vector3 Vector3Subtract(Vector3 x, Vector3 y) {
	Vector3 z;
	z.x = x.x - y.x;
	z.y = x.y - y.y;
	z.z = x.z - y.z;
	return z;
}
Vector3 Vector3Add(Vector3 x, Vector3 y) {
	Vector3 z;
	z.x = x.x + y.x;
	z.y = x.y + y.y;
	z.z = x.z + y.z;
	return z;
}