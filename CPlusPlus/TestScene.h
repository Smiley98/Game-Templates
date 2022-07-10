#pragma once
#include "Scene.h"

class TestScene :
    public Scene
{
public:
	TestScene();
	~TestScene();

	void OnStart() final;
	void OnFinish() final;
	HRESULT OnCreateDevice(ID2D1HwndRenderTarget* rt) final;
	void OnDiscardDevice() final;
	void OnUpdate(float deltaTime) final;
	void OnRender(ID2D1HwndRenderTarget* rt) final;

private:
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
};

