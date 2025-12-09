#pragma once
#include "SubWindow.h"
class Object;

class SpamWindow :
    public SubWindow
{
public:
	SpamWindow(HINSTANCE _hInst, wstring type, Vector2 pos, Vector2 size)
		: SubWindow(_hInst, type, pos, size)
	{
	}
	virtual ~SpamWindow() override;
	void AddObject(Object* obj);
private:
	std::vector<Object*> m_objects;
};

