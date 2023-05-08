#pragma once
#include "chScript.h"
#include "CharacterBase.h"
#include "chRigidbody.h"

namespace ch
{
    enum PlayerState
    {
        Idle = 1, // 기본 상태		//1
        Walk = 2, //걷기				//2
        Dodge = 3 // 구르기			//3
    };
    enum PlayerDodgeDirections
    {
        NorthDodge = 1,//위 1
        SouthDodge = 2,//아래 2

        EastDodge = 3,//동 3
        WestDodge = 4,//서 4

        NEDodge = 5,//북동쪽 5
        NWDodge = 6//북서쪽 6
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


//죄수 캐릭터 움직임 스크립
