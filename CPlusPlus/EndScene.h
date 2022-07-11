#pragma once
#include "Scene.h"

class EndScene :
	public Scene
{
public:
	void OnStart() final;
	void OnFinish() final;
	HRESULT OnCreateDevice(ID2D1HwndRenderTarget* rt) final;
	void OnDiscardDevice() final;
	void OnUpdate(float deltaTime) final;
	void OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt) final;
};

