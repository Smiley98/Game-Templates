#include "Scene.h"
#include "BeginScene.h"
#include "MiddleScene.h"
#include "EndScene.h"

std::array<Scene*, Scene::COUNT> Scene::sScenes;
Scene* Scene::sScene = nullptr;

void Scene::Initialize()
{
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

void Scene::Update(float deltaTime)
{
	sScene->OnUpdate(deltaTime);
}

void Scene::Render()
{
	sScene->OnRender();
}

void Scene::Transition(Type type)
{
	sScene->OnFinish();
	sScene = sScenes[type];
	sScene->OnStart();
}
