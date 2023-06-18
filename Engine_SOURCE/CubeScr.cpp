#include "CubeScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chasePlayerSCR.h"
#include "chObject.h"
namespace ch
{
	CubeScr::CubeScr()
	{
	}
	CubeScr::~CubeScr()
	{
	}
	void CubeScr::Initalize()
	{

		thisMonster = dynamic_cast<MonsterBase*>(GetOwner());

		anima = GetOwner()->AddComponent<Animator>();
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Cube_Idle", L"enterthe/enemy/Cube/Idle.png");
			anima->Create(L"M_Cube_Idle", texture, Vector2(0.0f, 0.0f), Vector2(28.0f, 23.0f), Vector2::Zero, 3, 0.2f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Cube_Idle_back", L"enterthe/enemy/Cube/Idle_back.png");
			anima->Create(L"M_Cube_Idle_back", texture, Vector2(0.0f, 0.0f), Vector2(28.0f, 23.0f), Vector2::Zero, 3, 0.2f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Cube_Attack", L"enterthe/enemy/Cube/Attack.png");
			anima->Create(L"M_Cube_Attack", texture, Vector2(0.0f, 0.0f), Vector2(28.0f, 23.0f), Vector2::Zero, 10, 0.2f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Cube_death", L"enterthe/enemy/Cube/death.png");
			anima->Create(L"M_Cube_death", texture, Vector2(0.0f, 0.0f), Vector2(47.0f, 49.0f), Vector2::Zero, 6, 0.2f);
		}
		anima->Play(L"M_Cube_Idle");

		GetOwner()->SetLayerType(eLayerType::Monster);

		mTr = GetOwner()->GetComponent<Transform>();
		mTr->SetScale(Vector3(5.3f, 5.6f, 0.0f));

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BulletKinMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		Collider2D* mCollider = GetOwner()->AddComponent<Collider2D>();
		mCollider->SetName(L"CubeCollider");
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.1f, 0.1f));


		ms = monsterState::Move;

		bulletMakeCount = 0;
		bulletMakeTime = 0.f;
		monsterHp = 8;

	}
	void CubeScr::Update()
	{
		switch (ms)
		{
		case monsterState::Move:
			Idle();
			break;
		case monsterState::Attack:
			Attack();
			break;
		case monsterState::Death:
			Death();
			break;
		case monsterState::SkyBomb:
			BulletMake();
			break;
		default:
			break;
		}



	}
	void CubeScr::FixedUpdate()
	{
	}
	void CubeScr::Render()
	{
	}
	void CubeScr::OnCollisionEnter(Collider2D* oppo)
	{
	}
	void CubeScr::OnCollision(Collider2D* oppo)
	{
	}
	void CubeScr::OnCollisionExit(Collider2D* oppo)
	{
	}
	void CubeScr::Idle()
	{
		if (anima->IsAnimationRunning(L"M_Cube_Idle") == false)
		{
			anima->Play(L"M_Cube_Idle");
		}

		if (thisMonster->GetMonsterChaseCollider()->GetComponent<chasePlayerSCR>()->isFindPlayer() == true) 
		{
			ms = monsterState::SkyBomb;
		}

	}

	void CubeScr::Attack()
	{
		nullbulletTime += Time::DeltaTime();
		if (moveOn == true) 
		{
			moveOn = false;
			Mbscr[0]->moveOns();
			Mbscr[1]->moveOns();
			Mbscr[2]->moveOns();
			Mbscr[3]->moveOns();
			Mbscr[4]->moveOns();
			Mbscr[5]->moveOns();
			Mbscr[6]->moveOns();
			Mbscr[7]->moveOns();
			
		}
		

		if (nullbulletTime >= 1.6f) {

			for (int i = 0; i < 8; i++)
			{
				Mbobj[i] = nullptr;
				Mbscr[i] = nullptr;
			}
			nullbulletTime = 0.f;
			ms = monsterState::Move;
		}
		
	}
	
	void CubeScr::Death()
	{

	}
	void CubeScr::BulletMake()
	{
		if (anima->IsAnimationRunning(L"M_Cube_Attack") == false) 
		{
			anima->Play(L"M_Cube_Attack", false);
		}

		Vector3 a = mTr->GetPosition();

		bulletMakeTime += Time::DeltaTime();

		if (bulletMakeTime > 0.15f) 
		{
			bulletMakeTime = 0;
			bulletMakeCount += 1;

			switch (bulletMakeCount)
			{
			case 1:
				Mbobj[0] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[0] = Mbobj[0]->AddComponent<MonsterBullet2Scr>();
				Mbscr[0]->Initalize();
				Mbscr[0]->shootingBullet(0, a +Vector3(0.7f,0.f,0.f));
				break;
			case 2:
				Mbobj[1] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[1] = Mbobj[1]->AddComponent<MonsterBullet2Scr>();
				Mbscr[1]->Initalize();
				Mbscr[1]->shootingBullet(45, a + Vector3(0.5f, 0.5f, 0.f));
				break;
			case 3:
				Mbobj[2] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[2] = Mbobj[2]->AddComponent<MonsterBullet2Scr>();
				Mbscr[2]->Initalize();
				Mbscr[2]->shootingBullet(90, a + Vector3(0.f, 0.7f, 0.f));
				break;
			case 4:
				Mbobj[3] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[3] = Mbobj[3]->AddComponent<MonsterBullet2Scr>();
				Mbscr[3]->Initalize();
				Mbscr[3]->shootingBullet(135, a + Vector3(-0.5f, 0.5f, 0.f));
				break;
			case 5:
				Mbobj[4] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[4] = Mbobj[4]->AddComponent<MonsterBullet2Scr>();
				Mbscr[4]->Initalize();
				Mbscr[4]->shootingBullet(180, a + Vector3(-0.7f, 0.f, 0.f));
				break;
			case 6:
				Mbobj[5] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[5] = Mbobj[5]->AddComponent<MonsterBullet2Scr>();
				Mbscr[5]->Initalize();
				Mbscr[5]->shootingBullet(225, a + Vector3(-0.5f, -0.5f, 0.f));
				break;
			case 7:
				Mbobj[6] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[6] = Mbobj[6]->AddComponent<MonsterBullet2Scr>();
				Mbscr[6]->Initalize();
				Mbscr[6]->shootingBullet(270, a + Vector3(0.0f, -0.7f, 0.f));
				break;
			case 8:
				Mbobj[7] = object::Instantiate<MonsterBullet2Obj>(eLayerType::MonsterBullet);
				Mbscr[7] = Mbobj[7]->AddComponent<MonsterBullet2Scr>();
				Mbscr[7]->Initalize();
				Mbscr[7]->shootingBullet(315, a + Vector3(0.5f, -0.5f, 0.f));
				break;
			case 9:
				moveOn = true;
				bulletMakeCount = 0;
				ms = monsterState::Attack;
				break;
			default:
				break;
			}
		}

		

		
	}
}