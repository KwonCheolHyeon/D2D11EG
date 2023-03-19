#pragma once
#include "chScript.h"

namespace ch
{
    enum class ePlayerState
    {
        Front,
        Back,
        Dodge,
        Attack,
        Reload,
        Fall,

        End,
    };

    class mainPlayerScript :
        public Script
    {
    public:
        mainPlayerScript();
        virtual ~mainPlayerScript();

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


    private:
      

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;

    };
}

