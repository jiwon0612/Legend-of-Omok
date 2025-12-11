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
	if (!RegisterFontFile(L"Font\\a자막체.ttf"))
		return false;
	if (!RegisterFontFile(L"Font\\윤고딕330.ttf"))
		return false;
	RegisterTexture();
	LoadSpamTextures();
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
	LoadTexture(L"TimerImage", L"Texture\\Timer.bmp");
	LoadTexture(L"BrokenTimerImage", L"Texture\\BrokenTimer.bmp");
	LoadTexture(L"FrozenTimerImage", L"Texture\\FrozenTimer.bmp");
	LoadTexture(L"TimerBackground", L"Texture\\TimerBackground.bmp");
	LoadTexture(L"BlackButton", L"Texture\\BlackButton.bmp");
	LoadTexture(L"WhiteButton", L"Texture\\WhiteButton.bmp");
	LoadTexture(L"WhiteStone", L"Texture\\WhiteStone.bmp");
	LoadTexture(L"BlackStone", L"Texture\\BlackStone.bmp");

	//카드 이미지
	LoadTexture(L"CardImage",L"Texture\\CardImage.bmp");
	LoadTexture(L"CardBackground", L"Texture\\CardBackground.bmp");
	LoadTexture(L"IndialnkIcon", L"Texture\\CardIcon\\IndialnkIcon.bmp");
	LoadTexture(L"EarthquakeIcon", L"Texture\\CardIcon\\EarthquakeIcon.bmp");
	LoadTexture(L"PlaceMineIcon", L"Texture\\CardIcon\\PlaceMineIcon.bmp");
	LoadTexture(L"TimeStopIcon", L"Texture\\CardIcon\\TimeStopIcon.bmp");
	LoadTexture(L"DeleteTimeIcon", L"Texture\\CardIcon\\DeleteTimeIcon.bmp");
	LoadTexture(L"ReplaceRandomStoneIcon", L"Texture\\CardIcon\\ReplaceRandomStoneIcon.bmp");
	LoadTexture(L"RerollIcon", L"Texture\\CardIcon\\RerollIcon.bmp");
	LoadTexture(L"BlindAllStonesIcon", L"Texture\\CardIcon\\BlindAllStonesIcon.bmp");
	LoadTexture(L"OneMoreIcon", L"Texture\\CardIcon\\OneMoreIcon.bmp");
	LoadTexture(L"PeaceIcon", L"Texture\\CardIcon\\PeaceIcon.bmp");
	LoadTexture(L"OneMinusIcon", L"Texture\\CardIcon\\OneMinusIcon.bmp");
	LoadTexture(L"SoundIcon", L"Texture\\CardIcon\\SoundIcon.bmp");
	LoadTexture(L"StopMusicIcon", L"Texture\\CardIcon\\StopMusicIcon.bmp");
	LoadTexture(L"ClapIcon", L"Texture\\CardIcon\\ClapIcon.bmp");
	LoadTexture(L"DummyIcon", L"Texture\\CardIcon\\DummyIcon.bmp");
	LoadTexture(L"SayHiIcon", L"Texture\\CardIcon\\SayHiIcon.bmp");
	LoadTexture(L"CheerinIcon", L"Texture\\CardIcon\\CheerinIcon.bmp");
	LoadTexture(L"BlameIcon", L"Texture\\CardIcon\\BlameIcon.bmp");
	LoadTexture(L"RestIcon", L"Texture\\CardIcon\\RestIcon.bmp");
	LoadTexture(L"ShakeCursorIcon", L"Texture\\CardIcon\\ShakeCursorIcon.bmp");
	LoadTexture(L"SpamIcon", L"Texture\\CardIcon\\SpamIcon.bmp");
	LoadTexture(L"CardImageRare", L"Texture\\CardImageRare.bmp");
	LoadTexture(L"CardImageLegendary", L"Texture\\CardImageLegendary.bmp");
}
void ResourceManager::RegisterGDI()
{
	// BRUSH
	m_Brushs[(UINT)BrushType::HOLLOW] = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	m_Brushs[(UINT)BrushType::RED] = (HBRUSH)::CreateSolidBrush(RGB(255, 167, 167));
	m_Brushs[(UINT)BrushType::GREEN] = (HBRUSH)::CreateSolidBrush(RGB(134, 229, 134));
	m_Brushs[(UINT)BrushType::BLACK] = (HBRUSH)::CreateSolidBrush(RGB(0, 0, 0));
	m_Brushs[(UINT)BrushType::GRAY] = (HBRUSH)::CreateSolidBrush(RGB(200, 200, 200));
	m_Brushs[(UINT)BrushType::WHITE] = (HBRUSH)::CreateSolidBrush(RGB(255, 255, 255));

	// PEN 
	m_Pens[(UINT)PenType::HOLLOW] = (HPEN)::GetStockObject(NULL_PEN);
	m_Pens[(UINT)PenType::RED] = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pens[(UINT)PenType::GREEN] = ::CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pens[(UINT)PenType::BLACK] = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	// ��Ʈ ���
	RegisterFont(FontType::TITLE, L"-윤고딕330", 70);
	RegisterFont(FontType::GUIDE, L"a자막체", 30);
	RegisterFont(FontType::MAIN, L"-윤고딕330", 0);
	RegisterFont(FontType::UI, L"a자막체", 0);
	RegisterFont(FontType::NUMBER, L"-윤고딕330", 30);
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
void ResourceManager::LoadSpamTextures()
{
	// 22종류
	LoadTexture(L"Spam_0", L"Texture\\Spam\\spam_0.bmp");
	m_vecSpamTextures.push_back(L"Spam_0");
	LoadTexture(L"Spam_1", L"Texture\\Spam\\spam_1.bmp");
	m_vecSpamTextures.push_back(L"Spam_1");
	LoadTexture(L"Spam_2", L"Texture\\Spam\\spam_2.bmp");
	m_vecSpamTextures.push_back(L"Spam_2");
	LoadTexture(L"Spam_3", L"Texture\\Spam\\spam_3.bmp");
	m_vecSpamTextures.push_back(L"Spam_3");
	LoadTexture(L"Spam_4", L"Texture\\Spam\\spam_4.bmp");
	m_vecSpamTextures.push_back(L"Spam_4");
	LoadTexture(L"Spam_5", L"Texture\\Spam\\spam_5.bmp");
	m_vecSpamTextures.push_back(L"Spam_5");
	LoadTexture(L"Spam_6", L"Texture\\Spam\\spam_6.bmp");
	m_vecSpamTextures.push_back(L"Spam_6");
	LoadTexture(L"Spam_7", L"Texture\\Spam\\spam_7.bmp");
	m_vecSpamTextures.push_back(L"Spam_7");
	LoadTexture(L"Spam_8", L"Texture\\Spam\\spam_8.bmp");
	m_vecSpamTextures.push_back(L"Spam_8");
	LoadTexture(L"Spam_9", L"Texture\\Spam\\spam_9.bmp");
	m_vecSpamTextures.push_back(L"Spam_9");
	LoadTexture(L"Spam_10", L"Texture\\Spam\\spam_10.bmp");
	m_vecSpamTextures.push_back(L"Spam_10");
	LoadTexture(L"Spam_11", L"Texture\\Spam\\spam_11.bmp");
	m_vecSpamTextures.push_back(L"Spam_11");
	LoadTexture(L"Spam_12", L"Texture\\Spam\\spam_12.bmp");
	m_vecSpamTextures.push_back(L"Spam_12");
	LoadTexture(L"Spam_13", L"Texture\\Spam\\spam_13.bmp");
	m_vecSpamTextures.push_back(L"Spam_13");
	LoadTexture(L"Spam_14", L"Texture\\Spam\\spam_14.bmp");
	m_vecSpamTextures.push_back(L"Spam_14");
	LoadTexture(L"Spam_15", L"Texture\\Spam\\spam_15.bmp");
	m_vecSpamTextures.push_back(L"Spam_15");
	LoadTexture(L"Spam_16", L"Texture\\Spam\\spam_16.bmp");
	m_vecSpamTextures.push_back(L"Spam_16");
	LoadTexture(L"Spam_17", L"Texture\\Spam\\spam_17.bmp");
	m_vecSpamTextures.push_back(L"Spam_17");
	LoadTexture(L"Spam_18", L"Texture\\Spam\\spam_18.bmp");
	m_vecSpamTextures.push_back(L"Spam_18");
	LoadTexture(L"Spam_19", L"Texture\\Spam\\spam_19.bmp");
	m_vecSpamTextures.push_back(L"Spam_19");
	LoadTexture(L"Spam_20", L"Texture\\Spam\\spam_20.bmp");
	m_vecSpamTextures.push_back(L"Spam_20");
	LoadTexture(L"Spam_21", L"Texture\\Spam\\spam_21.bmp");
	m_vecSpamTextures.push_back(L"Spam_21");

	LoadTexture(L"CloseButton", L"Texture\\Spam\\CloseButton.bmp");
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


	LoadSound(L"BGM_01",L"Sound\\BGM_01.wav",true);
	LoadSound(L"BGM_02",L"Sound\\BGM_02.wav",true);
	LoadSound(L"BGM_03",L"Sound\\BGM_03.wav",true);
	LoadSound(L"ClapEffect",L"Sound\\ClapEffect.wav",false);

	LoadSound(L"SeleteCard", L"Sound\\SeleteCardSound.wav", false);
	LoadSound(L"ShowCard", L"Sound\\ShowCardSound.wav", false);
}

wstring ResourceManager::GetSpamTexture()
{
	int randIndex = rand() % m_vecSpamTextures.size();
	return m_vecSpamTextures[randIndex];
}
