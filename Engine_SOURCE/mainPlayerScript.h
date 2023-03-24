#pragma once
#include "chScript.h"

namespace ch
{
    enum class ePlayerState
    {
        Front,
        Back,
        Left,
        Right,
        Walking,//walking idle dodge묶어서 
        Idle,
        Dodge,
        Attack,
        Reload,
        Fall,

        End,
    };

    class mainPlayerScript :
        public Script
    {
    public:
        mainPlayerScript();
        virtual ~mainPlayerScript();

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
    public://행동 
        void chWalking();
        bool chCheckDirectionKey();//방향키를 눌렀는지 확인
        void chState();

        void chDodging();//구르기 움직임

    public : //애니메이션 상태
        void IdleState();
        void WalkingState();
        void DodgeState();//구르기 애니메이션
    private:
      

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;
        Animator* animator;
        Rigidbody* rigidi;
        bool keyLock = true;

    };
}

