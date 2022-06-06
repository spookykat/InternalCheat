#pragma once
struct GlowObject
{
	float r, g, b, a;
};
GlowObject ColorToGlowObject(float Color[4]) {
	GlowObject glow;
	glow.r = Color[0];
	glow.g = Color[1];
	glow.b = Color[2];
	glow.a = Color[3];
	return glow;
}