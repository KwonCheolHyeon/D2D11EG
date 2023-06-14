#pragma once
#include "chGameObject.h"
#include "chCollider2D.h"
#include "chRigidbody.h"
#include "chAnimator.h"
namespace ch
{
	class FightSabreObject :public GameObject
	{
	public:
		FightSabreObject();
		virtual ~FightSabreObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void turnEquipItme() { equipItem = true; }

	private:
		Collider2D* obCollider;
		Rigidbody* obRigid;
		Animator* obAnima;

	private:
		bool firstKey;
		bool equipItem;
	};
}
