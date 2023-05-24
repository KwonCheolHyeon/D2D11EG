#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "MonsterBase.h"
namespace ch
{
	class Boss : public Script
	{
    public:
        Boss();
        virtual ~Boss();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        virtual void OnTriggerEnter(Collider2D* oppo);
        virtual void OnTrigger(Collider2D* oppo);
        virtual void OnTriggerExit(Collider2D* oppo);

    private:
        Animator* mBossAni;
        GameObject* mBoss;
        Transform* mBtr;
        Collider2D* mBcol;

	};
}

