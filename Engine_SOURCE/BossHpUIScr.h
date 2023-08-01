#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "EventObj.h"
#include "MonsterBase.h"

namespace ch
{
	class BossHpUIScr : public Script
	{
	public:
		BossHpUIScr();
		virtual ~BossHpUIScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		/*void SetBossMonster(MonsterBase* _a) { boss = _a; }
		MonsterBase* GetBossMonster() { return boss; }*/

		void SetEvent(EventObj* _a) { eventObj = _a; }

	private:
		Animator* ani;
		EventObj* eventObj;
		MonsterBase* boss;

		float maxHp;
		float hp;
		float timer;

	};
}


