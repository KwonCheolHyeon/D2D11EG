#pragma once
#include "chGameObject.h"
#include "chasePlayerOBJ.h"
namespace ch 
{
	enum monsterState 
	{
		Spawn,
		mIdle,
		chase,
		Hit,
		Move,
		Attack,
		SkyBomb,
		Death
	};
	enum monsterDir 
	{
		mNorth = 1,//위 1
		mSouth = 2,//아래 2

		mEast = 3,//동 3
		mWest = 4,//서 4

		mNE = 5,//북동쪽 5
		mNW = 6,//북서쪽 6

		mSE = 7,//남동쪽 7
		mSW = 8//남서쪽 8
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

	public:
		void SetMonsterChaseCollider(GameObject* _a) { monsterChaseCollider = _a; }
		GameObject* GetMonsterChaseCollider() { return monsterChaseCollider; }

	private:
		GameObject* monsterChaseCollider; // Declare the member variable
	};
}

