#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "ItemBox.h"
namespace ch 
{
    enum itemBoxState 
    {
        CloseBox,
        OpenBox,
    };
	class ItemBoxScr :public Script
	{
    public:
        ItemBoxScr();
        virtual ~ItemBoxScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        void openBox();
        void closeBox();

    private:
        Animator* bAnimator;
        itemBoxState ibs;
        bool oneOpen;
        bool p2bOn;
        bool p2bOnKey;

	};


}

