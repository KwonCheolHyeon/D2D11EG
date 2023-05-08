#pragma once
#include "chScript.h"
#include "CharacterBase.h"
#include "chRigidbody.h"

namespace ch
{
    enum PlayerState
    {
        Idle = 1, // �⺻ ����		//1
        Walk = 2, //�ȱ�				//2
        Dodge = 3 // ������			//3
    };
    enum PlayerDodgeDirections
    {
        NorthDodge = 1,//�� 1
        SouthDodge = 2,//�Ʒ� 2

        EastDodge = 3,//�� 3
        WestDodge = 4,//�� 4

        NEDodge = 5,//�ϵ��� 5
        NWDodge = 6//�ϼ��� 6
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

    public:
        void Walking();
        void Dodging();
        void afterDodging();
        void gotoNormal();
        bool CheckKeyDirection();
    private://
        PlayerState pS;
        PlayerDodgeDirections pDD;
    private://
        Transform* pTr;
        Rigidbody* pRb;
        CharacterBase* player;
        
	};
}


//�˼� ĳ���� ������ ��ũ��
