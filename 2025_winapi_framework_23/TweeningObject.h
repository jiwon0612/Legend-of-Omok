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
	void SetMoveTweenSpeed(float _speed) { moveTweenSpeed = _speed; }
	void SetScaleTweenSpeed(float _speed) { scaleTweenSpeed = _speed; }
	void MoveToPosition(const Vector2& _startPos, const Vector2& _endPos);
	void ScaleToSize(const Vector2& _startSize, const Vector2& _endSize);

public:
	bool IsMoveTween() const { return isMoveTween; }
	bool IsScaleTween() const { return isScaleTween; }

private:
	Vector2 startMovePosition;
	Vector2 endMovePosition; 
	Vector2 startScaleSize;
	Vector2 endScaleSize;
	float moveTweenSpeed;
	float scaleTweenSpeed;
	float moveTweenTimer;
	float scaleTweenTimer;
	bool isMoveTween;
	bool isScaleTween;
	bool isTween;
};

