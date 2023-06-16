#include "CubeScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
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
		
	}

	void CubeScr::Attack()
	{

	}
	
	void CubeScr::Death()
	{

	}
	void CubeScr::BulletMake()
	{
		Vector3 a = mTr->GetPosition();

		
	}
}