#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "TestScene.h"
#include "OmokScene.h"
#include "CardTestScene.h"
#include "TitleScene.h"
#include "Object.h"
#include "Collider.h"
#include "WindowManager.h"

void SceneManager::PhysicsSyncColliders()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		const auto& objects = m_curScene->GetLayerObjects((Layer)i);
		for (Object* obj : objects)
		{
			if (!obj)
				continue;

			if (auto* col = obj->GetComponent<Collider>())
				col->LateUpdate(); // sync  
		}
	}
}
void SceneManager::Init()
{
	m_curScene = nullptr;

	// 씬 등록
	RegisterScene(L"TitleScene", new TitleScene);
	RegisterScene(L"TestScene", new TestScene);
	RegisterScene(L"DevScene", new DevScene);
	RegisterScene(L"OmokScene", new OmokScene);
	RegisterScene(L"CardTestScene", new CardTestScene);


	// 첫 씬 지정
	LoadScene(L"TitleScene");
}
void SceneManager::LateInit()
{
	if (m_curScene != nullptr)
		m_curScene->LateInit();
}
void SceneManager::Update()
{
	if (m_curScene == nullptr)
		return;
	m_curScene->Update();
	m_curScene->LateUpdate();
}

void SceneManager::FixedUpdate(float _fixedDT)
{
	if (m_curScene == nullptr)
		return;
	m_curScene->FixedUpdate(_fixedDT);
	PhysicsSyncColliders();
}

void SceneManager::Render(HDC _hdc)
{
	if (m_curScene == nullptr)
		return;
	m_curScene->Render(_hdc);
}

void SceneManager::RegisterScene(const wstring& _name, Scene* _scene)
{
	if (_name.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), { _name, _scene });
}

void SceneManager::LoadScene(const wstring& _name)
{
	// 2번째 load 일시 change 역할
	if (m_curScene != nullptr)
	{
		m_curScene->Release();
		m_curScene = nullptr;
	}
	auto iter = m_mapScenes.find(_name);
	if (iter != m_mapScenes.end())
	{
		m_curScene = iter->second;
		m_curScene->Init();
		m_curScene->LateInit();
	}
}

void SceneManager::UnRegisterScene()
{
	for (auto& scene : m_mapScenes)
	{
		SAFE_DELETE(scene.second);
	}
	m_mapScenes.clear();
}
