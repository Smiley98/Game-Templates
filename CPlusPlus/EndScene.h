#pragma once
#include "Scene.h"

class EndScene :
	public Scene
{
public:
	EndScene();
	~EndScene();

	HRESULT OnLoad(ID2D1HwndRenderTarget* rt) final;
	void OnUnload() final;

	void OnUpdate(float deltaTime) final;
	void OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt) final;

private:
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pPurpleBrush;
	RECT mButtonArea;

	void Cleanup();
};

