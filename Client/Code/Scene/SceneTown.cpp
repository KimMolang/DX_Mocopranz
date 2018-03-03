#include "stdafx.h"
#include "SceneTown.h"

SceneTown::SceneTown()
{
}

SceneTown::~SceneTown()
{
}

HRESULT SceneTown::Init()
{
	Engine::Scene::Init();

	return S_OK;
}

void SceneTown::Update()
{
	Engine::Scene::Update();
}

void SceneTown::Render()
{
	Engine::Scene::Render();
}

void SceneTown::Release()
{
	Engine::Scene::Release();
}