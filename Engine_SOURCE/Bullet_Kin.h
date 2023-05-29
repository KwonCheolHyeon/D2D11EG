#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "MonsterBase.h"

namespace ch
{
	class Bullet_Kin : public Script
	{
    public:
        Bullet_Kin();
        virtual ~Bullet_Kin();

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

        void endHitAnimation();

    public:
        void Spawn();
        void Idle();
        void chase();
        void Hit();
        void Move();
        void Attack();
        void Death();

    private:
        Animator* monsAnimator;
        Transform* mTr;
        monsterState mS;

    private:
        int monsterHp;
        bool HitAcc;
	};

}

