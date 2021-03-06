#pragma once
#include "Scene.h"

class MiddleScene :
	public Scene
{
public:
	MiddleScene();
	~MiddleScene();

	HRESULT OnLoad(ID2D1HwndRenderTarget* rt) final;
	void OnUnload() final;

	void OnUpdate(float deltaTime) final;
	void OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt) final;

private:
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pBlueBrush;
	RECT mButtonArea;
	D2D1_RECT_F mRect1;
	D2D1_RECT_F mRect2;
	LONG mWidth;
	LONG mHeight;
	BOOL m_bIntersect = false;

	void Cleanup();
};
