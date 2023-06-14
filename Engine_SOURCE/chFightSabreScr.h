#pragma once
#include "chScript.h"
#include "chGun.h"

namespace ch
{
	enum FightSabreState
	{
		SabreItemBox,
		SabreActive,//idle
		SabrenonActive,//pistol»óÅÂ
		SabreReload,
		SabreShot,
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

		void FightSabreOn() { fss = FightSabreState::SabreActive; }
		void FightSabreOff() { fss = FightSabreState::SabrenonActive; }

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

