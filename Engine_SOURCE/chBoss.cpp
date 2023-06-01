#include "chBoss.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "MonsterBulletScr.h"
namespace ch
{
	Boss::Boss()
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Initalize()
	{
		thisMonster = dynamic_cast<MonsterBase*>(GetOwner());

		mBoss = GetOwner();
		mBossAni = GetOwner()->AddComponent<Animator>();
		mBtr = GetOwner()->GetComponent<Transform>();
		mBcol = GetOwner()->AddComponent<Collider2D>();
		mBcol->SetName(L"BossCollider");
		mBcol->SetType(eColliderType::Rect);
		mBcol->SetSize(Vector2(0.3f, 0.3f));


		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

	#pragma region �ִ�
		{//Down

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Attack", L"enterthe/enemy/Boss/Down_Attack.png");
				mBossAni->Create(L"Boss_Down_Attack", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 2, 0.5f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Hit", L"enterthe/enemy/Boss/Down_Hit.png");
				mBossAni->Create(L"Boss_Down_Hit", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 1, 0.1f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Idle", L"enterthe/enemy/Boss/Down_Idle.png");
				mBossAni->Create(L"Boss_Down_Idle", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 1, 0.1f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Down_Move", L"enterthe/enemy/Boss/Down_Move.png");
				mBossAni->Create(L"Boss_Down_Move", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 68.0f), Vector2::Zero, 4, 0.15f);
			}
		}
		{//Up
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Attack", L"enterthe/enemy/Boss/Up_Attack.png");
				mBossAni->Create(L"Boss_Up_Attack", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), Vector2::Zero, 2, 0.5f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Hit", L"enterthe/enemy/Boss/Up_Hit.png");
				mBossAni->Create(L"Boss_Up_Hit", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Idle", L"enterthe/enemy/Boss/Up_Idle.png");
				mBossAni->Create(L"Boss_Up_Idle", texture, Vector2(0.0f, 0.0f), Vector2(37.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Up_Move", L"enterthe/enemy/Boss/Up_Move.png");
				mBossAni->Create(L"Boss_Up_Move", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), Vector2::Zero, 4, 0.15f);
			}
		}
		{//Left
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Attack", L"enterthe/enemy/Boss/Left_Attack.png");
				mBossAni->Create(L"Boss_Left_Attack", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 46.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Hit", L"enterthe/enemy/Boss/Left_Hit.png");
				mBossAni->Create(L"Boss_Left_Hit", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 50.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Idle", L"enterthe/enemy/Boss/Left_Idle.png");
				mBossAni->Create(L"Boss_Left_Idle", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Left_Move", L"enterthe/enemy/Boss/Left_Move.png");
				mBossAni->Create(L"Boss_Left_Move", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 4, 0.15f);
			}

		}
		{//Right
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Attack", L"enterthe/enemy/Boss/Right_Attack.png");
				mBossAni->Create(L"Boss_Right_Attack", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 46.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Hit", L"enterthe/enemy/Boss/Right_Hit.png");
				mBossAni->Create(L"Boss_Right_Hit", texture, Vector2(0.0f, 0.0f), Vector2(76.0f, 50.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Idle", L"enterthe/enemy/Boss/Right_Idle.png");
				mBossAni->Create(L"Boss_Right_Idle", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_Right_Move", L"enterthe/enemy/Boss/Right_Move.png");
				mBossAni->Create(L"Boss_Right_Move", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 48.0f), Vector2::Zero, 4, 0.15f);
			}

		}
		{//Right down

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Attack", L"enterthe/enemy/Boss/RightDown_Attack.png");
				mBossAni->Create(L"Boss_RightDown_Attack", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 61.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Hit", L"enterthe/enemy/Boss/RightDown_Hit.png");
				mBossAni->Create(L"Boss_RightDown_Hit", texture, Vector2(0.0f, 0.0f), Vector2(59.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Idle", L"enterthe/enemy/Boss/RightDown_Idle.png");
				mBossAni->Create(L"Boss_RightDown_Idle", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightDown_Move", L"enterthe/enemy/Boss/RightDown_Move.png");
				mBossAni->Create(L"Boss_RightDown_Move", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero, 6, 0.15f);
			}
		}
		{//Left Down
			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Attack", L"enterthe/enemy/Boss/LeftDown_Attack.png");
				mBossAni->Create(L"Boss_LeftDown_Attack", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 59.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Hit", L"enterthe/enemy/Boss/LeftDown_Hit.png");
				mBossAni->Create(L"Boss_LeftDown_Hit", texture, Vector2(0.0f, 0.0f), Vector2(59.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Idle", L"enterthe/enemy/Boss/LeftDown_Idle.png");
				mBossAni->Create(L"Boss_LeftDown_Idle", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftDown_Move", L"enterthe/enemy/Boss/LeftDown_Move.png");
				mBossAni->Create(L"Boss_LeftDown_Move", texture, Vector2(0.0f, 0.0f), Vector2(65.0f, 60.0f), Vector2::Zero,5, 0.15f);
			}

		}
		{//Right Up

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Attack", L"enterthe/enemy/Boss/RightUp_Attack.png");
				mBossAni->Create(L"Boss_RightUp_Attack", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 46.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Hit", L"enterthe/enemy/Boss/RightUp_Hit.png");
				mBossAni->Create(L"Boss_RightUp_Hit", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 44.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Idle", L"enterthe/enemy/Boss/RightUp_Idle.png");
				mBossAni->Create(L"Boss_RightUp_Idle", texture, Vector2(0.0f, 0.0f), Vector2(41.0f, 44.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_RightUp_Move", L"enterthe/enemy/Boss/RightUp_Move.png");
				mBossAni->Create(L"Boss_RightUp_Move", texture, Vector2(0.0f, 0.0f), Vector2(46.0f, 43.0f), Vector2::Zero, 3, 0.15f);
			}
		}
		{//Left Up

			{//Attack
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Attack", L"enterthe/enemy/Boss/LeftUp_Attack.png");
				mBossAni->Create(L"Boss_LeftUp_Attack", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 43.0f), Vector2::Zero, 2, 1.f);
			}
			{//Hit
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Hit", L"enterthe/enemy/Boss/LeftUp_Hit.png");
				mBossAni->Create(L"Boss_LeftUp_Hit", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 48.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Idle
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Idle", L"enterthe/enemy/Boss/LeftUp_Idle.png");
				mBossAni->Create(L"Boss_LeftUp_Idle", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 44.0f), Vector2::Zero, 1, 0.5f);
			}
			{//Move
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Boss_LeftUp_Move", L"enterthe/enemy/Boss/LeftUp_Move.png");
				mBossAni->Create(L"Boss_LeftUp_Move", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 43.0f), Vector2::Zero, 3, 0.15f);
			}
		}


	#pragma endregion
		mBtr->SetPosition(Vector3(1.f, 1.f, 1.f));
		mBtr->SetScale(Vector3(5.f, 6.f, 1.f));
		mBossAni->Play(L"Boss_LeftDown_Idle");
		monsterHp = 6;
		
		player = thisMonster->GetPlayer();
	}
	void Boss::Update()
	{
		
		SetMd();
		mS = monsterState::Attack;
		switch (mS)
		{
		case monsterState::Spawn:
			BossSpawn();
			break;
		case monsterState::mIdle:
			BossIdle();
			break;
		case monsterState::chase:
			BossChase();
			break;
		case monsterState::Hit:
			BossHit();
			break;
		case monsterState::Move:
			BossMove();
			break;
		case monsterState::Attack:
			BossAttack();
			break;
		case monsterState::SkyBomb:
			BossSkyBomb();
			break;
		case monsterState::Death:
			BossDeath();
			break;
		default:
			break;
		}


		
	}
	void Boss::FixedUpdate()
	{
	}
	void Boss::Render()
	{
	}
	void Boss::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Weapone)
		{
			monsterHp -= 1;
			if (monsterHp == 0)
			{
				mS = monsterState::Death;
			}
			else
			{
				mS = monsterState::Hit;
			}
		}
	}
	void Boss::OnCollision(Collider2D* oppo)
	{

	}
	void Boss::OnCollisionExit(Collider2D* oppo)
	{

	}
	void Boss::OnTriggerEnter(Collider2D* oppo)
	{

	}
	void Boss::OnTrigger(Collider2D* oppo)
	{

	}
	void Boss::OnTriggerExit(Collider2D* oppo)
	{

	}
	void Boss::BossSpawn()
	{

	}
	void Boss::BossIdle()
	{

	}
	void Boss::BossChase()
	{

	}
	void Boss::BossHit()
	{

		switch (mD)
		{
		case monsterDir::mNorth:

			break;
		case monsterDir::mSouth:

			break;
		case monsterDir::mEast:

			break;
		case monsterDir::mWest:

			break;
		case monsterDir::mNE:

			break;
		case monsterDir::mNW:

			break;
		case monsterDir::mSE:

			break;
		case monsterDir::mSW:

			break;
		default:
			break;
		}




	}
	void Boss::BossMove()
	{



	}
	void Boss::BossAttack()
	{
		switch (mD)
		{
		case monsterDir::mNorth:

			break;
		case monsterDir::mSouth:

			break;
		case monsterDir::mEast:

			break;
		case monsterDir::mWest:

			break;
		case monsterDir::mNE:

			break;
		case monsterDir::mNW:

			break;
		case monsterDir::mSE:

			break;
		case monsterDir::mSW:

			break;
		default:
			break;
		}

		attackTimer -= Time::DeltaTime(); // attackTimer ���� ����

		if (attackTimer <= 0.0f)
		{
			Attack();
			attackTimer = 0.2f; // 0.2�ʷ� Ÿ�̸� �缳��
		}
	}
	void Boss::BossSkyBomb()
	{

	}
	void Boss::BossDeath()
	{

	}
	void Boss::SetMd()
	{
		
		Vector3 monsterPosition = mBoss->GetComponent<Transform>()->GetPosition();
		Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

		float dx = playerPosition.x - monsterPosition.x;
		float dy = playerPosition.y - monsterPosition.y;

		float angle = atan2(dy, dx) * 180 / 3.141592f;


		if (angle >= -22.5 && angle < 22.5)
		{
			mD = monsterDir::mEast;
		}
		else if (angle >= 22.5 && angle < 67.5)
		{
			mD = monsterDir::mNE;
		}
		else if (angle >= 67.5 && angle < 112.5)
		{
			mD = monsterDir::mNorth;
		}
		else if (angle >= 112.5 && angle < 157.5)
		{
			mD = monsterDir::mNW;
		}
		else if (angle >= 157.5 || angle < -157.5)
		{
			mD = monsterDir::mWest;
		}
		else if (angle >= -157.5 && angle < -112.5)
		{
			mD = monsterDir::mSW;
		}
		else if (angle >= -112.5 && angle < -67.5)
		{
			mD = monsterDir::mSouth;
		}
		else if (angle >= -67.5 && angle < -22.5)
		{
			mD = monsterDir::mSE;
		}
	}
	void Boss::Attack()
	{
		monsBullet = new MonsterBulletObj();
		MonsterBulletScr* bulletScript = monsBullet->AddComponent<MonsterBulletScr>();
		bulletScript->Initalize();
		float angle = 0;
		Vector3 boss = mBoss->GetComponent<Transform>()->GetPosition();

		switch (mD)
		{
		case monsterDir::mNorth:
			angle = 90.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(0.f,1.f,0.f);
			break;
		case monsterDir::mSouth:
			angle = 270.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(0.f, -1.f, 0.f);
			break;
		case monsterDir::mEast:
			angle = 0.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(1.f, 0.f, 0.f);
			break;
		case monsterDir::mWest:
			angle = 180.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(-1.f, 0.f, 0.f);
			break;
		case monsterDir::mNE:
			angle = 45.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(1.f, 1.f, 0.f);
			break;
		case monsterDir::mNW:
			angle = 135.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(-1.f, 1.f, 0.f);
			break;
		case monsterDir::mSE:
			angle = 315.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(1.f, -1.f, 0.f);
			break;
		case monsterDir::mSW:
			angle = 225.f;
			boss = mBoss->GetComponent<Transform>()->GetPosition() + Vector3(-1.f, -1.f, 0.f);
			break;
		default:
			break;
		}



		bulletScript->shootingBullet(angle, boss);

	}
}