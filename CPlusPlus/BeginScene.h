#pragma once
#include "Scene.h"

class BeginScene :
	public Scene
{
public:
	BeginScene();
	~BeginScene();

	void OnStart() final;
	void OnFinish() final;
	HRESULT OnCreateDevice(ID2D1HwndRenderTarget* rt) final;
	void OnDiscardDevice() final;
	void OnUpdate(float deltaTime) final;
	void OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt) final;

private:
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pTealBrush;
	RECT mButtonArea;
	BOOL m_bMouseOver = 0;

	void Cleanup();
};

