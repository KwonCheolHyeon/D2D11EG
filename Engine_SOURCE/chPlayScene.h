#pragma once
#include "chScene.h"
#include "chBulletPool.h"
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


	public://생성할 함수
		void generateBullet(int size);
		

	private:
		GameObject* chCameraOBJ;
		GameObject* chUiCursor;
		Transform* chUiCursorTR;
		GameObject* player;

		BulletPool* pool;
	


		//저장할 공간
		std::vector<Bullet*> containBullets;
		
		
	};
}

