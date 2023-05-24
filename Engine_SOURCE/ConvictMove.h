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

	};
}


//�˼� ĳ���� ������ ��ũ��
