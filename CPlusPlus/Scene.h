#pragma once
#include <array>

class Scene
{
public:
	enum Type {
		BEGIN,
		MIDDLE,
		END,
		COUNT
	};

	static void Initialize();
	static void Shutdown();
	static void Update(float deltaTime);
	static void Render();
	static void Transition(Type type);

	virtual void OnStart() = 0;
	virtual void OnFinish() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender() = 0;

private:
	static std::array<Scene*, COUNT> sScenes;
	static Scene* sScene;
};
