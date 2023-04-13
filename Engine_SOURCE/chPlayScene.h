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


	public://������ �Լ�
		void generateBullet(int size);
		

	private:
		GameObject* chCameraOBJ;
		GameObject* chUiCursor;
		Transform* chUiCursorTR;
		GameObject* player;

		BulletPool* pool;
	


		//������ ����
		std::vector<Bullet*> containBullets;
		
		
	};
}

