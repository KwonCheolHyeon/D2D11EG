#pragma once
#include "chScript.h"
#include "chAnimator.h"
#include "MonsterBase.h"
#include "MonsterBulletObj.h"
namespace ch
{
	class Boss : public Script
	{
    public:
        Boss();
        virtual ~Boss();

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
        void BossSpawn();
        void BossIdle();
        void BossChase();
        void BossHit();
        void BossMove();
        void BossAttack();
        void BossSkyBomb();
        void BossDeath();

        void SetMd();
        void Attack();

    private://수학
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
        Animator* mBossAni;
        GameObject* mBoss;
        Transform* mBtr;
        Collider2D* mBcol;
        monsterState mS;

        monsterDir mD;
        monsterDir prevmD;

    private:
        GameObject* player;
        MonsterBase* thisMonster;
        chasePlayerOBJ* thisMosterCollider;
        MonsterBulletObj* monsBullet;
        int monsterHp;
        int first;
        bool hit;

    private://타이머
        float attackTimer;
        float hitAniTimer;
        GenericAnimator GenericAnimator;
	};
}

