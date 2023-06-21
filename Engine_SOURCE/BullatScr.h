#pragma once
#include "chScript.h"
#include "MonsterBase.h"
#include "chAnimator.h"

namespace ch 
{

	class BullatScr : public Script
	{
    public:
        BullatScr();
        virtual ~BullatScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* collider) override;
        virtual void OnCollisionStay(Collider2D* collider) override;
        virtual void OnCollisionExit(Collider2D* collider) override;

     

    public:
        void Fly();
        void Attack();
        void AttackOk();
        void Death();
        void afterDeath();

        void GetP2Mangle();
        void shootingBullet(float Gunangle, Vector3 pos);
        void MoveBullet();
    private:
        Animator* anima;
        MonsterBase* thisMonster;
        monsterState ms;
        Transform* mTr;

    private:
        float P2Mangle;
        int monsterHp;
        float setAttackTime;
        float speed;
        float bulletDirectionX;
        float bulletDirectionY;
        float angles;
        Vector3 GunPos;
        float DeathTIME;
        float goToDeathTime;


	};


}

