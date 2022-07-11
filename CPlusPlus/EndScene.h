#pragma once
#include "Scene.h"

class EndScene :
	public Scene
{
public:
	HRESULT OnLoad(ID2D1HwndRenderTarget* rt) final;
	void OnUnload() final;

	void OnUpdate(float deltaTime) final;
	void OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt) final;
};

