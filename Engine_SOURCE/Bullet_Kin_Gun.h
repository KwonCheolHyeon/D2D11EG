#pragma once
#include "chGameObject.h"

namespace ch 
{
	class Bullet_Kin_Gun : public GameObject
	{
	public:
		Bullet_Kin_Gun();
		virtual ~Bullet_Kin_Gun();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetOwnerMoster(MonsterBase* _a) { OwnerMonster = _a; }
		MonsterBase* GetOwnerMonster() { return OwnerMonster; }
	private:
		class MonsterBase* OwnerMonster;
		Animator* monsterGunAni;

	};


}

