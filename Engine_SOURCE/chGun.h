#pragma once
#include "chGameObject.h"
#include "chPlayerHand.h"
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
		void SwapGun();

		//void SetPlayer(GameObject* _player) { player = _player; }
		void SetHand(PlayerHand* hand) { playerHand = hand; }
	protected:
		void GunLookCursor();

		GunStat pistol;
		GunStat shotGun;
		PlayerHand* playerHand;
	private:
		GameObject* gunObject;
		Transform* gunTransform;

		//GameObject* player;
		

	};

}
