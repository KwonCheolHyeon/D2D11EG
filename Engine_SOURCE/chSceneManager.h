#pragma once
#include "chScene.h"

namespace ya
{
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Release();

		static Scene* GetActiveScene() { return mActiveScene; }

	private:
		static Scene* mActiveScene;
	};
}
