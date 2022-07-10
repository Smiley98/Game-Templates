#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <chrono>

#include <cstdlib>
#include <cstdio>
#include <cwchar>
#include <cmath>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Scene.h"

template<class Interface>
inline void SafeRelease(
    Interface** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

float gTime = 0.0f;

class App
{
public:
    App() :
        m_hwnd(NULL),
        m_pDirect2dFactory(NULL),
        m_pRenderTarget(NULL),
        m_pLightSlateGrayBrush(NULL),
        m_pCornflowerBlueBrush(NULL)
    {}

    ~App()
    {
        SafeRelease(&m_pDirect2dFactory);
        SafeRelease(&m_pRenderTarget);
        SafeRelease(&m_pLightSlateGrayBrush);
        SafeRelease(&m_pCornflowerBlueBrush);
    }

    // Register the window class and call methods for instantiating drawing resources
    HRESULT Initialize()
    {
        HRESULT hr = CreateDeviceIndependentResources();

        if (SUCCEEDED(hr))
        {
            // Register the window class.
            WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = WndProc;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = sizeof(LONG_PTR);
            wcex.hInstance = HINST_THISCOMPONENT;
            wcex.hbrBackground = NULL;
            wcex.lpszMenuName = NULL;
            wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
            wcex.lpszClassName = L"D2DDemoApp";

            RegisterClassEx(&wcex);

            m_hwnd = CreateWindow(
                L"D2DDemoApp",
                L"Direct2D demo application",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                NULL,
                NULL,
                HINST_THISCOMPONENT,
                this
            );

            if (m_hwnd)
            {
                // Because the SetWindowPos function takes its size in pixels, we
                // obtain the window's DPI, and use it to scale the window size.
                float dpi = GetDpiForWindow(m_hwnd);

                SetWindowPos(
                    m_hwnd,
                    NULL,
                    NULL,
                    NULL,
                    static_cast<int>(ceil(640.0f * dpi / 96.0f)),
                    static_cast<int>(ceil(480.0f * dpi / 96.0f)),
                    SWP_NOMOVE);
                ShowWindow(m_hwnd, SW_SHOWNORMAL);
                UpdateWindow(m_hwnd);
            }
        }

        return hr;
    }

    // Process and dispatch messages
    void GameLoop()
    {
        while (!m_bQuit)
        {
            static float delta = 0.0f;
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            MSG msg;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                {
                    m_bQuit = true;
                }
            }

            Scene::Update(delta);
            delta = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - start).count();
            gTime += delta;
        }
    }

private:
    // Initialize device-independent resources.
    HRESULT CreateDeviceIndependentResources()
    {
        return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
    }

    // Initialize device-dependent resources.
    HRESULT CreateDeviceResources()
    {
        HRESULT hr = S_OK;

        if (!m_pRenderTarget)
        {
            RECT rc;
            GetClientRect(m_hwnd, &rc);

            D2D1_SIZE_U size = D2D1::SizeU(
                rc.right - rc.left,
                rc.bottom - rc.top
            );

            // Create a Direct2D render target.
            hr = m_pDirect2dFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(m_hwnd, size),
                &m_pRenderTarget
            );

            if (SUCCEEDED(hr))
            {
                // Create a gray brush.
                hr = m_pRenderTarget->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                    &m_pLightSlateGrayBrush
                );
            }
            if (SUCCEEDED(hr))
            {
                // Create a blue brush.
                hr = m_pRenderTarget->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
                    &m_pCornflowerBlueBrush
                );
            }
        }

        return hr;
    }

    // Release device-dependent resource.
    void DiscardDeviceResources()
    {
        SafeRelease(&m_pRenderTarget);
        SafeRelease(&m_pLightSlateGrayBrush);
        SafeRelease(&m_pCornflowerBlueBrush);
    }

    // Draw content.
    HRESULT OnRender()
    {
        HRESULT hr = S_OK;

        hr = CreateDeviceResources();

        if (SUCCEEDED(hr))
        {
            m_pRenderTarget->BeginDraw();
            m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

            D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

            // Draw a grid background.
            int width = static_cast<int>(rtSize.width);
            int height = static_cast<int>(rtSize.height);

            for (int x = 0; x < width; x += 10)
            {
                m_pRenderTarget->DrawLine(
                    D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                    D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                    m_pLightSlateGrayBrush,
                    0.5f
                );
            }

            for (int y = 0; y < height; y += 10)
            {
                m_pRenderTarget->DrawLine(
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
            m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);

            // Draw the outline of a rectangle.
            m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);

            hr = m_pRenderTarget->EndDraw();
        }

        if (hr == D2DERR_RECREATE_TARGET)
        {
            hr = S_OK;
            DiscardDeviceResources();
        }

        return hr;
    }

    // Resize the render target.
    void OnResize(UINT width, UINT height)
    {
        if (m_pRenderTarget)
        {
            m_pRenderTarget->Resize(D2D1::SizeU(width, height));
        }
    }

    // The windows procedure.
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT result = 0;

        if (msg == WM_CREATE)
        {
            LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
            App* pApp = (App*)pcs->lpCreateParams;

            ::SetWindowLongPtrW(
                hWnd,
                GWLP_USERDATA,
                reinterpret_cast<LONG_PTR>(pApp)
            );

            result = 1;
        }
        else
        {
            App* pDemoApp = reinterpret_cast<App*>(static_cast<LONG_PTR>(
                ::GetWindowLongPtrW(
                    hWnd,
                    GWLP_USERDATA
                )));

            bool wasHandled = false;

            if (pDemoApp)
            {
                switch (msg)
                {
                case WM_SIZE:
                {
                    UINT width = LOWORD(lParam);
                    UINT height = HIWORD(lParam);
                    pDemoApp->OnResize(width, height);
                }
                result = 0;
                wasHandled = true;
                break;

                case WM_DISPLAYCHANGE:
                {
                    InvalidateRect(hWnd, NULL, FALSE);
                }
                result = 0;
                wasHandled = true;
                break;

                case WM_PAINT:
                {
                    pDemoApp->OnRender();
                    ValidateRect(hWnd, NULL);
                }
                result = 0;
                wasHandled = true;
                break;

                case WM_KEYDOWN:
                {
                    printf("WM_KEYDOWN: 0x%x\n", wParam);
                }
                break;

                case WM_KEYUP:
                {
                    printf("WM_KEYUP: 0x%x\n", wParam);
                }
                break;

                case WM_DESTROY:
                {
                    PostQuitMessage(0);
                }
                result = 1;
                wasHandled = true;
                break;
                }
            }

            if (!wasHandled)
            {
                result = DefWindowProc(hWnd, msg, wParam, lParam);
            }
        }

        return result;
    }

    HWND m_hwnd;
    ID2D1Factory* m_pDirect2dFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
    ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
    bool m_bQuit = false;
};

bool RedirectConsoleIO()
{
    bool result = true;
    FILE* fp;

    // Redirect STDIN if the console has an input handle
    if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
            result = false;
        else
            setvbuf(stdin, NULL, _IONBF, 0);

    // Redirect STDOUT if the console has an output handle
    if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
            result = false;
        else
            setvbuf(stdout, NULL, _IONBF, 0);

    // Redirect STDERR if the console has an error handle
    if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
            result = false;
        else
            setvbuf(stderr, NULL, _IONBF, 0);

    // Make C++ standard streams point to console as well.
    std::ios::sync_with_stdio(true);

    // Clear the error state for each of the C++ standard streams.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();

    return result;
}

bool ReleaseConsole()
{
    bool result = true;
    FILE* fp;

    // Redirect STDIN to NUL
    if (freopen_s(&fp, "NUL:", "r", stdin) != 0)
        result = false;
    else
        setvbuf(stdin, NULL, _IONBF, 0);

    // Redirect STDOUT to NULL
    if (freopen_s(&fp, "NUL:", "w", stdout) != 0)
        result = false;
    else
        setvbuf(stdout, NULL, _IONBF, 0);

    // Redirect STDERR to NULL
    if (freopen_s(&fp, "NUL:", "w", stderr) != 0)
        result = false;
    else
        setvbuf(stderr, NULL, _IONBF, 0);

    // Detach from console
    if (!FreeConsole())
        result = false;

    return result;
}

void AdjustConsoleBuffer(int16_t minLength)
{
    // Set the screen buffer to be big enough to scroll some text
    CONSOLE_SCREEN_BUFFER_INFO conInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
    conInfo.dwSize.Y = min(conInfo.dwSize.Y, minLength);
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
}

bool CreateConsole(int16_t minLength, bool bAttachToParent = false)
{
    bool result = false;

    // Release any current console and redirect IO to NUL
    ReleaseConsole();

    // Attempt to create new console
    if (bAttachToParent ? AttachConsole(ATTACH_PARENT_PROCESS) : AllocConsole())
    {
        AdjustConsoleBuffer(minLength);
        result = RedirectConsoleIO();
    }

    return result;
}

int WINAPI WinMain(
    HINSTANCE /* hInstance */,
    HINSTANCE /* hPrevInstance */,
    LPSTR /* lpCmdLine */,
    int /* nCmdShow */)
{
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
    CreateConsole(1024);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        App app;
        if (SUCCEEDED(app.Initialize()))
        {
            Scene::Initialize();
            app.GameLoop();
            Scene::Shutdown();
        }
        CoUninitialize();
    }

    ReleaseConsole();
    return 0;
}
