#pragma once
#include "chScript.h"
#include "MonsterBase.h"
#include "chAnimator.h"
namespace ch
{

    class CubeScr : public Script
    {
    public:
        CubeScr();
        virtual ~CubeScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);


    public:
        void Attack();
        void Idle();
        void Death();
        void BulletMake();

    private:
        Animator* anima;
        MonsterBase* thisMonster;
        monsterState ms;
        Transform* mTr;
    private:
        float bulletMakeTime;
        int monsterHp;
    };


}

