#include "Bullet_Kin.h"
#include "chGameObject.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chCollider2D.h"
#include "chRigidbody.h"
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
	}

	void Bullet_Kin::Update()
	{
		monsAnimator->GetCompleteEvent(L"M_Hit") = std::bind(&Bullet_Kin::endHitAnimation, this);
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
			monsAnimator->Play(L"M_Hit", false);
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

	void Bullet_Kin::endHitAnimation()
	{
		monsAnimator->Play(L"M_Idle_Front", true);
	}

}