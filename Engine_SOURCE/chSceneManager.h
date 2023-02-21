#pragma once
#include "chScene.h"

namespace ch
{
	//class Scene;
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
