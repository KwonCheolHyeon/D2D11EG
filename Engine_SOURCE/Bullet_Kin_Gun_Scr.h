#pragma once
#include "chScript.h"
#include "chAnimator.h"
namespace ch 
{
	class Bullet_Kin_Gun_Scr :public Script
	{
    public:
        Bullet_Kin_Gun_Scr();
        virtual ~Bullet_Kin_Gun_Scr();

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
        Animator* anima;
        Transform* thisTrans;
        class MonsterBase* Owner;
	};


}

