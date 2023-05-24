#pragma once
#include "chGameObject.h"

namespace ch 
{
	enum monsterState 
	{
		Spawn,
		mIdle,
		Hit,
		Move,
		Attack,
		SkyBomb,
		Death
	};
	class MonsterBase : public GameObject
	{
	public:
		MonsterBase();
		virtual ~MonsterBase();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	};
}

