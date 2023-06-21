#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "BossHpBarObj.h"
#include "chTexture.h"
namespace ch
{
	class BossHpScr : public Script
	{
	public:
		BossHpScr();
		virtual ~BossHpScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		
	private:

		Animator* ani;
		std::shared_ptr<Texture> hpTexture;

	private:
		float health;
		float bossHp;
		float maxHp;

	};
}


