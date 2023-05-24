#include "chBoss.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
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
		mBoss = GetOwner();
		mBossAni = GetOwner()->AddComponent<Animator>();
		mBtr = GetOwner()->GetComponent<Transform>();
		mBcol = GetOwner()->AddComponent<Collider2D>();

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

	#pragma region 애니
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleFront", L"enterthe/character/weap/Idle/WIdleFront.png");
			mBossAni->Create(L"P_O_Idle_Front", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleFront", L"enterthe/character/weap/Idle/WIdleFront.png");
			mBossAni->Create(L"P_O_Idle_Front", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}

	#pragma endregion

	}
	void Boss::Update()
	{
	}
	void Boss::FixedUpdate()
	{
	}
	void Boss::Render()
	{
	}
	void Boss::OnCollisionEnter(Collider2D* oppo)
	{
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
}