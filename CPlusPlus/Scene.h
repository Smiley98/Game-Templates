#pragma once
#include <array>
#include <functional>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

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

using MouseHandler = std::function<void(POINT)>;

class Scene
{
public:
	enum Type {
		TEST,
		BEGIN,
		MIDDLE,
		END,
		COUNT
	};

	static void Initialize();
	static void Shutdown();
	static HRESULT CreateDevice(ID2D1HwndRenderTarget* rt);
	static void DiscardDevice();
	static void Update(float deltaTime);
	static void Render(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt);
	static void MouseMove(POINT cursor);
	static void MouseClick(POINT cursor);
	static void Transition(Type type);

	virtual void OnStart() = 0;
	virtual void OnFinish() = 0;
	virtual HRESULT OnCreateDevice(ID2D1HwndRenderTarget* rt) = 0;
	virtual void OnDiscardDevice() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender(ID2D1HwndRenderTarget* rt, IDWriteTextFormat* txt) = 0;

protected:
	MouseHandler mMoveHandler = nullptr;
	MouseHandler mClickHandler = nullptr;

private:
	static std::array<Scene*, COUNT> sScenes;
	static Scene* sScene;
};
