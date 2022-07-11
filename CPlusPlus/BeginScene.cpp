#include "BeginScene.h"

BeginScene::BeginScene() :
	m_pWhiteBrush(NULL),
	m_pRedBrush(NULL),
	m_pTealBrush(NULL)
{
}

BeginScene::~BeginScene()
{
	Cleanup();
}

void BeginScene::OnStart()
{
}

void BeginScene::OnFinish()
{
}

HRESULT BeginScene::OnCreateDevice(ID2D1HwndRenderTarget* rt)
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

	mMoveHandler = [this](POINT cursor) {
		m_bMouseOver = PtInRect(&mButtonArea, cursor);
	};

	mClickHandler = [this](POINT cursor) {
		if (PtInRect(&mButtonArea, cursor))
		{
			Transition(MIDDLE);
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
		D2D1::ColorF(D2D1::ColorF::Teal),
		&m_pTealBrush
	);

	return hr;
}

void BeginScene::OnDiscardDevice()
{
	Cleanup();
}

void BeginScene::OnUpdate(float deltaTime)
{
}

void BeginScene::OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt)
{
	D2D1_RECT_F beginButton = D2D1::Rect(mButtonArea.left, mButtonArea.top, mButtonArea.right, mButtonArea.bottom);
	rt->FillRectangle(&beginButton, m_bMouseOver ? m_pTealBrush : m_pRedBrush);
}

void BeginScene::Cleanup()
{
	mMoveHandler = nullptr;
	mClickHandler = nullptr;
	SafeRelease(&m_pWhiteBrush);
	SafeRelease(&m_pRedBrush);
	SafeRelease(&m_pTealBrush);
}
