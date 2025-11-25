#pragma once
#include "Object.h"
class TweeningObject : public Object
{
public:
	TweeningObject();
	~TweeningObject();
public:
	void Update() override;
public:
	void SetAnimationSpeed(float _speed) { animationSpeed = _speed; }
	void MoveToPosition(const Vector2& _startPos, const Vector2& _endPos);
	void ScaleToSize(const Vector2& _startSize, const Vector2& _endSize);

private:
	Vector2 startMovePosition;
	Vector2 endMovePosition;
	Vector2 startScaleSize;
	Vector2 endScaleSize;
	float animationSpeed;
	float moveTweenTimer;
	float scaleTweenTimer;
	bool isMoveTweenEnd;
	bool isScaleTweenEnd;
	bool isTweenEnd;
};

