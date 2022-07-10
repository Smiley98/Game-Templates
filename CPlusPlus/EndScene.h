#pragma once
#include "Scene.h"

class EndScene : public Scene
{
public:
	void OnStart() final;
	void OnFinish() final;
	void OnUpdate(float deltaTime) final;
	void OnRender() final;
};

