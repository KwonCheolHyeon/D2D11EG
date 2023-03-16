#pragma once
#include "chGameObject.h"

namespace ch
{
	class Animator;
	class Image;
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Animator* mAnimator;
		Transform* mTr;
	};
}
