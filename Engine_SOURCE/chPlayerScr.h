#pragma once
#include "chScript.h"
#include "chHeart_UI.h"
#include "chGenericAnimator.h"
#include "chAnimator.h"

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

            Walking,//walking idle dodge��� 
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

    public://�ൿ ����
        void chWalking(); //�ȱ�
        void chDodging();//������
        
    public://���콺�� ĳ���� ���� ����
        void mousePos();//���콺 ��ġ�� ���� ĳ���� �ٶ󺸴� ���� ����
        void gunHandSide();
        void playerLookMouse();

    public:
        bool chCheckDirectionKey(); //����Ű �������� Ȯ��
        bool chCheckDirectionKeyDoge(); //������

    public:  //�ִϸ��̼�
        void chIdleAni();
        void afterDodgeIdleAni();
        void chWalkAni();
        void afterDodgeWalkAni();
        void chDodgeAni();
        void chState();//���¿� ���� �ִϸ��̼� ����

    public: //���� ��
        void afterDodge();
        void allowDodge();
        //������ �ִϸ��̼�
        void GenAnimate(Vector3 dodgePos);
  
    public: //ü�°��� �Լ�
        void SetHeart_UI(std::vector<Heart_UI*> a) { pHeartControl = a; }
        void SetHeart();

    private:
        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;
        std::bitset<static_cast<UINT>(ePlayerState::End)> mPrevState;
        bool compareState();
        Animator* animator;
        Transform* transform;
        Vector3 pos;
        bool keyLock = true;

    private:
        Vector3 mousePositon;
        Vector3 CharterPosition;
        float C2Mangle;//ĳ���Ϳ� ���콺 ���� ����
        float playerSpeed;
        bool canDodge;

    private:
        GenericAnimator GenericAnimator;
        Vector3 Position;
        
    private://ü�� ���� ����
        std::vector<Heart_UI*> pHeartControl;
        int pHp;
        int prevHp;
        
	};

}

