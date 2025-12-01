#pragma once
#include "Object.h"
class Stone :
    public Object
{
    public:
    Stone(StoneType type, Vec2 size, Vec2 pos);
    virtual ~Stone();
    void Render(HDC _hdc) override;
	StoneType GetType() const { return m_type; }

private:
	StoneType m_type;

    // Object을(를) 통해 상속됨
    void Update() override;
};

