#pragma once
#include <cmath>
#include "chScript.h"
#include "chAnimator.h"
#include "MonsterBase.h"
#include "chasePlayerOBJ.h"
#include "chGenericAnimator.h"

namespace ch
{
	class Bullet_Kin : public Script
	{
    public:
        Bullet_Kin();
        virtual ~Bullet_Kin();

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

        void endHitAnimation();

    public:
        void Spawn();
        void Idle();
        void chase();
        void Hit();
        void Move();
        void Attack();
        void Death();

    private:
        Animator* monsAnimator;
        Transform* mTr;
        monsterState mS;

        GameObject* player;
        MonsterBase* thisMonster;
        GameObject* thisMosterCollider;

    private://����
        float CalculateDistance(const Vector3& position1, const Vector3& position2)
        {
            Vector3 distanceVector = position2 - position1;
            return distanceVector.Length(); 
        }

        Vector3 Normalize(const Vector3& vector)
        {
            float magnitude = vector.Length(); 
            if (magnitude != 0.0f)
            {
                return vector / magnitude;
            }
            else
            {
                return Vector3(0.0f, 0.0f, 0.0f); 
            }
        }

    private:
        void GenericMoveAnimator(int dire);
        GenericAnimator GenericAnimator;
        Vector3 dir;
    private:
        int monsterHp;
        bool HitAcc;

  

	};

}

