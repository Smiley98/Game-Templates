#include "BeginScene.h"
#include <cstdio>
extern float gTime;

void BeginScene::OnStart()
{
}

void BeginScene::OnFinish()
{
}

void BeginScene::OnUpdate(float deltaTime)
{
	printf("Frame time: %f. Total time: %f.\n", deltaTime, gTime);
}

void BeginScene::OnRender()
{
}
