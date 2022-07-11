#include "TestScene.h"
#include <cstdio>
extern float gTime;

TestScene::TestScene() :
    m_pBlackBrush(NULL),
    m_pWhiteBrush(NULL),
    m_pLightSlateGrayBrush(NULL),
    m_pCornflowerBlueBrush(NULL)
{
    mMoveHandler = [this](POINTS cursor) {
        //printf("Test move: %i, %i.\n", cursor.x, cursor.y);
    };

    mClickHandler = [this](POINTS cursor) {
        printf("Test click: %i, %i.\n", cursor.x, cursor.y);
    };
}

TestScene::~TestScene()
{
    Cleanup();
}

void TestScene::OnStart()
{
}

void TestScene::OnFinish()
{
}

HRESULT TestScene::OnCreateDevice(ID2D1HwndRenderTarget* rt)
{
    // Create a black brush.
    HRESULT hr = rt->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Black),
        &m_pBlackBrush
    );

    // Create a white brush.
    hr = rt->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White),
        &m_pWhiteBrush
    );

    // Create a gray brush.
    hr = rt->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::LightSlateGray),
        &m_pLightSlateGrayBrush
    );

    // Create a blue brush.
    hr = rt->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
        &m_pCornflowerBlueBrush
    );

    return hr;
}

void TestScene::OnDiscardDevice()
{
    Cleanup();
}

void TestScene::OnUpdate(float deltaTime)
{
    //printf("Frame time: %f. Total time: %f.\n", deltaTime, gTime);
}

void TestScene::OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt)
{
    // Draw a grid background.
    D2D1_SIZE_F rtSize = rt->GetSize();
    int width = static_cast<int>(rtSize.width);
    int height = static_cast<int>(rtSize.height);

    for (int x = 0; x < width; x += 10)
    {
        rt->DrawLine(
            D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
            D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
            m_pLightSlateGrayBrush,
            0.5f
        );
    }

    for (int y = 0; y < height; y += 10)
    {
        rt->DrawLine(
            D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
            D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
            m_pLightSlateGrayBrush,
            0.5f
        );
    }

    // Draw two rectangles.
    D2D1_RECT_F rectangle1 = D2D1::RectF(
        rtSize.width / 2 - 50.0f,
        rtSize.height / 2 - 50.0f,
        rtSize.width / 2 + 50.0f,
        rtSize.height / 2 + 50.0f
    );

    D2D1_RECT_F rectangle2 = D2D1::RectF(
        rtSize.width / 2 - 100.0f,
        rtSize.height / 2 - 100.0f,
        rtSize.width / 2 + 100.0f,
        rtSize.height / 2 + 100.0f
    );

    // Draw a filled rectangle.
    rt->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);

    // Draw the outline of a rectangle.
    rt->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);

    // Draw text within the 1st rectangle.
    static const WCHAR sc_helloWorld[] = L"Hello, World!";
    rt->DrawText(
        sc_helloWorld,
        ARRAYSIZE(sc_helloWorld) - 1,
        txt,
        rectangle1,
        m_pBlackBrush
    );
}

void TestScene::Cleanup()
{
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pWhiteBrush);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pCornflowerBlueBrush);
}
