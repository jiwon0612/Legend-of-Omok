#pragma once
#include"pch.h"

using std::clamp;

float Lerp(float _a, float _b, float _t)
{
	return (1 - _t) * _a + _b * _t;
}

Vector2 Lerp(const Vector2& _a, const Vector2& _b, float _t)
{
	return Vector2
	(
		(1 - _t) * _a.x + _b.x * _t,
		(1 - _t) * _a.y + _b.y * _t
	);
}