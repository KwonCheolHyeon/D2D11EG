#pragma once
#include "chScript.h"
#include "CharacterBase.h"
#include "chRigidbody.h"

namespace ch
{
    enum PlayerState
    {
        Idle, // �⺻ ����		//1
        Walk, //�ȱ�				//2
        Rolling, // ������			//3
        Default
    };
    enum PlayerDodgeDirections
    {
        NorthDodge,//�� 1
        SouthDodge,//�Ʒ� 2

        EastDodge,//�� 3
        WestDodge,//�� 4

        NEDodge,//�ϵ��� 5
        NWDodge//�ϼ��� 6
    };
	class ConvictMove :public Script
	{
    public:
        ConvictMove();
        virtual ~ConvictMove();

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

        PlayerState GetPS() { return pS; }
        void SetPS(PlayerState _a) { pS = _a; };

        PlayerDodgeDirections GetPDD() { return pDD; }
        void SetPDD(PlayerDodgeDirections _a) { pDD = _a; };

        bool GetCandDodging() {return canDodge;}
    public:
        void Idle();
        void Walking();
        void afterWalking();
        void Dodging();
        void afterDodging();
        void gotoNormal();
        

    public:
        bool CheckKeyDirection();
        bool chCheckDirectionKeyDoge(); //������
        void chState();//���¿� ���� �ִϸ��̼� ����
        void chIdleAni();

    private://
        PlayerState pS;
        PlayerDodgeDirections pDD;
    private://
        Transform* pTr;
        Rigidbody* pRb;
        CharacterBase* player;

    public:
        static bool canDodge; 
        bool isDodging;
        bool isRolling;
        bool isWall;
        Vector3 wallPosition;
        float speed;
    private: //�÷��̾� ��
        int directNum; //���� ����
        int secdirectNum;
        int GetClosestDirection(Collider2D* collider);
        int colliderCount;
	};
}


//�˼� ĳ���� ������ ��ũ��
