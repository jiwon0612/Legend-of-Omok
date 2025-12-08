#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
bool ResourceManager::Init()
{
	//fs::path curPath = fs::current_path();
	//m_resourcePath = curPath.parent_path() / L"Output\\build\\Resource\\";
	wchar_t buf[MAX_PATH] = {}; // windows �ִ� ��� ����
	::GetModuleFileNameW(nullptr, buf, MAX_PATH); // ���� �������� exe ��� buf�� ����   
	fs::path exeDir = fs::path(buf).parent_path();                //  buf ��ü ��θ� path ��ü�� ���� ���丮�� ����
	fs::path resourceDir = exeDir.parent_path() / L"build" / L"Resource\\"; // release����϶� build �ѹ��� ���̴°� ����
	m_resourcePath = resourceDir.native();

	if (!RegisterFontFile(L"Font\\TestFont.ttf"))
		return false;
	RegisterTexture();
	RegisterGDI();

	FMOD::System_Create(&m_pSoundSystem);
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init(64, FMOD_INIT_NORMAL, nullptr);
	RegisterSound();
	return true;
}

void ResourceManager::FmodUpdate()
{
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->update();
}

void ResourceManager::Release()
{
	std::unordered_map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTextures.begin(); iter != m_mapTextures.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapTextures.clear();

	ReleaseGDI();
	ReleaseFonts();

	std::unordered_map<wstring, SoundInfo*>::iterator iterSound;
	for (iterSound = m_mapSounds.begin(); iterSound != m_mapSounds.end(); ++iterSound)
		SAFE_DELETE(iterSound->second);
	m_mapSounds.clear();

	m_pSoundSystem->close();
	m_pSoundSystem->release();
}
void ResourceManager::RegisterTexture()
{
	LoadTexture(L"Plane", L"Texture\\planem.bmp");
	LoadTexture(L"Bullet", L"Texture\\Bullet.bmp");
	LoadTexture(L"Jiwoo", L"Texture\\jiwoo.bmp");
	LoadTexture(L"IndiaInkImage", L"Texture\\IndiaInkImage.bmp");
	LoadTexture(L"TestCard", L"Texture\\TestCard.bmp");

}
void ResourceManager::RegisterGDI()
{
	// BRUSH
	m_Brushs[(UINT)BrushType::HOLLOW] = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	m_Brushs[(UINT)BrushType::RED] = (HBRUSH)::CreateSolidBrush(RGB(255, 167, 167));
	m_Brushs[(UINT)BrushType::GREEN] = (HBRUSH)::CreateSolidBrush(RGB(134, 229, 134));

	// PEN 
	m_Pens[(UINT)PenType::RED] = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pens[(UINT)PenType::GREEN] = ::CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

	// ��Ʈ ���
	RegisterFont(FontType::TITLE, L"TestFont", 0);
}
void ResourceManager::ReleaseGDI()
{
	for (int i = 0; i < (UINT)PenType::END; ++i)
		::DeleteObject(m_Pens[i]);
	for (int i = 1; i < (UINT)BrushType::END; ++i)
		// Hollow �����ϰ�
		::DeleteObject(m_Brushs[i]);
	for (int i = 0; i < (UINT)FontType::END; ++i)
		::DeleteObject(m_Fonts[i]);
}
bool ResourceManager::RegisterFontFile(const wstring& _path)
{
	wstring fontPath = m_resourcePath;
	fontPath += _path;
	if (!(AddFontResourceExW(fontPath.c_str(), FR_PRIVATE, 0) > 0))
		return false;
	m_vecFontFiles.push_back(fontPath);
	return true;
}

void ResourceManager::ReleaseFonts()
{
	for (const auto& path : m_vecFontFiles)
		::RemoveFontResourceExW(path.c_str(), FR_PRIVATE, 0);
	m_vecFontFiles.clear();
}
void ResourceManager::RegisterFont(FontType _type, const wstring& _name, int _height, int _weight, bool _italic, int _quality)
{

	HFONT h = ::CreateFont(_height, 0, 0, 0, _weight, _italic, false, false, HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, _quality, DEFAULT_PITCH || FF_DONTCARE, _name.c_str());
	m_Fonts[(UINT)_type] = h;

}
void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (FindSound(_key) || !m_pSoundSystem)
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// �������� ���� ����
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // �ݺ� ���
	if (!_isLoop)
		eMode = FMOD_DEFAULT; // ���� 1���� ���
	FMOD::Sound* p = nullptr;

	// BGM�� stream, �ƴϸ� sound
	// ���丮�Լ�
	//// ���� ��ü�� ����� ���� system��.
	//						//���ϰ��,  FMOD_MODE, NULL, &sound
	FMOD_RESULT r = _isLoop
		? m_pSoundSystem->createStream(str.c_str(), eMode, nullptr, &p)
		: m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &p);

	if (r != FMOD_OK || !p)
		return;

	SoundInfo* pSound = new SoundInfo;
	pSound->IsLoop = _isLoop;
	pSound->pSound = p;
	m_mapSounds.insert({ _key, pSound });

}

void ResourceManager::Play(const wstring& _key)
{
	SoundInfo* pSound = FindSound(_key);
	if (!pSound)
		return;
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!pSound->IsLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	// ���� ��� �Լ�. &channel�� � ä���� ���� ����Ǵ��� ������ �ѱ�
	m_pSoundSystem->playSound(pSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);

}

void ResourceManager::Stop(SOUND_CHANNEL _channel)
{
	m_pChannel[(UINT)_channel]->stop();

}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 ���� ����
	m_pChannel[(UINT)_channel]->setVolume(_vol);

}

void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}
SoundInfo* ResourceManager::FindSound(const wstring& _key)
{
	std::unordered_map<wstring, SoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}


void ResourceManager::LoadTexture(const wstring& _key, const wstring& _path)
{
	Texture* tex = GetTexture(_key);
	if (nullptr != tex)
		return;

	// ����
	wstring texPath = m_resourcePath;
	texPath += _path;

	tex = new Texture;
	tex->Load(texPath);
	tex->SetKey(_key);
	tex->SetRelativePath(texPath);
	m_mapTextures.insert({ _key, tex });
}

Texture* ResourceManager::GetTexture(const wstring& _key)
{
	auto iter = m_mapTextures.find(_key);
	if (iter != m_mapTextures.end())
		return iter->second;
	return nullptr;
}


void ResourceManager::RegisterSound()
{
	LoadSound(L"BGM",L"Sound\\Retro_bgm.wav",true);
	LoadSound(L"Shoot",L"Sound\\laserShoot.wav",false);


	LoadSound(L"BGM_01",L"Sound\\RBGM_01.mp3",true);
	LoadSound(L"BGM_02",L"Sound\\RBGM_02.mp3",true);
}
