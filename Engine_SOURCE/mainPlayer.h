#pragma once
#include "chGameObject.h"
#include "chScript.h"

namespace ch
{
	class MeshRenderer;
	class mainPlayer : public Script
	{
	public:
		mainPlayer();
		virtual ~mainPlayer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		MeshRenderer* mMr;
	};
}

