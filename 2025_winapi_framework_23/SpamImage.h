#pragma once
#include "Object.h"
class Texture;
class SpamImage :
    public Object
{
public:
	SpamImage(Texture* tex);
	~SpamImage() = default;

    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC _hdc) override;

private:
	Texture* m_texture;
};

