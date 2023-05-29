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
		mNorth = 1,//�� 1
		mSouth = 2,//�Ʒ� 2

		mEast = 3,//�� 3
		mWest = 4,//�� 4

		mNE = 5,//�ϵ��� 5
		mNW = 6,//�ϼ��� 6

		mSE = 7,//������ 7
		mSW = 8//������ 8
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

