#pragma once
#include "chScene.h"
#include "chBulletPool.h"
#include "chHeart_UI.h"
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


	public://������ �Լ�
		void generateBullet(int size);
		void generateMap();

	private:
		GameObject* chCameraOBJ;
		GameObject* chUiCursor;
		Transform* chUiCursorTR;
		GameObject* player;

		BulletPool* pool;
		
		Transform* mapTr;

		std::vector<Heart_UI*> HeartControl;
		//������ ����
		std::vector<Bullet*> containBullets;
		
		
	};
}

