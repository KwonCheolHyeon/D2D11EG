#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "DoorObj.h"
namespace ch 
{
	class DoorScr : public Script
	{
    public:
        DoorScr();
        virtual ~DoorScr();

        virtual void Initalize() override;
        virtual void Update() override;
        virtual void FixedUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* oppo);
        virtual void OnCollision(Collider2D* oppo);
        virtual void OnCollisionExit(Collider2D* oppo);

        void openDoor();
        void closeDoor();
        
        void setState();
    private:
        Animator* tAnimator;
        DoorObj* door;
        int doorKey;
        OpenClose oc;
        OpenClose prevoc;
        bool prevDoorState;
	};

}


