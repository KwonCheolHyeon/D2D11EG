#pragma once
#include "chScript.h"
namespace ch 
{
	class PlayerScr
        : public Script
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

            Weapone,
            Count,
            End,
        };

    public:
        PlayerScr();
        virtual ~PlayerScr();

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

    public://행동 관련
        void chWalking(); //걷기
        void chDodging();//구르기
        
    public://마우스와 캐릭터 사이 각도
        void mousePos();//마우스 위치에 따라 캐릭터 바라보는 방향 결정

    public:
        bool chCheckDirectionKey(); //방향키 눌렀는지 확인
        bool chCheckDirectionKeyDoge(); //닷지용

    public:  //애니메이션
        void chIdleAni();
        void chWalkAni();
        void chDodgeAni();
        void chState();//상태에 따라 애니메이션 실행

        void gunHandSide();
        void playerLookMouse();

  
    private:
        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;
        std::bitset<static_cast<UINT>(ePlayerState::End)> mPrevState;
        Animator* animator;
        Transform* transform;
        Vector3 pos;
        bool keyLock = true;

    private:
        Vector3 mousePositon;
        Vector3 CharterPosition;
        float C2Mangle;//캐릭터와 마우스 사이 각도



       

	};

}

