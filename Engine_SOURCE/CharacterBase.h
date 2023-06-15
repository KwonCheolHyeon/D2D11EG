#pragma once
#include "chGameObject.h"
#include "chAnimator.h"
#include "chCameraScript.h"
namespace ch
{

	enum PlayerDirections//��� �ϳ��� ����
	{
		North=1,//�� 1
		South=2,//�Ʒ� 2

		East=3,//�� 3
		West=4,//�� 4

		NE=5,//�ϵ��� 5
		NW=6//�ϼ��� 6
	};

	class CharacterBase : public GameObject
	{
	public:
		CharacterBase();
		virtual ~CharacterBase();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		PlayerDirections GetPD() { return pD; }
		void SetPD(PlayerDirections _a) { pD = _a; };

		void reset();

	public:// 01   : ���콺�÷��̾� ���� ���� ����
		void MouseAndPlayerAngle();
		void playerLookingMouse();
		

	public:
		PlayerDirections pD;
		Collider2D* pCollider;
	private://01
		float c2mAngle;

	private://����
		Animator* pAnima;
		GameObject* playerOBJ;
		
	};
}

