#include "MiddleScene.h"

MiddleScene::MiddleScene() :
	m_pWhiteBrush(NULL),
	m_pRedBrush(NULL),
	m_pGreenBrush(NULL),
	m_pBlueBrush(NULL)
{
}

MiddleScene::~MiddleScene()
{
	Cleanup();
}

HRESULT MiddleScene::OnLoad(ID2D1HwndRenderTarget* rt)
{
	D2D1_SIZE_F rtSize = rt->GetSize();
	LONG width = static_cast<LONG>(rtSize.width);
	LONG height = static_cast<LONG>(rtSize.height);

	mButtonArea = {
		 width / 2 - mMargin,
		 height / 2 - mMargin,
		 width / 2 + mMargin,
		 height / 2 + mMargin
	};

	mClickHandler = [this](POINT cursor) {
		if (PtInRect(&mButtonArea, cursor))
		{
			Transition(END);
		}
	};

	HRESULT hr = rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&m_pWhiteBrush
	);

	hr = rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&m_pRedBrush
	);

	hr = rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green),
		&m_pGreenBrush
	);

	hr = rt->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&m_pBlueBrush
	);

	return hr;
}

void MiddleScene::OnUnload()
{
	Cleanup();
}

void MiddleScene::OnUpdate(float deltaTime)
{
}

void MiddleScene::OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt)
{
	D2D1_RECT_F endButton = D2D1::Rect(mButtonArea.left, mButtonArea.top, mButtonArea.right, mButtonArea.bottom);
	rt->FillRectangle(&endButton, m_pBlueBrush);

	static const WCHAR sc_end[] = L"End";
	rt->DrawText(
		sc_end,
		ARRAYSIZE(sc_end) - 1,
		txt,
		endButton,
		m_pWhiteBrush
	);
}

void MiddleScene::Cleanup()
{
	mClickHandler = nullptr;
	SafeRelease(&m_pWhiteBrush);
	SafeRelease(&m_pRedBrush);
	SafeRelease(&m_pGreenBrush);
	SafeRelease(&m_pBlueBrush);
}
