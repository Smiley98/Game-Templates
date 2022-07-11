#include "EndScene.h"

EndScene::EndScene() :
	m_pWhiteBrush(NULL),
	m_pPurpleBrush(NULL)
{
}

EndScene::~EndScene()
{
	Cleanup();
}

HRESULT EndScene::OnLoad(ID2D1HwndRenderTarget* rt)
{
	D2D1_SIZE_F rtSize = rt->GetSize();
	LONG width = static_cast<LONG>(rtSize.width);
	LONG height = static_cast<LONG>(rtSize.height);
	LONG margin = 50;

	mButtonArea = {
		 width / 2 - margin,
		 height / 2 - margin,
		 width / 2 + margin,
		 height / 2 + margin
	};

	mClickHandler = [this](POINT cursor) {
		if (PtInRect(&mButtonArea, cursor))
		{
			Transition(BEGIN);
		}
	};

	HRESULT hr = rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&m_pWhiteBrush
	);

	hr = rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Purple),
		&m_pPurpleBrush
	);

	return hr;
}

void EndScene::OnUnload()
{
	Cleanup();
}

void EndScene::OnUpdate(float deltaTime)
{
}

void EndScene::OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt)
{
	D2D1_RECT_F restartButton = D2D1::Rect(mButtonArea.left, mButtonArea.top, mButtonArea.right, mButtonArea.bottom);
	rt->FillRectangle(&restartButton, m_pPurpleBrush);

	static const WCHAR sc_begin[] = L"Restart?";
	rt->DrawText(
		sc_begin,
		ARRAYSIZE(sc_begin) - 1,
		txt,
		restartButton,
		m_pWhiteBrush
	);
}

void EndScene::Cleanup()
{
	mClickHandler = nullptr;
	SafeRelease(&m_pWhiteBrush);
	SafeRelease(&m_pPurpleBrush);
}
