#include "Bullet_Kin.h"
#include "chGameObject.h"
#include <random>
#include "MonsterBase.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chCollider2D.h"
#include "chRigidbody.h"
#include "chScene.h"
#include "chTestScene.h"
#include "chasePlayerOBJ.h"
#include "chasePlayerSCR.h"
namespace ch 
{
	Bullet_Kin::Bullet_Kin()
	{
	}

	Bullet_Kin::~Bullet_Kin()
	{
	}

	void Bullet_Kin::Initalize()
	{
		
		thisMonster = dynamic_cast<MonsterBase*>(GetOwner());
		thisMosterCollider = thisMonster->GetMonsterChaseCollider();
		
		monsterHp = 5;
		
		monsAnimator = GetOwner()->AddComponent<Animator>();
		GetOwner()->SetLayerType(eLayerType::Monster);
		mTr = GetOwner()->GetComponent<Transform>();
		mTr->SetPosition(Vector3(6.f, 6.f, 0.f));
		mTr->SetScale(Vector3(5.3f, 5.6f, 0.0f));
		
#pragma region idle
		{
			{
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MIdleFront", L"enterthe/enemy/bullet_Kin/idle/idle_02.png");
				monsAnimator->Create(L"M_Idle_Front", texture, Vector2(0.0f, 0.0f), Vector2(15.0f, 23.0f), Vector2::Zero, 2, 0.3f);
			}
			{
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MIdleLeft", L"enterthe/enemy/bullet_Kin/idle/idle_01.png");
				monsAnimator->Create(L"M_Idle_Left", texture, Vector2(0.0f, 0.0f), Vector2(15.0f, 23.0f), Vector2::Zero, 2, 0.3f);
			}
			{
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MIdleBack", L"enterthe/enemy/bullet_Kin/idle/idle_03.png");
				monsAnimator->Create(L"M_Idle_Back", texture, Vector2(0.0f, 0.0f), Vector2(15.0f, 23.0f), Vector2::Zero, 2, 0.3f);
			}
		}
#pragma endregion

#pragma region Hit
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MHit", L"enterthe/enemy/bullet_Kin/hit/hit01.png");
			monsAnimator->Create(L"M_Hit", texture, Vector2(0.0f, 0.0f), Vector2(13.0f, 23.0f), Vector2::Zero, 2, 0.3f);

		}
#pragma endregion

#pragma region Walk
		{
			{
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"M_walk_Left", L"enterthe/enemy/bullet_Kin/walk/walk_01.png");
				monsAnimator->Create(L"M_Walk_left", texture, Vector2(0.0f, 0.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 6, 0.2f);
			}
			{
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"M_walk_Front", L"enterthe/enemy/bullet_Kin/walk/walk_02.png");
				monsAnimator->Create(L"M_Walk_Front", texture, Vector2(0.0f, 0.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 6, 0.2f);
			}
			{
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"M_walk_Back", L"enterthe/enemy/bullet_Kin/walk/walk_03.png");
				monsAnimator->Create(L"M_Walk_Back", texture, Vector2(0.0f, 0.0f), Vector2(16.0f, 24.0f), Vector2::Zero, 7, 0.2f);
			}
		}
#pragma endregion

#pragma region Death
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"M_death", L"enterthe/enemy/bullet_Kin/death/death01.png");
			monsAnimator->Create(L"M_Death", texture, Vector2(0.0f, 0.0f), Vector2(23.0f, 23.0f), Vector2::Zero, 4, 0.3f);
		}
#pragma endregion
		
		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BulletKinMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
		

		Collider2D* mCollider = GetOwner()->AddComponent<Collider2D>();
		mCollider->SetName(L"billetKinCollider");
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.075f, 0.12f));

		monsAnimator->Play(L"M_Idle_Front", true);

		GetOwner()->AddComponent<Rigidbody>();

		term = 1;
		player = thisMonster->GetPlayer(); // 플레이어 
		mS = monsterState::mIdle;
	}

	void Bullet_Kin::Update()
	{
		GenericAnimator.Update(Time::DeltaTime());

		switch (mS)
		{
		case monsterState::Spawn:
			Spawn();
			break;
		case monsterState::mIdle:
			Idle();
			break;
		case monsterState::chase:
			chase();
			break;
		case monsterState::Hit:
			Hit();
			break;
		case monsterState::Move:
			Move();
			break;
		case monsterState::Attack:
			Attack();
			break;
		case monsterState::Death:
			Death();
			break;
		default:
			break;
		}


	}

	void Bullet_Kin::FixedUpdate()
	{
	}

	void Bullet_Kin::Render()
	{
	}

	void Bullet_Kin::OnCollisionEnter(Collider2D* oppo)
	{
		
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Weapone)
		{
			monsterHp -= 1;
			if(monsterHp == 0)
			{
				mS = monsterState::Death;
			}
			else 
			{
				mS = monsterState::Hit;
			}
		}

		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall) 
		{
			
		}
	}

	void Bullet_Kin::OnCollision(Collider2D* oppo)
	{

	}

	void Bullet_Kin::OnCollisionExit(Collider2D* oppo)
	{

	}

	void Bullet_Kin::OnTriggerEnter(Collider2D* oppo)
	{

	}

	void Bullet_Kin::OnTrigger(Collider2D* oppo)
	{

	}

	void Bullet_Kin::OnTriggerExit(Collider2D* oppo)
	{


	}
	void Bullet_Kin::Spawn()
	{


	}

	void Bullet_Kin::Idle()
	{

		if (thisMosterCollider->GetComponent<chasePlayerSCR>()->isFindPlayer() == true)
		{
			mS = monsterState::chase;
		}
		else //false
		{
			mS = monsterState::Move;
		}

	}

	void Bullet_Kin::chase()
	{

		Vector3 monsterPosition = mTr->GetPosition();
		Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

		float distanceToPlayer = CalculateDistance(monsterPosition, playerPosition);

		if (distanceToPlayer > 3.0f)//3거리 밖일때
		{
			Vector3 direction = Normalize(playerPosition - monsterPosition);
			float moveDistance = 0.1f * Time::DeltaTime();

			// Interpolate the movement gradually
			Vector3 newPosition = monsterPosition + direction * moveDistance;
			mTr->SetPosition(newPosition);
		}
		else //3거리 안에 들어옴
		{
			mS = monsterState::Attack;
		}


	}

	void Bullet_Kin::Hit()
	{
		if (HitAcc == true)
		{
			HitAcc = false;
			monsAnimator->Play(L"M_Hit", false);
		}

		monsAnimator->GetCompleteEvent(L"M_Hit") = std::bind(&Bullet_Kin::endHitAnimation, this);
	}

	void Bullet_Kin::Move()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<int> dist(1, 8);
		

		int dir = dist(gen);
		if (term == 1) 
		{
			term *= -1;
		}
		else if (term == -1) 
		{
			term *= -1;
			dir = 9;
		}

		GenericMoveAnimator(dir);
	}

	void Bullet_Kin::Attack()
	{


	}

	void Bullet_Kin::Death()
	{
		monsAnimator->Play(L"M_Death", false);

	}

	void Bullet_Kin::GetP2Mangle()
	{
		Vector3 playerPos = thisMonster->GetPlayer()->GetComponent<Transform>()->GetPosition();

		Vector3 MonsterPos = GetOwner()->GetCenterPos();

		playerPos += MonsterPos;//마우스 위치가 화면에 고정되어 있으므로 캐릭터가 이동한 위치 만큼 더해줌
		float aaa = atan2(playerPos.y - MonsterPos.y, playerPos.x - MonsterPos.x);
		P2Mangle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360각

	}

	void Bullet_Kin::endHitAnimation()
	{

		HitAcc = true;
		monsAnimator->Play(L"M_Idle_Front", true);
		mS = monsterState::mIdle;
		
	}

	void Bullet_Kin::GenericMoveAnimator(int dire)
	{
		mS = monsterState::Attack;
		dir = Vector3::Zero;
		switch (dire)
		{
		case 1:
			dir = Vector3::Up; // North
			monsAnimator->Play(L"M_Walk_Back", true);
			break;
		case 2:
			dir = Vector3::Down; // South
			monsAnimator->Play(L"M_Walk_Front", true);
			break;
		case 3:
			dir = Vector3::Right; // East
			monsAnimator->Play(L"M_Walk_left", true);
			GetOwner()->SetLeft();
			break;
		case 4:
			dir = Vector3::Left; // West
			monsAnimator->Play(L"M_Walk_left", true);
			GetOwner()->SetRight();
			break;
		case 5:
			dir = Vector3::Up + Vector3::Right; // NE
			monsAnimator->Play(L"M_Walk_Back", true);
			break;
		case 6:
			dir = Vector3::Up + Vector3::Left; // NW
			monsAnimator->Play(L"M_Walk_Back", true);
			break;
		case 7:
			dir = Vector3::Down + Vector3::Right; // SE
			monsAnimator->Play(L"M_Walk_Front", true);
			break;
		case 8:
			dir = Vector3::Down + Vector3::Left; // SW
			monsAnimator->Play(L"M_Walk_Front", true);
			break;
		case 9:
			monsAnimator->Play(L"M_Idle_Front", true);
			break;
		default:
			return; // Invalid direction
		}
		dir *= 1;

		// Set animation parameters
		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 0.5f;
		param.DurationTime = 2.f;
		param.DurationFunc = [this](float InCurValue) {
			Vector3 pos = mTr->GetPosition();
			pos += dir * InCurValue * Time::DeltaTime();
			mTr->SetPosition(pos);
			
		};
		param.CompleteFunc = [this](float InCurValue) {
			mS = monsterState::mIdle;
		};
		
		GenericAnimator.Start(param);

	
	
	}

	



}
