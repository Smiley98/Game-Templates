#pragma once
#include "Scene.h"

class BeginScene : public Scene
{
public:
	void OnStart() final;
	void OnFinish() final;
	void OnUpdate(float deltaTime) final;
	void OnRender() final;
};

