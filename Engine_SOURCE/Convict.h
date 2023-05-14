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

    public:// 01   : ���콺�÷��̾� ���� ���� ����
        void MouseAndPlayerAngle();
        void playerLookingMouse();
    private:
        void SetAnimation();

    private:
        Transform* pTr;
        Collider2D* pCollider;
        Animator* pAnimator;

        CharacterBase* player;

    private://01
        float c2mAngle;

	};
}

//�˼� ĳ���� �̹����� �ݶ��̴��� ü�� ���