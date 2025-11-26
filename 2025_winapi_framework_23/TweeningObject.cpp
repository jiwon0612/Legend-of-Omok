#include "pch.h"
#include "TweeningObject.h"
#include "Mathf.h"

TweeningObject::TweeningObject()
	: startMovePosition(0, 0)
	, endMovePosition(0, 0)
	, startScaleSize(0, 0)
	, endScaleSize(0, 0)
	, moveTweenSpeed(1)
	, moveTweenTimer(0)
	, scaleTweenTimer(0)
	, isMoveTween(false)
	, isScaleTween(false)
	, isTween(false)
{
}

TweeningObject::~TweeningObject()
{
}

void TweeningObject::Update()
{
	if (isMoveTween)
	{
		moveTweenTimer += fDT * moveTweenSpeed;
		Vector2 lerpValue = Lerp(startMovePosition, endMovePosition, moveTweenTimer);
		SetPos(lerpValue);

		if (moveTweenTimer >= 1)
		{
			isMoveTween = false;
			SetPos(endMovePosition);
		}
	}
	if (isScaleTween)
	{
		scaleTweenTimer += fDT * moveTweenSpeed;
		SetSize(Lerp(startScaleSize, endScaleSize, scaleTweenTimer));
		if (scaleTweenTimer >= 1)
		{
			isScaleTween = false;
			SetSize(endScaleSize);
		}
	}


}

void TweeningObject::MoveToPosition(const Vector2& _startPos, const Vector2& _endPos)
{
	startMovePosition = _startPos;
	endMovePosition = _endPos;
	moveTweenTimer = 0.f;
	isMoveTween = true;
}

void TweeningObject::ScaleToSize(const Vector2& _startSize, const Vector2& _endSize)
{
	startScaleSize = _startSize;
	endScaleSize = _endSize;
	scaleTweenTimer = 0.f;
	isScaleTween = true;
}



