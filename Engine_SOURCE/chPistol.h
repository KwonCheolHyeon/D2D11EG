#pragma once
#include "chGun.h"
#include "chPlayerHand.h"
#include "chBullet.h"

namespace ch 
{
	class Pistol : public Gun
	{
	public:
		Pistol();
		virtual ~Pistol();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetPlayer(GameObject* _player) { player = _player; }
		void SetHand(PlayerHand* hand) { pHand = hand; }
		void pistolSetPosition();

	public:
		std::vector<Bullet*> bullets;
		float angle;

	private:
		Transform* pistolPosition;
		GameObject* pistolOBJ;
		GameObject* player;
		PlayerHand* pHand;

		
	};


}

