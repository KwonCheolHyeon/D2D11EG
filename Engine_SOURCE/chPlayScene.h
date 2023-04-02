#pragma once
#include "chScene.h"

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
		GameObject* chCameraOBJ;
		GameObject* chUiCursor;
		Transform* chUiCursorTR;
		GameObject* player;
		
	};
}

