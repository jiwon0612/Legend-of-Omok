#include "pch.h"
#include "SpamImage.h"
#include "Texture.h"

SpamImage::SpamImage(Texture* tex)
{
	m_texture = tex;
}

void SpamImage::Update()
{
}

void SpamImage::Render(HDC _hdc)
{
	BitBlt(_hdc,
		0,
		0,
		m_texture->GetWidth(),
		m_texture->GetHeight(),
		m_texture->GetTextureDC(),
		0,
		0,
		SRCCOPY);
}
