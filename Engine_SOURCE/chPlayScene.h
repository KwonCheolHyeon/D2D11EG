#pragma once
#include "chScene.h"
#include <vector>
namespace ch
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		virtual void LoadResources() override;
		std::vector<GameObject*> psGo;
		/*std::vector<Transform*> psTrR;
		std::vector<SpriteRenderer*> psSr;*/
	};
}

