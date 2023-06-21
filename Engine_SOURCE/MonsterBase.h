#pragma once
#include "chGameObject.h"
#include "chasePlayerOBJ.h"

namespace ch 
{
	class DoorObj;
	enum monsterState 
	{
		Spawn,
		mIdle,
		chase,
		Hit,
		Move,
		Attack,
		SkyBomb,
		BossFlyAni,
		BossGoMid,
		Death
	};
	enum monsterDir 
	{
		mNorth = 1,//�� 1
		mSouth = 2,//�Ʒ� 2

		mEast = 3,//�� 3
		mWest = 4,//�� 4

		mNE = 5,//�ϵ��� 5
		mNW = 6,//�ϼ��� 6

		mSE = 7,//������ 7
		mSW = 8,//������ 8
		prev
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
		void SetMonsterChaseCollider(chasePlayerOBJ* _a) { monsterChaseCollider = _a; }
		chasePlayerOBJ* GetMonsterChaseCollider() { return monsterChaseCollider; }

		void SetPlayer(GameObject* _a) { player = _a; }
		GameObject* GetPlayer() { return player; }

	private:
		chasePlayerOBJ* monsterChaseCollider; // Declare the member variable
		GameObject* player;
		
		
	};
}

