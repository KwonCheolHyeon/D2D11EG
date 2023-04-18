#pragma once
#include "chGameObject.h"
#include "chPlayerHand.h"
#include "chBullet.h"
#include "chBulletPool.h"
#include "chGenericAnimator.h"
namespace ch
{
	struct GunStat 
	{
		int damage; // ÃÑ µ¥¹ÌÁö
		int speed; //ÃÑ ½ºÇÇµå
		int bulletCount; // ÃÑ¾ËÀÇ °¹¼ö
		int magazineCount;//ÅºÃ¢ÀÇ ÃÑ °¹¼ö
	};

	class Gun : public GameObject
	{
	public:
		Gun();
		Gun(int a);
		virtual ~Gun();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void Reload();
		void Shot();
		void ReturnBullet();
		void SwapGun();

		//void SetPlayer(GameObject* _player) { player = _player; }
		void SetHand(PlayerHand* hand) { playerHand = hand; }
		void SetPool(BulletPool* pool) { bulletpool = pool; }
		BulletPool* GetPool() { return bulletpool; }

		static bool reboundTrue;
	public:
		float angle;
		void angleFind();

	public:
		Vector3 rebound;
		void HandDownAnimate(Vector3 handPos);//GenericAnimator
		void HandUpAnimate(Vector3 handPos);//GenericAnimator
		void HandDownPos(float cur);
		void HandUpPos(float cur);

	protected:
		void GunLookCursor();
	

		GunStat pistol;
		GunStat shotGun;
		PlayerHand* playerHand;


	private:
		GameObject* gunObject;
		Transform* gunTransform;
		BulletPool* bulletpool;
		Bullet* bulletOBJ;
		std::vector<Bullet*> bullets;
		bool CollectAcces;

		GenericAnimator genericAnimator;
	};

}
