#pragma once
#include "chScript.h"
#include "chPlayerHand.h"
#include "chBullet.h"
#include "chBulletPool.h"
#include "chGenericAnimator.h"

namespace ch 
{
	
	class PistolScr : public Script
	{
	public:
		PistolScr();
		virtual ~PistolScr();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void Reload();
		void Shot();
		void ReturnBullet();
	

		void SetpistolHand(PlayerHand* hand) { playerHand = hand; }
		PlayerHand* GetpistolHand() { return playerHand; }
		void SetpistolPool(BulletPool* pool) { bulletpool = pool; }
		BulletPool* GetpistolPool() { return bulletpool; }
		void SetGunBox(GameObject* box) { gunBox = box; }

		static bool reboundTrue;
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
		float shotTimer = 0.0f;

	private://������
		float reloadTime;//������ �ð�
		int magazine;//źâ


	};
}

