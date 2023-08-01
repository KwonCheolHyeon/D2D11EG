#include "BossHpUIScr.h"
#include "BossHpUIObj.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "EventScr.h"
namespace ch
{
	BossHpUIScr::BossHpUIScr()
		: ani(nullptr)
		, eventObj(nullptr)
		, boss(nullptr)
		, maxHp(100)
		, hp(50)
		, timer(0)
	{
	}
	BossHpUIScr::~BossHpUIScr()
	{
	}
	void BossHpUIScr::Initalize()
	{
		ani = GetOwner()->AddComponent<Animator>();

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossHpBar", L"enterthe/UI/BossHp/HpBar.png");
			ani->Create(L"Boss_HpBar", texture, Vector2(0.0f, 0.0f), Vector2(200.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BossHPMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMaterial(mateiral);
		sprite->SetMesh(mesh);

		maxHp = 100;
		hp = 100;
		timer = 100;
		//ani->Play(L"Boss_HpBar");
	}
	void BossHpUIScr::Update()
	{

		timer -= Time::DeltaTime() * 5;

		hp = timer;

		if (timer <= 0)
		{
			timer = 100;
		}
	}
	void BossHpUIScr::FixedUpdate()
	{

	}
	void BossHpUIScr::Render()
	{
		renderer::BossHpCB bosshpcb = {};
		float bosssss = hp / maxHp;
		bosshpcb.bossHpCB = bosssss;
		bosshpcb.bossHpCB1 = 0;
		bosshpcb.bossHpCB2 = 0;
		bosshpcb.bossHpCB3 = 0;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::BossHp];
		cb->SetData(&bosshpcb);
		cb->Bind(eShaderStage::ALL);

	}
}