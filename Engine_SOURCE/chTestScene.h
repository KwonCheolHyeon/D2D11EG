#pragma once
#include "chScene.h"

namespace ch
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* chCameraOBJ;
		GameObject* player;
	


	};
}

