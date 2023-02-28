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
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene; //³» ÇöÀç ¾À
	};
}
