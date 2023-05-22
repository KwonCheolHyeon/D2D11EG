#pragma once
#include "chScript.h"
#include "CharacterBase.h"
#include "chAnimator.h"
#include "chCollider2D.h"

namespace ch
{
	class Convict : public Script
	{
	public:
        Convict();
        virtual ~Convict();

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

    public:// 01   : 마우스플레이어 사이 각도 관련
      
        void playerLookingMouse();
        void HandSide();
        void MouseAndPlayerAngle();
        void SetAnimation();
    private:
        
        bool isDodgeAnimationing();
        void afterDodging();
        void playWalkingAin();
    private:
        Transform* pTr;
        Collider2D* pCollider;
        Animator* pAnimator;

        CharacterBase* player;

    private://01
        float c2mAngle;
        int prevIdleDirection;//
        int prevWalkDirection;//
        int prevPlayerState;
        bool playWalking;
	};
}

//죄수 캐릭터 이미지와 콜라이더와 체력 담당
