#pragma once
#include "chGameObject.h"

namespace ch 
{
	struct monsterState 
	{
		int state;
		bool death;
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

