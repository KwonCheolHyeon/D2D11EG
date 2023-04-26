#pragma once
#include "chScript.h"
#include "chPlayerHand.h"
#include "chBullet.h"
#include "chBulletPool.h"
#include "chAnimator.h"
#include "chCollider2D.h"
#include "chGenericAnimator.h"
#include "mainPlayer.h"

namespace ch
{
	class FightSabreScr : public Script
	{
	public:
		FightSabreScr();
		virtual ~FightSabreScr();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void Reload();
		void Shot();
		void ReturnBullet();

		static bool reboundTrue;
	public:
		void SetpistolHand(PlayerHand* hand) { playerHand = hand; }
		PlayerHand* GetpistolHand() { return playerHand; }
		void SetpistolPool(BulletPool* pool) { bulletpool = pool; }
		BulletPool* GetpistolPool() { return bulletpool; }
		
		void SetGunBox(GameObject* box) { gunBox = box; }

		void SetPlayer(GameObject* _player) { player = _player; }


	public://���� ����
		float angle;
		void angleFind();

	public://���� ���� �ش� ���� ��� �ִ��� �ƴ���
		void notActiveState();
		GunState pistolState;

	public://�ݵ�ȿ��
		Vector3 rebound;
		void HandDownAnimate(Vector3 handPos);//GenericAnimator
		void HandUpAnimate(Vector3 handPos);//GenericAnimator
		void HandDownPos(float cur);
		void HandUpPos(float cur);

	protected:
		void GunLookCursor();

		PlayerHand* playerHand;
		GameObject* player;
	private:
		GameObject* gunBox;
		GameObject* gunObject;
		Transform* gunTransform;
		BulletPool* bulletpool;
		Bullet* bulletOBJ;
		std::vector<Bullet*> bullets;
		bool CollectAcces;

		GenericAnimator genericAnimator;

	private:
		Animator* gAnimator;
		Collider2D* gCollider;
	};

}

