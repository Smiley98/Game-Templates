#include "Scene.h"
#include "TestScene.h"
#include "BeginScene.h"
#include "MiddleScene.h"
#include "EndScene.h"

std::array<Scene*, Scene::COUNT> Scene::sScenes;
Scene* Scene::sScene = nullptr;

void Scene::Initialize()
{
	sScenes[TEST] = new TestScene;
	sScenes[BEGIN] = new BeginScene;
	sScenes[MIDDLE] = new MiddleScene;
	sScenes[END] = new EndScene;

	sScene = sScenes[BEGIN];
	sScene->OnStart();
}

void Scene::Shutdown()
{
	sScene = nullptr;
	for (Scene* scene : sScenes)
	{
		delete scene;
		scene = nullptr;
	}
}

HRESULT Scene::CreateDevice(ID2D1HwndRenderTarget* rt)
{
	return sScene->OnCreateDevice(rt);
}

void Scene::DiscardDevice()
{
	sScene->OnDiscardDevice();
}

void Scene::Update(float deltaTime)
{
	sScene->OnUpdate(deltaTime);
}

void Scene::Render(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt)
{
	sScene->OnRender(rt, txt);
}

void Scene::MouseMove(POINT cursor)
{
	if (sScene->mMoveHandler)
	{
		sScene->mMoveHandler(cursor);
	}
}

void Scene::MouseClick(POINT cursor)
{
	if (sScene->mClickHandler)
	{
		sScene->mClickHandler(cursor);
	}
}

void Scene::Transition(Type type)
{
	sScene->OnFinish();
	sScene = sScenes[type];
	sScene->OnStart();
}
