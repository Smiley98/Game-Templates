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
	mWidth = static_cast<LONG>(rtSize.width);
	mHeight = static_cast<LONG>(rtSize.height);
	LONG margin = 50;

	mButtonArea = {
		 mWidth / 2 - margin,
		 mHeight / 2 - margin,
		 mWidth / 2 + margin,
		 mHeight / 2 + margin
	};

	mClickHandler = [this](POINT cursor) {
		if (PtInRect(&mButtonArea, cursor))
		{
			Transition(END);
		}
	};

	float rw = 69.0f;
	float rh = 42.0f;
	float right = (float)mWidth - rw;
	float bottom = (float)mHeight - rh;

	mRect1 = {
		rw,
		rh,
		rw + rw,
		rh + rh
	};

	mRect2 = {
		right - rw,
		bottom - rh,
		right,
		bottom
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
	const static float aspect = (mHeight * 1.0f) / (mWidth * 1.0f);
	const static float vx = 250.0f;
	const static float vy = vx * aspect;
	static float vx1 = vx, vx2 = -vx, vy1 = vy, vy2 = -vy;

	auto translate = [](D2D1_RECT_F& rect, float& vx, float& vy, float w, float h, float dt) {
		const float resolution = 1.10f;
		float tx = vx * dt;
		float ty = vy * dt;

		if (rect.left + tx <= 0.0f || rect.right + tx >= w) {
			vx *= -1.0f;
			tx = vx * dt * resolution;
		}

		if (rect.top + ty <= 0.0f || rect.bottom + ty >= h) {
			vy *= -1.0f;
			ty = vy * dt * resolution;
		}

		const float rw = rect.right - rect.left;
		const float rh = rect.bottom - rect.top;
		rect.left += tx;
		rect.top += ty;
		rect.right = rect.left + rw;
		rect.bottom = rect.top + rh;
	};

	translate(mRect1, vx1, vy1, (float)mWidth, (float)mHeight, deltaTime);
	translate(mRect2, vx2, vy2, (float)mWidth, (float)mHeight, deltaTime);

	RECT r;
	RECT r1{ mRect1.left, mRect1.top, mRect1.right, mRect1.bottom };
	RECT r2{ mRect2.left, mRect2.top, mRect2.right, mRect2.bottom };
	m_bIntersect = IntersectRect(&r, &r1, &r2);
}

void MiddleScene::OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt)
{
	D2D1_RECT_F endButton = D2D1::Rect(mButtonArea.left, mButtonArea.top, mButtonArea.right, mButtonArea.bottom);
	rt->FillRectangle(&endButton, m_pBlueBrush);

	rt->FillRectangle(&mRect1, m_bIntersect ? m_pRedBrush : m_pGreenBrush);
	rt->FillRectangle(&mRect2, m_bIntersect ? m_pRedBrush : m_pGreenBrush);

	static const WCHAR sc_end[] = L"End.";
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
