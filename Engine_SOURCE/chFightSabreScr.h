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
	enum FightSabreState
	{
		ItemBox,
		Active,//idle
		nonActive,//pistol»óÅÂ
		Reload,
		Shot,
	};

	class FightSabreScr : public Script
	{
	public:
		FightSabreScr();
		virtual ~FightSabreScr();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* oppo);
		virtual void OnCollision(Collider2D* oppo);
		virtual void OnCollisionExit(Collider2D* oppo);


		void ItemBox();
		void Idle();
		void nonActiveGun();
		void Reload();
		void Shot();

		bool touchGun;
		bool prevTouchGun;
	private:
		Animator* anima;
		FightSabreState fss;
		FightSabreState prevFss;
	};

}

